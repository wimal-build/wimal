import os
import requests
import shutil

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
OUTPUT_DIR = os.path.join(SCRIPT_DIR, "output")
SYSROOT_DIR = os.path.join(OUTPUT_DIR, "sysroot")

GITHUB_URL = "https://github.com"
EMSCRIPTEN_VERSION = "3.1.64"
EMSCRIPTEN_REPO = "emscripten-core/emscripten"
EMSCRIPTEN_TARBALL = "%s.tar.gz" % EMSCRIPTEN_VERSION

DOWNLOAD_URL = "%s/%s/archive/refs/tags/%s" % (
    GITHUB_URL,
    EMSCRIPTEN_REPO,
    EMSCRIPTEN_TARBALL,
)


# Download and extract emscripten sdk to sysroot/emscripten
response = requests.get(DOWNLOAD_URL, stream=True)
os.makedirs(OUTPUT_DIR, exist_ok=True)
with open(os.path.join(OUTPUT_DIR, EMSCRIPTEN_TARBALL), "wb") as file:
    shutil.copyfileobj(response.raw, file)
    shutil.unpack_archive(
        os.path.join(OUTPUT_DIR, EMSCRIPTEN_TARBALL),
        os.path.join(OUTPUT_DIR, "emscripten"),
    )
    shutil.rmtree(os.path.join(SYSROOT_DIR, "emscripten"), ignore_errors=True)
    shutil.copytree(
        os.path.join(OUTPUT_DIR, "emscripten", "emscripten-%s" % EMSCRIPTEN_VERSION),
        os.path.join(SYSROOT_DIR, "emscripten"),
    )
    with open(os.path.join(SYSROOT_DIR, "emscripten", ".emscripten"), "w") as file:
        file.write(
            """
import os
import sys

BINARYEN_ROOT = os.path.join(
    os.path.abspath(os.path.dirname(sys.argv[0])), os.pardir, os.pardir
)
LLVM_ROOT = os.path.join(BINARYEN_ROOT, "bin")
NODE_JS = "node"
"""
        )
