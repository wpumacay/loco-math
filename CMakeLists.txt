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

option(TINYMATH_BUILD_SSE "Build using SSE support (requires cpu support)" OFF)
option(TINYMATH_BUILD_AVX "Build using AVX support (requires cpu support)" OFF)
option(TINYMATH_BUILD_PYTHON_BINDINGS "Build bindings (requires Pybind11)" OFF)
option(TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen+Breathe)" OFF)
option(TINYMATH_BUILD_TESTS "Build C++ unit-tests (requires google-test)" ON)
option(TINYMATH_BUILD_EXAMPLES "Build C++ examples" ON)

add_library(
  TinyMathCpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tinymath/vec3_t.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tinymath/impl/vec3_t_scalar_impl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tinymath/impl/vec3_t_sse_impl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tinymath/impl/vec3_t_avx_impl.cpp)
# Set features and other settings for this target
target_compile_features(TinyMathCpp PUBLIC cxx_std_11)
target_include_directories(TinyMathCpp
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Make sure that we don't re-define the make_unique if it's already exposed
if(MSVC)
  target_compile_options(TinyUtilsCpp PUBLIC "/Zc:__cplusplus")
endif()

if(TINYMATH_BUILD_SSE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(TinyMathCpp PUBLIC -msse)
    target_compile_definitions(TinyMathCpp PUBLIC -DTINYMATH_SSE_ENABLED)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(TinyMathCpp PUBLIC -msse)
    target_compile_definitions(TinyMathCpp PUBLIC -DTINYMATH_SSE_ENABLED)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(TinyMathCpp PUBLIC /arch:SSE)
    target_compile_definitions(TinyMathCpp PUBLIC -DTINYMATH_SSE_ENABLED)
  else()
    tmMessage("We don't yet support SSE for compiler '${CMAKE_CXX_COMPILER_ID}'"
              LOG_LEVEL WARNING)
  endif()
endif()

if(TINYMATH_BUILD_AVX)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(TinyMathCpp PUBLIC -mavx)
    target_compile_definitions(TinyMathCpp PUBLIC -DTINYMATH_AVX_ENABLED)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(TinyMathCpp PUBLIC -mavx)
    target_compile_definitions(TinyMathCpp PUBLIC -DTINYMATH_AVX_ENABLED)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(TinyMathCpp PUBLIC /arch:AVX)
    target_compile_definitions(TinyMathCpp PUBLIC -DTINYMATH_AVX_ENABLED)
  else()
    tmMessage("We don't yet support AVX for compiler '${CMAKE_CXX_COMPILER_ID}'"
              LOG_LEVEL WARNING)
  endif()
endif()

# Expose an alias for the library (CMake namespace convention)
add_library(tinymath::tinymath ALIAS TinyMathCpp)

# Add dependencies to the build process
add_subdirectory(third_party)

# Add C++ examples to the build process
add_subdirectory(examples/cpp)

# Add C++ tests to the build process
add_subdirectory(tests/cpp)

# ~~~
# add_subdirectory(python)
# add_subdirectory(docs)
# ~~~

tmPrintSummary()
