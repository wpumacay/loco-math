# ~~~
# CMake configuration for third-party dependencies.
#
# Dependencies:
# * pybind11
# * catch2
#
# - Based on the superbuild script by jeffamstutz for ospray
#   https://github.com/jeffamstutz/superbuild_ospray/blob/main/macros.cmake
# - Based on MuJoCo's helper find_or_fetch content macro
#   https://github.com/deepmind/mujoco/blob/main/cmake/FindOrFetch.cmake
# ~~~

set(MATH3D_DEP_VERSION_catch2
    182c910b4b63ff587a3440e08f84f70497e49a81 # Release 2.13.10
    CACHE STRING "Version of Catch2 to be fetched (used for unittests)")

set(MATH3D_DEP_VERSION_pybind11
    a2e59f0e7065404b44dfe92a28aca47ba1378dc4 # Release v2.13.6
    CACHE STRING "Version of PyBind11 to be fetched (used for python bindings)")

set(MATH3D_DEP_VERSION_fast_noise_lite
    7ccfbc16eb1c932568f177d63a9ba51d89bbe516 # Release v1.1.1
    CACHE STRING "Version of FastNoiseLite to be fetched")

mark_as_advanced(MATH3D_DEP_VERSION_catch2)
mark_as_advanced(MATH3D_DEP_VERSION_pybind11)
mark_as_advanced(MATH3D_DEP_VERSION_fast_noise_lite)

# cmake-format: off
# ------------------------------------------------------------------------------
# Catch2 is used for generating unittests for our C++ codebase
# ------------------------------------------------------------------------------

set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_EXTRAS OFF CACHE BOOL "" FORCE)
set(CATCH_DEVELOPMENT_BUILD OFF CACHE BOOL "" FORCE)

loco_find_or_fetch_dependency(
  USE_SYSTEM_PACKAGE FALSE
  PACKAGE_NAME Catch2
  LIBRARY_NAME catch2
  GIT_REPO https://github.com/catchorg/Catch2.git
  GIT_TAG ${MATH3D_DEP_VERSION_catch2}
  GIT_PROGRESS FALSE
  GIT_SHALLOW TRUE
  TARGETS Catch2::Catch2
  EXCLUDE_FROM_ALL)

# Add custom scripts for test-case registration to the module path
if (catch2_POPULATED)
  list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
endif()

# ------------------------------------------------------------------------------
# Pybind11 is used for generating Python bindings for this project's C++ API.
# Notice that we're using a forked version in which usage of unique-ptr is
# allowed, as we use this functionality in some other parent projects
# ------------------------------------------------------------------------------

set(PYBIND11_TEST OFF CACHE BOOL "" FORCE)

loco_find_or_fetch_dependency(
  USE_SYSTEM_PACKAGE FALSE
  PACKAGE_NAME pybind11
  LIBRARY_NAME pybind11
  GIT_REPO https://github.com/pybind/pybind11.git
  GIT_TAG ${MATH3D_DEP_VERSION_pybind11}
  GIT_PROGRESS FALSE
  GIT_SHALLOW TRUE
  TARGETS pybind11::headers
  EXCLUDE_FROM_ALL)

# ------------------------------------------------------------------------------
# FastNoiseLite is used as backend for the noise functions. We just wrap the
# noise functions provided by the library
# ------------------------------------------------------------------------------

FetchContent_Declare(
  fastnoise
  GIT_REPOSITORY https://github.com/Auburn/FastNoiseLite.git
  GIT_TAG ${MATH3D_DEP_VERSION_fast_noise_lite}
  GIT_PROGRESS FALSE
  GIT_SHALLOW FALSE
  USES_TERMINAL_DOWNLOAD TRUE
)
FetchContent_GetProperties(fastnoise)

if (NOT fastnoise_POPULATED)
  FetchContent_Populate(fastnoise)
endif()

# cmake-format: on
