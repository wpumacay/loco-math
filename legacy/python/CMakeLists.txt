# ~~~
# CMake configuration for Python bindings using pybind11
#
# We use the awesome pybind11 library to generate bindings from a C++ interface
# https://github.com/pybind/pybind11
# ~~~

if(NOT TINYMATH_BUILD_PYTHON_BINDINGS)
  tmMessage("Bindings are not required for the current build" LOG_LEVEL TRACE)
  return()
endif()

# Create target for our python bindings (standalone MODULE)
pybind11_add_module(
  tinymath MODULE "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings_all.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings_common.cpp")
target_include_directories(tinymath PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tinymath PRIVATE TinyMathCpp)
