#pragma once

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

// Kernels for single-precision types (float32_t)
using Vec3f = Vector3<float32_t>;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Vec3f::BufferType& dst, const Vec3f::BufferType& lhs,
                const Vec3f::BufferType& rhs) -> void;  // NOLINT

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Vec3f::BufferType& dst, const Vec3f::BufferType& lhs,
                const Vec3f::BufferType& rhs) -> void;  // NOLINT

// Kernels for double-precision types (float64_t)
using Vec3d = Vector3<float64_t>;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Vec3d::BufferType& dst, const Vec3d::BufferType& lhs,
                const Vec3d::BufferType& rhs) -> void;  // NOLINT

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Vec3d::BufferType& dst, const Vec3d::BufferType& lhs,
                const Vec3d::BufferType& rhs) -> void;  // NOLINT

}  // namespace scalar
}  // namespace math
}  // namespace tiny
