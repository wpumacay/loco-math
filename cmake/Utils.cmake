# ~~~
# This file exposes some utilities that are used throughout this project
# ~~~

# Helper macro that sets up a required git dependency for this project
macro(tmConfigureGitDependency)
    set(oneValueArgs TARGET REPO TAG)
    set(multiValueArgs BUILD_ARGS DEPENDS_ON)
    cmake_parse_arguments(GIT_DEP "" "${oneValueArgs}" "${multiValueArgs}"
                          ${ARGN})

    ExternalProject_Add(
        ${GIT_DEP_TARGET}
        GIT_REPOSITORY ${GIT_DEP_REPO}
        GIT_TAG ${GIT_DEP_TAG}
        GIT_PROGRESS ON
        PREFIX "${CMAKE_SOURCE_DIR}/third_party/${GIT_DEP_TARGET}"
        DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/third_party/${GIT_DEP_TARGET}"
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/third_party/${GIT_DEP_TARGET}/source"
        BINARY_DIR "${CMAKE_BINARY_DIR}/third_party/${GIT_DEP_TARGET}/build"
        STAMP_DIR "${CMAKE_BINARY_DIR}/third_party/${GIT_DEP_TARGET}/stamp"
        TMP_DIR "${CMAKE_BINARY_DIR}/third_party/${GIT_DEP_TARGET}/tmp"
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
                   -DCMAKE_GENERATOR=${CMAKE_GENERATOR}
                   -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                   -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
                   -DCMAKE_INSTALL_INCLUDEDIR=${CMAKE_INSTALL_INCLUDEDIR}
                   -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}
                   -DCMAKE_INSTALL_DOCDIR=${CMAKE_INSTALL_DOCDIR}
                   -DCMAKE_INSTALL_BINDIR=${CMAKE_INSTALL_BINDIR}
                   -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
                   ${GIT_DEP_BUILD_ARGS}
        BUILD_ALWAYS OFF)

    if(GIT_DEP_DEPENDS_ON)
        ExternalProject_Add_StepDependencies(${GIT_DEP_TARGET} configure
                                             ${GIT_DEP_DEPENDS_ON})
    endif()
endmacro()
