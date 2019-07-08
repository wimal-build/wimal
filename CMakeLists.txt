cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Suppress warnings of policy CMP0042
set(CMAKE_POLICY_DEFAULT_CMP0042 NEW CACHE STRING CMAKE_POLICY_DEFAULT_CMP0042)

# Enable PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CcChecks)
cc_check_compile_flag(-pipe)

# Add zlib
add_subdirectory(zlib)

# Enable zlib
set(LLVM_ENABLE_ZLIB ON CACHE BOOL LLVM_ENABLE_ZLIB)
set(HAVE_LIBZ_Z 1 CACHE INTERNAL HAVE_LIBZ_Z)
set(HAVE_ZLIB_H 1 CACHE INTERNAL HAVE_ZLIB_H)
include_directories($<TARGET_PROPERTY:zlibstatic,INCLUDE_DIRECTORIES>)
link_directories("${CMAKE_CURRENT_BINARY_DIR}/zlib")

# Add libxml2
add_subdirectory(libxml2)

# Disable libxml2 for llvm
set(LLVM_ENABLE_LIBXML2 OFF CACHE BOOL LLVM_ENABLE_LIBXML2)

# Add libressl
add_subdirectory(libressl)

# Add xar
add_subdirectory(xar)

# Add uuid
add_subdirectory(uuid)

# Necessary for ld64
set(LLVM_ENABLE_EH ON CACHE BOOL LLVM_ENABLE_EH)
set(LLVM_ENABLE_RTTI ON CACHE BOOL LLVM_ENABLE_RTTI)

# Build libLLVM.so
set(LLVM_LINK_LLVM_DYLIB ON CACHE BOOL LLVM_LINK_LLVM_DYLIB)

# Enable LLVMgold
set(LLVM_ENABLE_PIC ON CACHE BOOL LLVM_ENABLE_PIC)
set(LLVM_BINUTILS_INCDIR "." CACHE PATH LLVM_BINUTILS_INCDIR)

# Skip unnecessary components
set(LLVM_INCLUDE_BENCHMARKS OFF CACHE BOOL LLVM_INCLUDE_BENCHMARKS)
set(LLVM_INCLUDE_DOCS OFF CACHE BOOL LLVM_INCLUDE_DOCS)
set(LLVM_INCLUDE_RUNTIMES OFF CACHE BOOL LLVM_INCLUDE_RUNTIMES)
set(LLVM_INCLUDE_TESTS OFF CACHE BOOL LLVM_INCLUDE_TESTS)
set(LLVM_INCLUDE_UTILS OFF CACHE BOOL LLVM_INCLUDE_UTILS)

# Skip unnecessary builds
set(LLVM_BUILD_EXAMPLES OFF CACHE BOOL LLVM_BUILD_EXAMPLES)

# Disable bindings
set(LLVM_ENABLE_BINDINGS OFF CACHE BOOL LLVM_ENABLE_BINDINGS)

# Disable unnecessary targets
set(LLVM_TARGETS_TO_BUILD X86 AArch64 ARM CACHE STRING LLVM_TARGETS_TO_BUILD)

# Enable tools
set(LLVM_BUILD_TOOLS ON CACHE BOOL LLVM_BUILD_TOOLS)
set(
    LLVM_TOOLCHAIN_TOOLS
    llvm-ar
    llvm-nm
    llvm-objcopy
    llvm-objdump
    llvm-ranlib
    llvm-readelf
    llvm-readobj
    llvm-strip
    CACHE STRING
    LLVM_TOOLCHAIN_TOOLS
)

# Include external projects
set(LLVM_EXTERNAL_PROJECTS
    wimal
    clang
    lld
    tapi
    ld64
    cctools
    CACHE STRING
    LLVM_EXTERNAL_PROJECTS
)

# Enable wimal
set(
    LLVM_EXTERNAL_WIMAL_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/wimal"
    CACHE STRING
    LLVM_EXTERNAL_WIMAL_SOURCE_DIR
)

# Enable clang
set(LLVM_TOOL_CLANG_BUILD ON CACHE BOOL LLVM_TOOL_CLANG_BUILD)
set(
    LLVM_EXTERNAL_CLANG_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/clang"
    CACHE STRING
    LLVM_EXTERNAL_CLANG_SOURCE_DIR
)

# Enable lld
set(LLVM_TOOL_LLD_BUILD ON CACHE BOOL LLVM_TOOL_LLD_BUILD)
set(
    LLVM_EXTERNAL_LLD_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/lld"
    CACHE STRING
    LLVM_EXTERNAL_LLD_SOURCE_DIR
)

# Enable tapi
set(
    LLVM_EXTERNAL_TAPI_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/tapi"
    CACHE STRING
    LLVM_EXTERNAL_TAPI_SOURCE_DIR
)

# Enable ld64
set(
    LLVM_EXTERNAL_LD64_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/ld64"
    CACHE STRING
    LLVM_EXTERNAL_LD64_SOURCE_DIR
)

# Enable cctools
set(
    LLVM_EXTERNAL_CCTOOLS_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/cctools"
    CACHE STRING
    LLVM_EXTERNAL_CCTOOLS_SOURCE_DIR
)

# Skip unnecessary components
set(CLANG_INCLUDE_TESTS OFF CACHE BOOL CLANG_INCLUDE_TESTS)
set(CLANG_INCLUDE_DOCS OFF CACHE BOOL CLANG_INCLUDE_DOCS)

# Skip unnecessary builds
set(CLANG_BUILD_EXAMPLES OFF CACHE BOOL CLANG_BUILD_EXAMPLES)

# Add LLVM
add_subdirectory(llvm)

# Fix dependencies
add_dependencies(LLVMSupport zlibstatic)

# Add install targets for wimal
add_llvm_install_targets(install-wimal COMPONENT wimal DEPENDS wimal)

# Add install targets for ld64
add_llvm_install_targets(install-ld64 COMPONENT ld64 DEPENDS ld64)

# Add install targets for cctools
add_llvm_install_targets(install-cctools COMPONENT cctools DEPENDS cctools)

# Add all install targets
add_custom_target(
    installation DEPENDS

    install-cctools-stripped

    install-LLVM-stripped

    install-LLVMgold-stripped

    install-ld64-stripped

    install-wimal-stripped

    install-llvm-ar-stripped
    install-llvm-nm-stripped
    install-llvm-objcopy-stripped
    install-llvm-objdump-stripped
    install-llvm-ranlib-stripped
    install-llvm-readelf-stripped
    install-llvm-strip-stripped
    install-llvm-rc-stripped
    install-llvm-symbolizer-stripped
    install-dsymutil-stripped

    install-clang-stripped
    install-clang-headers-stripped

    install-lld-stripped
)
