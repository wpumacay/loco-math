#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace avx {

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Vector3<float64_t>::BufferType& dst,
                const Vector3<float64_t>::BufferType& lhs,
                const Vector3<float64_t>::BufferType& rhs) -> void;  // NOLINT

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Vector3<float64_t>::BufferType& dst,
                const Vector3<float64_t>::BufferType& lhs,
                const Vector3<float64_t>::BufferType& rhs) -> void;  // NOLINT

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
