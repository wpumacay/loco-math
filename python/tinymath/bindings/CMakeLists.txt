# ~~~
# CMake configuration rules used to generate Python Bindings via Pybind11
# ~~~

if(NOT TINYMATH_BUILD_PYTHON_BINDINGS)
  tmMessage("Bindings are not required for the current build" LOG_LEVEL TRACE)
  return()
endif()

<<<<<<< HEAD
# Create target for our python bindings (standalone MODULE)
pybind11_add_module(
  tinyutils
  MODULE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/logging_py.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/path_handling_py.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/timing_py.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/perlin_noise_py.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/profiling_py.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings_py.cpp")
target_include_directories(tinyutils
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tinyutils PRIVATE TinyUtilsCpp)
=======
if(NOT TARGET tinymath::tinymath)
  tmMessage("Bindings require the tinymath::tinymath target" LOG_LEVEL WARNING)
  return()
endif()

pybind11_add_module(tinymath_py ${CMAKE_CURRENT_SOURCE_DIR}/bindings_py.cpp)
target_include_directories(tinymath_py
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tinymath_py PRIVATE tinymath::tinymath)
>>>>>>> dev
