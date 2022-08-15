# ~~~
# CMake configuration for C++ unittests
# ~~~
if(NOT LOCOMATH_BUILD_TESTS)
  return()
endif()

if(NOT TARGET loco::math)
  loco_message("Unittests require target [loco::math], but wasn't found"
               LOG_LEVEL WARNING)
  return()
endif()

if(NOT TARGET Catch2::Catch2)
  loco_message("Unittests require target [Catch2::Catch2], but wasn't found"
               LOG_LEVEL WARNING)
  return()
endif()

include(CTest)

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
