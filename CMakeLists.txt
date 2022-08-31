cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# -------------------------------------
# Get loco_cmake to help us configure our CMake based project
include(FetchContent)
FetchContent_Declare(
  loco_cmake
  GIT_REPOSITORY https://github.com/wpumacay/loco_cmake.git
  GIT_TAG dev
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(loco_cmake)
include(${loco_cmake_SOURCE_DIR}/Index.cmake)

# -------------------------------------
# Define our project :)
project(
  LocoMath
  VERSION 0.4.1
  DESCRIPTION "A basic math library for vectors and matrices"
  HOMEPAGE_URL "https://github.com/wpumacay/loco_math"
  LANGUAGES C CXX)

# -------------------------------------
# Define some options the user can set before|while configuring the project
option(LOCOMATH_BUILD_SSE "Build using SSE SIMD-extensions support" ON)
option(LOCOMATH_BUILD_AVX "Build using AVX SIMD-extensions support" ON)
option(LOCOMATH_BUILD_FORCE_INLINE "Build with inlining when requested" OFF)
option(LOCOMATH_BUILD_PYTHON_BINDINGS "Build bindings (requires Pybind11)" ON)
option(LOCOMATH_BUILD_DOCS "Build documentation (requires Doxygen+Breathe)" OFF)
option(LOCOMATH_BUILD_TESTS "Build C++ unit-tests (requires google-test)" ON)
option(LOCOMATH_BUILD_EXAMPLES "Build C++ examples" ON)

# -------------------------------------
# Initialize the project using our helper modules :D
loco_initialize_project()

# -------------------------------------
# Allow the usage of our helper macros and functions
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# -------------------------------------
# Bring our dependencies accordingly
include(LocoMathDependencies)

# cmake-format: off
# -------------------------------------
# Setup the main C++ target `LocoMathCpp`
loco_create_target(LocoMathCpp INTERFACE
  SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/common.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/vec2_t.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/vec2_t_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/vec3_t.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/vec3_t_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/vec4_t.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/vec4_t_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/mat4_t.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/mat4_t_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/vec2_t_scalar_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/vec2_t_sse_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/vec3_t_scalar_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/vec3_t_sse_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/vec3_t_avx_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/vec4_t_scalar_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/vec4_t_sse_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/vec4_t_avx_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/mat4_t_scalar_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/mat4_t_sse_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/impl/mat4_t_avx_impl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loco/math/all.hpp
  INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  WARNINGS_AS_ERRORS
    FALSE
  ENABLE_SSE
    ${LOCOMATH_BUILD_SSE}
  ENABLE_AVX
    ${LOCOMATH_BUILD_AVX}
)
# cmake-format: on

# -------------------------------------
# If force-inline is being requested, then add it to the target
if(LOCOMATH_BUILD_FORCE_INLINE)
  # @todo(wilbert): Move this to one of the setup helpers on the loco-cmake repo
  target_compile_definitions(LocoMathCpp PUBLIC -DLOCOMATH_FORCE_INLINE)
endif()

# -------------------------------------
# Expose an alias for the library (CMake namespace convention)
add_library(loco::math ALIAS LocoMathCpp)

# -------------------------------------
# Add C++ examples to the build process
add_subdirectory(examples/cpp)

# -------------------------------------
# Add C++ tests to the build process
add_subdirectory(tests/cpp)

# -------------------------------------
# Add Python bindings to the build process
add_subdirectory(python/math)

# -------------------------------------
# Build the required documentation accordingly
if(LOCOUTILS_BUILD_DOCS)
  # cmake-format: off
  # -------------------------------------
  # Setup documentation for our target
  loco_setup_cppdocs(LocoUtilsCpp
    DOXYGEN_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
    DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxygen
    DOXYGEN_GENERATE_HTML FALSE
    DOXYGEN_GENERATE_LATEX FALSE
    DOXYGEN_GENERATE_XML TRUE
    DOXYGEN_QUIET TRUE
    SPHINX_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/conf.py.in
    SPHINX_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/Sphinx
    SPHINX_BREATHE_PROJECT LocoUtilsCpp
    SPHINX_DOXYGEN_XML_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxygen/xml)
  # cmake-format: on
endif()

# -------------------------------------
# Show the properties of our main target
loco_print_target_properties(LocoMathCpp)

# -------------------------------------
# Show some info of the this project
loco_print_project_info()

# -------------------------------------
# Show some info of the host
loco_print_host_info()
