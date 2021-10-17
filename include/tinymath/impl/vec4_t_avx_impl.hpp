#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <immintrin.h>

#include <tinymath/vec4_t.hpp>

/**
 * AVX instruction sets required for each kernel:
 *
 * - kernel_add_v4d                 : AVX
 * - kernel_sub_v4d                 : AVX
 * - kernel_scale_v4d               : AVX
 * - kernel_hadamard_v4d            : AVX
 * - kernel_dot_v4d                 : AVX + SSE2
 */

namespace tiny {
namespace math {
namespace avx {

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//
using Vec4d = Vector4<float64_t>;
using Array4d = Vec4d::BufferType;

TM_INLINE auto kernel_add_v4d(Array4d& dst, const Array4d& lhs,
                              const Array4d& rhs) -> void {
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_result = _mm256_add_pd(ymm_lhs, ymm_rhs);
    _mm256_store_pd(dst.data(), ymm_result);
}

TM_INLINE auto kernel_sub_v4d(Array4d& dst, const Array4d& lhs,
                              const Array4d& rhs) -> void {
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_result = _mm256_sub_pd(ymm_lhs, ymm_rhs);
    _mm256_store_pd(dst.data(), ymm_result);
}

TM_INLINE auto kernel_scale_v4d(Array4d& dst, float64_t scale,
                                const Array4d& vec) -> void {
    auto ymm_scale = _mm256_set1_pd(scale);
    auto ymm_vector = _mm256_load_pd(vec.data());
    auto ymm_result = _mm256_mul_pd(ymm_scale, ymm_vector);
    _mm256_store_pd(dst.data(), ymm_result);
}

TM_INLINE auto kernel_hadamard_v4d(Array4d& dst, const Array4d& lhs,
                                   const Array4d& rhs) -> void {
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    _mm256_store_pd(dst.data(), _mm256_mul_pd(ymm_lhs, ymm_rhs));
}

TM_INLINE auto kernel_dot_v4d(const Array4d& lhs, const Array4d& rhs)
    -> float64_t {
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_prod = _mm256_mul_pd(ymm_lhs, ymm_rhs);
    auto ymm_hsum = _mm256_hadd_pd(ymm_prod, ymm_prod);
    auto xmm_lo_sum = _mm256_extractf128_pd(ymm_hsum, 0);
    auto xmm_hi_sum = _mm256_extractf128_pd(ymm_hsum, 1);
    auto xmm_result = _mm_add_pd(xmm_lo_sum, xmm_hi_sum);
    return _mm_cvtsd_f64(xmm_result);
}

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
