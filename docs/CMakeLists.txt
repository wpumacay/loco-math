# ~~~
# CMake configuration for docs-generation using Sphinx+Doxygen
#
# We use the awesome pybind11 library to generate bindings from a C++ interface
# https://github.com/pybind/pybind11
# ~~~

if(NOT LOCOMATH_BUILD_DOCS)
  loco_message("Configuring without docs generation" LOG_LEVEL TRACE)
  return()
endif()

if(NOT LOCOMATH_IS_ROOT_PROJECT)
  loco_message("Main|Root project would be in charge of setup" LOG_LEVEL TRACE)
  return()
endif()

# ~~~
# Configuring Doxygen (converts C++ doc-comments)
# ~~~
find_package(Doxygen QUIET)

if(DOXYGEN_FOUND)
  # Find all public headers for the documentation
  get_target_property(LOCOMATH_PUBLIC_INCS_DIR LocoMathCpp
                      INTERFACE_INCLUDE_DIRECTORIES)
  file(GLOB_RECURSE LOCOMATH_PUBLIC_INCS_FILES
       "${LOCOMATH_PUBLIC_INCS_DIR}/*.hpp")
  # Where to send the documentation
  set(DOXYGEN_INPUT_DIR "${LOCOMATH_PUBLIC_INCS_DIR}")
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
    DEPENDS ${LOCOMATH_PUBLIC_INCS_FILES}
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    MAIN_DEPENDENCY ${DOXYFILE_OUT}
    ${DOXYFILE_IN}
    COMMENT "LocoMath >>> Configuring docs-generation using Doxygen")
  add_custom_target(
    LocoMathDocsDoxygen ALL
    DEPENDS ${DOXYGEN_INDEX_FILE}
    COMMENT "LocoMath >>> Configuring target for docs-generation using Doxygen")
  loco_message("Successfully configured first docs-generation pass!")
else()
  # If Doxygen is not found, then just stop processing this file
  loco_message("Couldn't find Doxygen. Skipping docs-generation")
  set(LOCOMATH_BUILD_DOCS
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
      -Dbreathe_projects.LocoMath=${DOXYGEN_OUTPUT_DIR}/xml ${SPHINX_SOURCE}
      ${SPHINX_BUILD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/index.rst ${DOXYGEN_INDEX_FILE}
    MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
    COMMENT "LocoMath >>> Configuring docs-generation using Sphinx")
  add_custom_target(
    LocoMathDocsSphinx ALL
    DEPENDS ${SPHINX_INDEX_FILE}
    COMMENT "LocoMath >>> Configuring target for docs-generation using Sphinx")
  loco_message("Successfully configured second docs-generation pass!")
else()
  loco_message("Couldn't find Sphinx. Skipping docs-generation")
  set(LOCOMATH_BUILD_DOCS
      OFF
      PARENT_SCOPE)
  return()
endif()
