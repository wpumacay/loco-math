#pragma once

#if defined(TINYMATH_SSE_ENABLED)

#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {
namespace sse {

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

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
