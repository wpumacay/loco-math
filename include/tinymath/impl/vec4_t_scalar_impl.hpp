#pragma once

#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//
using Vec4f = Vector4<float32_t>;
using Array4f = Vec4f::BufferType;

TM_INLINE auto kernel_add_v4f(Array4f& dst, const Array4f& lhs,
                              const Array4f& rhs) -> void {
    for (int32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

TM_INLINE auto kernel_sub_v4f(Array4f& dst, const Array4f& lhs,
                              const Array4f& rhs) -> void {
    for (int32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

TM_INLINE auto kernel_scale_v4f(Array4f& dst, float32_t scale,
                                const Array4f& vec) -> void {
    for (int32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

TM_INLINE auto kernel_hadamard_v4f(Array4f& dst, const Array4f& lhs,
                                   const Array4f& rhs) -> void {
    for (int32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] * rhs[i];
    }
}

TM_INLINE auto kernel_dot_v4f(const Array4f& lhs, const Array4f& rhs)
    -> float32_t {
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] +
           lhs[3] * rhs[3];
}

TM_INLINE auto kernel_compare_eq_v4f(const Array4f& lhs, const Array4f& rhs)
    -> bool {
    // Check all-close within an epsilon (EPS)
    constexpr auto EPSILON = tiny::math::EPS<float32_t>;
    return (std::abs(lhs[0] - rhs[0]) < EPSILON) &&
           (std::abs(lhs[1] - rhs[1]) < EPSILON) &&
           (std::abs(lhs[2] - rhs[2]) < EPSILON) &&
           (std::abs(lhs[3] - rhs[3]) < EPSILON);
}

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//
using Vec4d = Vector4<float64_t>;
using Array4d = Vec4d::BufferType;

TM_INLINE auto kernel_add_v4d(Array4d& dst, const Array4d& lhs,
                              const Array4d& rhs) -> void {
    for (int32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

TM_INLINE auto kernel_sub_v4d(Array4d& dst, const Array4d& lhs,
                              const Array4d& rhs) -> void {
    for (int32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

TM_INLINE auto kernel_scale_v4d(Array4d& dst, float64_t scale,
                                const Array4d& vec) -> void {
    for (int32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

TM_INLINE auto kernel_hadamard_v4d(Array4d& dst, const Array4d& lhs,
                                   const Array4d& rhs) -> void {
    for (int32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] * rhs[i];
    }
}

TM_INLINE auto kernel_dot_v4d(const Array4d& lhs, const Array4d& rhs)
    -> float64_t {
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] +
           lhs[3] * rhs[3];
}

TM_INLINE auto kernel_compare_eq_v4d(const Array4d& lhs, const Array4d& rhs)
    -> bool {
    // Check all-close within an epsilon (EPS)
    constexpr auto EPSILON = tiny::math::EPS<float64_t>;
    return (std::abs(lhs[0] - rhs[0]) < EPSILON) &&
           (std::abs(lhs[1] - rhs[1]) < EPSILON) &&
           (std::abs(lhs[2] - rhs[2]) < EPSILON) &&
           (std::abs(lhs[3] - rhs[3]) < EPSILON);
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
