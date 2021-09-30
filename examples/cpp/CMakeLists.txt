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
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec3_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/example_vec3_operations.cpp)

# Create all the example targets
foreach(example_filepath IN LISTS TINYMATH_EXAMPLES_LIST)
  tmConfigureExample(${example_filepath})
endforeach()
