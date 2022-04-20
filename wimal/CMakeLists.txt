project(wimal)

set(CMAKE_CXX_STANDARD 11)

get_target_property(JSONCPP_INCLUDE_DIRECTORIES jsoncpp_static INCLUDE_DIRECTORIES)
get_target_property(LIBUV_INCLUDE_DIRECTORIES uv_a INCLUDE_DIRECTORIES)
include_directories(
    .
    ${JSONCPP_INCLUDE_DIRECTORIES}
    ${LIBUV_INCLUDE_DIRECTORIES}
)

add_executable(
    wimal
    action.cpp
    bear.cpp
    cc.cpp
    context.cpp
    export.cpp
    export.cpp
    install.cpp
    invoke.cpp
    main.cpp

    boost/system/error_code.cpp

    boost/filesystem/codecvt_error_category.cpp
    boost/filesystem/operations.cpp
    boost/filesystem/path.cpp
    boost/filesystem/path_traits.cpp
    boost/filesystem/portability.cpp
    boost/filesystem/unique_path.cpp
    boost/filesystem/utf8_codecvt_facet.cpp
    boost/filesystem/windows_file_codecvt.cpp
)
target_link_libraries(wimal jsoncpp_static uv_a pthread)
install(TARGETS wimal DESTINATION bin COMPONENT wimal)
