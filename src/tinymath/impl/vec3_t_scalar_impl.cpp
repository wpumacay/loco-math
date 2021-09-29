#include <tinymath/impl/vec3_t_scalar_impl.hpp>

namespace tiny {
namespace math {
namespace scalar {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_add(Vector3<float32_t>::BufferType& dst,
                                     const Vector3<float32_t>::BufferType& lhs,
                                     const Vector3<float32_t>::BufferType& rhs)
    -> void {
    for (uint32_t i = 0; i < Vector3<float32_t>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_sub(Vector3<float32_t>::BufferType& dst,
                                     const Vector3<float32_t>::BufferType& lhs,
                                     const Vector3<float32_t>::BufferType& rhs)
    -> void {
    for (uint32_t i = 0; i < Vector3<float32_t>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_add(Vector3<float64_t>::BufferType& dst,
                                     const Vector3<float64_t>::BufferType& lhs,
                                     const Vector3<float64_t>::BufferType& rhs)
    -> void {
    for (uint32_t i = 0; i < Vector3<float64_t>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_sub(Vector3<float64_t>::BufferType& dst,
                                     const Vector3<float64_t>::BufferType& lhs,
                                     const Vector3<float64_t>::BufferType& rhs)
    -> void {
    for (uint32_t i = 0; i < Vector3<float64_t>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
