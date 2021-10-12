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

auto kernel_dot_v3d(const Array3d& lhs, const Array3d& rhs) -> float64_t {
    auto ymm_lhs = _mm256_loadu_pd(lhs.data());
    auto ymm_rhs = _mm256_loadu_pd(rhs.data());
    auto ymm_prod = _mm256_mul_pd(ymm_lhs, ymm_rhs);
    auto ymm_hsum = _mm256_hadd_pd(ymm_prod, ymm_prod);
    auto xmm_lo_sum = _mm256_extractf128_pd(ymm_hsum, 0);
    auto xmm_hi_sum = _mm256_extractf128_pd(ymm_hsum, 1);
    auto xmm_result = _mm_add_pd(xmm_lo_sum, xmm_hi_sum);
    return _mm_cvtsd_f64(xmm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_cross_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void {
    // Implementation adapted from @ian_mallett (https://bit.ly/3lu6pVe)
    auto vec_a = _mm256_loadu_pd(lhs.data());
    auto vec_b = _mm256_loadu_pd(rhs.data());

    // Construct both {a[1], a[2], a[0], 0} and {a[2], a[0], a[1], 0} **********
    auto tmp_0a = _mm256_permute2f128_pd(vec_a, vec_a, 0x21);
    auto tmp_1a = _mm256_permute_pd(vec_a, 0x09);
    auto tmp_2a = _mm256_permute_pd(tmp_0a, 0x05);
    // Constructing {a[2], a[0], a[1], 0}
    auto tmp_3a = _mm256_blend_pd(tmp_0a, tmp_1a, 0x0e);
    auto tmp_4a = _mm256_blend_pd(tmp_2a, tmp_3a, 0x0b);  // {a[2],a[0],a[1],0}
    // Constructing {a[1], a[2], a[0], 0}
    auto tmp_5a = _mm256_blend_pd(tmp_1a, tmp_2a, 0x02);
    auto tmp_6a = _mm256_blend_pd(tmp_0a, tmp_5a, 0x0b);  // {a[1],a[2],a[0],0}
    // *************************************************************************

    // Construct both {b[1], b[2], b[0], 0} and {b[2], b[0], b[1], 0} **********
    auto tmp_0b = _mm256_permute2f128_pd(vec_b, vec_b, 0x21);
    auto tmp_1b = _mm256_permute_pd(vec_b, 0x09);
    auto tmp_2b = _mm256_permute_pd(tmp_0b, 0x05);
    // Constructing {a[2], a[0], a[1], 0}
    auto tmp_3b = _mm256_blend_pd(tmp_0b, tmp_1b, 0x0e);
    auto tmp_4b = _mm256_blend_pd(tmp_2b, tmp_3b, 0x0b);  // {b[2],b[0],b[1],0}
    // Constructing {a[1], a[2], a[0], 0}
    auto tmp_5b = _mm256_blend_pd(tmp_1b, tmp_2b, 0x02);
    auto tmp_6b = _mm256_blend_pd(tmp_0b, tmp_5b, 0x0b);  // {b[1],b[2],b[0],0}
    // *************************************************************************
    _mm256_storeu_pd(dst.data(), _mm256_sub_pd(_mm256_mul_pd(tmp_6a, tmp_4b),
                                               _mm256_mul_pd(tmp_4a, tmp_6b)));
    // @todo(wilbert): replace permutation madness with "permute4x64_pd" (AVX2)
}

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
