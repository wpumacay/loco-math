<!--
@todo(wilbert): generalize this process a bit:
  * If using a static-site generator (e.g. HUGO/Jekyll):
    - Choose a theme/template
    - Could write a script that creates this from a template .md and .json data
  * If using just markdown files
    - Could write a script that creates this from a template .md and .json data
    - -->
# Dashboard

Here you can find information related to the current status of the projects, e.g.
`build status`, current `todo-list`, view of `issues` and `pull requests`, etc.

## Project Overview

This is a C/C++ project that implements a simple math-library designed for
**Computer Graphics** and **Robotics applications**. Our niche is **2D** and
**3D** computations for these applications, and taking advantage of this
constraint we try to support both **scalar** and **vectorized (SIMD)**
implementations of the various operations defined for our types.

## Build Status

|      OS      |  Flavor  | Vectorization |  Status  |
| ------------ | -------- | ------------- |--------- |
|   `Linux`    | <ul><li>`ubuntu-20.04`</li><li>`ubuntu-18.04`</li></ul> | `SIMD (SSE\|AVX)` | [![`ci-linux`][0]][1]   |
|   `Windows`  | <ul><li>`windows-2019`</li></ul>                        | `Not tested`      | [![`ci-windows`][2]][3] |
|   `MacOS`    | <ul><li>`macos-11`</li></ul>                            | `Not tested`      | [![`ci-macos`][4]][5]   |

## To-do list

- [ ] Generate `Python Bindings` for the types created so far
- [ ] Update CI to consider `SSE-AVX` as options in the build matrix
- [ ] Implement `quat_t` type for quaternions (type definition and API)
- [ ] Implement the required kernels for the operations defined by the `quat_t`
  type (both `scalar` and `simd-vectorized`)
- [ ] Implement `vec2_t` type for 2d-vectors :sweat_smile: (type definition and
  API), as well as the required kernels for the operations defined by this type
- [ ] Implement `mat3_t` type for 3x3 matrices :sweat_smile: (type definition
  and API), as well as the required kernels for the operations defined
- [ ] Implement `transform_t` type to represent transformations without having
  to use 4x4 matrices. Instead, we should use a `quaternion` for orientation and
  a single `3d-vector` for position (**scale** might be required for CG stuff)
- [ ] Implement factory functions for the `transform_t` type (e.g. Cg and Robo
  related ones)

[0]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-linux.yml/badge.svg> (ci-linux-badge)
[1]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-linux.yml> (ci-linux-link)
[2]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-windows.yml/badge.svg> (ci-windows-badge)
[3]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-windows.yml> (ci-windows-link)
[4]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-macos.yml/badge.svg> (ci-macos-badge)
[5]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-macos.yml> (ci-macos-link)
