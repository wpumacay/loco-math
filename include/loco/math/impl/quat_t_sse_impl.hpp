#pragma once

#if defined(LOCOMATH_SSE_ENABLED)

#include <smmintrin.h>
#include <xmmintrin.h>

#include <loco/math/quat_t.hpp>

namespace loco {
namespace math {
namespace sse {

template <typename T>
using QuatBuffer = typename Quaternion<T>::BufferType;

template <typename T>
using SFINAE_QUAT_F32_SSE_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat32<T>::value>::type*;

template <typename T>
using SFINAE_QUAT_F64_SSE_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat64<T>::value>::type*;

template <typename T, SFINAE_QUAT_F32_SSE_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_quat(QuatBuffer<T>& dst, const QuatBuffer<T>& lhs,
                               const QuatBuffer<T>& rhs) -> void {
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    _mm_storeu_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_QUAT_F64_SSE_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_quat(QuatBuffer<T>& dst, const QuatBuffer<T>& lhs,
                               const QuatBuffer<T>& rhs) -> void {
    auto xmm_lhs_lo = _mm_loadu_pd(lhs.data());
    auto xmm_lhs_hi = _mm_loadu_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_loadu_pd(rhs.data());
    auto xmm_rhs_hi = _mm_loadu_pd(rhs.data() + 2);
    auto xmm_result_lo = _mm_add_pd(xmm_lhs_lo, xmm_rhs_lo);
    auto xmm_result_hi = _mm_add_pd(xmm_lhs_hi, xmm_rhs_hi);
    _mm_storeu_pd(dst.data(), xmm_result_lo);
    _mm_storeu_pd(dst.data() + 2, xmm_result_hi);
}

template <typename T, SFINAE_QUAT_F32_SSE_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_quat(QuatBuffer<T>& dst, const QuatBuffer<T>& lhs,
                               const QuatBuffer<T>& rhs) -> void {
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    _mm_storeu_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_QUAT_F64_SSE_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_quat(QuatBuffer<T>& dst, const QuatBuffer<T>& lhs,
                               const QuatBuffer<T>& rhs) -> void {
    auto xmm_lhs_lo = _mm_loadu_pd(lhs.data());
    auto xmm_lhs_hi = _mm_loadu_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_loadu_pd(rhs.data());
    auto xmm_rhs_hi = _mm_loadu_pd(rhs.data() + 2);
    auto xmm_result_lo = _mm_sub_pd(xmm_lhs_lo, xmm_rhs_lo);
    auto xmm_result_hi = _mm_sub_pd(xmm_lhs_hi, xmm_rhs_hi);
    _mm_storeu_pd(dst.data(), xmm_result_lo);
    _mm_storeu_pd(dst.data(), xmm_result_hi);
}

template <typename T, SFINAE_QUAT_F32_SSE_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_quat(QuatBuffer<T>& dst, T scale,
                                 const QuatBuffer<T>& quat) -> void {
    auto xmm_scale = _mm_set1_ps(scale);
    auto xmm_quat = _mm_loadu_ps(quat.data());
    auto xmm_result = _mm_mul_ps(xmm_scale, xmm_quat);
    _mm_storeu_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_QUAT_F64_SSE_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_quat(QuatBuffer<T>& dst, T scale,
                                 const QuatBuffer<T>& quat) -> void {
    auto xmm_scale = _mm_set1_pd(scale);
    auto xmm_quat_lo = _mm_loadu_pd(quat.data());
    auto xmm_quat_hi = _mm_loadu_pd(quat.data() + 2);
    auto xmm_result_lo = _mm_mul_pd(xmm_scale, xmm_quat_lo);
    auto xmm_result_hi = _mm_mul_pd(xmm_scale, xmm_quat_hi);
    _mm_storeu_pd(dst.data(), xmm_result_lo);
    _mm_storeu_pd(dst.data(), xmm_result_hi);
}

}  // namespace sse
}  // namespace math
}  // namespace loco

#endif  // LOCOMATH_SSE_ENABLED
