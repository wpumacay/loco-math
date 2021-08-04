cmake_minimum_required(VERSION 3.15..3.19)

project(
    TinyMath
    VERSION 0.1.0
    DESCRIPTION "A basic math library for vectors and matrices"
    HOMEPAGE_URL "https://github.com/wpumacay/tiny_math"
    LANGUAGES C CXX)

# @todo: these should go to target-compile-features (per-target) and propagate correctly
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")

# Check if we're currently working as the main project
set(TINYMATH_IS_MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    message("TINYMATH >>> configuring as MASTER project")
    set(TINYMATH_IS_MASTER_PROJECT ON)
else()
    message("TINYMATH >>> configuring as CHILD project")
endif()

# @todo: building docs requires doxygen, so check if found on the system
option(TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen)" ON)
option(TINYMATH_BUILD_EXAMPLES "Build c/c++ examples" ON)
option(TINYMATH_BUILD_PYTHON_BINDINGS "Build python bindings" ON)

# Add cmake find-modules helpers (for sphinx)
if(TINYMATH_IS_MASTER_PROJECT)
    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
endif()

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    message("TINYMATH >>> Sending generated libs to OWN build directory")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs")
else()
    message("TINYMATH >>> Sending generated libs to USER-DEFINED build directory")
endif()

# @todo: use of GLOB and GLOB_RECURSE is discouraged, and should be replaced by listing the sources
file(GLOB_RECURSE TINYMATH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# @todo: this might be better configured as part of the target (include_directories) and propagated through PUBLIC
set(TINYMATH_INCS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# @todo: move this one to target-include-directories instead
include_directories("${TINYMATH_INCS_DIR}")

add_library(tinymath_cpp_lib SHARED ${TINYMATH_SRCS})
target_include_directories(tinymath_cpp_lib PUBLIC "${TINYMATH_INCS_DIR}")

# @todo: change this part to follow the super-build modern pattern
if(TINYMATH_IS_MASTER_PROJECT)
    add_subdirectory(ext)
endif()

# Add bindings subdirectory
if(TINYMATH_BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()

if(TINYMATH_IS_MASTER_PROJECT AND TINYMATH_BUILD_EXAMPLES)
    add_subdirectory(examples/cpp)
endif()

if(TINYMATH_BUILD_DOCS AND TINYMATH_IS_MASTER_PROJECT)
    add_subdirectory(docs)
endif()

message("BUILD-OPTIONS SUMMARY")
message("TINYMATH_BUILD_DOCS               : ${TINYMATH_BUILD_DOCS}")
message("TINYMATH_BUILD_EXAMPLES           : ${TINYMATH_BUILD_EXAMPLES}")
message("TINYMATH_BUILD_PYTHON_BINDINGS    : ${TINYMATH_BUILD_PYTHON_BINDINGS}")
