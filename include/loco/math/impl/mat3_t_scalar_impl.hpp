#pragma once

#include <cmath>
#include <utility>

#include <loco/math/mat3_t.hpp>
#include "loco/math/common.hpp"

namespace loco {
namespace math {
namespace scalar {

template <typename T>
using Mat3Buffer = typename Matrix3<T>::BufferType;

template <typename T>
using Vec3Buffer = typename Matrix3<T>::ColumnType;

template <typename T>
using SFINAE_MAT3_SCALAR_GUARD =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_MAT3_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_transpose_inplace_mat3(Mat3Buffer<T>& mat) -> void {
    std::swap(mat[0][1], mat[1][0]);
    std::swap(mat[0][2], mat[2][0]);
    std::swap(mat[1][2], mat[2][1]);
}

template <typename T, SFINAE_MAT3_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix3<T>::MATRIX_SIZE; ++col) {
        for (uint32_t row = 0; row < Matrix3<T>::MATRIX_SIZE; ++row) {
            dst[col][row] = lhs[col][row] + rhs[col][row];
        }
    }
}

template <typename T, SFINAE_MAT3_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix3<T>::MATRIX_SIZE; ++col) {
        for (uint32_t row = 0; row < Matrix3<T>::MATRIX_SIZE; ++row) {
            dst[col][row] = lhs[col][row] - rhs[col][row];
        }
    }
}

template <typename T, SFINAE_MAT3_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_mat3(Mat3Buffer<T>& dst, T scale,
                                 const Mat3Buffer<T>& mat) -> void {
    for (uint32_t col = 0; col < Matrix3<T>::MATRIX_SIZE; ++col) {
        for (uint32_t row = 0; row < Matrix3<T>::MATRIX_SIZE; ++row) {
            dst[col][row] = scale * mat[col][row];
        }
    }
}

template <typename T, SFINAE_MAT3_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                                  const Mat3Buffer<T>& rhs) -> void {
    // We're assumming that dst is zero-initialized (default-constructor)
    for (uint32_t col = 0; col < Matrix3<T>::MATRIX_SIZE; ++col) {
        for (uint32_t row = 0; row < Matrix3<T>::MATRIX_SIZE; ++row) {
            for (uint32_t k = 0; k < Matrix3<T>::MATRIX_SIZE; ++k) {
                dst[col][row] += lhs[k][row] * rhs[col][k];
            }
        }
    }
}

template <typename T, SFINAE_MAT3_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_vec_mat3(Vec3Buffer<T>& dst,
                                      const Mat3Buffer<T>& mat,
                                      const Vec3Buffer<T>& vec) -> void {
    dst[0] = mat[0][0] * vec[0] + mat[1][0] * vec[1] + mat[2][0] * vec[2];
    dst[1] = mat[0][1] * vec[0] + mat[1][1] * vec[1] + mat[2][1] * vec[2];
    dst[2] = mat[0][2] * vec[0] + mat[1][2] * vec[1] + mat[2][2] * vec[2];
}

template <typename T, SFINAE_MAT3_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_hadamard_mat3(Mat3Buffer<T>& dst,
                                    const Mat3Buffer<T>& lhs,
                                    const Mat3Buffer<T>& rhs) -> void {
    for (uint32_t col = 0; col < Matrix3<T>::MATRIX_SIZE; ++col) {
        for (uint32_t row = 0; row < Matrix3<T>::MATRIX_SIZE; ++row) {
            dst[col][row] = lhs[col][row] * rhs[col][row];
        }
    }
}

template <typename T, SFINAE_MAT3_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_compare_eq_mat3(const Mat3Buffer<T>& lhs,
                                      const Mat3Buffer<T>& rhs) -> bool {
    for (uint32_t col = 0; col < Matrix3<T>::MATRIX_SIZE; ++col) {
        for (uint32_t row = 0; row < Matrix3<T>::MATRIX_SIZE; ++row) {
            if (std::abs(lhs[col][row] - rhs[col][row]) >
                static_cast<T>(loco::math::EPS)) {
                return false;
            }
        }
    }
}

}  // namespace scalar
}  // namespace math
}  // namespace loco
