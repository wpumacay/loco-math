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

pybind11_add_module(_math ${CMAKE_CURRENT_SOURCE_DIR}/bindings_py.cpp)
target_include_directories(_math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(_math PRIVATE loco::math)

add_library(math_py_helpers INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/conversions_py.hpp)
target_include_directories(math_py_helpers
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(math_py_helpers INTERFACE loco::math)

add_library(loco::math_py_helpers ALIAS math_py_helpers)
