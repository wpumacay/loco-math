#pragma once

#include <cmath>
#include <tinymath/mat4_t.hpp>
#include <utility>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//
using Mat4f = Matrix4<float32_t>;
using ArrayCols4f = Mat4f::BufferType;

TM_INLINE auto kernel_transpose_in_place_m4f(ArrayCols4f& cols) -> void {
    for (int32_t i = 1; i < Mat4f::MATRIX_NDIM; ++i) {
        for (int32_t j = 0; j < i; ++j) {
            std::swap(cols[i][j], cols[j][i]);
        }
    }
}

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//
using Mat4d = Matrix4<float64_t>;
using ArrayCols4d = Mat4d::BufferType;

TM_INLINE auto kernel_transpose_in_place_m4d(ArrayCols4d& cols) -> void {
    for (int32_t i = 1; i < Mat4d::MATRIX_NDIM; ++i) {
        for (int32_t j = 0; j < i; ++j) {
            std::swap(cols[i][j], cols[j][i]);
        }
    }
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
