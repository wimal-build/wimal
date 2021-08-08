project(wimal)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(
    wimal
    action.cpp
    cc.cpp
    context.cpp
    export.cpp
    export.cpp
    install.cpp
    invoke.cpp
    main.cpp
    filesystem.cpp
)
install(TARGETS wimal DESTINATION bin COMPONENT wimal)
