cmake_minimum_required(VERSION 3.10)

project(wimal-build)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/wimal-cmake")

# Suppress warnings of policies
set(CMAKE_POLICY_DEFAULT_CMP0042 NEW CACHE STRING CMAKE_POLICY_DEFAULT_CMP0042)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/CMakePolicy.cmake)

# Enable PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(MeChecks)
me_compile_options(-pipe)

# Add zlib
add_subdirectory(zlib)

# Enable zlib
set(LLVM_ENABLE_ZLIB FORCE_ON CACHE BOOL LLVM_ENABLE_ZLIB)
set(HAVE_LIBZ_Z 1 CACHE INTERNAL HAVE_LIBZ_Z)
set(HAVE_ZLIB_H 1 CACHE INTERNAL HAVE_ZLIB_H)
get_target_property(ZLIB_INCLUDE_DIRECTORIES zlibstatic INCLUDE_DIRECTORIES)
include_directories(${ZLIB_INCLUDE_DIRECTORIES})
link_directories("${CMAKE_CURRENT_BINARY_DIR}/zlib")
set(ZLIB_LIBNAME ${CMAKE_STATIC_LIBRARY_PREFIX}z${CMAKE_STATIC_LIBRARY_SUFFIX})
set(ZLIB_LIBRARY "${CMAKE_CURRENT_BINARY_DIR}/zlib/${ZLIB_LIBNAME}")
set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIRECTORIES})
set(ZLIB_FOUND ON CACHE BOOL ZLIB_FOUND)
set(HAVE_ZLIB ON CACHE BOOL HAVE_ZLIB)

# Disable zstd
set(LLVM_ENABLE_ZSTD OFF CACHE BOOL LLVM_ENABLE_ZSTD)

# Add libxml2
add_subdirectory(libxml2)

# Disable libxml2 for llvm
set(LLVM_ENABLE_LIBXML2 OFF CACHE BOOL LLVM_ENABLE_LIBXML2)

# Add jsoncpp
set(JSONCPP_WITH_TESTS OFF CACHE BOOL JSONCPP_WITH_TESTS)
set(
  JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL
                                             JSONCPP_WITH_POST_BUILD_UNITTEST
)
set(JSONCPP_WITH_WARNING_AS_ERROR OFF CACHE BOOL JSONCPP_WITH_WARNING_AS_ERROR)
set(
  JSONCPP_WITH_PKGCONFIG_SUPPORT OFF CACHE BOOL JSONCPP_WITH_PKGCONFIG_SUPPORT
)
set(JSONCPP_WITH_CMAKE_PACKAGE OFF CACHE BOOL JSONCPP_WITH_CMAKE_PACKAGE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL BUILD_SHARED_LIBS)
add_subdirectory(jsoncpp)

# Add libuv
add_subdirectory(libuv)

# Add apple-codesign
add_subdirectory(apple-codesign)

# Disable terminfo
set(LLVM_ENABLE_TERMINFO OFF CACHE BOOL LLVM_ENABLE_TERMINFO)

# Disable assertions
set(LLVM_ENABLE_ASSERTIONS OFF CACHE BOOL LLVM_ENABLE_ASSERTIONS)

# Enable exceptions and RTTI
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
set(
  LLVM_TARGETS_TO_BUILD X86 AArch64 ARM WebAssembly #
  CACHE STRING LLVM_TARGETS_TO_BUILD
)

# Enable tools
set(LLVM_BUILD_TOOLS ON CACHE BOOL LLVM_BUILD_TOOLS)
set(
  LLVM_TOOLCHAIN_TOOLS
  llvm-ar
  llvm-as
  llvm-lib
  llvm-libtool-darwin
  llvm-nm
  llvm-objcopy
  llvm-objdump
  llvm-ranlib
  llvm-readelf
  llvm-readobj
  llvm-size
  llvm-strings
  llvm-strip
  llvm-symbolizer
  CACHE STRING LLVM_TOOLCHAIN_TOOLS
)

# Include external projects
set(
  LLVM_EXTERNAL_PROJECTS wimal libcxx clang lld #
  CACHE STRING LLVM_EXTERNAL_PROJECTS
)

# Enable wimal
set(
  LLVM_EXTERNAL_WIMAL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/wimal"
  CACHE STRING LLVM_EXTERNAL_WIMAL_SOURCE_DIR
)

# Enable libcxx
set(
  LLVM_EXTERNAL_LIBCXX_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libcxx"
  CACHE STRING LLVM_EXTERNAL_LIBCXX_SOURCE_DIR
)

# Disable libcxx tests
set(LIBCXX_INCLUDE_TESTS OFF CACHE BOOL LIBCXX_INCLUDE_TESTS)
set(LIBCXXABI_INCLUDE_TESTS OFF CACHE BOOL LIBCXXABI_INCLUDE_TESTS)

# Disable libcxx benchmarks
set(LIBCXX_INCLUDE_BENCHMARKS OFF CACHE BOOL LIBCXX_INCLUDE_BENCHMARKS)

# Disable libcxx docs
set(LIBCXX_INCLUDE_DOCS OFF CACHE BOOL LIBCXX_INCLUDE_DOCS)

# Disable installing libcxx library
set(LIBCXX_INSTALL_LIBRARY OFF CACHE BOOL LIBCXX_INSTALL_LIBRARY)

# Enable clang
set(LLVM_TOOL_CLANG_BUILD ON CACHE BOOL LLVM_TOOL_CLANG_BUILD)
set(
  LLVM_EXTERNAL_CLANG_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/clang"
  CACHE STRING LLVM_EXTERNAL_CLANG_SOURCE_DIR
)
# Disable clang dylib
set(CLANG_LINK_CLANG_DYLIB OFF CACHE BOOL CLANG_LINK_CLANG_DYLIB)

# Enable lld
set(LLVM_TOOL_LLD_BUILD ON CACHE BOOL LLVM_TOOL_LLD_BUILD)
set(
  LLVM_EXTERNAL_LLD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lld"
  CACHE STRING LLVM_EXTERNAL_LLD_SOURCE_DIR
)

# Skip unnecessary components
set(CLANG_INCLUDE_TESTS OFF CACHE BOOL CLANG_INCLUDE_TESTS)
set(CLANG_INCLUDE_DOCS OFF CACHE BOOL CLANG_INCLUDE_DOCS)

# Skip unnecessary builds
set(CLANG_BUILD_EXAMPLES OFF CACHE BOOL CLANG_BUILD_EXAMPLES)

# Disable Z3 resolver
set(LLVM_ENABLE_Z3_SOLVER OFF CACHE BOOL LLVM_ENABLE_Z3_SOLVER)

# Disable linker color diagnostics
set(
  LINKER_SUPPORTS_COLOR_DIAGNOSTICS OFF #
  CACHE BOOL LINKER_SUPPORTS_COLOR_DIAGNOSTICS
)

# Add LLVM
add_subdirectory(llvm)

# Fix dependencies
add_dependencies(LLVMSupport zlibstatic)

# Add install targets for wimal
add_llvm_install_targets(install-wimal COMPONENT wimal DEPENDS wimal)

# Fix cross-compiling issues
execute_process(
  COMMAND
    cmake -E create_symlink "${CMAKE_BINARY_DIR}/llvm/bin"
    "${CMAKE_BINARY_DIR}/bin"
)

set(CMAKE_CXX_STANDARD 17)

set(BYN_ENABLE_ASSERTIONS OFF CACHE BOOL BYN_ENABLE_ASSERTIONS)
set(BUILD_EMSCRIPTEN_TOOLS_ONLY ON CACHE BOOL BUILD_EMSCRIPTEN_TOOLS_ONLY)
set(ENABLE_WERROR OFF CACHE BOOL ENABLE_WERROR)
set(BUILD_TESTS OFF CACHE BOOL BUILD_TESTS FORCE)

file(MAKE_DIRECTORY binaryen/test/lit)
file(WRITE binaryen/test/lit/CMakeLists.txt "")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/llvm/bin)
set(
  CMAKE_INSTALL_DEFAULT_COMPONENT_NAME binaryen
  CACHE STRING CMAKE_INSTALL_DEFAULT_COMPONENT_NAME FORCE
)
add_subdirectory(binaryen)

add_llvm_install_targets(
  install-binaryen
  COMPONENT
  binaryen
  DEPENDS
  wasm-as
  wasm-ctor-eval
  wasm-dis
  wasm-emscripten-finalize
  wasm-metadce
  wasm-opt
  wasm-split
  wasm2js
)

# Add all install targets
add_custom_target(
  installation
  DEPENDS
    install-LLVM-stripped
    install-LLVMgold-stripped
    install-LTO-stripped
    install-binaryen-stripped
    install-clang-resource-headers-stripped
    install-clang-stripped
    install-cxx-headers-stripped
    install-dsymutil-stripped
    install-lld-stripped
    install-llvm-ar-stripped
    install-llvm-ifs-stripped
    install-llvm-install-name-tool-stripped
    install-llvm-libtool-darwin
    install-llvm-lipo-stripped
    install-llvm-nm-stripped
    install-llvm-objcopy-stripped
    install-llvm-objdump-stripped
    install-llvm-otool-stripped
    install-llvm-ranlib-stripped
    install-llvm-rc-stripped
    install-llvm-readelf-stripped
    install-llvm-strip-stripped
    install-llvm-symbolizer-stripped
    install-wimal-stripped
)
