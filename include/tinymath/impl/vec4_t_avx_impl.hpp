#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {
namespace avx {

// ***************************************************************************//
//    Declarations for double-precision floating point numbers (float64_t)    //
// ***************************************************************************//
using Vec4d = Vector4<float64_t>;
using Array4d = Vec4d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Array4d& dst, const Array4d& lhs, const Array4d& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Array4d& dst, const Array4d& lhs, const Array4d& rhs) -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale(Array4d& dst, float64_t scale, const Array4d& vec) -> void;

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
