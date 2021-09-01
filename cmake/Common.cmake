# ~~~
# This file exposes some helper functions that are used in this project All
# functions and macros are "namespaced" with the prefix "tm_" for tiny_math
# ~~~

# Helper function that displays a message to the console, prefixed with the name
# of the project (TinyMath) accordingly. Notice that we cam pass the log-level
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
    # @note: notice we're setting the variable twice (one for the local scope,
    # and another for the parent scope). This is required as we still use the
    # variable inside this function for some other checks (a bit of a hack >.<)
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
            list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
            tmMessage("Added .cmake files for project ${PROJECT_NAME}")
        endif()
        # Configure the output-directory (where libs/binaries go) accordingly
        if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
            # If used as root project, then send all to this path
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
                "${CMAKE_BINARY_DIR}/libs"
                PARENT_SCOPE)
            tmMessage("Sending generated libs/binaries to OWN build directory")
        else()
            # If it's not the root project, then use the user-defined output
            # directory. This might be required for installation by the user
            tmMessage(
                "Sending generated libs/binaries to USER-DEFINED directory")
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

# Helper macro that shows various settings obtained during configuration
function(tmPrintSummary)
    if(NOT PROJECT_NAME)
        return()
    endif()
    # The list of all valid options exposed by the project TinyMath. Notice that
    # this part is project specific, so we have to rewrite this macro on every
    # project we use (we could generalize it further, but for now this works ok)
    set(optionsArgs DOCS EXAMPLES PYTHON_BINDINGS)
    # cmake-format: off
    message("****************************************************")
    message("Build options summary for project ${PROJECT_NAME}")
    # General settings from cmake
    message("CMAKE_GENERATOR                            : ${CMAKE_GENERATOR}")
    message("CMAKE_C_COMPILER                           : ${CMAKE_C_COMPILER}")
    message("CMAKE_CXX_COMPILER                         : ${CMAKE_CXX_COMPILER}")
    message("CMAKE_BUILD_TYPE                           : ${CMAKE_BUILD_TYPE}")
    message("CMAKE_LIBRARY_OUTPUT_DIRECTORY             : ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    message("CMAKE_C_FLAGS                              : ${CMAKE_C_FLAGS}")
    message("CMAKE_CXX_FLAGS                            : ${CMAKE_CXX_FLAGS}")
    message("CMAKE_INSTALL_PREFIX                       : ${CMAKE_INSTALL_PREFIX}")
    message("CMAKE_INSTALL_INCLUDEDIR                   : ${CMAKE_INSTALL_INCLUDEDIR}")
    message("CMAKE_INSTALL_LIBDIR                       : ${CMAKE_INSTALL_LIBDIR}")
    message("CMAKE_INSTALL_DOCDIR                       : ${CMAKE_INSTALL_DOCDIR}")
    message("CMAKE_INSTALL_BINDIR                       : ${CMAKE_INSTALL_BINDIR}")
    message("CMAKE_PREFIX_PATH                          : ${CMAKE_PREFIX_PATH}")

    # Project-specific settings
    message("${PROJECT_IS_ROOT_VARNAME} > ${${PROJECT_IS_ROOT_VARNAME}}")
    foreach(varOption IN LISTS optionsArgs)
        message("${PROJECT_NAME_UPPER}_BUILD_${varOption} > ${${PROJECT_NAME_UPPER}_BUILD_${varOption}}")
    endforeach()
    message("****************************************************")
    # cmake-format: on
endfunction()
