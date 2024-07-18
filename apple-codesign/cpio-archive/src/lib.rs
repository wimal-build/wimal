// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

pub mod newc;
pub use newc::{NewcHeader, NewcReader};
pub mod odc;
pub use odc::{OdcBuilder, OdcHeader, OdcReader};

use {
    chrono::{DateTime, NaiveDateTime, Utc},
    std::{
        fmt::Debug,
        io::{Chain, Cursor, Read},
        path::PathBuf,
    },
};

#[derive(Debug, thiserror::Error)]
pub enum Error {
    #[error("I/O error: {0}")]
    Io(#[from] std::io::Error),

    #[error("bad magic value encountered")]
    BadMagic,

    #[error("value in header is not an ASCII string")]
    BadHeaderString,

    #[error("string value in header is not in hex: {0}")]
    BadHeaderHex(String),

    #[error("filename could not be decoded")]
    FilenameDecode,

    #[error("Numeric value too large to be encoded")]
    ValueTooLarge,

    #[error("Size mismatch between header length and provided data")]
    SizeMismatch,

    #[error("path is not a file: {0}")]
    NotAFile(PathBuf),
}

/// Result type for this crate.
pub type CpioResult<T> = Result<T, Error>;

/// Common behavior for a header/entry in a cpio archive.
pub trait CpioHeader: Debug {
    /// Device number.
    fn device(&self) -> u32;

    /// Inode number.
    fn inode(&self) -> u32;

    /// File mode.
    fn mode(&self) -> u32;

    /// User ID.
    fn uid(&self) -> u32;

    /// Group ID.
    fn gid(&self) -> u32;

    /// Number of links.
    fn nlink(&self) -> u32;

    /// Associated device number.
    fn rdev(&self) -> u32;

    /// Modified time as seconds since UNIX epoch.
    fn mtime(&self) -> u32;

    /// Modified time as a [DateTime].
    fn modified_time(&self) -> DateTime<Utc> {
        DateTime::<Utc>::from_naive_utc_and_offset(
            NaiveDateTime::from_timestamp_opt(self.mtime() as _, 0)
                .expect("out of range timestamp"),
            Utc,
        )
    }

    /// File size in bytes.
    fn file_size(&self) -> u64;

    /// File name.
    fn name(&self) -> &str;
}

/// Common interface for cpio archive reading.
///
/// In addition to the members of this trait, instances implement [Iterator] over
/// the members of the archive and [Read] to obtain a reader for the current
/// archive member.
///
/// Instances behave like a cursor over members of the archive. The cursor is
/// advanced by calling [Self::read_next]. When the cursor is advanced, the
/// [Read] trait will read data for this and only this archive member. The reader
/// will hit EOF at the end of the current archive member.
pub trait CpioReader<T>: Iterator<Item = CpioResult<Box<dyn CpioHeader>>> + Read
where
    T: Read + Sized,
{
    /// Construct a new instance from a reader.
    fn new(reader: T) -> Self
    where
        Self: Sized;

    /// Read the next header from the archive.
    ///
    /// `Some` on another file entry. `None` if at end of file.
    ///
    /// The special `TRAILER!!!` entry is not emitted.
    fn read_next(&mut self) -> CpioResult<Option<Box<dyn CpioHeader>>>;

    /// Finish reading the current member.
    ///
    /// This will advance the reader to the next archive member if the
    /// current member hasn't been fully consumed.
    fn finish(&mut self) -> CpioResult<()>;
}

pub type ChainedCpioReader<T> = dyn CpioReader<Chain<Cursor<Vec<u8>>, T>>;

/// Construct a new cpio archive reader.
///
/// This will sniff the type of the cpio archive and return an appropriate
/// instance.
pub fn reader<T: 'static + Read + Sized>(mut reader: T) -> CpioResult<Box<ChainedCpioReader<T>>> {
    let mut magic = vec![0u8; 6];
    reader.read_exact(&mut magic)?;

    match magic.as_ref() {
        crate::newc::MAGIC => Ok(Box::new(NewcReader::new(Cursor::new(magic).chain(reader)))),
        crate::odc::MAGIC => Ok(Box::new(OdcReader::new(Cursor::new(magic).chain(reader)))),
        _ => Err(Error::BadMagic),
    }
}
