<!--
@todo(wilbert): generalize this process a bit:
  * If using a static-site generator (e.g. HUGO/Jekyll):
    - Choose a theme/template
    - Could write a script that creates this from a template .md and .json data
  * If using just markdown files
    - Could write a script that creates this from a template .md and .json data

@todo(wilbert): copy this into index.md to serve as entrypoint for a static-site
  generator (either Jekyll or HUGO), and add required JS that uses the gh-api as
  required by this dashboard -->
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

## Feature list | Roadmap

These are the required types and operations that we intend to support for v1.0
of this project:

- [ ] **Vector** types:
  - [ ] `vec2_t` for representing 2d-vectors (used in some 2d stuff, like UVs)
  - [x] `vec3_t` for representing 3d-vectors (yeah, 3d-space is our friend)
  - [x] `vec4_t` for representing 4d-vectors (used for homogeneous transforms)
  - [ ] `vecn_t` for representing general linear arrays of data on which to
    operate or do transformations (terrain-generation, etc.)
- [ ] **Rotation** types:
  - [ ] `Rotation matrices (3x3)` for rotating 3d-vectors and changing basis
  - [ ] `Quaternions` for efficiently represent and store orientation
  - [ ] `Euler Angles` for a user-friendly representation of orientation
  - [ ] `Axis-Angle` for completeness :sweat_smile:
- [ ] **Transformations in 3D**:
  - [ ] `mat4_t`, used by various CG pipelines
  - [ ] `transform_t` type, used for intermediate transformations. This is
    stored as `quat + vec3` for more efficient storage and computation (avoid
    having to re-orthonormalize rotation matrices by keeping quaternions as
    unitary)
- [ ] **Helper functions**:
  - [ ] Factory functions to create `transform_t` and `mat4_t` common types,
    e.g. `rotationX|Y|Z`, `translation`, etc.
  - [ ] Factory functions for some other types, as they might be required in
    some use cases
  - [ ] `Casting`-like functions to transform one representation in one specific
    precision (e.g. `transform:float64`) to another required representation (e.g.
    `mat4:float32`)

## To-do list

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
- [ ] Generate `Python Bindings` for the types created so far :sweat_smile:
- [ ] Implement factory functions for the `transform_t` type (e.g. `ortho`,
  `perspective`, `rotationX|Y|Z`, etc.)
- [ ] `...`

## Issues
<!-- @todo(wilbert): use some JS + GH-Rest-API to grab and show issues -->

## Pull Requests
<!-- @todo(wilbert): use some JS + GH-Rest-API to grab and show PRs -->

[0]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-linux.yml/badge.svg> (ci-linux-badge)
[1]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-linux.yml> (ci-linux-link)
[2]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-windows.yml/badge.svg> (ci-windows-badge)
[3]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-windows.yml> (ci-windows-link)
[4]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-macos.yml/badge.svg> (ci-macos-badge)
[5]: <https://github.com/wpumacay/tiny_math/actions/workflows/ci-macos.yml> (ci-macos-link)
