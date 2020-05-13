#ifndef TAPI_CLANG_BASIC_FILEMANAGER_H_
#define TAPI_CLANG_BASIC_FILEMANAGER_H_

#include_next "clang/Basic/FileManager.h"

#include "clang/Basic/FileSystemStatCache.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/VirtualFileSystem.h"

#include "tapi/Defines.h"

TAPI_NAMESPACE_INTERNAL_BEGIN

namespace clang {

namespace vfs {
    using namespace ::clang::vfs;
}

using FileSystemOptions = ::clang::FileSystemOptions;
using FileSystemStatCache = ::clang::FileSystemStatCache;
using FileEntry = ::clang::FileEntry;
using DirectoryEntry = ::clang::DirectoryEntry;

class FileManager {
public:
    FileManager(const clang::FileSystemOptions &fileSystemOpts,
                llvm::IntrusiveRefCntPtr<clang::vfs::FileSystem> fs)
            : _fm(fileSystemOpts, std::move(fs)) {
    }

    const FileEntry * getFile(StringRef Filename, bool OpenFile = false, bool CacheFailure = true) {
        return _fm.getFile(Filename, OpenFile, CacheFailure).get();
    }

    const DirectoryEntry * getDirectory(StringRef DirName, bool CacheFailure = true) {
        return _fm.getDirectory(DirName, CacheFailure).get();
    }

    llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> getBufferForFile(const FileEntry *Entry, bool isVolatile = false) {
        return _fm.getBufferForFile(Entry, isVolatile);
    }

    std::error_code getNoncachedStatValue(StringRef Path, llvm::vfs::Status &Result) {
        return _fm.getNoncachedStatValue(Path, Result);
    }

    void setStatCache(std::unique_ptr<FileSystemStatCache> statCache) {
        return _fm.setStatCache(std::move(statCache));
    }

    void clearStatCache() {
        return _fm.clearStatCache();
    }

    llvm::vfs::FileSystem *getVirtualFileSystem() const {
        return &_fm.getVirtualFileSystem();
    }

private:
    ::clang::FileManager _fm;
};

} // namespace clang

TAPI_NAMESPACE_INTERNAL_END

#endif // TAPI_CLANG_BASIC_FILEMANAGER_H_
