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

# Make sure that if the user doesn't provide CMAKE_INSTALL_PREFIX, we then use a
# default path for installation (relative to build). We only make sure in the
# case we're the main project. If not, then the main project should handle this
if(TINYMATH_IS_ROOT_PROJECT)
    if(NOT CMAKE_INSTALL_PREFIX)
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
        set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")
        set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
        set(CMAKE_INSTALL_BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
        set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/doc")
    endif()
endif()

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

add_subdirectory(third_party)
add_subdirectory(python)

# ~~~
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
