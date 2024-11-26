cmake_minimum_required(VERSION 3.10)

project(apple-codesign)

include(MeDetectTarget)

me_detect_target(ME)

if(WIMAL_TARGET STREQUAL "a64-macos")
  set(CARGO_TARGET "aarch64-apple-darwin")
  set(CARGO_TARGET_ENV "AARCH64_APPLE_DARWIN")
elseif(WIMAL_TARGET STREQUAL "x64-macos")
  set(CARGO_TARGET "x86_64-apple-darwin")
  set(CARGO_TARGET_ENV "X86_64_APPLE_DARWIN")
elseif(WIMAL_TARGET STREQUAL "a64-linux")
  set(CARGO_TARGET "aarch64-unknown-linux-gnu")
  set(CARGO_TARGET_ENV "AARCH64_UNKNOWN_LINUX_GNU")
elseif(WIMAL_TARGET STREQUAL "x64-linux")
  set(CARGO_TARGET "x86_64-unknown-linux-gnu")
  set(CARGO_TARGET_ENV "X86_64_UNKNOWN_LINUX_GNU")
else()
  message(WARNING "Unsupported target")
  return()
endif()

find_program(RUSTUP rustup)

if(NOT RUSTUP)
  message(WARNING "Rustup is required")
  file(
    DOWNLOAD "https://sh.rustup.rs" "${CMAKE_CURRENT_BINARY_DIR}/rustup-init.sh"
    STATUS RUSTUP_INIT_RESULT
  )
  if(NOT RUSTUP_INIT_RESULT EQUAL 0)
    message(WARNING "Failed to download rustup-init.sh")
    return()
  endif()
  set(
    RUSTUP_ENV "RUSTUP_HOME=${CMAKE_CURRENT_BINARY_DIR}/rustup"
               "CARGO_HOME=${CMAKE_CURRENT_BINARY_DIR}/cargo"
  )
  execute_process(
    COMMAND
      ${CMAKE_COMMAND} -E env ${RUSTUP_ENV} bash
      "${CMAKE_CURRENT_BINARY_DIR}/rustup-init.sh" "-y"
      "--default-toolchain=stable" "--profile=minimal" "--no-modify-path"
    RESULT_VARIABLE RUSTUP_INIT_RESULT
  )
  if(NOT RUSTUP_INIT_RESULT EQUAL 0)
    message(WARNING "Failed to install Rustup")
    return()
  endif()
  set(RUSTUP "${CMAKE_CURRENT_BINARY_DIR}/cargo/bin/rustup")
  if(NOT EXISTS ${RUSTUP})
    message(WARNING "Failed to install Rustup")
    return()
  endif()
endif()

file(GLOB_RECURSE CARGO_SOURCES "*.rs" "Cargo.toml" "Cargo.lock")

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bin/rcodesign
  COMMAND ${CMAKE_COMMAND} -E env ${RUSTUP_ENV} ${RUSTUP} component add rust-src
  COMMAND
    ${CMAKE_COMMAND} -E env ${RUSTUP_ENV} "TARGET_CC=${CMAKE_C_COMPILER}"
    "CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR}/build"
    "CARGO_INSTALL_ROOT=${CMAKE_CURRENT_BINARY_DIR}"
    "CARGO_TARGET_${CARGO_TARGET_ENV}_LINKER=${CMAKE_C_COMPILER}"
    "RUSTC_BOOTSTRAP=1" ${RUSTUP} run stable cargo install -Z build-std --bin
    rcodesign apple-codesign --target ${CARGO_TARGET} --force
  DEPENDS ${CARGO_SOURCES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  VERBATIM
)

add_custom_target(
  apple-codesign DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/bin/rcodesign
)

if(CMAKE_STRIP)
  add_custom_command(
    TARGET apple-codesign POST_BUILD
    COMMAND ${CMAKE_STRIP} ${CMAKE_CURRENT_BINARY_DIR}/bin/rcodesign
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} VERBATIM
  )
endif()

install(
  PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/bin/rcodesign DESTINATION bin
  COMPONENT apple-codesign
)

add_custom_target(
  install-apple-codesign
  DEPENDS apple-codesign
  COMMAND
    "${CMAKE_COMMAND}" -DCMAKE_INSTALL_COMPONENT=apple-codesign -P
    "${CMAKE_BINARY_DIR}/cmake_install.cmake"
  USES_TERMINAL
)
