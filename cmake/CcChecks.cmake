cmake_minimum_required(VERSION 3.0)

function(cc_check_name name var)
    string(TOUPPER ${name} name)
    string(REGEX REPLACE [^A-Z|0-9] _ name ${name})
    set(${var} ${name} PARENT_SCOPE)
endfunction(cc_check_name)

function(cc_check_compile_flag _flag)
    include(CheckCCompilerFlag)
    cc_check_name(HAVE${_flag} variable)
    set(flag ${_flag} -Wno-error=unknown-warning)
    check_c_compiler_flag(${_flag} ${variable})
    if(ARGN)
        set(${ARGV1} ${${variable}} PARENT_SCOPE)
    else()
        set(${variable} ${${variable}} PARENT_SCOPE)
        if(${variable})
            add_compile_options(${_flag})
        endif()
    endif()
endfunction(cc_check_compile_flag)

function(cc_check_headers)
    include(CheckIncludeFile)
    foreach(header ${ARGV})
        cc_check_name("HAVE_${header}" variable)
        check_include_file(${header} ${variable})
        if(${variable})
            set(${variable} ${${variable}} PARENT_SCOPE)
            add_definitions(-D${variable})
        endif()
    endforeach()
endfunction(cc_check_headers)

function(cc_check_funcs)
    include(CheckCSourceCompiles)
    foreach(fun ${ARGV})
        cc_check_name("HAVE_${fun}" variable)
        check_c_source_compiles(
            "
                void ${fun}();
                int main() {
                    return (int) (&${fun});
                }
            "
            ${variable}
        )
        if(${variable})
            set(${variable} ${${variable}} PARENT_SCOPE)
            add_definitions(-D${variable})
        endif()
    endforeach()
endfunction(cc_check_funcs)

function(cc_check_members type field)
    include(CheckCSourceCompiles)
    cc_check_name("HAVE_struct_${type}_${field}" variable)
    set(includes)
    foreach(include ${ARGN})
        set(includes "${includes}\n#include <${include}>")
    endforeach()
    check_c_source_compiles(
        "
            ${includes}
            int main() {
                struct ${type} v;
                (void) v.${field};
            }
        "
        ${variable}
    )
    if(${variable})
        set(${variable} ${${variable}} PARENT_SCOPE)
        add_definitions(-D${variable})
    endif()
endfunction()

function(cc_check_sizeof type)
    include(CheckTypeSize)
    cc_check_name("SIZEOF_${type}" variable)
    set(CMAKE_EXTRA_INCLUDE_FILES ${ARGN})
    check_type_size(${type} ${variable})
    if(${variable})
        set(${variable} ${${variable}} PARENT_SCOPE)
        add_definitions(-D${variable}=${${variable}})
    endif()
endfunction(cc_check_sizeof)
