# ~~~
# CMake configuration for third-party dependencies.
#
# Based on the superbuild script by jeffamstutz for ospray
# https://github.com/jeffamstutz/superbuild_ospray/blob/main/macros.cmake
#
# @todo(wilbert): Update the macro to use Fetch instead of ExternalProject_Add
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
    BUILD_ARGS -DPYBIND11_TEST=OFF)

tmConfigureGitDependency(
    TARGET googletest
    REPO https://github.com/google/googletest.git
    TAG release-1.11.0
    BUILD_ARGS -DBUILD_GMOCK=OFF)
# cmake-format: on
