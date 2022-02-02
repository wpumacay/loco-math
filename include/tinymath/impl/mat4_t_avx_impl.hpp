#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <immintrin.h>

#include <tinymath/mat4_t.hpp>

namespace tiny {
namespace math {
namespace avx {

template <typename T>
using Mat4Buffer = typename Matrix4<T>::BufferType;

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_MAT4_F32_AVX() -> void {
    constexpr uint32_t EXPECTED_BUFFER_SIZE = 16;
    constexpr uint32_t EXPECTED_NUM_DIMENSIONS = 4;

    static_assert(std::is_same<float, T>::value,
                  "4x4 f32 matrices should use single-precision floats");
    static_assert(Matrix4<T>::BUFFER_SIZE == EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must use 16 elements for the internal buffer");
    static_assert(Matrix4<T>::MATRIX_NDIM == EXPECTED_NUM_DIMENSIONS,
                  "4x4 matrices must have 4 as number of dimensions");
    static_assert(sizeof(Matrix4<T>) == sizeof(T) * EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must use exactly this many bytes of storage");
    static_assert(alignof(Matrix4<T>) == sizeof(T) * EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must be aligned to its corresponding size");
}

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_MAT4_F64_AVX() -> void {
    constexpr uint32_t EXPECTED_BUFFER_SIZE = 16;
    constexpr uint32_t EXPECTED_NUM_DIMENSIONS = 4;

    static_assert(std::is_same<double, T>::value,
                  "4x4 f32 matrices should use single-precision floats");
    static_assert(Matrix4<T>::BUFFER_SIZE == EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must use 16 elements for the internal buffer");
    static_assert(Matrix4<T>::MATRIX_NDIM == EXPECTED_NUM_DIMENSIONS,
                  "4x4 matrices must have 4 as number of dimensions");
    static_assert(sizeof(Matrix4<T>) == sizeof(T) * EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must use exactly this many bytes of storage");
    static_assert(alignof(Matrix4<T>) == sizeof(T) * EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must be aligned to its corresponding size");
}

template <typename T>
using SFINAE_MAT4_F32_AVX_GUARD =
    typename std::enable_if<CpuHasAVX<T>::value && IsFloat32<T>::value>::type*;

template <typename T>
using SFINAE_MAT4_F64_AVX_GUARD =
    typename std::enable_if<CpuHasAVX<T>::value && IsFloat64<T>::value>::type*;

// ***************************************************************************//
//                    Dispatch AVX-kernel for matrix addition                 //
// ***************************************************************************//

template <typename T, SFINAE_MAT4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f64 matrices
}

// ***************************************************************************//
//                 Dispatch AVX-kernel for matrix substraction                //
// ***************************************************************************//

template <typename T, SFINAE_MAT4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f64 matrices
}

// ***************************************************************************//
//                Dispatch AVX-kernel for matrix-scalar product               //
// ***************************************************************************//

template <typename T, SFINAE_MAT4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_mat4(Mat4Buffer<T>& dst, T scale,
                                 const Mat4Buffer<T>& mat) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_mat4(Mat4Buffer<T>& dst, T scale,
                                 const Mat4Buffer<T>& mat) -> void {
    // @todo(wilbert): AVX implementation for mat4-f64 matrices
}

// ***************************************************************************//
//                Dispatch AVX-kernel for matrix-matrix product               //
// ***************************************************************************//

template <typename T, SFINAE_MAT4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_matmul_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                                  const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_matmul_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                                  const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f64 matrices
}

// ***************************************************************************//
//             Dispatch AVX-kernel for matrix element-wise product            //
// ***************************************************************************//

template <typename T, SFINAE_MAT4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_mat4(Mat4Buffer<T>& dst,
                                    const Mat4Buffer<T>& lhs,
                                    const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_mat4(Mat4Buffer<T>& dst,
                                    const Mat4Buffer<T>& lhs,
                                    const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat64-f64 matrices
}

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
