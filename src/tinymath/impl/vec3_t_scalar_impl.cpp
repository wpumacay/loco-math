#include <cmath>
#include <tinymath/impl/vec3_t_scalar_impl.hpp>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//
using Vec3f = Vector3<float32_t>;
using Array3f = Vec3f::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void {
    for (uint32_t i = 0; i < Vec3f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void {
    for (uint32_t i = 0; i < Vec3f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v3f(Array3f& dst, float32_t scale, const Array3f& vec)
    -> void {
    for (uint32_t i = 0; i < Vec3f::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

auto kernel_length_square_v3f(const Array3f& vec) -> float32_t {
    return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
}

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//
using Vec3d = Vector3<float64_t>;
using Array3d = Vec3d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void {
    for (uint32_t i = 0; i < Vec3d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void {
    for (uint32_t i = 0; i < Vec3d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v3d(Array3d& dst, float64_t scale, const Array3d& vec)
    -> void {
    for (uint32_t i = 0; i < Vec3d::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

auto kernel_length_square_v3d(const Array3d& vec) -> float64_t {
    return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
