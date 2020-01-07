cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

project( tinymath )

set( CMAKE_CXX_STANDARD 11 )

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

option( TINYMATH_BUILD_DOCS "Build documentation (requires Doxygen)" ON )
if ( TINYMATH_BUILD_DOCS )
    add_subdirectory( docs )
endif()

add_subdirectory( tests )
add_subdirectory( ext/pybind11 )
add_subdirectory( python )