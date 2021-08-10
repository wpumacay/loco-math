message("TINYMATH::examples>> configuring examples")

file(GLOB_RECURSE ExampleFilesSources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
include_directories("${TINYMATH_INCS_DIR}")

foreach(ExampleFileSource ${ExampleFilesSources})
    string(
        REPLACE ".cpp"
                ""
                ExampleFilePathNoExt
                ${ExampleFileSource})
    get_filename_component(ExampleFileExecName ${ExampleFilePathNoExt} NAME)
    add_executable(${ExampleFileExecName} ${ExampleFileSource})
    target_link_libraries(${ExampleFileExecName} tinymath_cpp_lib)
endforeach(ExampleFileSource)
