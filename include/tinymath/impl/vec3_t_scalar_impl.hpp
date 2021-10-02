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

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Array3f& dst, const Array3f& lhs, const Array3f& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Array3f& dst, const Array3f& lhs, const Array3f& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale(Array3f& dst, float32_t scale, const Array3f& vec) -> void;

// ***************************************************************************//
//    Declarations for double-precision floating point numbers (float64_t)    //
// ***************************************************************************//
using Vec3d = Vector3<float64_t>;
using Array3d = Vec3d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Array3d& dst, const Array3d& lhs, const Array3d& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Array3d& dst, const Array3d& lhs, const Array3d& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale(Array3d& dst, float64_t scale, const Array3d& vec) -> void;

}  // namespace scalar
}  // namespace math
}  // namespace tiny
