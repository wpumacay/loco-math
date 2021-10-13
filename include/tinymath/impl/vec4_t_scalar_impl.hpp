#pragma once

#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//    Declarations for single-precision floating point numbers (float32_t)    //
// ***************************************************************************//
using Vec4f = Vector4<float32_t>;
using Array4f = Vec4f::BufferType;

auto kernel_add_v4f(Array4f& dst, const Array4f& lhs, const Array4f& rhs)
    -> void;

auto kernel_sub_v4f(Array4f& dst, const Array4f& lhs, const Array4f& rhs)
    -> void;

auto kernel_scale_v4f(Array4f& dst, float32_t scale, const Array4f& vec)
    -> void;

auto kernel_dot_v4f(const Array4f& lhs, const Array4f& rhs) -> float32_t;

// ***************************************************************************//
//    Declarations for double-precision floating point numbers (float64_t)    //
// ***************************************************************************//
using Vec4d = Vector4<float64_t>;
using Array4d = Vec4d::BufferType;

auto kernel_add_v4d(Array4d& dst, const Array4d& lhs, const Array4d& rhs)
    -> void;

auto kernel_sub_v4d(Array4d& dst, const Array4d& lhs, const Array4d& rhs)
    -> void;

auto kernel_scale_v4d(Array4d& dst, float64_t scale, const Array4d& vec)
    -> void;

auto kernel_dot_v4d(const Array4d& lhs, const Array4d& rhs) -> float64_t;

}  // namespace scalar
}  // namespace math
}  // namespace tiny
