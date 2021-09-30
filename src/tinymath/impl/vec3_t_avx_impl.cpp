#if defined(TINYMATH_AVX_ENABLED)

#include <immintrin.h>

#include <tinymath/impl/vec3_t_avx_impl.hpp>

namespace tiny {
namespace math {
namespace avx {

// ***************************************************************************//
//   Implementations for double-precision floating point numbers (float64_t)  //
// ***************************************************************************//

// NOLINTNEXTLINE(runtime/references)
auto kernel_add(Vector3<float64_t>::BufferType& dst,
                const Vector3<float64_t>::BufferType& lhs,
                const Vector3<float64_t>::BufferType& rhs) -> void {  // NOLINT
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_result = _mm256_add_pd(ymm_lhs, ymm_rhs);
    _mm256_store_pd(dst.data(), ymm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub(Vector3<float64_t>::BufferType& dst,
                const Vector3<float64_t>::BufferType& lhs,
                const Vector3<float64_t>::BufferType& rhs) -> void {  // NOLINT
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_result = _mm256_sub_pd(ymm_lhs, ymm_rhs);
    _mm256_store_pd(dst.data(), ymm_result);
}

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
