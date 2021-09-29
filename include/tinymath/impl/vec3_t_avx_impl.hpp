#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace avx {

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_add(Vector3<float64_t>::BufferType& dst,
                                     const Vector3<float64_t>::BufferType& lhs,
                                     const Vector3<float64_t>::BufferType& rhs)
    -> void;

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_sub(Vector3<float64_t>::BufferType& dst,
                                     const Vector3<float64_t>::BufferType& lhs,
                                     const Vector3<float64_t>::BufferType& rhs)
    -> void;

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
