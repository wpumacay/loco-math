#pragma once

#if defined(TINYMATH_SSE_ENABLED)

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace sse {

// ***************************************************************************//
//    Declarations for single-precision floating point numbers (float32_t)    //
// ***************************************************************************//
using Vec3f = Vector3<float32_t>;
using Array3f = Vec3f::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v3f(Array3f& dst, float32_t scale, const Array3f& vec)
    -> void;

auto kernel_length_square_v3f(const Array3f& vec) -> float32_t;

auto kernel_length_v3f(const Array3f& vec) -> float32_t;

auto kernel_dot_v3f(const Array3f& lhs, const Array3f& rhs) -> float32_t;

// NOLINTNEXTLINE(runtime/references)
auto kernel_cross_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void;

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
