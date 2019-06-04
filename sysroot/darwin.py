import os
import subprocess
from distutils import dir_util


def copy_sdk(sdk, dst):
    src = subprocess.check_output(['xcrun', '--sdk', sdk, '--show-sdk-path'])
    src = src.decode('UTF-8').strip()
    print('    - [' + src + '] -> [' + dst + ']')
    if not os.path.isdir(src):
        exit(1)
    dir_util.copy_tree(src, dst, preserve_symlinks=1)
    dir_util.remove_tree(os.path.join(dst, 'usr', 'share'))


sysroot = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'sysroot')
sysroot = os.getenv('WIMAL_SYSROOT', sysroot)

copy_sdk('iphoneos', os.path.join(sysroot, 'a64-ios'))
copy_sdk('iphonesimulator', os.path.join(sysroot, 'x64-ios'))
copy_sdk('macosx', os.path.join(sysroot, 'x64-macos'))

os.symlink('a64-ios', os.path.join(sysroot, 'arm-ios'))
os.symlink('x64-ios', os.path.join(sysroot, 'x86-ios'))
os.symlink('x64-macos', os.path.join(sysroot, 'x86-macos'))
