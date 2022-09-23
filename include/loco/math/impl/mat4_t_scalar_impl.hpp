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
    for (uint32_t col = 1; col < Matrix4<T>::MATRIX_SIZE; ++col) {
        for (uint32_t row = 0; row < Matrix4<T>::MATRIX_SIZE; ++row) {
            std::swap(cols[col][row], cols[row][col]);
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_SIZE; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_SIZE; ++idx) {
            dst[col][idx] = lhs[col][idx] + rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                               const Mat4Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_SIZE; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_SIZE; ++idx) {
            dst[col][idx] = lhs[col][idx] - rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_mat4(Mat4Buffer<T>& dst, T scale,
                                 const Mat4Buffer<T>& mat) -> void {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_SIZE; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_SIZE; ++idx) {
            dst[col][idx] = scale * mat[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_mat4(Mat4Buffer<T>& dst, const Mat4Buffer<T>& lhs,
                                  const Mat4Buffer<T>& rhs) -> void {
    // We're assumming that dst is zero-initialized (default-constructor)
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_SIZE; ++col) {
        for (uint32_t row = 0; row < Matrix4<T>::MATRIX_SIZE; ++row) {
            for (uint32_t k = 0; k < Matrix4<T>::MATRIX_SIZE; ++k) {
                dst[col][row] += lhs[k][row] * rhs[col][k];
            }
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_vec_mat4(Vec4Buffer<T>& dst,
                                      const Mat4Buffer<T>& mat,
                                      const Vec4Buffer<T>& vec) -> void {
    dst[0] = mat[0][0] * vec[0] + mat[1][0] * vec[1] + mat[2][0] * vec[2] +
             mat[3][0] * vec[3];
    dst[1] = mat[0][1] * vec[0] + mat[1][1] * vec[1] + mat[2][1] * vec[2] +
             mat[3][1] * vec[3];
    dst[2] = mat[0][2] * vec[0] + mat[1][2] * vec[1] + mat[2][2] * vec[2] +
             mat[3][2] * vec[3];
    dst[3] = mat[0][3] * vec[0] + mat[1][3] * vec[1] + mat[2][3] * vec[2] +
             mat[3][3] * vec[3];
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_hadamard_mat4(Mat4Buffer<T>& dst,
                                    const Mat4Buffer<T>& lhs,
                                    const Mat4Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_SIZE; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_SIZE; ++idx) {
            dst[col][idx] = lhs[col][idx] * rhs[col][idx];
        }
    }
}

template <typename T, SFINAE_MAT4_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_compare_eq_mat4(const Mat4Buffer<T>& lhs,
                                      const Mat4Buffer<T>& rhs) -> bool {
    for (uint32_t col = 0; col < Matrix4<T>::MATRIX_SIZE; ++col) {
        for (uint32_t idx = 0; idx < Matrix4<T>::MATRIX_SIZE; ++idx) {
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
