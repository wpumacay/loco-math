cmake_minimum_required(VERSION 3.15..3.19)

project(
  TinyMath
  VERSION 0.2.0
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

option(TINYMATH_BUILD_SSE "Build using SSE SIMD-extensions support" OFF)
option(TINYMATH_BUILD_AVX "Build using AVX SIMD-extensions support" OFF)
option(TINYMATH_BUILD_INLINE "Build with inlining when requested" OFF)
option(TINYMATH_BUILD_PYTHON_BINDINGS "Build bindings (requires Pybind11)" OFF)
option(TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen+Breathe)" OFF)
option(TINYMATH_BUILD_TESTS "Build C++ unit-tests (requires google-test)" ON)
option(TINYMATH_BUILD_EXAMPLES "Build C++ examples" ON)

add_library(TinyMathCpp INTERFACE)
# Set features and other settings for this target
target_compile_features(TinyMathCpp INTERFACE cxx_std_11)
target_include_directories(TinyMathCpp
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Configure the target with the required compiler features and options
# cmake-format: off
tmSetupCompileProperties(
  PROJECT TinyMath
  TARGET TinyMathCpp
  USE_SSE ${TINYMATH_BUILD_SSE}
  USE_AVX ${TINYMATH_BUILD_AVX}
  USE_INLINE ${TINYMATH_BUILD_INLINE})
# cmake-format: on

# Expose an alias for the library (CMake namespace convention)
add_library(tinymath::tinymath ALIAS TinyMathCpp)

# Add dependencies to the build process
add_subdirectory(third_party)

# Add C++ examples to the build process
add_subdirectory(examples/cpp)

# Add C++ tests to the build process
add_subdirectory(tests/cpp)

# Add Python bindings to the build process
add_subdirectory(python/tinymath/bindings)

# ~~~
# add_subdirectory(docs)
# ~~~

tmPrintSummary(TARGET TinyMathCpp)
