import bz2
import gzip
import io
import os
import re
import requests
import sys
import tarfile
from distutils import dir_util, file_util

if sys.version_info > (3, 0):
    # noinspection PyUnresolvedReferences
    import lzma
else:
    # noinspection PyUnresolvedReferences,PyPackageRequirements
    from backports import lzma


# noinspection PyClassHasNoInit,PyShadowingBuiltins
class AR:
    @staticmethod
    def parse(file):
        # noinspection PyClassHasNoInit
        class Header:
            GLOBAL_MAGIC = b"!<arch>\n"
            HEADER_LEN = 60
            BSD = 1
            GNU = 2
            GNU_TABLE = 3
            GNU_SYMBOLS = 4
            NORMAL = 5

        if file.read(len(Header.GLOBAL_MAGIC)) != Header.GLOBAL_MAGIC:
            raise IOError("file is missing the global header")
        files = {}
        gnu_table = None
        offset = len(Header.GLOBAL_MAGIC)

        while True:
            data = file.read(Header.HEADER_LEN)
            if len(data) == 0:
                return files
            if len(data) < Header.HEADER_LEN:
                raise IOError("file header too short")

            import struct
            name, timestamp, uid, gid, mode, size, magic = struct.unpack(
                "16s 12s 6s 6s 8s 10s 2s", data
            )
            if magic != b"\x60\x0a":
                raise IOError("file header magic doesn't match")

            try:
                size = int(size)
            except ValueError as error:
                raise IOError("cannot convert the `size` field to integer", error)

            if name.startswith(b"#1/"):
                header = Header.BSD
            elif name.startswith(b"//"):
                header = Header.GNU_TABLE
            elif name.strip() == b"/":
                header = Header.GNU_SYMBOLS
            elif name.startswith(b"/"):
                header = Header.GNU
            else:
                header = Header.NORMAL

            name = name.rstrip()
            if len(name) > 1:
                name = name.rstrip(b'/')

            if header == Header.BSD:
                name = file.read(int(name[3:]))
            elif header == Header.GNU:
                name = gnu_table[int(name[1:])]
            elif header == Header.GNU_TABLE:
                gnu_table = {}
                position = 0
                text = file.read(size)
                for filename in text.split(b"\n"):
                    gnu_table[position] = filename[:-1]
                    position += len(filename) + 1
                continue
            files[name] = file.read(size)
            offset += Header.HEADER_LEN + size
            if offset % 2 != 0:
                offset += 1
                file.read(1)


# noinspection PyShadowingBuiltins
class Apt:
    def __init__(self, repo, dist, arch):
        self.repo = repo
        self.dist = dist
        self.arch = arch
        self.packages = {}

    def __update__(self, section):
        url = '%s/dists/%s/%s/binary-%s/Packages.gz' % (self.repo, self.dist, section, self.arch)
        print('updating: ' + url)
        response = requests.get(url)
        content = gzip.GzipFile(fileobj=io.BytesIO(response.content)).read().decode('UTF-8')

        parts = re.split('\n\n+', content, flags=re.MULTILINE)
        for part in parts:
            match = re.search('^Package: ([^\n]+)', part, re.MULTILINE)
            if not match:
                continue
            package = match.group(1)
            match = re.search('^Filename: ([^\n]+)', part, re.MULTILINE)
            if not match:
                continue
            filename = match.group(1)
            self.packages[package] = filename

    def __install__(self, package, path):
        url = '%s/%s' % (self.repo, self.packages[package])
        print('installing: ' + url)
        file = io.BytesIO(requests.get(url).content)
        files = AR.parse(file)
        data = None
        for file in files.keys():
            if file.startswith(b'data.tar.'):
                data = files[file]
                break
        if data is None:
            return
        print('extracting: ' + file.decode('UTF-8'))
        if file.endswith(b'.xz') or file.endswith(b'.lzma'):
            data = lzma.decompress(data)
        elif file.endswith(b'.gz'):
            data = gzip.GzipFile(fileobj=io.BytesIO(data)).read()
        elif file.endswith(b'.bz2'):
            data = bz2.decompress(data)
        tar = tarfile.open(fileobj=io.BytesIO(data))
        tar.extractall(path=path)
        tar.close()

    @staticmethod
    def repair(path):
        for root, dirs, files in os.walk(path):
            for file in files:
                src = os.path.join(root, file)
                if os.path.islink(src):
                    dst = os.readlink(src)
                    if os.path.isabs(dst):
                        dst = os.path.normpath(dst)
                        parts = []
                        while True:
                            basename = os.path.basename(dst)
                            if not basename:
                                parts.reverse()
                                break
                            parts.append(os.path.basename(dst))
                            dst = os.path.dirname(dst)

                        os.unlink(src)
                        os.symlink(os.path.relpath(os.path.join(path, *parts), root), src)

    def update(self, sections):
        for section in sections:
            self.__update__(section)

    def install(self, packages, path):
        for package in packages:
            self.__install__(package, path)


output = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'sysroot')
output = os.getenv('WIMAL_SYSROOT', output)
output = os.path.join(output, 'x64-linux')

apt = Apt('http://apt.llvm.org/trusty', 'llvm-toolchain-trusty-8', 'amd64')
apt.update(['main'])
apt.install((
    'libc++-8-dev',
    'libc++1-8',
    'libc++abi-8-dev',
    'libc++abi1-8'
), output)
dir_util.copy_tree(
    os.path.join(output, 'usr', 'lib', 'llvm-8', 'include'),
    os.path.join(output, 'usr', 'include')
)
file_util.copy_file(
    os.path.join(output, 'usr', 'lib', 'llvm-8', 'lib', 'libc++abi.a'),
    os.path.join(output, 'usr', 'lib', 'libc++abi.a'),
)
file_util.copy_file(
    os.path.join(output, 'usr', 'lib', 'llvm-8', 'lib', 'libc++.a'),
    os.path.join(output, 'usr', 'lib', 'libc++_static.a'),
)
dir_util.remove_tree(os.path.join(output, 'usr', 'lib', 'llvm-8'))

file = open(os.path.join(output, 'usr', 'lib', 'libc++.so'), 'w')
file.write('INPUT(-lc++_static -lc++abi -lpthread)')
file.close()

apt = Apt('http://archive.ubuntu.com/ubuntu', 'trusty', 'amd64')
apt.update(('main', 'universe'))
apt.install((
    'linux-libc-dev',
    'libc6',
    'libc6-dev',
    'libgcc1',
    'libgcc-4.8-dev',
    'libstdc++6',
    'libstdc++-4.8-dev',

    'libgomp1',
    'libitm1',
    'libquadmath0',
    'libtsan0',
    'libatomic1',
    'libasan0'
), output)

apt.repair(output)
