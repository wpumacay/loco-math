#if defined(TINYMATH_SSE_ENABLED)

#include <xmmintrin.h>

#include <tinymath/impl/vec3_t_sse_impl.hpp>

namespace tiny {
namespace math {
namespace sse {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Vector3<float32_t>::BufferType& dst,
                const Vector3<float32_t>::BufferType& lhs,
                const Vector3<float32_t>::BufferType& rhs) -> void {  // NOLINT
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    _mm_storeu_ps(dst.data(), xmm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Vector3<float32_t>::BufferType& dst,
                const Vector3<float32_t>::BufferType& lhs,
                const Vector3<float32_t>::BufferType& rhs) -> void {  // NOLINT
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_result = _mm_sub_ps(xmm_lhs, xmm_rhs);
    _mm_storeu_ps(dst.data(), xmm_result);
}

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
