# ~~~
# CMake configuration for third-party dependencies.
#
# Based on the superbuild script by jeffamstutz for ospray
# https://github.com/jeffamstutz/superbuild_ospray/blob/main/macros.cmake
# ~~~

if(NOT TINYMATH_IS_ROOT_PROJECT)
    tmMessage("Third-party deps. should be handled by root" LOG_LEVEL TRACE)
    return()
endif()

# cmake-format: off
tmConfigureGitDependency(
    TARGET pybind11 
    REPO https://github.com/pybind/pybind11.git
    TAG v2.7.1
    BUILD_MODE Release
    BUILD_ARGS -DPYBIND11_TEST=OFF)

tmConfigureGitDependency(
    TARGET googletest
    REPO https://github.com/google/googletest.git
    TAG release-1.11.0
    BUILD_MODE Release
    BUILD_ARGS -DBUILD_GMOCK=OFF)
# cmake-format: on
