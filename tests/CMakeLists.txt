message( "TINYMATH::tests>> configuring tests" )

file( GLOB_RECURSE TestFilesSources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
include_directories( "${TINYMATH_INCS_DIR}" )

foreach( TestFileSource ${TestFilesSources} )
    string( REPLACE ".cpp" "" TestFilePathNoExt ${TestFileSource} )
    get_filename_component( TestFileExecName ${TestFilePathNoExt} NAME )
    add_executable( ${TestFileExecName} ${TestFileSource} )
    target_link_libraries( ${TestFileExecName} tinymath_cpp_lib )
endforeach( TestFileSource )