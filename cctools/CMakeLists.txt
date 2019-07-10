cmake_minimum_required(VERSION 3.0)

project(cctools)

include(CcChecks)
cc_check_compile_flag(-Wno-covered-switch-default)
cc_check_compile_flag(-Wno-format)
cc_check_compile_flag(-Wno-gnu-include-next)
cc_check_compile_flag(-Wno-implicit-function-declaration)
cc_check_compile_flag(-Wno-import-preprocessor-directive-pedantic)
cc_check_compile_flag(-Wno-incompatible-pointer-types)
cc_check_compile_flag(-Wno-int-conversion)
cc_check_compile_flag(-Wno-macro-redefined)
cc_check_compile_flag(-Wno-missing-field-initializers)
cc_check_compile_flag(-Wno-pedantic)
cc_check_compile_flag(-Wno-sign-compare)
cc_check_compile_flag(-Wno-unused-variable)
cc_check_compile_flag(-Wno-visibility)

# Endian check
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    add_definitions(-D__BIG_ENDIAN__=1)
else()
    add_definitions(-D__LITTLE_ENDIAN__=1)
endif()

include_directories(port include)

# libstuff
add_library(
    stuff

    libstuff/allocate.c
    libstuff/arch.c
    libstuff/arch_usage.c
    libstuff/best_arch.c
    libstuff/breakout.c
    libstuff/bytesex.c
    libstuff/checkout.c
    libstuff/coff_bytesex.c
    libstuff/crc32.c
    libstuff/errors.c
    libstuff/execute.c
    libstuff/fatal_arch.c
    libstuff/fatals.c
    libstuff/get_arch_from_host.c
    libstuff/get_toc_byte_sex.c
    libstuff/guess_short_name.c
    libstuff/hppa.c
    libstuff/llvm.c
    libstuff/ofile.c
    libstuff/ofile_error.c
    libstuff/print.c
    libstuff/reloc.c
    libstuff/rnd.c
    libstuff/set_arch_flag_name.c
    libstuff/swap_headers.c
    libstuff/symbol_list.c
    libstuff/unix_standard_mode.c
    libstuff/version_number.c
    libstuff/writeout.c

    # Use cpp for symbol __cxa_demangle
    port/port.cpp
)

set_property(
    SOURCE libstuff/execute.c
    PROPERTY COMPILE_DEFINITIONS
    # Make the prefix contains the prefix in executable names.
    # i.e. `/usr/bin/apple-ar` is prefixed with `/usr/bin/apple-`.
    # Remove the default implementation here, reimplement in port.cpp
    add_execute_list_with_prefix=no_add_execute_list_with_prefix
    cmd_with_prefix=no_cmd_with_prefix
)

# ar
add_executable(
    apple-ar
    ar/append.c
    ar/ar.c
    ar/archive.c
    ar/contents.c
    ar/delete.c
    ar/extract.c
    ar/misc.c
    ar/move.c
    ar/print.c
    ar/replace.c
)
# Fix duplicated symbol issue.
target_compile_definitions(apple-ar PRIVATE error=xerror print=xprint)
target_link_libraries(apple-ar stuff)

# lipo
add_executable(apple-lipo misc/lipo.c)
target_link_libraries(apple-lipo stuff)

# strip
add_executable(apple-strip misc/strip.c)
target_link_libraries(apple-strip stuff)

# nm
add_executable(apple-nm misc/nm.c)
target_link_libraries(apple-nm stuff)

# ranlib
add_executable(apple-ranlib misc/libtool.c)
# Set `cmd_flags.ranlib` to TRUE when the executable ends with `ranlib`.
target_compile_definitions(apple-ranlib PRIVATE strncmp=cctools_strncmp)
target_link_libraries(apple-ranlib stuff)

# install_name_tool
add_executable(apple-install_name_tool misc/install_name_tool.c)
target_link_libraries(apple-install_name_tool stuff)

# otool
add_executable(
    apple-otool
    otool/arm64_disasm.c
    otool/arm_disasm.c
    otool/coff_print.c
    otool/dyld_bind_info.c
    otool/hppa_disasm.c
    otool/i386_disasm.c
    otool/i860_disasm.c
    otool/m68k_disasm.c
    otool/m88k_disasm.c
    otool/main.c
    otool/notify.c
    otool/ofile_print.c
    otool/ppc_disasm.c
    otool/print_bitcode.c
    otool/print_objc.c
    otool/print_objc2_32bit.c
    otool/print_objc2_64bit.c
    otool/sparc_disasm.c
)
target_include_directories(apple-otool BEFORE PRIVATE port)
target_compile_definitions(apple-otool PRIVATE STATIC_LLVM __DYNAMIC__)
target_link_libraries(apple-otool stuff LLVMMCDisassembler)

# install
add_custom_target(
    cctools DEPENDS
    apple-ar
    apple-lipo
    apple-strip
    apple-nm
    apple-ranlib
    apple-install_name_tool
    apple-otool
)
install(
    TARGETS
    apple-ar
    apple-lipo
    apple-strip
    apple-nm
    apple-ranlib
    apple-install_name_tool
    apple-otool
    DESTINATION bin
    COMPONENT cctools
)
