cmake_minimum_required(VERSION 3.0)

project(tapi)

include(CcChecks)

cc_check_compile_flag(-Wno-gnu-include-next)
cc_check_compile_flag(-Wno-nested-anon-types)
cc_check_compile_flag(-Wno-delete-non-virtual-dtor)

aux_source_directory(lib/Core TAPI_CORE_SOURCES)
aux_source_directory(tools/libtapi LIBTAPI_SOURCES)

llvm_add_library(tapi ${TAPI_CORE_SOURCES} ${LIBTAPI_SOURCES} DEPENDS LLVMSupport clangBasic)

target_include_directories(
    tapi BEFORE PUBLIC
    port
    include
    $<TARGET_PROPERTY:clangBasic,INCLUDE_DIRECTORIES>
)
set_property(
    SOURCE lib/Core/FileManager.cpp
    PROPERTY COMPILE_DEFINITIONS TAPI_CORE_FILEMANAGER_CPP=1
)
set_property(
    SOURCE lib/Core/Path.cpp
    PROPERTY COMPILE_DEFINITIONS TAPI_CORE_PATH_CPP=1
)
set_property(
    SOURCE tools/libtapi/libtapi.cpp
    PROPERTY COMPILE_DEFINITIONS
    RemoveFileOnSignal=TapiRemoveFileOnSignal;
    DontRemoveFileOnSignal=TapiDontRemoveFileOnSignal
    AddSignalHandler=TapiAddSignalHandler
)
