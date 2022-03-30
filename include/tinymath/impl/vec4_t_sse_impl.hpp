#pragma once

#if defined(TINYMATH_SSE_ENABLED)

#include <smmintrin.h>
#include <xmmintrin.h>

#include <tinymath/vec4_t.hpp>

/**
 * SSE instruction sets required for each kernel:
 *
 * - kernel_add_vec4        : SSE|SSE2
 * - kernel_sub_vec4        : SSE|SSE2
 * - kernel_scale_vec4      : SSE|SSE2
 * - kernel_hadamard_vec4   : SSE|SSE2
 * - kernel_dot_vec4        : SSE|SSE2|SSE4.1
 *
 * Notes:
 * 1. For SSE-float32:
 *    All elements of the buffer (4xf32, recall padding for alignment) fit into
 *    a single xmm register (128-bits <=> 4xfloat32)
 *
 * 2. For SSE-float64:
 *    Vector buffer contains 4xfloat64 <=> 256 bits <=> 32 bytes; however, xmm
 *    registers are only 16 bytes wide. We'll just unroll the loop once (make
 *    the point-wise operation twice on the registers, using lo-hi parts). Note
 *    that we also require support for SSE2 to use the appropriate intrinsics
 *    @todo(wilbert): try using static_cast and pointer-arithmetic replacements
 */

namespace tiny {
namespace math {
namespace sse {

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
using SFINAE_VEC4_F32_SSE_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat32<T>::value>::type*;

template <typename T>
using SFINAE_VEC4_F64_SSE_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat64<T>::value>::type*;

template <typename T, SFINAE_VEC4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    auto xmm_lhs_lo = _mm_load_pd(lhs.data());      // load first two doubles
    auto xmm_lhs_hi = _mm_load_pd(lhs.data() + 2);  // load the next two doubles
    auto xmm_rhs_lo = _mm_load_pd(rhs.data());
    auto xmm_rhs_hi = _mm_load_pd(rhs.data() + 2);
    auto xmm_result_lo = _mm_add_pd(xmm_lhs_lo, xmm_rhs_lo);
    auto xmm_result_hi = _mm_add_pd(xmm_lhs_hi, xmm_rhs_hi);
    _mm_store_pd(dst.data(), xmm_result_lo);
    _mm_store_pd(dst.data() + 2, xmm_result_hi);
}

template <typename T, SFINAE_VEC4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_result = _mm_sub_ps(xmm_lhs, xmm_rhs);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    auto xmm_lhs_lo = _mm_load_pd(lhs.data());
    auto xmm_lhs_hi = _mm_load_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_load_pd(rhs.data());
    auto xmm_rhs_hi = _mm_load_pd(rhs.data() + 2);
    auto xmm_result_lo = _mm_sub_pd(xmm_lhs_lo, xmm_rhs_lo);
    auto xmm_result_hi = _mm_sub_pd(xmm_lhs_hi, xmm_rhs_hi);
    _mm_store_pd(dst.data(), xmm_result_lo);
    _mm_store_pd(dst.data() + 2, xmm_result_hi);
}

template <typename T, SFINAE_VEC4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_vec4(Vec4Buffer<T>& dst, T scale,
                                 const Vec4Buffer<T>& vec) -> void {
    auto xmm_scale = _mm_set1_ps(scale);
    auto xmm_vector = _mm_load_ps(vec.data());
    auto xmm_result = _mm_mul_ps(xmm_scale, xmm_vector);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_vec4(Vec4Buffer<T>& dst, T scale,
                                 const Vec4Buffer<T>& vec) -> void {
    auto xmm_scale = _mm_set1_pd(scale);
    auto xmm_vector_lo = _mm_load_pd(vec.data());
    auto xmm_vector_hi = _mm_load_pd(vec.data() + 2);
    auto xmm_result_lo = _mm_mul_pd(xmm_scale, xmm_vector_lo);
    auto xmm_result_hi = _mm_mul_pd(xmm_scale, xmm_vector_hi);
    _mm_store_pd(dst.data(), xmm_result_lo);
    _mm_store_pd(dst.data() + 2, xmm_result_hi);
}

template <typename T, SFINAE_VEC4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_vec4(Vec4Buffer<T>& dst,
                                    const Vec4Buffer<T>& lhs,
                                    const Vec4Buffer<T>& rhs) -> void {
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    _mm_store_ps(dst.data(), _mm_mul_ps(xmm_lhs, xmm_rhs));
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_vec4(Vec4Buffer<T>& dst,
                                    const Vec4Buffer<T>& lhs,
                                    const Vec4Buffer<T>& rhs) -> void {
    auto xmm_lhs_lo = _mm_load_pd(lhs.data());
    auto xmm_lhs_hi = _mm_load_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_load_pd(rhs.data());
    auto xmm_rhs_hi = _mm_load_pd(rhs.data() + 2);
    _mm_store_pd(dst.data(), _mm_mul_pd(xmm_lhs_lo, xmm_rhs_lo));
    _mm_store_pd(dst.data() + 2, _mm_mul_pd(xmm_lhs_hi, xmm_rhs_hi));
}

template <typename T, SFINAE_VEC4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_dot_vec4(const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> T {
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_cond_prod = _mm_dp_ps(xmm_lhs, xmm_rhs, 0xf1);
    return _mm_cvtss_f32(xmm_cond_prod);
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_dot_vec4(const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> T {
    auto xmm_lhs_lo = _mm_load_pd(lhs.data());
    auto xmm_lhs_hi = _mm_load_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_load_pd(rhs.data());
    auto xmm_rhs_hi = _mm_load_pd(rhs.data() + 2);
    auto xmm_dot_lo = _mm_dp_pd(xmm_lhs_lo, xmm_rhs_lo, 0x31);
    auto xmm_dot_hi = _mm_dp_pd(xmm_lhs_hi, xmm_rhs_hi, 0x31);
    return _mm_cvtsd_f64(_mm_add_pd(xmm_dot_lo, xmm_dot_hi));
}

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
