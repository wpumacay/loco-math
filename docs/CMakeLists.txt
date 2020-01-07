message( "TINYMATH::docs >>> trying to setup the build process for the docs" )

find_package( Doxygen )

if ( DOXYGEN_FOUND )
    # find all public headers for the documentation
    get_target_property( TINYMATH_PUBLIC_INCS_DIR tinymath_cpp_lib INTERFACE_INCLUDE_DIRECTORIES )
    file( GLOB_RECURSE TINYMATH_PUBLIC_INCS_FILES "${TINYMATH_PUBLIC_INCS_DIR}/*.h" )
    # where to send the documentation
    set( DOXYGEN_INPUT_DIR "${TINYMATH_PUBLIC_INCS_DIR}" )
    set( DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/doxygen" )
    set( DOXYGEN_INDEX_FILE "${DOXYGEN_OUTPUT_DIR}/html/index.html" )
    set( DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in" )
    set( DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" )
    # replace variables inside @@ with the current values
    configure_file( ${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY )
    # create the directory where to send the documentation
    file( MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR} )
    # configure doxygen external command
    add_custom_command( OUTPUT ${DOXYGEN_INDEX_FILE}
                        DEPENDS ${TINYMATH_PUBLIC_INCS_FILES}
                        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                        COMMENT "TINYMATH::docs >>> Generating docs ..." )
    add_custom_target( tinymath_cpp_docs ALL DEPENDS ${DOXYGEN_INDEX_FILE} )
    message( "TINYMATH::docs >>> successfully setup the build process for the docs!" )
else()
    message( "TINYMATH::docs >>> couldn't find Doxygen; skipping docs" )
endif()