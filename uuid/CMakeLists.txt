cmake_minimum_required(VERSION 3.0)

project(uuid)

set(CMAKE_C_STANDARD 99)

include(MeChecks)
me_checks(
    SET

    HEADERS
    fcntl.h
    inttypes.h
    limits.h
    netinet/in.h
    stdlib.h
    string.h
    sys/file.h
    sys/ioctl.h
    sys/socket.h
    sys/time.h
    unistd.h

    FUNCS
    ftruncate
    gettimeofday
    memset
    socket
    strtoul
    usleep
    srandom
)

set(
    UUID_SOURCES
    clear.c
    compare.c
    copy.c
    gen_uuid.c
    isnull.c
    pack.c
    parse.c
    unpack.c
    unparse.c
    uuid_time.c
    randutils.c
)

configure_file(
    uuid.h
    "${CMAKE_CURRENT_BINARY_DIR}/include/uuid/uuid.h"
    COPYONLY
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_library(uuid ${UUID_SOURCES})
