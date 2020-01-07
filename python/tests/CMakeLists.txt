message( "TINYMATH::python::tests >>> configuring python-bindings tests" )

include_directories( "${TINYMATH_INCS_DIR}" )
include_directories( "../include" )

file( GLOB TestBindingFilesSources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )

# add a single module for each test
foreach( TestBindingFileSource ${TestBindingFilesSources} )
    string( REPLACE ".cpp" "" TestBindingFilePathNoExt ${TestBindingFileSource} )
    get_filename_component( TestBindingFileExecName ${TestBindingFilePathNoExt} NAME )
    pybind11_add_module( ${TestBindingFileExecName} MODULE ${TestBindingFileSource} )
    target_link_libraries( ${TestBindingFileExecName} PRIVATE tinymath_cpp_lib tinymath_python_lib )
endforeach( TestBindingFileSource )