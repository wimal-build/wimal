import os
import requests
import shutil
import sys


def copy_file(src, dst):
    print("    - [" + src + "] -> [" + dst + "]")
    if os.path.isfile(src):
        shutil.copy2(src, dst, follow_symlinks=False)


def remove_file(file):
    if os.path.isfile(file):
        os.unlink(file)


def copy_directory(src, dst):
    print("    - [" + src + "] -> [" + dst + "]")
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


system = sys.platform

if system.startswith("linux"):
    system = "linux"
if system == "win32" or system == "cygwin":
    system = "windows"

print("system: " + system)

api = int(os.getenv("ANDROID_PLATFORM", "21"))

# Download the ndk and extract it to a temporary directory inside the current directory

# Download the ndk zip
ndk_zip = os.path.join(os.path.dirname(os.path.realpath(__file__)), "android-ndk.zip")

# https://github.com/android/ndk/wiki/Unsupported-Downloads
ndk_download_link = (
    "https://dl.google.com/android/repository/android-ndk-r21e-"
    + system
    + "-x86_64.zip"
)

if not os.path.isfile(ndk_zip):
    print("Downloading the Android NDK...")
    response = requests.get(ndk_download_link, stream=True)
    with open(ndk_zip, "wb") as file:
        shutil.copyfileobj(response.raw, file)
    del response

# Extract the ndk zip
ndk = os.path.join(os.path.dirname(os.path.realpath(__file__)), "output", "android-ndk")
if not os.path.isdir(ndk):
    print("Extracting the Android NDK...")
    shutil.unpack_archive(ndk_zip, ndk)

# Remove the ndk zip
# os.remove(ndk_zip)

# Set the ndk path
ndk = os.path.join(ndk, "android-ndk-r21e")

# ndk = os.getenv('ANDROID_NDK', 'android-ndk')
if not os.path.isdir(ndk):
    ndk = os.path.join(os.getenv("ANDROID_HOME", "android-sdk"), "ndk-bundle")
if not os.path.isdir(ndk):
    ndk = os.path.join(os.getenv("ANDROID_SDK_ROOT", "android-sdk"), "ndk-bundle")

print("ndk: " + ndk)

output = os.path.join(os.path.dirname(os.path.realpath(__file__)), "output")
sysroot = os.path.join(output, "sysroot")
sysroot = os.getenv("WIMAL_SYSROOT", sysroot)

targets = ("arm", "a64", "x86", "x64")

architectures = {"arm": "arm", "a64": "arm64", "x86": "x86", "x64": "x86_64"}
prefixes = {
    "arm": "arm-linux-androideabi-4.9",
    "a64": "aarch64-linux-android-4.9",
    "x86": "x86-4.9",
    "x64": "x86_64-4.9",
}
triplets = {
    "arm": "arm-linux-androideabi",
    "a64": "aarch64-linux-android",
    "x86": "i686-linux-android",
    "x64": "x86_64-linux-android",
}
abis = {"arm": "armeabi-v7a", "a64": "arm64-v8a", "x86": "x86", "x64": "x86_64"}

for target in targets:
    level = api

    print("+ [" + target + "-android]:")

    root = os.path.join(sysroot, target + "-android")
    usr = os.path.join(root, "usr")

    platform = os.path.join(ndk, "platforms", "android-" + str(level))

    arch = architectures[target]
    copy_directory(
        os.path.join(platform, "arch-" + arch, "usr", "lib"), os.path.join(usr, "lib")
    )

    if target == "x64":
        copy_directory(
            os.path.join(platform, "arch-" + arch, "usr", "lib64"),
            os.path.join(usr, "lib"),
        )

    copy_directory(
        os.path.join(ndk, "sysroot", "usr", "include"), os.path.join(usr, "include")
    )

    copy_directory(
        os.path.join(ndk, "sources", "android", "support", "include"),
        os.path.join(usr, "local", "include"),
    )

    copy_file(
        os.path.join(ndk, "source.properties"), os.path.join(root, "source.properties")
    )

    copy_directory(
        os.path.join(ndk, "sources", "cxx-stl", "llvm-libc++", "include"),
        os.path.join(usr, "include", "c++", "v1"),
    )
    copy_directory(
        os.path.join(ndk, "sources", "cxx-stl", "llvm-libc++abi", "include"),
        os.path.join(usr, "include", "c++", "v1"),
    )

    prefix = prefixes[target]
    copy_directory(
        os.path.join(
            ndk, "toolchains", prefix, "prebuilt", system + "-x86_64", "lib", "gcc"
        ),
        os.path.join(usr, "lib", "gcc"),
    )

    triplet = triplets[target]
    if target == "a64" or target == "x64":
        bits = "64"
    else:
        bits = ""
    copy_directory(
        os.path.join(
            ndk,
            "toolchains",
            prefix,
            "prebuilt",
            system + "-x86_64",
            triplet,
            "lib" + bits,
        ),
        os.path.join(usr, "lib"),
    )

    abi = abis[target]

    copy_file(
        os.path.join(
            ndk, "sources", "cxx-stl", "llvm-libc++", "libs", abi, "libc++abi.a"
        ),
        os.path.join(usr, "lib", "libc++abi.a"),
    )

    copy_file(
        os.path.join(
            ndk, "sources", "cxx-stl", "llvm-libc++", "libs", abi, "libc++_static.a"
        ),
        os.path.join(usr, "lib", "libc++_static.a"),
    )

    copy_file(
        os.path.join(
            ndk, "sources", "cxx-stl", "llvm-libc++", "libs", abi, "libunwind.a"
        ),
        os.path.join(usr, "lib", "libunwind.a"),
    )

    copy_file(
        os.path.join(
            ndk,
            "sources",
            "cxx-stl",
            "llvm-libc++",
            "libs",
            abi,
            "libc++.a." + str(level),
        ),
        os.path.join(usr, "lib", "libc++.a"),
    )

    copy_file(
        os.path.join(
            ndk,
            "sources",
            "cxx-stl",
            "llvm-libc++",
            "libs",
            abi,
            "libc++.a." + str(level),
        ),
        os.path.join(usr, "lib", "libc++.so"),
    )

    # Remove the unused libraries
    remove_file(os.path.join(usr, "lib", "libc.a"))
    remove_file(os.path.join(usr, "lib", "libm.a"))
    remove_file(os.path.join(usr, "lib", "libc++_shared.so"))

    # Create a dummy libpthread.a
    with open(os.path.join(usr, "lib", "libpthread.a"), "w") as file:
        file.write("INPUT()")
        file.close()
