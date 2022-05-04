#pragma once

#include <cmath>
#include <loco/math/mat4_t.hpp>
#include <utility>

namespace loco {
namespace math {
namespace scalar {

template <typename T>
using Mat4Buffer = typename Matrix4<T>::BufferType;

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
using SFINAE_MAT4_SCALAR_GUARD =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_transpose_inplace_mat4(Mat4Buffer<T>& cols) -> void {
    for (uint32_t col = 1; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (uint32_t row = 0; row < Matrix4<T>::MATRIX_NDIM; ++row) {
            std::swap(cols[col][row], cols[row][col]);
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] + rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] - rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_mat4(Mat4Buffer<T>& dst, T scale,
                                 const Mat4Buffer<T>& mat) -> void {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = scale * mat[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                                  const Mat4Buffer<T>& rhs) -> void {
    // We're assumming that dst is zero-initialized (default-constructor)
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (uint32_t row = 0; row < Matrix4<T>::MATRIX_NDIM; ++row) {
            for (uint32_t k = 0; k < Matrix4<T>::MATRIX_NDIM; ++k) {
                dst[col][row] += lhs[k][row] * rhs[col][k];
            }
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_vec_mat4(const Mat4Buffer<T>& mat,
                                      const Vec4Buffer<T>& vec) -> Vector4<T> {
    // Express as a linear combination of the columns of the matrix
    return vec[0] * mat[0] + vec[1] * mat[1] + vec[2] * mat[2] +
           vec[3] * mat[3];
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_hadamard_mat4(Mat4Buffer<T>& dst,
                                    const Mat4Buffer<T>& lhs,
                                    const Mat4Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] * rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_compare_eq_mat4(const Mat4Buffer<T>& lhs,
                                      const Mat4Buffer<T>& rhs) -> bool {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            if (std::abs(lhs[col][idx] - rhs[col][idx]) >
                static_cast<T>(loco::math::EPS)) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace scalar
}  // namespace math
}  // namespace loco
