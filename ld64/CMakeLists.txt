cmake_minimum_required(VERSION 3.0)

project(ld64)

file(GLOB_RECURSE LD64_SRCS src/ld/*.c src/ld/*.cpp)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    add_definitions(-D__BIG_ENDIAN__=1)
else()
    add_definitions(-D__LITTLE_ENDIAN__=1)
endif()

include(CcChecks)
cc_check_compile_flag(-Wno-cast-qual)
cc_check_compile_flag(-Wno-covered-switch-default)
cc_check_compile_flag(-Wno-date-time)
cc_check_compile_flag(-Wno-delete-non-virtual-dtor)
cc_check_compile_flag(-Wno-format)
cc_check_compile_flag(-Wno-format-pedantic)
cc_check_compile_flag(-Wno-gnu-include-next)
cc_check_compile_flag(-Wno-ignored-qualifiers)
cc_check_compile_flag(-Wno-implicit-fallthrough)
cc_check_compile_flag(-Wno-import-preprocessor-directive-pedantic)
cc_check_compile_flag(-Wno-non-virtual-dtor)
cc_check_compile_flag(-Wno-parentheses-equality)
cc_check_compile_flag(-Wno-pointer-arith)
cc_check_compile_flag(-Wno-unused-value)
cc_check_compile_flag(-Wno-vla-extension)
cc_check_compile_flag(-Wno-zero-length-array)
cc_check_compile_flag(-fblocks)

include_directories(
    port
    src/abstraction
    src/ld/parsers
    src/ld
    $<TARGET_PROPERTY:tapi,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:uuid,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:objc2,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:xar,INCLUDE_DIRECTORIES>
)

option(LD64_LTO_STATIC "Link LTO statically." ON)

if(LD64_LTO_STATIC)
    foreach(target ${LLVM_TARGETS_TO_BUILD})
        list(
            APPEND LD64_EXTRA_DEPENDS
            LLVM${target}Desc
            LLVM${target}CodeGen
            LLVM${target}AsmParser
            LLVM${target}Disassembler
        )
    endforeach()
    aux_source_directory(${LLVM_MAIN_SRC_DIR}/tools/lto LD64_EXTRA_SRCS)
else()
    set(LD64_EXTRA_DEPENDS LTO)
endif()

add_llvm_executable(
    ld64
    ${LD64_SRCS} ${LD64_EXTRA_SRCS} port/port.cpp
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
set_property(
    SOURCE src/ld/ld.cpp
    PROPERTY COMPILE_DEFINITIONS log2=ld64_log2
)
target_link_libraries(
    ld64 PRIVATE
    LLVMTarget
    LLVMLTO
    LLVMSupport
    LLVMBinaryFormat
    LLVMObject
    clangBasic
    tapi
    objc2
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
