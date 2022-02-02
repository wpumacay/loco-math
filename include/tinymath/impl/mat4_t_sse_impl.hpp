#pragma once

#include "tinymath/common.hpp"
#if defined(TINYMATH_SSE_ENABLED)

#include <smmintrin.h>
#include <xmmintrin.h>

#include <tinymath/mat4_t.hpp>
#include <type_traits>

namespace tiny {
namespace math {
namespace sse {

template <typename T>
using Mat4Buffer = typename Matrix4<T>::BufferType;

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_MAT4_F32_SSE() -> void {
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
constexpr auto COMPILE_TIME_CHECKS_MAT4_F64_SSE() -> void {
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
using SFINAE_MAT4_F32_SSE_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat32<T>::value>::type*;

template <typename T>
using SFINAE_MAT4_F64_SSE_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat64<T>::value>::type*;

template <typename T, SFINAE_MAT4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): SSE implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): SSE implementation for mat4-f64 matrices
}

template <typename T, SFINAE_MAT4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): SSE implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): SSE implementation for mat4-f64 matrices
}

template <typename T, SFINAE_MAT4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_mat4(Mat4Buffer<T>& dst, T scale,
                                 const Mat4Buffer<T>& mat) -> void {
    // @todo(wilbert): SSE implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_mat4(Mat4Buffer<T>& dst, T scale,
                                 const Mat4Buffer<T>& mat) -> void {
    // @todo(wilbert): SSE implementation for mat4-f64 matrices
}

template <typename T, SFINAE_MAT4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_matmul_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                                  const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): SSE implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_matmul_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                                  const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): SSE implementation for mat4-f64 matrices
}

template <typename T, SFINAE_MAT4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_matmul_vec_mat4(Vec4Buffer<T>& dst,
                                      const Mat4Buffer<T>& mat,
                                      const Vec4Buffer<T>& vec) -> void {
    // @todo(wilbert): implement matmul mat4-vec4
}

template <typename T, SFINAE_MAT4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_mat4(Mat4Buffer<T>& dst,
                                    const Mat4Buffer<T>& lhs,
                                    const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): SSE implementation for mat4-f32 matrices
}

template <typename T, SFINAE_MAT4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_mat4(Mat4Buffer<T>& dst,
                                    const Mat4Buffer<T>& lhs,
                                    const Mat4Buffer<T>& rhs) -> void {
    // @todo(wilbert): SSE implementation for mat64-f64 matrices
}

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
