#pragma once

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//    Declarations for single-precision floating point numbers (float32_t)    //
// ***************************************************************************//
using Vec3f = Vector3<float32_t>;
using Array3f = Vec3f::BufferType;

auto kernel_add_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void;

auto kernel_sub_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void;

auto kernel_scale_v3f(Array3f& dst, float32_t scale, const Array3f& vec)
    -> void;

auto kernel_hadamard_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void;

auto kernel_length_square_v3f(const Array3f& vec) -> float32_t;

auto kernel_normalize_in_place_v3f(Array3f& vec) -> void;

auto kernel_dot_v3f(const Array3f& lhs, const Array3f& rhs) -> float32_t;

auto kernel_cross_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void;

// ***************************************************************************//
//    Declarations for double-precision floating point numbers (float64_t)    //
// ***************************************************************************//
using Vec3d = Vector3<float64_t>;
using Array3d = Vec3d::BufferType;

auto kernel_add_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void;

auto kernel_sub_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void;

auto kernel_scale_v3d(Array3d& dst, float64_t scale, const Array3d& vec)
    -> void;

auto kernel_hadamard_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void;

auto kernel_length_square_v3d(const Array3d& vec) -> float64_t;

auto kernel_normalize_in_place_v3d(Array3d& vec) -> void;

auto kernel_dot_v3d(const Array3d& lhs, const Array3d& rhs) -> float64_t;

auto kernel_cross_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void;

}  // namespace scalar
}  // namespace math
}  // namespace tiny
