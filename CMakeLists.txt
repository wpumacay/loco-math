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
set( TINYMATH_INCS "${CMAKE_CURRENT_SOURCE_DIR}/include" )

include_directories( "${TINYMATH_INCS}" )

add_library( tinymath_cpp SHARED ${TINYMATH_SRCS} )

add_subdirectory( tests )
add_subdirectory( ext/pybind11 )
add_subdirectory( python )