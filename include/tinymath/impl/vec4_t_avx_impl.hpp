#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <immintrin.h>

#include <tinymath/vec4_t.hpp>

/**
 * AVX instruction sets required for each kernel:
 *
 * - kernel_add_vec4        : SSE|AVX
 * - kernel_sub_vec4        : SSE|AVX
 * - kernel_scale_vec4      : SSE|AVX
 * - kernel_hadamard_vec4   : SSE|AVX
 * - kernel_dot_vec4        : SSE|AVX|SSE2
 *
 * Notes:
 * 1. For AVX float32:
 *    _mm256_store functions could potentially write contiguous data, so we
 *    rather use SSE instructions and let the compiler use AVX instructions
 *    mixed with XMM registers instead of YMM registers. Another option would
 *    be to use `maskload` instead of `load` to avoid these out-of-bounds writes
 */

namespace tiny {
namespace math {
namespace avx {

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_VEC4_F32_AVX() -> void {
    static_assert(std::is_same<float, T>::value, "Must be using f32");
    static_assert(Vector4<T>::BUFFER_SIZE == 4,
                  "Must be using 4xf32 as aligned buffer");
    static_assert(Vector4<T>::VECTOR_NDIM == 4,
                  "Must be using 3xf32 for the elements of the vector");
    static_assert(
        sizeof(Vector4<T>) == sizeof(std::array<T, Vector4<T>::BUFFER_SIZE>),
        "Must use exactly this many bytes of storage");
    static_assert(
        alignof(Vector4<T>) == sizeof(std::array<T, Vector4<T>::BUFFER_SIZE>),
        "Must be aligned to its corresponding size");
}

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_VEC4_F64_AVX() -> void {
    static_assert(std::is_same<double, T>::value, "Must be using f64");
    static_assert(Vector4<T>::BUFFER_SIZE == 4,
                  "Must be using 4xf64 as aligned buffer");
    static_assert(Vector4<T>::VECTOR_NDIM == 4,
                  "Must be using 3xf64 for the elements of the vector");
    static_assert(
        sizeof(Vector4<T>) == sizeof(std::array<T, Vector4<T>::BUFFER_SIZE>),
        "Must use exactly this many bytes of storage");
    static_assert(
        alignof(Vector4<T>) == sizeof(std::array<T, Vector4<T>::BUFFER_SIZE>),
        "Must be aligned to its corresponding size");
}

template <typename T>
using SFINAE_VEC4_F32_AVX_GUARD =
    typename std::enable_if<CpuHasAVX<T>::value && IsFloat32<T>::value>::type*;

template <typename T>
using SFINAE_VEC4_F64_AVX_GUARD =
    typename std::enable_if<CpuHasAVX<T>::value && IsFloat64<T>::value>::type*;

template <typename T, SFINAE_VEC4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F32_AVX<T>();
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F64_AVX<T>();
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_result = _mm256_add_pd(ymm_lhs, ymm_rhs);
    _mm256_store_pd(dst.data(), ymm_result);
}

template <typename T, SFINAE_VEC4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F32_AVX<T>();
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_result = _mm_sub_ps(xmm_lhs, xmm_rhs);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F64_AVX<T>();
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_result = _mm256_sub_pd(ymm_lhs, ymm_rhs);
    _mm256_store_pd(dst.data(), ymm_result);
}

template <typename T, SFINAE_VEC4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_vec4(Vec4Buffer<T>& dst, T scale,
                                 const Vec4Buffer<T>& vec) -> void {
    COMPILE_TIME_CHECKS_VEC4_F32_AVX<T>();
    auto xmm_scale = _mm_set1_ps(scale);
    auto xmm_vector = _mm_load_ps(vec.data());
    auto xmm_result = _mm_mul_ps(xmm_scale, xmm_vector);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_vec4(Vec4Buffer<T>& dst, T scale,
                                 const Vec4Buffer<T>& vec) -> void {
    COMPILE_TIME_CHECKS_VEC4_F64_AVX<T>();
    auto ymm_scale = _mm256_set1_pd(scale);
    auto ymm_vector = _mm256_load_pd(vec.data());
    auto ymm_result = _mm256_mul_pd(ymm_scale, ymm_vector);
    _mm256_store_pd(dst.data(), ymm_result);
}

template <typename T, SFINAE_VEC4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_vec4(Vec4Buffer<T>& dst,
                                    const Vec4Buffer<T>& lhs,
                                    const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F32_AVX<T>();
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    _mm_store_ps(dst.data(), _mm_mul_ps(xmm_lhs, xmm_rhs));
}

template <typename T, SFINAE_VEC4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_vec4(Vec4Buffer<T>& dst,
                                    const Vec4Buffer<T>& lhs,
                                    const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F64_AVX<T>();
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    _mm256_store_pd(dst.data(), _mm256_mul_pd(ymm_lhs, ymm_rhs));
}

template <typename T, SFINAE_VEC4_F32_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_dot_vec4(const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> T {
    COMPILE_TIME_CHECKS_VEC4_F32_AVX<T>();
    constexpr int32_t COND_PROD_MASK = 0xf1;
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_cond_prod = _mm_dp_ps(xmm_lhs, xmm_rhs, COND_PROD_MASK);
    return _mm_cvtss_f32(xmm_cond_prod);
}

template <typename T, SFINAE_VEC4_F64_AVX_GUARD<T> = nullptr>
TM_INLINE auto kernel_dot_vec4(const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> T {
    COMPILE_TIME_CHECKS_VEC4_F64_AVX<T>();
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
