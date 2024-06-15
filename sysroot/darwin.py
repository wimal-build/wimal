import os
import re
import subprocess
import requests
import shutil
import zipfile

sdk_versions = {
    'iPhoneOS': '11.0',
    'iPhoneSimulator': '11.0',
    'MacOSX': '10.14'
}

sdk_url_format = 'https://github.com/wimal-build/{0}.sdk/archive/refs/tags/{0}{1}.sdk.zip'
sdk_folder_name_format = '{0}.sdk-{0}{1}.sdk'


def copy_file(src, dst):
    print('    - [' + src + '] -> [' + dst + ']')
    if os.path.isfile(src):
        shutil.copy2(src, dst, follow_symlinks=False)


def copy_directory(src, dst):
    print('    - [' + src + '] -> [' + dst + ']')
    if not os.path.isdir(src):
        return
    if not os.path.isdir(dst):
        os.makedirs(dst, exist_ok=True)
    for item in os.listdir(src):
        src_item = os.path.join(src, item)
        dst_item = os.path.join(dst, item)
        if os.path.isdir(src_item):
            copy_directory(src_item, dst_item)
        else:
            copy_file(src_item, dst_item)


def retrieve_sdk(sdk, folder):
    if not os.path.isdir(folder):
        os.makedirs(folder, exist_ok=True)
    sdk_version = sdk_versions[sdk]
    url = sdk_url_format.format(sdk, sdk_version)
    sdk_zip = os.path.join(folder, sdk + '.zip')
    # Download the sdk zip
    if not os.path.isfile(sdk_zip):
        print('Downloading the ' + sdk + ' SDK...')
        response = requests.get(url, stream=True)
        with open(sdk_zip, 'wb') as file:
            shutil.copyfileobj(response.raw, file)
    # Extract the sdk zip
    print('Extracting the ' + sdk + ' SDK...')
    zipfile.ZipFile(sdk_zip).extractall(folder)


def copy_sdk(src, dst):
    copy_directory(src, dst)
    shutil.rmtree(os.path.join(dst, 'usr', 'share'), ignore_errors=True)


output = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'output')
sysroot = os.path.join(output, 'sysroot')
sysroot = os.getenv('WIMAL_SYSROOT', sysroot)

retrieve_sdk('iPhoneOS', os.path.join(output, 'a64-ios'))
retrieve_sdk('iPhoneSimulator', os.path.join(output, 'x64-ios'))
retrieve_sdk('MacOSX', os.path.join(output, 'x64-macos'))

copy_sdk(os.path.join(output, 'a64-ios', sdk_folder_name_format.format(
    'iPhoneOS', sdk_versions['iPhoneOS'])
), os.path.join(sysroot, 'a64-ios'))
copy_sdk(os.path.join(output, 'x64-ios', sdk_folder_name_format.format(
    'iPhoneSimulator', sdk_versions['iPhoneSimulator'])
), os.path.join(sysroot, 'x64-ios'))
copy_sdk(os.path.join(output, 'x64-macos', sdk_folder_name_format.format(
    'MacOSX', sdk_versions['MacOSX'])
), os.path.join(sysroot, 'x64-macos'))

os.symlink('a64-ios', os.path.join(sysroot, 'arm-ios'))
os.symlink('x64-ios', os.path.join(sysroot, 'x86-ios'))
os.symlink('x64-macos', os.path.join(sysroot, 'x86-macos'))
os.symlink('x64-macos', os.path.join(sysroot, 'a64-macos'))
