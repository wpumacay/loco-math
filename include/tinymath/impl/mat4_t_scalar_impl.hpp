#pragma once

#include <cmath>
#include <tinymath/mat4_t.hpp>
#include <utility>

namespace tiny {
namespace math {
namespace scalar {

template <typename T>
using ArrayCols = typename Matrix4<T>::BufferType;

template <typename T>
TM_INLINE auto kernel_transpose_inplace_mat4(ArrayCols<T>& cols) -> void {
    for (int32_t col = 1; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t row = 0; row < Matrix4<T>::MATRIX_NDIM; ++row) {
            std::swap(cols[col][row], cols[row][col]);
        }
    }
}

template <typename T>
TM_INLINE auto kernel_add_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                               const ArrayCols<T>& rhs) -> void {
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] + rhs[col][idx];
        }
    }
}

template <typename T>
TM_INLINE auto kernel_sub_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                               const ArrayCols<T>& rhs) -> void {
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] - rhs[col][idx];
        }
    }
}

template <typename T>
TM_INLINE auto kernel_scale_mat4(ArrayCols<T>& dst, T scale,
                                 const ArrayCols<T>& mat) -> void {
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = scale * mat[col][idx];
        }
    }
}

template <typename T>
TM_INLINE auto kernel_matmul_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                                  const ArrayCols<T>& rhs) -> void {
    // We're assumming that dst is zero-initialized (default-constructor)
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t row = 0; row < Matrix4<T>::MATRIX_NDIM; ++row) {
            for (int32_t k = 0; k < Matrix4<T>::MATRIX_NDIM; ++k) {
                dst[col][row] += lhs[k][row] * rhs[col][k];
            }
        }
    }
}

template <typename T>
TM_INLINE auto kernel_hadamard_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                                    const ArrayCols<T>& rhs) -> void {
    for (int32_t col = 0; col < Matrix4<T>::MATRIX_NDIM; ++col) {
        for (int32_t idx = 0; idx < Matrix4<T>::MATRIX_NDIM; ++idx) {
            dst[col][idx] = lhs[col][idx] * rhs[col][idx];
        }
    }
}

template <typename T>
TM_INLINE auto kernel_compare_eq_mat4(const ArrayCols<T>& lhs,
                                      const ArrayCols<T>& rhs) -> bool {
    constexpr auto EPSILON = tiny::math::EPS<T>;
    constexpr auto NDIM = Matrix4<T>::MATRIX_NDIM;
    for (int32_t col = 0; col < NDIM; ++col) {
        for (int32_t idx = 0; idx < NDIM; ++idx) {
            if (std::abs(lhs[col][idx] - rhs[col][idx]) > EPSILON) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
