# ~~~
# This file exposes some utilities that are used throughout this project
# ~~~

# Sets some path variables used within the scope of the dependency configuration
macro(tmGetProjectPaths varDependencyName)
    set(DEPENDENCY_NAME ${varDependencyName})
    set(DEPENDENCY_SOURCE_PATH ${DEPENDENCY_NAME}/source)
    set(DEPENDENCY_STAMP_PATH ${DEPENDENCY_NAME}/stamp)
    set(DEPENDENCY_BUILD_PATH ${DEPENDENCY_NAME}/build)
endmacro()

# Helper function that sets up the required dependencies for this project. These
# might come mainly from git repos, so we use either ExternalProject_Add or
# Fetch to grab and configure the imported targets from those libraries
function(tmConfigureDependencies)
    if(NOT PROJECT_NAME)
        return()
    endif()
    # If we're not the root project, then the root project must configure the
    # dependencies by itself (download, expose the targets, and build them)
    if(NOT ${PROJECT_IS_ROOT_VARNAME})
        return()
    endif()

    # Grab pybind11 from github and expose its targets
    tmGetProjectPaths(pybind11)
    ExternalProject_Add(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v2.7.1
        GIT_PROGRESS ON
        PREFIX ${CMAKE_SOURCE_DIR}/third_party/pybind11
        DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/third_party/pybind11
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/pybind11/source
        BINARY_DIR ${CMAKE_BINARY_DIR}/third_party/pybind11/build
        STAMP_DIR ${CMAKE_BINARY_DIR}/third_party/pybind11/stamp
        TMP_DIR ${CMAKE_BINARY_DIR}/third_party/pybind11/tmp
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                   -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                   -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
                   -DCMAKE_INSTALL_INCLUDEDIR=${CMAKE_INSTALL_INCLUDEDIR}
                   -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}
                   -DCMAKE_INSTALL_DOCDIR=${CMAKE_INSTALL_DOCDIR}
                   -DCMAKE_INSTALL_BINDIR=${CMAKE_INSTALL_BINDIR}
                   -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        BUILD_ALWAYS OFF)

endfunction()

macro(tmConfigurePythonBindings)

endmacro()

macro(tmConfigureExamples)

endmacro()

macro(tmConfigureDocs)

endmacro()
