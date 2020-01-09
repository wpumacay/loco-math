message( "TINYMATH::python >>> configuring python-bindings" )

file( GLOB_RECURSE BindingsFilesSources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include" )
include_directories( "${TINYMATH_INCS_DIR}" )

pybind11_add_module( tinymath MODULE "${BindingsFilesSources}" )
target_link_libraries( tinymath PRIVATE tinymath_cpp_lib )

pybind11_add_module( tinymath_python_lib SHARED "${BindingsFilesSources}" )
target_link_libraries( tinymath_python_lib PRIVATE tinymath_cpp_lib )

if ( TINYMATH_BUILD_TESTS )
    add_subdirectory( tests )
endif()