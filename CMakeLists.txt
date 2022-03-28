cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# -------------------------------------
# Get loco_cmake to help us configure our CMake based project
include(FetchContent)
FetchContent_Declare(
  loco_cmake
  GIT_REPOSITORY https://github.com/wpumacay/loco_cmake.git
  GIT_TAG main
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(loco_cmake)
include(${loco_cmake_SOURCE_DIR}/Index.cmake)

# -------------------------------------
# Define our project :)
project(
  TinyMath
  VERSION 0.3.0
  DESCRIPTION "A basic math library for vectors and matrices"
  HOMEPAGE_URL "https://github.com/wpumacay/tiny_math"
  LANGUAGES C CXX)

# -------------------------------------
# Define some options the user can set before|while configuring the project
option(TINYMATH_BUILD_SSE "Build using SSE SIMD-extensions support" OFF)
option(TINYMATH_BUILD_AVX "Build using AVX SIMD-extensions support" OFF)
option(TINYMATH_BUILD_INLINE "Build with inlining when requested" OFF)
option(TINYMATH_BUILD_PYTHON_BINDINGS "Build bindings (requires Pybind11)" ON)
option(TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen+Breathe)" OFF)
option(TINYMATH_BUILD_TESTS "Build C++ unit-tests (requires google-test)" ON)
option(TINYMATH_BUILD_EXAMPLES "Build C++ examples" ON)

# -------------------------------------
# Initialize the project using our helper modules :D
loco_initialize_project()

# -------------------------------------
# Get the required third-party dependencies
add_subdirectory(third_party)

# cmake-format: off
# -------------------------------------
# Setup the main C++ target `TinyMathCpp`
add_library(TinyMathCpp INTERFACE)
loco_setup_target(
  TinyMathCpp
  SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/common.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/vec2_t.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/vec2_t_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/vec3_t.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/vec3_t_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/vec4_t.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/vec4_t_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/mat4_t.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/mat4_t_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/vec2_t_scalar_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/vec2_t_sse_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/vec3_t_scalar_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/vec3_t_sse_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/vec3_t_avx_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/vec4_t_scalar_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/vec4_t_sse_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/vec4_t_avx_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/mat4_t_scalar_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/mat4_t_sse_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/impl/mat4_t_avx_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinymath/tinymath.hpp
  INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  WARNINGS_AS_ERRORS
    FALSE
  ENABLE_SSE
    ${TINYMATH_BUILD_SSE}
  ENABLE_AVX
    ${TINYMATH_BUILD_AVX}
)
# cmake-format: on

# -------------------------------------
# If force-inline is being requested, then add it to the target
if(TINYMATH_BUILD_INLINE)
  # @todo(wilbert): Move this to one of the setup helpers on the loco-cmake repo
  target_compile_definitions(TinyMathCpp PUBLIC -DTINYMATH_FORCE_INLINE)
endif()

# -------------------------------------
# Expose an alias for the library (CMake namespace convention)
add_library(tinymath::tinymath ALIAS TinyMathCpp)

# -------------------------------------
# Add C++ examples to the build process
add_subdirectory(examples/cpp)

# -------------------------------------
# Add C++ tests to the build process
add_subdirectory(tests/cpp)

# -------------------------------------
# Add Python bindings to the build process
add_subdirectory(python/tinymath/bindings)

# -------------------------------------
# Show the properties of our main target
loco_print_target_properties(TinyMathCpp)

# -------------------------------------
# Show some info of the this project
loco_print_project_info()

# -------------------------------------
# Show some info of the host
loco_print_host_info()
