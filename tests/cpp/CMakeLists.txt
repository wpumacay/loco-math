# ~~~
# CMake configuration for C++ unittests
# ~~~
if(NOT LOCOMATH_BUILD_TESTS)
  return()
endif()

if((NOT TARGET loco::math) OR (NOT TARGET Catch2::Catch2))
  loco_message(
    "Unittests require both [loco::math] and [Catch2::Catch2] targets"
    LOG_LEVEL WARNING)
  return()
endif()

include(CTest)
include(${CMAKE_SOURCE_DIR}/third_party/catch2/source/contrib/Catch.cmake)

add_executable(
  LocoMathCppTests
  ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_vec2_type.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_vec2_operations.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_vec3_type.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_vec3_operations.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_vec4_type.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_vec4_operations.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_mat4_type.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_mat4_operations.cpp)
target_link_libraries(LocoMathCppTests PRIVATE loco::math Catch2::Catch2)
# Discover tets and pick an integer as the random seed
catch_discover_tests(LocoMathCppTests EXTRA_ARGS --rng-seed 721790)
