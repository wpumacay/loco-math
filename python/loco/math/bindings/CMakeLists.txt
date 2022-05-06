# ~~~
# CMake configuration rules used to generate Python Bindings via Pybind11
# ~~~

if(NOT LOCOMATH_BUILD_PYTHON_BINDINGS)
  loco_message("Bindings are not required for the current build" LOG_LEVEL
               TRACE)
  return()
endif()

if(NOT TARGET loco::math)
  loco_message("Bindings require the loco::math target" LOG_LEVEL WARNING)
  return()
endif()

pybind11_add_module(math ${CMAKE_CURRENT_SOURCE_DIR}/bindings_py.cpp)
target_link_libraries(math PRIVATE loco::math)
