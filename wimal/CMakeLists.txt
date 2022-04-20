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
    filesystem.cpp
    install.cpp
    invoke.cpp
    main.cpp
)
target_link_libraries(wimal jsoncpp_static uv_a pthread)
install(TARGETS wimal DESTINATION bin COMPONENT wimal)
