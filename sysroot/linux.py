import os
import subprocess

from distutils import dir_util, file_util

current = os.path.dirname(os.path.realpath(__file__))
output = os.path.join(current, 'output')
sysroot = os.path.join(output, 'sysroot')
sysroot = os.getenv('WIMAL_SYSROOT', sysroot)
target = os.path.join(sysroot, 'x64-linux')

build = os.path.join(current, 'cmake-build-cxx')
os.makedirs(build, exist_ok=True)
subprocess.run((
    'cmake', '-E', 'chdir', build,
    'cmake', '../..', '-GNinja',
    '-DCMAKE_BUILD_TYPE=Release',
    '-DCMAKE_TOOLCHAIN_FILE=../CxxToolchain.cmake',
    '-DCMAKE_INSTALL_PREFIX=target',
))
subprocess.run((
    'cmake', '--build', build, '--target',
    'install-cxx-stripped',
    'install-cxxabi-stripped',
    'install-cxx-headers-stripped'
))

os.makedirs(os.path.join(target, 'usr', 'include'), exist_ok=True)
os.makedirs(os.path.join(target, 'usr', 'lib'), exist_ok=True)

dir_util.copy_tree(
    os.path.join(current, 'cmake-build-cxx', 'target', 'include'),
    os.path.join(target, 'usr', 'include')
)
file_util.copy_file(
    os.path.join(current, 'cmake-build-cxx', 'target', 'lib', 'libc++abi.a'),
    os.path.join(target, 'usr', 'lib', 'libc++abi.a'),
)
file_util.copy_file(
    os.path.join(current, 'cmake-build-cxx', 'target', 'lib', 'libc++.a'),
    os.path.join(target, 'usr', 'lib', 'libc++_static.a'),
)

file = open(os.path.join(target, 'usr', 'lib', 'libc++.so'), 'w')
file.write('INPUT(-lc++_static -lc++abi -lpthread)')
file.close()
