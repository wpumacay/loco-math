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

if(TINYMATH_BUILD_PYTHON_BINDINGS)
  # cmake-format: off
  tmConfigureGitDependency(
      TARGET pybind11
      REPO https://github.com/pybind/pybind11.git
      TAG v2.9.1
      BUILD_MODE ${CMAKE_BUILD_TYPE}
      BUILD_ARGS
        -DPYBIND11_TEST=OFF)
  # cmake-format: on

  if(NOT pybind11_FOUND)
    tmMessage("Requested Python bindings, but couldn't find Pybind11 :("
              LOG_LEVEL WARNING)
    set(TINYMATH_BUILD_PYTHON_BINDINGS
        OFF
        PARENT_SCOPE)
  endif()
endif()

if(TINYMATH_BUILD_TESTS)
  # cmake-format: off
  tmConfigureGitDependency(
      TARGET catch2
      REPO https://github.com/catchorg/Catch2.git
      TAG v2.13.8
      BUILD_MODE ${CMAKE_BUILD_TYPE}
      BUILD_ARGS
        -DCATCH_INSTALL_DOCS=OFF
        -DCATCH_INSTALL_EXTRAS=OFF
        -DCATCH_DEVELOPMENT_BUILD=OFF)
  # cmake-format: on

  if(NOT TARGET Catch2::Catch2)
    tmMessage("Requested Catch2 support, but couldn't find Catch2 :(" LOG_LEVEL
              WARNING)
    set(TINYMATH_BUILD_TESTS
        OFF
        PARENT_SCOPE)
  endif()
endif()
