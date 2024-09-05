# ~~~
# CMake configuration for C++ examples
# ~~~
if(NOT TARGET math::math)
  loco_message("Examples require the [math::math] target to be defined"
               LOG_LEVEL WARNING)
  return()
endif()

# List of all examples to be built
set(MATH3D_EXAMPLES_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec2_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec2_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec3_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec3_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec4_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec4_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat2_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat2_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat3_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat3_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat4_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat4_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_euler_conversions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_lerp_vec2.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/example_lerp_vec3.cpp
)

# Create all the example targets
foreach(example_filepath IN LISTS MATH3D_EXAMPLES_LIST)
  loco_setup_single_file_example(${example_filepath} TARGET_DEPENDENCIES
                                 math::math)
endforeach()
