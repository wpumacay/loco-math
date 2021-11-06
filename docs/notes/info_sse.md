# Some notes on how to handle SSE support

We make use of `SSE` when available, so there are some key components that we have
to make sure work correctly:

- [ ] Check support for `SSE` using `CMake` (up to the required version according to the kernels
      required by the library, so could be up to `SSE4.1`).
- [x] Implement kernels that make use of `SSE` using intrinsic functions.
- [x] Make sure that the alignment of the containers used to store the data in
  `user` land are properly aligned such that functions like `_mm_load_ps` don't
  segfault (currently we're using `_mm_loadu_ps` for unaligned data).

## Checking `SSE` support using CMake

- [ ] Finished implementation for checking CPU's SSE support?

---

The approach we'll most likely follow is the same as the one proposed in the
`AVX` notes, which makes use of the [`check_cxx_source_runs`][1] function from
`CMake` to check that some simple `SSE` snippets compile successfully.

## Implementing required SSE kernel functions using intrinsics

- [x] Finished implementation of required kernels for `vec2_t`, `vec3_t`, `vec4_t`?
- [ ] Finished implementation of required kernels for `quat4_t`, `euler_t` ?
- [ ] Finished implementation of required kernels for `mat2_t`, `mat3_t`, `mat4_t` ?
- [ ] Finished implementation of required kernels for `transform_t` ?

---

## Check correct alignment of data to be loaded in `xmm/ymm` registers

- [x] Finished correcting segfault issues with bad aligned data?

---

In the first implementation (`SSE`) we had some issues with alignment when using
the intrinsic `_mm_load_ps`, which works for aligned data, but I'm currently not
sure why `std::array<float, 4>` **is not aligned** (I might not be understanding
alignment correctly).
In the meantime, I'm checking some resources on alignment, and in case that container
is not aligned, we then can use the C++11 `alignas()` function to fix this issue,
or else we might so still have to use `_mm_loadu_ps` for unaligned data, as in
the commit [`35bb6c0`][3].

[0]: <https://github.com/PaddlePaddle/Paddle/blob/develop/cmake/simd.cmake> (sse-cmake-opt-0)
[1]: <https://github.com/PaddlePaddle/Paddle/commit/90234791f41dbda698f626145fffac785671c27b> (sse-cmake-opt-1)
[2]: <https://cmake.org/cmake/help/v3.15/module/CheckCXXSourceRuns.html> (sse-cmake-opt-2)
[3]: <https://github.com/wpumacay/tiny_math/commit/35bb6c001a5a39c21f8abaa6a48195868be37b88> (fix-unaligned-1)
