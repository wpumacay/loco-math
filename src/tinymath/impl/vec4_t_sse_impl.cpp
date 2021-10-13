#if defined(TINYMATH_SSE_ENABLED)

#include <smmintrin.h>
#include <xmmintrin.h>

#include <tinymath/impl/vec4_t_sse_impl.hpp>

/**
 * SSE instruction sets required for each kernel:
 *
 * - kernel_add_v4f                 : SSE
 * - kernel_sub_v4f                 : SSE
 * - kernel_scale_v4f               : SSE
 * - kernel_hadamard_v4f            : SSE
 * - kernel_dot_v4f                 : SSE4.1 (_mm_dp_ps)
 */

namespace tiny {
namespace math {
namespace sse {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//
using Vec4f = Vector4<float32_t>;
using Array4f = Vec4f::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v4f(Array4f& dst, const Array4f& lhs, const Array4f& rhs)
    -> void {
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    // @todo(wilbert): check alignment (I thought it was already aligned :O)
    _mm_storeu_ps(dst.data(), xmm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v4f(Array4f& dst, const Array4f& lhs, const Array4f& rhs)
    -> void {
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_result = _mm_sub_ps(xmm_lhs, xmm_rhs);
    _mm_storeu_ps(dst.data(), xmm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v4f(Array4f& dst, float32_t scale, const Array4f& vec)
    -> void {
    auto xmm_scale = _mm_set1_ps(scale);
    auto xmm_vector = _mm_loadu_ps(vec.data());
    auto xmm_result = _mm_mul_ps(xmm_scale, xmm_vector);
    _mm_storeu_ps(dst.data(), xmm_result);
}

auto kernel_dot_v4f(const Array4f& lhs, const Array4f& rhs) -> float32_t {
    constexpr int32_t COND_PROD_MASK = 0xf1;
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_cond_prod = _mm_dp_ps(xmm_lhs, xmm_rhs, COND_PROD_MASK);
    return _mm_cvtss_f32(xmm_cond_prod);
}

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
