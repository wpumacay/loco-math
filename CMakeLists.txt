cmake_minimum_required(VERSION 3.15..3.19)

project(
    TinyMath
    VERSION 0.1.0
    DESCRIPTION "A basic math library for vectors and matrices"
    HOMEPAGE_URL "https://github.com/wpumacay/tiny_math"
    LANGUAGES C CXX)

# Include some helper functions that we might need
include(${PROJECT_SOURCE_DIR}/cmake/Common.cmake)

# Check if we're currently working as the root project. If so, configure some
# common settings that we might need later during configuration
tmInitializeProject()

# @todo: building docs requires doxygen, so check if found on the system
option(TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen)" ON)
option(TINYMATH_BUILD_EXAMPLES "Build C++ examples" ON)
option(TINYMATH_BUILD_PYTHON_BINDINGS "Build python bindings" ON)

# ~~~
# # @todo: use of GLOB and GLOB_RECURSE is discouraged, and should be replaced
# # by listing the sources
# file(GLOB_RECURSE TINYMATH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# # @todo: this might be better configured as part of the target
# # (include_directories) and propagated through PUBLIC
# set(TINYMATH_INCS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# # @todo: move this one to target-include-directories instead
# include_directories("${TINYMATH_INCS_DIR}")
#
# add_library(tinymath_cpp_lib SHARED ${TINYMATH_SRCS})
# target_compile_features(tinymath_cpp_lib PUBLIC cxx_std_11)
# target_include_directories(tinymath_cpp_lib PUBLIC "${TINYMATH_INCS_DIR}")
#
# # @todo: change this part to follow the super-build modern pattern
# if(TINYMATH_IS_ROOT_PROJECT)
#     add_subdirectory(ext)
# endif()
#
# # Add bindings subdirectory
# if(TINYMATH_BUILD_PYTHON_BINDINGS)
#     add_subdirectory(python)
# endif()
#
# if(TINYMATH_IS_ROOT_PROJECT AND TINYMATH_BUILD_EXAMPLES)
#     add_subdirectory(examples/cpp)
# endif()
#
# if(TINYMATH_BUILD_DOCS AND TINYMATH_IS_ROOT_PROJECT)
#     add_subdirectory(docs)
# endif()
#
# ~~~

tmPrintSummary()
