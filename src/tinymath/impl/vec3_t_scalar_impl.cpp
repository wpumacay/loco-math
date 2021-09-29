#include <tinymath/impl/vec3_t_scalar_impl.hpp>

namespace tiny {
namespace math {
namespace scalar {

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_add(Vector3<float32_t>::BufferType& dst,
                                     const Vector3<float32_t>::BufferType& lhs,
                                     const Vector3<float32_t>::BufferType& rhs)
    -> void {
    dst[0] = lhs[0] + rhs[0];
    dst[1] = lhs[1] + rhs[1];
    dst[2] = lhs[2] + rhs[2];
}

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_sub(Vector3<float32_t>::BufferType& dst,
                                     const Vector3<float32_t>::BufferType& lhs,
                                     const Vector3<float32_t>::BufferType& rhs)
    -> void {
    dst[0] = lhs[0] - rhs[0];
    dst[1] = lhs[1] - rhs[1];
    dst[2] = lhs[2] - rhs[2];
}

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_add(Vector3<float64_t>::BufferType& dst,
                                     const Vector3<float64_t>::BufferType& lhs,
                                     const Vector3<float64_t>::BufferType& rhs)
    -> void {
    dst[0] = lhs[0] + rhs[0];
    dst[1] = lhs[1] + rhs[1];
    dst[2] = lhs[2] + rhs[2];
}

// NOLINTNEXTLINE(runtime/references)
TINYMATH_INLINE_EXPR auto kernel_sub(Vector3<float64_t>::BufferType& dst,
                                     const Vector3<float64_t>::BufferType& lhs,
                                     const Vector3<float64_t>::BufferType& rhs)
    -> void {
    dst[0] = lhs[0] - rhs[0];
    dst[1] = lhs[1] - rhs[1];
    dst[2] = lhs[2] - rhs[2];
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
