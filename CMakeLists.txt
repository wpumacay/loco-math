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
include(ExternalProject)
include(FetchContent)
include(GNUInstallDirs)

# Check if we're currently working as the root project. If so, configure some
# common settings that we might need later during configuration
tmInitializeProject()

# @todo(wilbert): For development builds, the installation directory will be
# pointing just to a sub-directory of the build directory
if(TINYMATH_IS_ROOT_PROJECT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
    set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")
    set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
    set(CMAKE_INSTALL_BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
    set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/doc")
endif()

# @todo(wilbert): building docs requires doxygen, so check if found on the
# system
option(TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen)" ON)
option(TINYMATH_BUILD_EXAMPLES "Build C++ examples" ON)
option(TINYMATH_BUILD_PYTHON_BINDINGS "Build python bindings" ON)

add_library(
    TinyMathCpp SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_t_spec.cpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix_t_spec.cpp)
# Set features and other settings for this target
target_compile_features(TinyMathCpp PUBLIC cxx_std_11)
target_include_directories(TinyMathCpp
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

tmConfigureDependencies()

# ~~~
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
