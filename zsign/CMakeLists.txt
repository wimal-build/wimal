cmake_minimum_required(VERSION 3.14)

project(zsign)

set(CMAKE_CXX_STANDARD 11)

add_executable(
  zsign
  common/base64.cpp
  common/common.cpp
  common/json.cpp
  archo.cpp
  bundle.cpp
  macho.cpp
  openssl.cpp
  signing.cpp
  zsign.cpp
)
target_link_libraries(zsign crypto zlibstatic)

install(TARGETS zsign DESTINATION bin COMPONENT zsign)
