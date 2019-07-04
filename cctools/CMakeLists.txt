cmake_minimum_required(VERSION 3.0)

project(cctools)

include(CcChecks)
cc_check_compile_flag(-Wno-macro-redefined)
cc_check_compile_flag(-Wno-incompatible-pointer-types)
cc_check_compile_flag(-Wno-int-conversion)

include_directories(port include)

add_executable(
    lipo

    port/port.c

    misc/lipo.c

    libstuff/allocate.c
    libstuff/arch.c
    libstuff/arch_usage.c
    libstuff/bytesex.c
    libstuff/errors.c
    libstuff/fatals.c
)
install(TARGETS lipo DESTINATION bin COMPONENT lipo)

add_executable(
    install_name_tool

    port/port.c

    misc/install_name_tool.c

    libstuff/allocate.c
    libstuff/arch.c
    libstuff/arch_usage.c
    libstuff/breakout.c
    libstuff/bytesex.c
    libstuff/checkout.c
    libstuff/crc32.c
    libstuff/errors.c
    libstuff/fatal_arch.c
    libstuff/fatals.c
    libstuff/get_arch_from_host.c
    libstuff/get_toc_byte_sex.c
    libstuff/ofile.c
    libstuff/ofile_error.c
    libstuff/print.c
    libstuff/rnd.c
    libstuff/set_arch_flag_name.c
    libstuff/swap_headers.c
    libstuff/writeout.c
)
install(TARGETS install_name_tool DESTINATION bin COMPONENT install_name_tool)
