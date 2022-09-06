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

# cmake-format: off
# ------------------------------------------------------------------------------
# Catch2 is used for generating unittests for our C++ codebase
# ------------------------------------------------------------------------------
loco_find_or_fetch_dependency(
  USE_SYSTEM_PACKAGE FALSE
  PACKAGE_NAME Catch2
  LIBRARY_NAME catch2
  GIT_REPO https://github.com/catchorg/Catch2.git
  GIT_TAG v2.x
  TARGETS Catch2::Catch2
  BUILD_ARGS
    -DCATCH_INSTALL_DOCS=OFF
    -DCATCH_INSTALL_EXTRAS=OFF
    -DCATCH_DEVELOPMENT_BUILD=OFF
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

loco_find_or_fetch_dependency(
  USE_SYSTEM_PACKAGE FALSE
  PACKAGE_NAME pybind11
  LIBRARY_NAME pybind11
  GIT_REPO https://github.com/RobotLocomotion/pybind11.git
  GIT_TAG drake
  TARGETS pybind11::headers
  BUILD_ARGS
    -DPYBIND11_TEST=OFF
  PATCH_COMMAND
    "${GIT_EXECUTABLE}"
    "apply"
    "-q"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/pybind11-fix-vs2022.patch"
    "||"
    "${CMAKE_COMMAND}"
    "-E"
    "true"
  EXCLUDE_FROM_ALL)

# cmake-format: on
