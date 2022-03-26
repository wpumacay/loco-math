# ~~~
# CMake configuration rules used to generate Python Bindings via Pybind11
# ~~~

if(NOT TINYMATH_BUILD_PYTHON_BINDINGS)
  tmMessage("Bindings are not required for the current build" LOG_LEVEL TRACE)
  return()
endif()

if(NOT TARGET tinymath::tinymath)
  tmMessage("Bindings require the tinymath::tinymath target" LOG_LEVEL WARNING)
  return()
endif()

pybind11_add_module(tinymath_py ${CMAKE_CURRENT_SOURCE_DIR}/bindings_py.cpp)
target_link_libraries(tinymath_py PRIVATE tinymath::tinymath)
