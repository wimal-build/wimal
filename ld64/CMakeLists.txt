cmake_minimum_required(VERSION 3.10)

project(ld64)

file(GLOB_RECURSE LD64_SRCS src/ld/*.c src/ld/*.cpp)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
  add_definitions(-D__BIG_ENDIAN__=1)
else()
  add_definitions(-D__LITTLE_ENDIAN__=1)
endif()

include(MeChecks)
me_compile_options(
  -Wno-cast-qual
  -Wno-covered-switch-default
  -Wno-date-time
  -Wno-delete-non-virtual-dtor
  -Wno-deprecated-declarations
  -Wno-format
  -Wno-format-pedantic
  -Wno-gnu-include-next
  -Wno-ignored-qualifiers
  -Wno-implicit-fallthrough
  -Wno-import-preprocessor-directive-pedantic
  -Wno-missing-field-initializers
  -Wno-non-virtual-dtor
  -Wno-parentheses-equality
  -Wno-pointer-arith
  -Wno-unused-value
  -Wno-vla-extension
  -Wno-zero-length-array
  -fblocks
)

include_directories(
  port
  src/abstraction
  src/ld/parsers
  src/ld
  $<TARGET_PROPERTY:tapi,INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:uuid,INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:xar,INCLUDE_DIRECTORIES>
)

option(LD64_FORCE_16KB_PAGES "Force 16kb pages." OFF)

if(LD64_FORCE_16KB_PAGES)
  add_definitions(-DLD_PAGE_SIZE=0x4000)
else()
  add_definitions(-DLD_PAGE_SIZE=0x1000)
endif()

if(LLVM_LINK_LLVM_DYLIB)
  set(LD64_LLVM_LIBS LLVM)
else()
  set(LD64_LLVM_LIBS LLVMTarget LLVMLTO LLVMSupport LLVMBinaryFormat LLVMObject)
endif()

add_llvm_executable(
  ld64
  ${LD64_SRCS}
  port/port.cpp
  port/runtime.c
  DEPENDS
  LLVMLTO
  LLVMSupport
  LLVMBinaryFormat
  LLVMObject
  clangBasic
  uuid
  tapi
  ${LD64_EXTRA_DEPENDS}
)
set_target_properties(ld64 PROPERTIES OUTPUT_NAME apple-ld)
target_link_libraries(
  ld64
  PRIVATE
    ${LD64_LLVM_LIBS}
    clangBasic
    tapi
    uuid
    dl
    xar
    xml2
    ssl
    crypto
    zlibstatic
    ${LD64_EXTRA_DEPENDS}
)

install(TARGETS ld64 DESTINATION bin COMPONENT ld64)
