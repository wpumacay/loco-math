cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

project( tinymath )

set( CMAKE_CXX_STANDARD 11 )

file( GLOB_RECURSE TINYMATH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
set( TINYMATH_INCS "${CMAKE_CURRENT_SOURCE_DIR}/include" )

include_directories( "${TINYMATH_INCS}" )

add_library( tinymath ${TINYMATH_SRCS} )

add_subdirectory( tests )
