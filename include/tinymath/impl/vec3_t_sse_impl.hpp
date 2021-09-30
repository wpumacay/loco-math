#pragma once

#if defined(TINYMATH_SSE_ENABLED)

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace sse {

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Vector3<float32_t>::BufferType& dst,
                const Vector3<float32_t>::BufferType& lhs,
                const Vector3<float32_t>::BufferType& rhs) -> void;  // NOLINT

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Vector3<float32_t>::BufferType& dst,
                const Vector3<float32_t>::BufferType& lhs,
                const Vector3<float32_t>::BufferType& rhs) -> void;  // NOLINT

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
