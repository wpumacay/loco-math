message( "TINYMATH::python>> configuring python-bindings" )

file( GLOB_RECURSE BindingsFilesSources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
include_directories( "${TINYMATH_INCS}" )