project(wimal)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(
    wimal
    action.cpp
    autobuild.cpp
    cc.cpp
    cmakebuild.cpp
    context.cpp
    export.cpp
    export.cpp
    install.cpp
    invoke.cpp
    main.cpp
    shell.cpp

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
install(TARGETS wimal DESTINATION bin COMPONENT wimal)
