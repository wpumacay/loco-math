# ~~~
# CMake configuration for third-party dependencies.
#
# Dependencies:
# * pybind11
# * catch2
#
# Based on the superbuild script by jeffamstutz for ospray
# https://github.com/jeffamstutz/superbuild_ospray/blob/main/macros.cmake
# ~~~

if(NOT LOCOMATH_IS_ROOT_PROJECT)
  return()
endif()

# cmake-format: off

# ------------------------------------------------------------------------------
# Pybind11 is used for generating Python bindings for this project's C++ API.
# Notice that we're using a forked version in which usage of unique-ptr is
# allowed, as we use this functionality in some other parent projects
# ------------------------------------------------------------------------------
loco_configure_git_dependency(
    TARGET pybind11
    REPO https://github.com/pybind/pybind11.git
    TAG v2.9.1
    BUILD_MODE ${CMAKE_BUILD_TYPE}
    BUILD_ARGS
      -DPYBIND11_TEST=OFF
    DISCARD_UNLESS LOCOMATH_BUILD_PYTHON_BINDINGS)

if(NOT pybind11_FOUND)
  loco_message("Requested Python bindings, but couldn't find Pybind11 :("
               LOG_LEVEL FATAL_ERROR)
endif()

# ------------------------------------------------------------------------------
# Catch2 is used for generating unittests for our C++ codebase
# ------------------------------------------------------------------------------
loco_configure_git_dependency(
    TARGET catch2
    REPO https://github.com/catchorg/Catch2.git
    TAG v2.13.8
    BUILD_TYPE ${CMAKE_BUILD_TYPE}
    BUILD_ARGS
      -DCATCH_INSTALL_DOCS=OFF
      -DCATCH_INSTALL_EXTRAS=OFF
      -DCATCH_DEVELOPMENT_BUILD=OFF
    DISCARD_UNLESS LOCOMATH_BUILD_TESTS)

if(NOT TARGET Catch2::Catch2)
  loco_message("Requested Catch2 support, but couldn't find Catch2 :("
               LOG_LEVEL FATAL_ERROR)
endif()

# cmake-format: on
