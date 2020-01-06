message( "TINYMATH::python>> configuring python-bindings" )

file( GLOB_RECURSE BindingsFilesSources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
include_directories( "${TINYMATH_INCS}" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}" )

pybind11_add_module( tinymath MODULE "${BindingsFilesSources}" )
target_link_libraries( tinymath PRIVATE tinymath_cpp )