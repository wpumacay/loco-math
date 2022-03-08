# ~~~
# CMake configuration for C++ examples
# ~~~

if(NOT TINYMATH_BUILD_EXAMPLES)
  return()
endif()

if(NOT TARGET tinymath::tinymath)
  tmMessage("Examples require tinymath::tinymath target" LOG_LEVEL WARNING)
  return()
endif()

# List of all examples to be built
set(TINYMATH_EXAMPLES_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec2_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec3_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec3_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec4_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec4_operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat4_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_mat4_operations.cpp
    # Examples used to check each op assembly listing
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/ex_vec3f_ops.cpp)

# Create all the example targets
foreach(example_filepath IN LISTS TINYMATH_EXAMPLES_LIST)
  tmConfigureExample(${example_filepath})
endforeach()
