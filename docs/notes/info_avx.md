# Some notes on how to handle AVX and AVX2 support

We make use of `AVX` and `AVX2` when available, so there are some key components
that we have to make sure work correctly:

* Check support for `AVX` and `AVX2` support using `CMake`
* Implement kernels that make use of `AVX`, `AVX2` using intrinsic functions
* Do the required usage of `avx-based kernels` or `fallback kernels`

## Checking `AVX` support using CMake

Our first approach would be to use [`cmake_host_system_information`][1], but
unfortunately there's no check for `AVX` (only `SSE`). This would force us to
use a combination of checks outside of CMake that can be called within CMake,
like checking if a C/C++ file can be compiled or not. This is the approach that
is followed in [`this`][2] repo, where they make use of the CMake function
[`check_cxx_source_runs`][3] to check if a sample `AVX` snippet compiles
successfully.

[1]: <https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html>(avx-cmake-opt-1)
[2]: <https://github.com/PaddlePaddle/Paddle/commit/90234791f41dbda698f626145fffac785671c27b>(avx-cmake-opt-2)
[3]: <https://cmake.org/cmake/help/v3.15/module/CheckCXXSourceRuns.html>(avx-cmake-opt-3)
