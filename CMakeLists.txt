cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

project( TinyMath )

set( CMAKE_CXX_STANDARD 11 )

# Check if we're currently working as the main project
set( TINYMATH_IS_MASTER_PROJECT OFF )
if( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( "TINYMATH >>> configuring as MASTER project" )
    set( TINYMATH_IS_MASTER_PROJECT ON )
else()
    message( "TINYMATH >>> configuring as CHILD project" )
endif()

option( TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen)" ON )
option( TINYMATH_BUILD_EXAMPLES "Build c/c++ examples" ON )
option( TINYMATH_BUILD_TESTS "Build c/c++ tests" ON )

# Add cmake find-modules helpers (for sphinx)
if( TINYMATH_IS_MASTER_PROJECT )
    set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH} )
endif()

if ( NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    message( "TINYMATH >>> Sending generated libs to OWN build directory" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs" )
else()
    message( "TINYMATH >>> Sending generated libs to USER-DEFINED build directory" )
endif()

file( GLOB_RECURSE TINYMATH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
set( TINYMATH_INCS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" )
include_directories( "${TINYMATH_INCS_DIR}" )

add_library( tinymath_cpp_lib SHARED ${TINYMATH_SRCS} )
target_include_directories( tinymath_cpp_lib PUBLIC "${TINYMATH_INCS_DIR}" )

# Add subdirectories only if master-project
if ( TINYMATH_IS_MASTER_PROJECT )
    if ( TINYMATH_BUILD_TESTS )
        add_subdirectory( tests ) # if child project, no tests are required
    endif()
    add_subdirectory( ext ) # if child project, root project adds the dependencies
endif()

# Add bindings subdirectory
add_subdirectory( python )

if ( TINYMATH_BUILD_DOCS AND TINYMATH_IS_MASTER_PROJECT )
    add_subdirectory( docs )
endif()

message( "BUILD-OPTIONS SUMMARY" )
message( "TINYMATH_BUILD_DOCS: ${TINYMATH_BUILD_DOCS}" )
message( "TINYMATH_BUILD_TESTS: ${TINYMATH_BUILD_TESTS}" )
message( "TINYMATH_BUILD_EXAMPLES: ${TINYMATH_BUILD_EXAMPLES}" )