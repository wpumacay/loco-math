#if defined(TINYMATH_AVX_ENABLED)

#include <immintrin.h>

#include <tinymath/impl/vec4_t_avx_impl.hpp>

namespace tiny {
namespace math {
namespace avx {

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//
using Vec4d = Vector4<float64_t>;
using Array4d = Vec4d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v4d(Array4d& dst, const Array4d& lhs, const Array4d& rhs)
    -> void {
    auto ymm_lhs = _mm256_loadu_pd(lhs.data());
    auto ymm_rhs = _mm256_loadu_pd(rhs.data());
    auto ymm_result = _mm256_add_pd(ymm_lhs, ymm_rhs);
    // @todo(wilbert): check alignment (I thought it was already aligned :O)
    _mm256_storeu_pd(dst.data(), ymm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v4d(Array4d& dst, const Array4d& lhs, const Array4d& rhs)
    -> void {
    auto ymm_lhs = _mm256_loadu_pd(lhs.data());
    auto ymm_rhs = _mm256_loadu_pd(rhs.data());
    auto ymm_result = _mm256_sub_pd(ymm_lhs, ymm_rhs);
    _mm256_storeu_pd(dst.data(), ymm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v4d(Array4d& dst, float64_t scale, const Array4d& vec)
    -> void {
    auto ymm_scale = _mm256_set1_pd(scale);
    auto ymm_vector = _mm256_loadu_pd(vec.data());
    auto ymm_result = _mm256_mul_pd(ymm_scale, ymm_vector);
    _mm256_storeu_pd(dst.data(), ymm_result);
}

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
