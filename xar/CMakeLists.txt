cmake_minimum_required(VERSION 3.0)

project(xar)

# Set versions
set(MAJOR_VERSION 1)
set(MINOR_VERSION 8dev)
set(XAR_VERSION ${MAJOR_VERSION}.${MINOR_VERSION})

# Generate header
configure_file(
    xar/include/xar.h.in
    "${CMAKE_CURRENT_BINARY_DIR}/include/xar/xar.h"
    @ONLY
)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/include/config.h")

# Include directories
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories($<TARGET_PROPERTY:ssl,PUBLIC_INCLUDE_DIRECTORIES>)
include_directories($<TARGET_PROPERTY:crypto,PUBLIC_INCLUDE_DIRECTORIES>)
include_directories($<TARGET_PROPERTY:zlibstatic,INCLUDE_DIRECTORIES>)
include_directories($<TARGET_PROPERTY:zlibstatic,SOURCE_DIR>)
include_directories($<TARGET_PROPERTY:xml2,INCLUDE_DIRECTORIES>)

# Checks
include(CcChecks)
cc_check_headers(
    ext2fs/ext2_fs.h
    libutil.h
    sys/acl.h
    sys/extattr.h
    sys/param.h
    sys/statfs.h
    sys/xattr.h
)
cc_check_funcs(
    lgetxattr
    lsetxattr
    getxattr
    setxattr
    getattrlist
    setattrlist
    lchmod
    lchown
    chflags
    statvfs
    statfs
    strmode
    safe_dirname
)

if(NOT HAVE_SAFE_DIRNAME)
    add_definitions(-Dsafe_dirname=dirname)
endif()

cc_check_members(statfs f_fstypename sys/types.h sys/param.h sys/mount.h)
cc_check_members(statvfs f_fstypename sys/statvfs.h)
cc_check_members(stat st_flags sys/stat.h)

if(NOT HAVE_STRUCT_STAT_ST_FLAGS)
    add_definitions("-DXAR_FLAG_FORK=\"flags\"")
endif()

cc_check_sizeof(uid_t)
if(SIZEOF_UID_T EQUAL 4)
    add_definitions(-DUID_STRING=RId32)
    add_definitions("-DUID_CAST=(uint32_t)")
elseif(SIZEOF_UID_T EQUAL 8)
    add_definitions(-DUID_STRING=PRId64)
    add_definitions("-DUID_CAST=(uint64_t)")
else()
    message(FATAL_ERROR "can not detect the size of your system's uid_t type")
endif()

cc_check_sizeof(gid_t)
if(SIZEOF_GID_T EQUAL 4)
    add_definitions(-DGID_STRING=PRId32)
    add_definitions("-DGID_CAST=(uint32_t)")
elseif(SIZEOF_GID_T EQUAL 8)
    add_definitions(-DGID_STRING=PRId64)
    add_definitions("-DGID_CAST=(uint64_t)")
else()
    message(FATAL_ERROR "can not detect the size of your system's gid_t type")
endif()

cc_check_sizeof(ino_t)
if(SIZEOF_INO_T EQUAL 4)
    add_definitions(-DINO_STRING=PRId32)
    add_definitions(-DINO_HEXSTRING=PRIx32)
    add_definitions("-DINO_CAST=(uint32_t)")
elseif(SIZEOF_INO_T EQUAL 8)
    add_definitions(-DINO_STRING=PRId64)
    add_definitions(-DINO_HEXSTRING=PRIx64)
    add_definitions("-DINO_CAST=(uint64_t)")
else()
    message(FATAL_ERROR "can not detect the size of your system's ino_t type")
endif()

cc_check_sizeof(dev_t)
if(SIZEOF_DEV_T EQUAL 4)
    add_definitions(-DDEV_STRING=PRId32)
    add_definitions(-DDEV_HEXSTRING=PRIx32)
    add_definitions("-DDEV_CAST=(uint32_t)")
elseif(SIZEOF_DEV_T EQUAL 8)
    add_definitions(-DDEV_STRING=PRId64)
    add_definitions(-DDEV_HEXSTRING=PRIx64)
    add_definitions("-DDEV_CAST=(uint64_t)")
else()
    message(FATAL_ERROR "can not detect the size of your system's dev_t type")
endif()

cc_check_compile_flag(-Wno-format)
cc_check_compile_flag(-Wno-implicit-function-declaration)

add_definitions(-DHAVE_LIBPTHREAD=1)

# Sources
set(
    XAR_SOURCES
    xar/lib/hash.c
    xar/lib/fbsdattr.c
    xar/lib/ext2.c
    xar/lib/arcmod.c
    xar/lib/data.c
    xar/lib/io.c
    xar/lib/err.c
    xar/lib/script.c
    xar/lib/ea.c
    xar/lib/macho.c
    xar/lib/lzmaxar.c
    xar/lib/archive.c
    xar/lib/b64.c
    xar/lib/darwinattr.c
    xar/lib/linuxattr.c
    xar/lib/filetree.c
    xar/lib/bzxar.c
    xar/lib/signature.c
    xar/lib/stat.c
    xar/lib/subdoc.c
    xar/lib/util.c
    xar/lib/zxar.c
)

add_library(xar ${XAR_SOURCES})
target_link_libraries(xar xml2 ssl crypto zlibstatic)
target_include_directories(xar PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include/xar")
