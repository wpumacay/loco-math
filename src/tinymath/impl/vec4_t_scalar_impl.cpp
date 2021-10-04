#include <tinymath/impl/vec4_t_scalar_impl.hpp>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//
using Vec4f = Vector3<float32_t>;
using Array4f = Vec4f::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Array4f& dst, const Array4f& lhs, const Array4f& rhs) -> void {
    for (uint32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Array4f& dst, const Array4f& lhs, const Array4f& rhs) -> void {
    for (uint32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale(Array4f& dst, float32_t scale, const Array4f& vec) -> void {
    for (uint32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

auto kernel_length_square(const Array4f& vec) -> float32_t {
    return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
}

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//
using Vec4d = Vector3<float64_t>;
using Array4d = Vec4d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Array4d& dst, const Array4d& lhs, const Array4d& rhs) -> void {
    for (uint32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Array4d& dst, const Array4d& lhs, const Array4d& rhs) -> void {
    for (uint32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale(Array4d& dst, float64_t scale, const Array4d& vec) -> void {
    for (uint32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
