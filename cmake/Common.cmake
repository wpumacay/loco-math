# ~~~
# This file exposes some helper functions that are used in this project All
# functions and macros are "namespaced" with the prefix "tm_" for tiny_math
# ~~~

# Helper function that displays a message to the console, prefixed with the name
# of the project accordingly. Notice that we cam pass the log-level
function(tmMessage var_message)
  if(NOT PROJECT_NAME)
    return()
  endif()

  set(oneValueArgs LOG_LEVEL)
  cmake_parse_arguments(TM_PRINT "" "${oneValueArgs}" "" ${ARGN})
  if(TM_PRINT_LOG_LEVEL)
    message(${TM_PRINT_LOG_LEVEL} "${PROJECT_NAME} >>> ${var_message}")
  else()
    message(STATUS "${PROJECT_NAME} >>> ${var_message}")
  endif()
endfunction()

# Helper macro that initializes the project properly (whether if root or not)
function(tmInitializeProject)
  if(NOT PROJECT_NAME)
    return()
  endif()

  # Grab the correct name for the variable to be exposed to the developer
  string(TOUPPER "${PROJECT_NAME}" ProjectNameUpper)
  string(TOUPPER "${PROJECT_NAME}_IS_ROOT_PROJECT" ProjectIsRootVarname)
  # @note: notice we're setting the variable twice (one for the local scope, and
  # another for the parent scope). This is required as we still use the variable
  # inside this function for some other checks (a bit of a hack >.<)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(${ProjectIsRootVarname} TRUE)
    set(${ProjectIsRootVarname}
        TRUE
        PARENT_SCOPE)
    tmMessage("The project ${PROJECT_NAME} is the root project")
  else()
    set(${ProjectIsRootVarname} FALSE)
    set(${ProjectIsRootVarname}
        FALSE
        PARENT_SCOPE)
    tmMessage("The project ${PROJECT_NAME} is NOT the root project")
  endif()

  # Configure some project settings according to whether or not we are root
  if(${ProjectIsRootVarname})
    if(EXISTS "${PROJECT_SOURCE_DIR}/cmake")
      set(CMAKE_MODULE_PATH
          "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH}
          PARENT_SCOPE)
      tmMessage("Added .cmake files for project ${PROJECT_NAME}")
    endif()
    # Configure the output-directory for SHARED libraries. For more information:
    # https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html, and
    # go to the section on library-output-artifacts for the details
    if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
      # If used as root project, then send all to this path
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
          "${CMAKE_BINARY_DIR}/libs"
          PARENT_SCOPE)
      tmMessage("Sending generated SHARED libraries to OWN build directory")
    else()
      # If it's not the root project, then use the user-defined output
      # directory. This might be required for installation by the user
      tmMessage("Sending generated SHARED libraries to USER-DEFINED directory")
    endif()
    # Configure the output-directory for STATIC libraries. For more information:
    # https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html, and
    # go to the section on archive-output-artifacts for the details
    if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
      # If used as root project, then send all to this path
      set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
          "${CMAKE_BINARY_DIR}/libs"
          PARENT_SCOPE)
      tmMessage("Sending generated STATIC libraries to OWN build directory")
    else()
      # If it's not the root project, then use the user-defined output
      # directory. This might be required for installation by the user
      tmMessage("Sending generated STATIC libraries to USER-DEFINED directory")
    endif()
    # Generate Position Independent Code (-fPIC), as bindings will need this.
    # Note that this is only set by the root-project (propagate from the root)
    if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
      tmMessage("Setting up -fPIC (Position Independent Code generation)")
      set(CMAKE_POSITION_INDEPENDENT_CODE
          ON
          PARENT_SCOPE)
    endif()
    # Export compile commands (used by clangd and other static analysis tools)
    if(NOT CMAKE_EXPORT_COMPILE_COMMANDS)
      tmMessage("Generating compile commands for static analysis tools")
      set(CMAKE_EXPORT_COMPILE_COMMANDS
          ON
          PARENT_SCOPE)
    endif()
    # Make sure that if the user doesn't provide CMAKE_INSTALL_PREFIX, we then
    # use a default path for installation (relative to build). We only make sure
    # in the case we're the main project. If not, then the main project should
    # handle this
    if(NOT CMAKE_INSTALL_PREFIX)
      set(CMAKE_INSTALL_PREFIX
          "${CMAKE_BINARY_DIR}/install"
          PARENT_SCOPE)
      set(CMAKE_INSTALL_INCLUDEDIR
          "${CMAKE_INSTALL_PREFIX}/include"
          PARENT_SCOPE)
      set(CMAKE_INSTALL_LIBDIR
          "${CMAKE_INSTALL_PREFIX}/lib"
          PARENT_SCOPE)
      set(CMAKE_INSTALL_BINDIR
          "${CMAKE_INSTALL_PREFIX}/bin"
          PARENT_SCOPE)
      set(CMAKE_INSTALL_DOCDIR
          "${CMAKE_INSTALL_PREFIX}/doc"
          PARENT_SCOPE)
    endif()
  endif()

  # Expose some extra variables to the parent context
  set(PROJECT_NAME_UPPER
      ${ProjectNameUpper}
      PARENT_SCOPE)
  set(PROJECT_IS_ROOT_VARNAME
      ${ProjectIsRootVarname}
      PARENT_SCOPE)
endfunction()

# Helper function that setups compiler flags and features to the given target
function(tmSetupCompileProperties)
  set(oneValueArgs PROJECT TARGET USE_SIMD USE_INLINE)
  cmake_parse_arguments(TM_SETUP "" "${oneValueArgs}" "" ${ARGN})

  if((NOT DEFINED TM_SETUP_PROJECT) OR (NOT DEFINED TM_SETUP_TARGET))
    tmMessage(
      "tmSetupCompileProperties: must provide at least PROJECT and TARGET"
      LOG_LEVEL FATAL_ERROR)
    return()
  endif()

  if(NOT TARGET ${TM_SETUP_TARGET})
    tmMessage("Tried baking compiler information into a non-target object"
              LOG_LEVEL WARNING)
    return()
  endif()

  # Make sure we're following the convention of setting flags as UPPER_CASE
  string(TOUPPER "${TM_SETUP_PROJECT}" TM_SETUP_PROJECT_NAME)

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_definitions(
      ${TM_SETUP_TARGET} INTERFACE -D${TM_SETUP_PROJECT_NAME}_COMPILER_CLANG)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_definitions(
      ${TM_SETUP_TARGET} INTERFACE -D${TM_SETUP_PROJECT_NAME}_COMPILER_GCC)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_definitions(
      ${TM_SETUP_TARGET} INTERFACE -D${TM_SETUP_PROJECT_NAME}_COMPILER_MSVC)
  endif()

  # Make sure that we don't re-define the make_unique if it's already exposed
  if(MSVC)
    target_compile_options(${TM_SETUP_TARGET} INTERFACE "/Zc:__cplusplus")
    target_compile_options(${TM_SETUP_TARGET} INTERFACE "/permissive-")
  endif()

  if(TM_SETUP_USE_SIMD)
    target_compile_definitions(${TM_SETUP_TARGET}
                               INTERFACE -D${TM_SETUP_PROJECT_NAME}_SSE_ENABLED)
    # ~~~
    # testing only SSE
    # target_compile_definitions(${TM_SETUP_TARGET}
    #                            INTERFACE -D${TM_SETUP_PROJECT_NAME}_AVX_ENABL)
    # ~~~
    # Enable compile-options according to each compiler variant
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
      target_compile_options(${TM_SETUP_TARGET} INTERFACE -msse -msse2 -msse4.1
                                                          -mavx)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
      target_compile_options(
        ${TM_SETUP_TARGET} INTERFACE /arch:SSE /arch:SSE2 /arch:SSE4.1
                                     /arch:AVX)
    else()
      tmMessage(
        "We don't yet support SIMD for compiler '${CMAKE_CXX_COMPILER_ID}'"
        LOG_LEVEL WARNING)
    endif()
  endif()

  if(TM_SETUP_USE_INLINE)
    target_compile_definitions(
      ${TM_SETUP_TARGET} INTERFACE -D${TM_SETUP_PROJECT_NAME}_FORCE_INLINE)
  endif()

endfunction()

# Helper macro that shows various settings obtained during configuration
function(tmPrintSummary)
  # cmake-lint: disable=R0915
  set(oneValueArgs TARGET)
  cmake_parse_arguments(TM "" "${oneValueArgs}" "" ${ARGN})

  if(NOT TARGET ${TM_TARGET})
    tmMessage("Tried printing summary of a non-target: [${TM_TARGET}]"
              LOG_LEVEL WARNING)
    return()
  endif()

  # Get the information set into the target
  get_target_property(TM_TARGET_TYPE ${TM_TARGET} TYPE)
  if(${TM_TARGET_TYPE} STREQUAL "INTERFACE_LIBRARY")
    get_target_property(TM_COMPILE_FEATURES ${TM_TARGET}
                        INTERFACE_COMPILE_FEATURES)
    get_target_property(TM_COMPILE_OPTIONS ${TM_TARGET}
                        INTERFACE_COMPILE_OPTIONS)
    get_target_property(TM_COMPILE_DEFINITIONS ${TM_TARGET}
                        INTERFACE_COMPILE_DEFINITIONS)
  elseif(${TM_TARGET} MATCHES "LIBRARY|EXECUTABLE")
    get_target_property(TM_COMPILE_FEATURES ${TM_TARGET} COMPILE_FEATURES)
    get_target_property(TM_COMPILE_OPTIONS ${TM_TARGET} COMPILE_OPTIONS)
    get_target_property(TM_COMPILE_DEFINITIONS ${TM_TARGET} COMPILE_DEFINITIONS)
  endif()

  # The list of all valid options exposed by the project TinyMath. Notice that
  # this part is project specific, so we have to rewrite this macro on every
  # project we use (we could generalize it further, but for now this works ok)
  set(optionsArgs PYTHON_BINDINGS DOCS TESTS EXAMPLES SIMD INLINE)
  # cmake-format: off
  message("****************************************************")
  message("Build options summary for project ${PROJECT_NAME}")
  # General settings from cmake
  message("PROJECT_VERSION                : ${PROJECT_VERSION}")
  message("CMAKE_GENERATOR                : ${CMAKE_GENERATOR}")
  message("CMAKE_MODULE_PATH              : ${CMAKE_MODULE_PATH}")
  message("CMAKE_EXPORT_COMPILE_COMMANDS  : ${CMAKE_EXPORT_COMPILE_COMMANDS}")
  message("CMAKE_POSITION_INDEPENDENT_CODE: ${CMAKE_POSITION_INDEPENDENT_CODE}")
  message("CMAKE_CXX_COMPILER             : ${CMAKE_CXX_COMPILER}")
  message("CMAKE_BUILD_TYPE               : ${CMAKE_BUILD_TYPE}")
  message("CMAKE_LIBRARY_OUTPUT_DIRECTORY : ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
  message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY : ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
  message("CMAKE_RUNTIME_OUTPUT_DIRECTORY : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  message("CMAKE_C_FLAGS                  : ${CMAKE_C_FLAGS}")
  message("CMAKE_CXX_FLAGS                : ${CMAKE_CXX_FLAGS}")
  message("CMAKE_INSTALL_PREFIX           : ${CMAKE_INSTALL_PREFIX}")
  message("CMAKE_INSTALL_INCLUDEDIR       : ${CMAKE_INSTALL_INCLUDEDIR}")
  message("CMAKE_INSTALL_LIBDIR           : ${CMAKE_INSTALL_LIBDIR}")
  message("CMAKE_INSTALL_DOCDIR           : ${CMAKE_INSTALL_DOCDIR}")
  message("CMAKE_INSTALL_BINDIR           : ${CMAKE_INSTALL_BINDIR}")
  message("CMAKE_PREFIX_PATH              : ${CMAKE_PREFIX_PATH}")
  message("CMAKE_BUILD_RPATH              : ${CMAKE_BUILD_RPATH}")
  # Some messages from the msvc compiler
  if(MSVC)
    message("MSVC_VERSION                   : ${MSVC_VERSION}")
  endif()
  # Target information
  message("Target [${TM_TARGET}] info --------------------------------")
  message("COMPILE_FEATURES               : ${TM_COMPILE_FEATURES}")
  message("COMPILE_OPTIONS                : ${TM_COMPILE_OPTIONS}")
  message("COMPILE_DEFINITIONS            : ${TM_COMPILE_DEFINITIONS}")
  message("-----------------------------------------------------------")
  # Project-specific settings
  message("${PROJECT_IS_ROOT_VARNAME} > ${${PROJECT_IS_ROOT_VARNAME}}")
  foreach(varOption IN LISTS optionsArgs)
    set(var_name "${PROJECT_NAME_UPPER}_BUILD_${varOption}")
    set(var_value "${${PROJECT_NAME_UPPER}_BUILD_${varOption}}")
    message("${var_name} > ${var_value}")
  endforeach()
  message("****************************************************")
  # cmake-format: on
endfunction()
