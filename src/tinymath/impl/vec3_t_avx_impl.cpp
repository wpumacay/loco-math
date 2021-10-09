#if defined(TINYMATH_AVX_ENABLED)

#include <immintrin.h>

#include <tinymath/impl/vec3_t_avx_impl.hpp>

namespace tiny {
namespace math {
namespace avx {

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//
using Vec3d = Vector3<float64_t>;
using Array3d = Vec3d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void {
    auto ymm_lhs = _mm256_loadu_pd(lhs.data());
    auto ymm_rhs = _mm256_loadu_pd(rhs.data());
    auto ymm_result = _mm256_add_pd(ymm_lhs, ymm_rhs);
    _mm256_storeu_pd(dst.data(), ymm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void {
    auto ymm_lhs = _mm256_loadu_pd(lhs.data());
    auto ymm_rhs = _mm256_loadu_pd(rhs.data());
    auto ymm_result = _mm256_sub_pd(ymm_lhs, ymm_rhs);
    _mm256_storeu_pd(dst.data(), ymm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v3d(Array3d& dst, float64_t scale, const Array3d& vec)
    -> void {
    auto ymm_scale = _mm256_set1_pd(scale);
    auto ymm_vector = _mm256_loadu_pd(vec.data());
    auto ymm_result = _mm256_mul_pd(ymm_scale, ymm_vector);
    _mm256_storeu_pd(dst.data(), ymm_result);
}

auto kernel_length_square_v3d(const Array3d& vec) -> float64_t {
    // Implementation based on this post: https://bit.ly/3lt3ts4
    // Instruction-sets required (AVX, SSE2)
    // -------------------------
    // AVX:_mm256_loadu_pd,_mm256_mul_pd,_mm256_hadd_pd,_mm256_extractf128_pd
    // SSE2: _mm_add_pd, _mm_sqrt_pd, _mm_cvtsd_f64
    auto ymm_v = _mm256_loadu_pd(vec.data());
    auto ymm_prod = _mm256_mul_pd(ymm_v, ymm_v);
    auto ymm_hsum = _mm256_hadd_pd(ymm_prod, ymm_prod);
    auto xmm_lo_sum = _mm256_extractf128_pd(ymm_hsum, 0);
    auto xmm_hi_sum = _mm256_extractf128_pd(ymm_hsum, 1);
    auto xmm_result = _mm_add_pd(xmm_lo_sum, xmm_hi_sum);
    return _mm_cvtsd_f64(xmm_result);
}

auto kernel_length_v3d(const Array3d& vec) -> float64_t {
    // Implementation based on this post: https://bit.ly/3lt3ts4
    // Instruction-sets required (AVX, SSE2)
    // -------------------------
    // AVX: _mm256_loadu_pd,_mm256_mul_pd,_mm256_hadd_pd,_mm256_extractf128_pd
    // SSE2: _mm_add_pd,_mm_sqrt_pd,_mm_cvtsd_f64
    auto ymm_v = _mm256_loadu_pd(vec.data());
    auto ymm_prod = _mm256_mul_pd(ymm_v, ymm_v);
    auto ymm_hsum = _mm256_hadd_pd(ymm_prod, ymm_prod);
    auto xmm_lo_sum = _mm256_extractf128_pd(ymm_hsum, 0);
    auto xmm_hi_sum = _mm256_extractf128_pd(ymm_hsum, 1);
    auto xmm_result = _mm_sqrt_pd(_mm_add_pd(xmm_lo_sum, xmm_hi_sum));
    return _mm_cvtsd_f64(xmm_result);
}

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
