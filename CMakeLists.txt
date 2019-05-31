cmake_minimum_required(VERSION 3.0)

add_subdirectory(wimal)

add_custom_target(installation DEPENDS wimal)
