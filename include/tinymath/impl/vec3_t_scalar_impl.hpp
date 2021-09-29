#pragma once

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_add(Vector3<float32_t>::BufferType& dst,
                                     const Vector3<float32_t>::BufferType& lhs,
                                     const Vector3<float32_t>::BufferType& rhs)
    -> void;

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_sub(Vector3<float32_t>::BufferType& dst,
                                     const Vector3<float32_t>::BufferType& lhs,
                                     const Vector3<float32_t>::BufferType& rhs)
    -> void;

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

}  // namespace scalar
}  // namespace math
}  // namespace tiny
