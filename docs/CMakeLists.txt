# ~~~
# CMake configuration for docs-generation using Sphinx+Doxygen
#
# We use the awesome pybind11 library to generate bindings from a C++ interface
# https://github.com/pybind/pybind11
# ~~~

if(NOT TINYMATH_BUILD_DOCS)
    tmMessage("Configuring without docs generation" LOG_LEVEL TRACE)
    return()
endif()

if(NOT TINYMATH_IS_ROOT_PROJECT)
    tmMessage("Main|Root project would be in charge of setup" LOG_LEVEL TRACE)
    return()
endif()

# ~~~
# Configuring Doxygen (converts C++ doc-comments)
# ~~~
find_package(Doxygen QUIET)

if(DOXYGEN_FOUND)
    # Find all public headers for the documentation
    get_target_property(TINYMATH_PUBLIC_INCS_DIR TinyMathCpp
                        INTERFACE_INCLUDE_DIRECTORIES)
    file(GLOB_RECURSE TINYMATH_PUBLIC_INCS_FILES
         "${TINYMATH_PUBLIC_INCS_DIR}/*.h")
    # Where to send the documentation
    set(DOXYGEN_INPUT_DIR "${TINYMATH_PUBLIC_INCS_DIR}")
    set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/doxygen")
    set(DOXYGEN_INDEX_FILE "${DOXYGEN_OUTPUT_DIR}/html/index.html")
    set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
    set(DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    # Replace variables inside @@ with the current values
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
    # Create the directory where to send the documentation
    file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
    # Configure doxygen external command
    add_custom_command(
        OUTPUT ${DOXYGEN_INDEX_FILE}
        DEPENDS ${TINYMATH_PUBLIC_INCS_FILES}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        MAIN_DEPENDENCY ${DOXYFILE_OUT}
        ${DOXYFILE_IN}
        COMMENT "TinyMath >>> Configuring docs-generation using Doxygen")
    add_custom_target(TinyMathDocsDoxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
    tmMessage("Successfully configured first docs-generation pass!")
else()
    # If Doxygen is not found, then just stop processing this file
    tmMessage("Couldn't find Doxygen. Skipping docs-generation")
    set(TINYMATH_BUILD_DOCS
        OFF
        PARENT_SCOPE)
    return()
endif()

# ~~~
# Configuring Sphinx
# ~~~
find_package(Sphinx REQUIRED)

if(Sphinx_FOUND)
    set(SPHINX_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}")
    set(SPHINX_BUILD "${CMAKE_CURRENT_BINARY_DIR}/sphinx")
    set(SPHINX_INDEX_FILE "${SPHINX_BUILD}/index.html")

    add_custom_command(
        OUTPUT ${SPHINX_INDEX_FILE}
        COMMAND
            ${SPHINX_EXECUTABLE} -b html
            # Tell breathe where to find the Doxygen output
            -Dbreathe_projects.TinyMath=${DOXYGEN_OUTPUT_DIR}/xml
            ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/index.rst ${DOXYGEN_INDEX_FILE}
        MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
        COMMENT "TinyMath >>> Configuring docs-generation using Sphinx")
    add_custom_target(TinyMathDocsSphinx ALL DEPENDS ${SPHINX_INDEX_FILE})
    tmMessage("Successfully configured second docs-generation pass!")
else()
    tmMessage("Couldn't find Sphinx. Skipping docs-generation")
    set(TINYMATH_BUILD_DOCS
        OFF
        PARENT_SCOPE)
    return()
endif()
