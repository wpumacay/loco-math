#pragma once

#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//    Declarations for single-precision floating point numbers (float32_t)    //
// ***************************************************************************//
using Vec4f = Vector3<float32_t>;
using Array4f = Vec4f::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Array4f& dst, const Array4f& lhs, const Array4f& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Array4f& dst, const Array4f& lhs, const Array4f& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale(Array4f& dst, float32_t scale, const Array4f& vec) -> void;

// ***************************************************************************//
//    Declarations for double-precision floating point numbers (float64_t)    //
// ***************************************************************************//
using Vec4d = Vector3<float64_t>;
using Array4d = Vec4d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Array4d& dst, const Array4d& lhs, const Array4d& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Array4d& dst, const Array4d& lhs, const Array4d& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale(Array4d& dst, float64_t scale, const Array4d& vec) -> void;

}  // namespace scalar
}  // namespace math
}  // namespace tiny