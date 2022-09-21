# ~~~
# CMake configuration for C++ examples
# ~~~
if(NOT TARGET loco::math)
  loco_message("Examples require the [loco::math] target to be defined"
               LOG_LEVEL WARNING)
  return()
endif()

# List of all examples to be built
set(LOCOMATH_EXAMPLES_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec2_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec2_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec3_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec3_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec4_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec4_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat2_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat4_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat4_operations.cpp
    # Examples used to check each op assembly listing
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/ex_vec3f_ops.cpp)

# Create all the example targets
foreach(example_filepath IN LISTS LOCOMATH_EXAMPLES_LIST)
  loco_setup_single_file_example(${example_filepath} TARGET_DEPENDENCIES
                                 loco::math)
endforeach()
