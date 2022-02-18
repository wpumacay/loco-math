#pragma once

#include <cmath>
#include <tinymath/mat4_t.hpp>
#include <utility>

namespace tiny {
namespace math {
namespace scalar {

template <typename T>
using Mat4Buffer = typename Matrix4<T>::BufferType;

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_MAT4_SCALAR() -> int {
    constexpr uint32_t EXPECTED_BUFFER_SIZE = 16;
    constexpr uint32_t EXPECTED_NUM_DIMENSIONS = 4;

    static_assert(Matrix4<T>::BUFFER_SIZE == EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must use 16 elements for the internal buffer");
    static_assert(Matrix4<T>::MATRIX_NDIM == EXPECTED_NUM_DIMENSIONS,
                  "4x4 matrices must have 4 as number of dimensions");
    static_assert(sizeof(Matrix4<T>) == sizeof(T) * EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must use exactly this many bytes of storage");
    static_assert(alignof(Matrix4<T>) == sizeof(T) * EXPECTED_BUFFER_SIZE,
                  "4x4 matrices must be aligned to its corresponding size");
    return 0;
}

template <typename T>
using SFINAE_MAT4_SCALAR_GUARD =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_transpose_inplace_mat4(Mat4Buffer<T>& cols) -> void {
    COMPILE_TIME_CHECKS_MAT4_SCALAR<T>();
    for (int32_t col = 1; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t row = 0; row < Matrix4<T>::MATRIX_NDIM; ++row) {
            std::swap(cols[col][row], cols[row][col]);
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_MAT4_SCALAR<T>();
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] + rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_MAT4_SCALAR<T>();
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] - rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_mat4(Mat4Buffer<T>& dst, T scale,
                                 const Mat4Buffer<T>& mat) -> void {
    COMPILE_TIME_CHECKS_MAT4_SCALAR<T>();
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = scale * mat[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_matmul_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                                  const Mat4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_MAT4_SCALAR<T>();
    // We're assumming that dst is zero-initialized (default-constructor)
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t row = 0; row < Matrix4<T>::MATRIX_NDIM; ++row) {
            for (int32_t k = 0; k < Matrix4<T>::MATRIX_NDIM; ++k) {
                dst[col][row] += lhs[k][row] * rhs[col][k];
            }
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_matmul_vec_mat4(const Mat4Buffer<T>& mat,
                                      const Vec4Buffer<T>& vec) -> Vector4<T> {
    COMPILE_TIME_CHECKS_MAT4_SCALAR<T>();
    // Express as a linear combination of the columns of the matrix
    return vec[0] * mat[0] + vec[1] * mat[1] + vec[2] * mat[2] +
           vec[3] * mat[3];
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_mat4(Mat4Buffer<T>& dst,
                                    const Mat4Buffer<T>& lhs,
                                    const Mat4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_MAT4_SCALAR<T>();
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] * rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_compare_eq_mat4(const Mat4Buffer<T>& lhs,
                                      const Mat4Buffer<T>& rhs) -> bool {
    COMPILE_TIME_CHECKS_MAT4_SCALAR<T>();
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            if (std::abs(lhs[col][idx] - rhs[col][idx]) > tiny::math::EPS<T>) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
