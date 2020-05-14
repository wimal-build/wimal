import os
import re
import subprocess
from distutils import dir_util, file_util


def copy_sdk(sdk, dst):
    src = subprocess.check_output(['xcrun', '--sdk', sdk, '--show-sdk-path'])
    src = src.decode('UTF-8').strip()
    print('    - [' + src + '] -> [' + dst + ']')
    if not os.path.isdir(src):
        exit(1)
    dir_util.copy_tree(src, dst, preserve_symlinks=1)
    dir_util.remove_tree(os.path.join(dst, 'usr', 'share'))

    xcode = subprocess.check_output(['xcode-select', '-p'])
    xcode = xcode.decode('UTF-8').strip()
    toolchain = os.path.join(xcode, 'Toolchains', 'XcodeDefault.xctoolchain')
    src = os.path.join(toolchain, 'usr', 'include', 'c++')
    dst = os.path.join(dst, 'usr', 'include', 'c++')
    print('    - [' + src + '] -> [' + dst + ']')
    dir_util.copy_tree(src, dst)


def copy_clang_rt(dst):
    clang = subprocess.check_output(['xcrun', '-f', 'clang'])
    clang = clang.decode('UTF-8').strip()
    search_dirs = subprocess.check_output([clang, '--print-search-dirs'])
    match = re.search('libraries: =(.*)$', search_dirs.decode('UTF-8').strip())
    libraries = match.group(1)
    src = os.path.join(libraries, 'lib', 'darwin', 'libclang_rt.ios.a')
    dst = os.path.join(dst, 'darwin')
    dir_util.mkpath(dst, mode=0o755)
    print('    - [' + src + '] -> [' + dst + ']')
    file_util.copy_file(src, dst)
    src = os.path.join(libraries, 'lib', 'darwin', 'libclang_rt.osx.a')
    print('    - [' + src + '] -> [' + dst + ']')
    file_util.copy_file(src, dst)


output = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'output')
sysroot = os.path.join(output, 'sysroot')
sysroot = os.getenv('WIMAL_SYSROOT', sysroot)

copy_sdk('iphoneos', os.path.join(sysroot, 'a64-ios'))
copy_sdk('iphonesimulator', os.path.join(sysroot, 'x64-ios'))
copy_sdk('macosx', os.path.join(sysroot, 'x64-macos'))

os.symlink('a64-ios', os.path.join(sysroot, 'arm-ios'))
os.symlink('x64-ios', os.path.join(sysroot, 'x86-ios'))
os.symlink('x64-macos', os.path.join(sysroot, 'x86-macos'))

libclang = os.path.join(output, 'lib', 'clang', '10.0.0', 'lib')
libclang = os.getenv('WIMAL_LIBCLANG', libclang)

copy_clang_rt(libclang)
