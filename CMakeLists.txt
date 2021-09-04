cmake_minimum_required(VERSION 3.15..3.19)

project(
  TinyMath
  VERSION 0.1.0
  DESCRIPTION "A basic math library for vectors and matrices"
  HOMEPAGE_URL "https://github.com/wpumacay/tiny_math"
  LANGUAGES C CXX)

# Include some helper functions that we will need later
include(${PROJECT_SOURCE_DIR}/cmake/Common.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/Utils.cmake)

# Include some internal tools we might need to use
include(FetchContent)
include(GNUInstallDirs)

# Check if we're currently working as the root project. If so, configure some
# common settings that we might need later during configuration
tmInitializeProject()

option(TINYMATH_BUILD_PYTHON_BINDINGS "Build bindings (requires Pybind11)" ON)
option(TINYMATH_BUILD_TESTS "Build C++ unit-tests (requires google-test" ON)
option(TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen)" OFF)

add_library(TinyMathCpp ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_t_spec.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix_t_spec.cpp)
# Set features and other settings for this target
target_compile_features(TinyMathCpp PUBLIC cxx_std_11)
target_include_directories(TinyMathCpp
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(third_party)
add_subdirectory(python)
add_subdirectory(docs)

tmPrintSummary()
