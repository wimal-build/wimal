function(me_install_toolchain)
    set(CACHE_DIR "${CMAKE_CURRENT_LIST_DIR}/.cache")
    # Remove cache directory if exists.
    if(EXISTS "${CACHE_DIR}")
        message(STATUS "Removing ${CACHE_DIR}")
        file(REMOVE_RECURSE "${CACHE_DIR}")
    endif()
    # Create cache directory.
    message(STATUS "Creating ${CACHE_DIR}")
    file(MAKE_DIRECTORY "${CACHE_DIR}")
    # Fetch latest release.
    set(RELEASE_URL https://github.com/wimal-build/wimal/releases)
    message(STATUS "Fetching ${RELEASE_URL}/latest")
    file(
        DOWNLOAD
        "${RELEASE_URL}/latest"
        "${CACHE_DIR}/releases"
    )
    file(READ "${CACHE_DIR}/releases" releases)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(system linux)
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(system macos)
    endif()
    # Parse the latest version and filenames.
    if(releases MATCHES "/download/([^/]+)/(wimal-${system}[^\"]*.tar.xz)")
        set(wimal-version ${CMAKE_MATCH_1})
        set(wimal-toolchain ${CMAKE_MATCH_2})
        message(STATUS "Latest version: ${wimal-version}")
        message(STATUS "Toolchain: ${wimal-toolchain}")
    else()
        message(FATAL_ERROR "No releases found")
        exit()
    endif()
    if(releases MATCHES "/download/${wimal-version}/(wimal-sysroot[^\"]*.tar.xz)")
        set(wimal-sysroot ${CMAKE_MATCH_1})
    else()
        message(FATAL_ERROR "No releases found")
    endif()
    message(STATUS "Sysroot: ${wimal-sysroot}")
    # Download the toolchain tarball.
    set(url "${RELEASE_URL}/download/${wimal-version}/${wimal-toolchain}")
    message(STATUS "Downloading: ${url}")
    file(DOWNLOAD "${url}" "${CACHE_DIR}/toolchain.tar.xz" SHOW_PROGRESS STATUS status)
    list(GET status 0 error)
    list(GET status 1 message)
    if(error)
        message(FATAL_ERROR "Failed to download, error=${error} message=${message}")
    endif()
    # Download the sysroot tarball.
    set(url "${RELEASE_URL}/download/${wimal-version}/${wimal-sysroot}")
    message(STATUS "Downloading: ${url}")
    file(DOWNLOAD "${url}" "${CACHE_DIR}/sysroot.tar.xz" SHOW_PROGRESS STATUS status)
    list(GET status 0 error)
    list(GET status 1 message)
    if(error)
        message(FATAL_ERROR "Failed to download, error=${error} message=${message}")
    endif()
    # Clean old wimal installation.
    set(WIMAL_DIR "${CMAKE_CURRENT_LIST_DIR}/wimal")
    if(EXISTS "${WIMAL_DIR}")
        message(STATUS "Removing ${WIMAL_DIR}")
        file(REMOVE_RECURSE "${WIMAL_DIR}")
    endif()
    # Extract toolchain.
    message(STATUS "Extracting ${CACHE_DIR}/toolchain.tar.xz")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar Jxf "${CACHE_DIR}/toolchain.tar.xz"
        WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
        RESULT_VARIABLE error
    )
    if(error)
        message(FATAL_ERROR "Failed to extract ${CACHE_DIR}/toolchain.tar.xz")
    endif()
    # Extract toolchain.
    message(STATUS "Extracting ${CACHE_DIR}/sysroot.tar.xz")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar Jxf "${CACHE_DIR}/sysroot.tar.xz"
        WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/wimal"
        RESULT_VARIABLE error
    )
    if(error)
        message(FATAL_ERROR "Failed to extract ${CACHE_DIR}/toolchain.tar.xz")
    endif()
    # Cleanup cache directory.
    file(REMOVE_RECURSE "${CACHE_DIR}")
    # Install wimal.
    message(STATUS "Installing wimal")
    execute_process(
        COMMAND "${CMAKE_CURRENT_LIST_DIR}/wimal/bin/wimal" install
        RESULT_VARIABLE error
    )
    if(error)
        message(FATAL_ERROR "Failed to install wimal")
    endif()
endfunction(me_install_toolchain)

if(NOT WIMAL_HOME)
    set(WIMAL_HOME $ENV{WIMAL_HOME})
endif()

if(NOT WIMAL_HOME)
    set(WIMAL_HOME "${CMAKE_CURRENT_LIST_DIR}/wimal")
endif()

if(NOT EXISTS "${WIMAL_HOME}/bin/wimal")
    if(EXISTS "/wimal/bin/wimal")
        set(WIMAL_HOME "/wimal")
    else(DEFINED ENV{WIMAL_HOME})
        message(STATUS "wimal not found, installing")
        me_install_toolchain()
    endif()
endif()

if(NOT EXISTS "${WIMAL_HOME}/bin/wimal")
    message(FATAL_ERROR "wimal not found in ${WIMAL_HOME}/bin/wimal")
endif()

set(CMAKE_SYSROOT ${CMAKE_CURRENT_LIST_DIR}/output/sysroot/x64-linux)

set(CMAKE_SYSTEM_NAME Linux CACHE STRING CMAKE_SYSTEM_NAME)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER_TARGET x86_64-linux-gnu)
set(CMAKE_CXX_COMPILER_TARGET x86_64-linux-gnu)

set(CMAKE_C_COMPILER ${WIMAL_HOME}/bin/clang CACHE PATH CMAKE_C_COMPILER)
set(CMAKE_CXX_COMPILER ${WIMAL_HOME}/bin/clang++ CACHE PATH CMAKE_CXX_COMPILER)

set(CMAKE_C_FLAGS "-fPIC -pipe" CACHE STRING CMAKE_C_FLAGS)
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG" CACHE STRING CMAKE_C_FLAGS_RELEASE)
set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=lld" CACHE STRING CMAKE_EXE_LINKER_FLAGS)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_BUILD_WITH_INSTALL_RPATH ON CACHE BOOL CMAKE_BUILD_WITH_INSTALL_RPATH)

# Suppress warnings
set(CMAKE_POLICY_DEFAULT_CMP0068 NEW CACHE STRING CMAKE_POLICY_DEFAULT_CMP0068)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW CACHE STRING CMAKE_POLICY_DEFAULT_CMP0069)
