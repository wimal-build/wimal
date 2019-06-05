cmake_minimum_required(VERSION 3.0)

project(libobjc2)

enable_language(ASM)

include_directories(.)

set(CMAKE_C_STANDARD 99)

include(CcChecks)
cc_check_compile_flag(-fexceptions)
cc_check_compile_flag(-Wno-deprecated-objc-isa-usage)
cc_check_compile_flag(-Wno-incompatible-pointer-types-discards-qualifier)
cc_check_compile_flag(-Wno-objc-root-class)

add_definitions(
    -DGNUSTEP
    -D__OBJC_RUNTIME_INTERNAL__=1
    -D_XOPEN_SOURCE=700
    -D__BSD_VISIBLE=1
    -D_BSD_SOURCE=1
)
add_definitions(-DNO_SELECTOR_MISMATCH_WARNINGS)
add_definitions(-DTYPE_DEPENDENT_DISPATCH)

set(
    OBJC2_C_SOURCES
    abi_version.c
    alias_table.c
    block_to_imp.c
    caps.c
    category_loader.c
    class_table.c
    dtable.c
    eh_personality.c
    encoding2.c
    gc_none.c
    hash_table.c
    hooks.c
    ivar.c
    legacy_malloc.c
    loader.c
    protocol.c
    runtime.c
    sarray2.c
    selector_table.c
    sendmsg2.c
    statics_loader.c
    toydispatch.c
)
set(
    OBJC2_OBJC_SOURCES
    NSBlocks.m
    Protocol2.m
    arc.m
    associate.m
    blocks_runtime.m
    mutation.m
    properties.m
)
set(
    OBJC2_ASM_SOURCES
    block_trampolines.S
    objc_msgSend.S
)

set(OBJC2_SOURCES ${OBJC2_C_SOURCES} ${OBJC2_OBJC_SOURCES} ${OBJC2_ASM_SOURCES})

add_library(objc2 ${OBJC2_SOURCES})
