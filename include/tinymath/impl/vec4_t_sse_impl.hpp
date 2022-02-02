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
 * - kernel_dot_vec4        : SSE|SSE4.1 (_mm_dp_ps, _mm_dp_pd)
 */

namespace tiny {
namespace math {
namespace sse {

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_VEC4_F32_SSE() -> void {
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
constexpr auto COMPILE_TIME_CHECKS_VEC4_F64_SSE() -> void {
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
using SFINAE_VEC4_F32_SSE_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat32<T>::value>::type*;

template <typename T>
using SFINAE_VEC4_F64_SSE_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat64<T>::value>::type*;

template <typename T, SFINAE_VEC4_F32_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F32_SSE<T>();
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F64_SSE<T>();
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
    COMPILE_TIME_CHECKS_VEC4_F32_SSE<T>();
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_result = _mm_sub_ps(xmm_lhs, xmm_rhs);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F64_SSE<T>();
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
    COMPILE_TIME_CHECKS_VEC4_F32_SSE<T>();
    auto xmm_scale = _mm_set1_ps(scale);
    auto xmm_vector = _mm_load_ps(vec.data());
    auto xmm_result = _mm_mul_ps(xmm_scale, xmm_vector);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_vec4(Vec4Buffer<T>& dst, T scale,
                                 const Vec4Buffer<T>& vec) -> void {
    COMPILE_TIME_CHECKS_VEC4_F64_SSE<T>();
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
    COMPILE_TIME_CHECKS_VEC4_F32_SSE<T>();
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    _mm_store_ps(dst.data(), _mm_mul_ps(xmm_lhs, xmm_rhs));
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_vec4(Vec4Buffer<T>& dst,
                                    const Vec4Buffer<T>& lhs,
                                    const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_F64_SSE<T>();
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
    COMPILE_TIME_CHECKS_VEC4_F32_SSE<T>();
    constexpr int32_t COND_PROD_MASK = 0xf1;
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_cond_prod = _mm_dp_ps(xmm_lhs, xmm_rhs, COND_PROD_MASK);
    return _mm_cvtss_f32(xmm_cond_prod);
}

template <typename T, SFINAE_VEC4_F64_SSE_GUARD<T> = nullptr>
TM_INLINE auto kernel_dot_vec4(const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> T {
    COMPILE_TIME_CHECKS_VEC4_F64_SSE<T>();
    constexpr int32_t COND_PROD_MASK = 0x31;
    auto xmm_lhs_lo = _mm_load_pd(lhs.data());
    auto xmm_lhs_hi = _mm_load_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_load_pd(rhs.data());
    auto xmm_rhs_hi = _mm_load_pd(rhs.data() + 2);
    auto xmm_dot_lo = _mm_dp_pd(xmm_lhs_lo, xmm_rhs_lo, COND_PROD_MASK);
    auto xmm_dot_hi = _mm_dp_pd(xmm_lhs_hi, xmm_rhs_hi, COND_PROD_MASK);
    return _mm_cvtsd_f64(_mm_add_pd(xmm_dot_lo, xmm_dot_hi));
}

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
