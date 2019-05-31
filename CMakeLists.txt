cmake_minimum_required(VERSION 3.0)

# Skip unnecessary components
set(LLVM_INCLUDE_BENCHMARKS OFF CACHE BOOL LLVM_INCLUDE_BENCHMARKS)
set(LLVM_INCLUDE_DOCS OFF CACHE BOOL LLVM_INCLUDE_DOCS)
set(LLVM_INCLUDE_RUNTIMES OFF CACHE BOOL LLVM_INCLUDE_RUNTIMES)
set(LLVM_INCLUDE_TESTS OFF CACHE BOOL LLVM_INCLUDE_TESTS)
set(LLVM_INCLUDE_UTILS OFF CACHE BOOL LLVM_INCLUDE_UTILS)

# Skip unnecessary builds
set(LLVM_BUILD_EXAMPLES OFF CACHE BOOL LLVM_BUILD_EXAMPLES)
set(LLVM_INSTALL_TOOLCHAIN_ONLY ON CACHE BOOL LLVM_INSTALL_TOOLCHAIN_ONLY)

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
    wimal clang
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
set(LLVM_TOOL_CLANG_BUILD ON CACHE BOOL "")
set(
    LLVM_EXTERNAL_CLANG_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/clang"
    CACHE STRING
    LLVM_EXTERNAL_CLANG_SOURCE_DIR
)

# Skip unnecessary components
set(CLANG_INCLUDE_TESTS OFF CACHE BOOL "")
set(CLANG_INCLUDE_DOCS OFF CACHE BOOL "")

# Skip unnecessary builds
set(CLANG_BUILD_EXAMPLES OFF CACHE BOOL "")

# Add LLVM
add_subdirectory(llvm)

# Add install targets for wimal
add_llvm_install_targets(install-wimal COMPONENT wimal DEPENDS wimal)

# Add all install targets
add_custom_target(
    installation DEPENDS

    install-wimal-stripped

    install-llvm-ar-stripped
    install-llvm-nm-stripped
    install-llvm-objcopy-stripped
    install-llvm-objdump-stripped
    install-llvm-ranlib-stripped
    install-llvm-readelf-stripped
    install-llvm-strip-stripped

    install-clang-stripped
)
