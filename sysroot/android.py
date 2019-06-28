import os
import subprocess
import sys
from distutils import dir_util, file_util


def copy_directory(src, dst):
    print('    - [' + src + '] -> [' + dst + ']')
    if not os.path.isdir(src):
        exit(1)
    dir_util.copy_tree(src, dst, preserve_symlinks=1)


def copy_file(src, dst):
    print('    - [' + src + '] -> [' + dst + ']')
    if os.path.isfile(src):
        file_util.copy_file(src, dst)


api = int(os.getenv('ANDROID_PLATFORM', '21'))

ndk = os.getenv('ANDROID_NDK', 'android-ndk')
if not os.path.isdir(ndk):
    ndk = os.path.join(os.getenv('ANDROID_HOME', 'android-sdk'), 'ndk-bundle')
if not os.path.isdir(ndk):
    ndk = os.path.join(os.getenv('ANDROID_SDK_ROOT', 'android-sdk'), 'ndk-bundle')

print('ndk: ' + ndk)

system = sys.platform

if system.startswith('linux'):
    system = 'linux'
if system == 'win32' or system == 'cygwin':
    system = 'windows'

print('system: ' + system)

sysroot = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'sysroot')
sysroot = os.getenv('WIMAL_SYSROOT', sysroot)

targets = ('arm', 'a64', 'x86', 'x64')

architectures = {
    'arm': 'arm',
    'a64': 'arm64',
    'x86': 'x86',
    'x64': 'x86_64'
}
prefixes = {
    'arm': 'arm-linux-androideabi-4.9',
    'a64': 'aarch64-linux-android-4.9',
    'x86': 'x86-4.9',
    'x64': 'x86_64-4.9'
}
triplets = {
    'arm': 'arm-linux-androideabi',
    'a64': 'aarch64-linux-android',
    'x86': 'i686-linux-android',
    'x64': 'x86_64-linux-android'
}
abis = {
    'arm': 'armeabi-v7a',
    'a64': 'arm64-v8a',
    'x86': 'x86',
    'x64': 'x86_64'
}

for target in targets:
    level = api

    if target == 'a64' or target == 'x64':
        if level < 21:
            level = 21

    print('+ [' + target + '-android]:')

    root = os.path.join(sysroot, target + '-android')
    usr = os.path.join(root, 'usr')

    platform = os.path.join(ndk, 'platforms', 'android-' + str(level))

    arch = architectures[target]
    copy_directory(os.path.join(platform, 'arch-' + arch, 'usr', 'lib'), os.path.join(usr, 'lib'))

    if target == 'x64':
        copy_directory(
            os.path.join(platform, 'arch-' + arch, 'usr', 'lib64'),
            os.path.join(usr, 'lib64')
        )

    copy_directory(os.path.join(ndk, 'sysroot', 'usr', 'include'), os.path.join(usr, 'include'))

    copy_directory(
        os.path.join(ndk, 'sources', 'android', 'support', 'include'),
        os.path.join(usr, 'local', 'include')
    )

    copy_file(os.path.join(ndk, 'source.properties'), root)

    copy_directory(
        os.path.join(ndk, 'sources', 'cxx-stl', 'llvm-libc++', 'include'),
        os.path.join(usr, 'include', 'c++', 'v1')
    )
    copy_directory(
        os.path.join(ndk, 'sources', 'cxx-stl', 'llvm-libc++abi', 'include'),
        os.path.join(usr, 'include', 'c++', 'v1')
    )

    prefix = prefixes[target]
    copy_directory(
        os.path.join(ndk, 'toolchains', prefix, 'prebuilt', system + '-x86_64', 'lib', 'gcc'),
        os.path.join(usr, 'lib', 'gcc')
    )

    triplet = triplets[target]
    if target == 'a64' or target == 'x64':
        bits='64'
    else:
        bits=''
    copy_directory(
        os.path.join(ndk, 'toolchains', prefix, 'prebuilt', system + '-x86_64', triplet, 'lib' + bits),
        os.path.join(usr, 'lib')
    )

    abi = abis[target]

    copy_file(
        os.path.join(ndk, 'sources', 'cxx-stl', 'llvm-libc++', 'libs', abi, 'libc++abi.a'),
        os.path.join(usr, 'lib', 'libc++abi.a')
    )

    copy_file(
        os.path.join(ndk, 'sources', 'cxx-stl', 'llvm-libc++', 'libs', abi, 'libc++_shared.so'),
        os.path.join(usr, 'lib', 'libc++_shared.so')
    )

    copy_file(
        os.path.join(ndk, 'sources', 'cxx-stl', 'llvm-libc++', 'libs', abi, 'libunwind.a'),
        os.path.join(usr, 'lib', 'libunwind.a')
    )

    if level < 21:
        copy_file(
            os.path.join(
                ndk, 'sources', 'cxx-stl', 'llvm-libc++', 'libs', abi, 'libandroid_support.a'
            ),
            os.path.join(usr, 'lib', 'libandroid_support.a')
        )

    copy_file(
        os.path.join(
            ndk, 'sources', 'cxx-stl', 'llvm-libc++', 'libs', abi, 'libc++.so.' + str(level)
        ),
        os.path.join(usr, 'lib', 'libc++.so')
    )

    objcopy = os.path.join(ndk, 'toolchains', 'llvm', 'prebuilt', system + '-x86_64', 'bin', 'llvm-objcopy')
    if os.path.isfile(objcopy):
        subprocess.call([objcopy, '--strip-all', os.path.join(usr, 'lib', 'libc++_shared.so')])
