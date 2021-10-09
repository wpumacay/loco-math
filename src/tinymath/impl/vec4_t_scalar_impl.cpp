#include <tinymath/impl/vec4_t_scalar_impl.hpp>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//
using Vec4f = Vector4<float32_t>;
using Array4f = Vec4f::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v4f(Array4f& dst, const Array4f& lhs, const Array4f& rhs)
    -> void {
    for (uint32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v4f(Array4f& dst, const Array4f& lhs, const Array4f& rhs)
    -> void {
    for (uint32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v4f(Array4f& dst, float32_t scale, const Array4f& vec)
    -> void {
    for (uint32_t i = 0; i < Vec4f::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

auto kernel_length_square_v4f(const Array4f& vec) -> float32_t {
    return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
}

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//
using Vec4d = Vector4<float64_t>;
using Array4d = Vec4d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v4d(Array4d& dst, const Array4d& lhs, const Array4d& rhs)
    -> void {
    for (uint32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v4d(Array4d& dst, const Array4d& lhs, const Array4d& rhs)
    -> void {
    for (uint32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v4d(Array4d& dst, float64_t scale, const Array4d& vec)
    -> void {
    for (uint32_t i = 0; i < Vec4d::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny