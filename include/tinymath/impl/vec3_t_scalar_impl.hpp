#pragma once

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Vector3<float32_t>::BufferType& dst,
                const Vector3<float32_t>::BufferType& lhs,
                const Vector3<float32_t>::BufferType& rhs) -> void;  // NOLINT

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Vector3<float32_t>::BufferType& dst,
                const Vector3<float32_t>::BufferType& lhs,
                const Vector3<float32_t>::BufferType& rhs) -> void;  // NOLINT

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Vector3<float64_t>::BufferType& dst,
                const Vector3<float64_t>::BufferType& lhs,
                const Vector3<float64_t>::BufferType& rhs) -> void;  // NOLINT

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Vector3<float64_t>::BufferType& dst,
                const Vector3<float64_t>::BufferType& lhs,
                const Vector3<float64_t>::BufferType& rhs) -> void;  // NOLINT

}  // namespace scalar
}  // namespace math
}  // namespace tiny
