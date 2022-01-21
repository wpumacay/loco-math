#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <immintrin.h>

#include <tinymath/vec3_t.hpp>

/**
 * AVX instruction sets required for each kernel:
 *
 * - kernel_add_v3d                 : AVX
 * - kernel_sub_v3d                 : AVX
 * - kernel_scale_v3d               : AVX
 * - kernel_hadamard_v3d            : AVX
 * - kernel_length_square_v3d       : AVX + SSE2
 * - kernel_length_v3d              : AVX + SSE2
 * - kernel_normalize_in_place_v3d  : AVX
 * - kernel_dot_v3d                 : AVX + SSE2
 * - kernel_cross_v3d               : AVX
 */

namespace tiny {
namespace math {
namespace avx {

template <typename T>
using ArrayBuffer = typename Vector3<T>::BufferType;

template <typename T>
constexpr int32_t VECTOR_NDIM = Vector3<T>::VECTOR_NDIM;

template <typename T>
constexpr int32_t BUFFER_SIZE = Vector3<T>::BUFFER_SIZE;

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_add_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
    auto ymm_lhs = _mm256_load_ps(lhs.data());
    auto ymm_rhs = _mm256_load_ps(rhs.data());
    auto ymm_result = _mm256_add_ps(ymm_lhs, ymm_rhs);
    _mm256_zeroupper();
    _mm256_store_ps(dst.data(), ymm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_add_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_result = _mm256_add_pd(ymm_lhs, ymm_rhs);
    _mm256_store_pd(dst.data(), ymm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_sub_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
    auto ymm_lhs = _mm256_load_ps(lhs.data());
    auto ymm_rhs = _mm256_load_ps(rhs.data());
    auto ymm_result = _mm256_sub_ps(ymm_lhs, ymm_rhs);
    _mm256_zeroupper();
    _mm256_store_ps(dst.data(), ymm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_sub_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_result = _mm256_sub_pd(ymm_lhs, ymm_rhs);
    _mm256_store_pd(dst.data(), ymm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_scale_vec3(ArrayBuffer<T>& dst, T scale,
                                 const ArrayBuffer<T>& vec) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
    auto ymm_scale = _mm256_set1_ps(scale);
    auto ymm_vector = _mm256_load_ps(vec.data());
    auto ymm_result = _mm256_mul_ps(ymm_scale, ymm_vector);
    _mm256_zeroupper();
    _mm256_store_ps(dst.data(), ymm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_scale_vec3(ArrayBuffer<T>& dst, T scale,
                                 const ArrayBuffer<T>& vec) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto ymm_scale = _mm256_set1_pd(scale);
    auto ymm_vector = _mm256_load_pd(vec.data());
    auto ymm_result = _mm256_mul_pd(ymm_scale, ymm_vector);
    _mm256_store_pd(dst.data(), ymm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_hadamard_vec3(ArrayBuffer<T>& dst,
                                    const ArrayBuffer<T>& lhs,
                                    const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
    auto ymm_lhs = _mm256_load_ps(lhs.data());
    auto ymm_rhs = _mm256_load_ps(rhs.data());
    auto ymm_result = _mm256_mul_ps(ymm_lhs, ymm_rhs);
    _mm256_zeroupper();
    _mm256_store_ps(dst.data(), ymm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_hadamard_vec3(ArrayBuffer<T>& dst,
                                    const ArrayBuffer<T>& lhs,
                                    const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    _mm256_store_pd(dst.data(), _mm256_mul_pd(ymm_lhs, ymm_rhs));
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_length_square_vec3(const ArrayBuffer<T>& vec) -> T {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_length_square_vec3(const ArrayBuffer<T>& vec) -> T {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    // Implementation based on this post: https://bit.ly/3lt3ts4
    // Instruction-sets required (AVX, SSE2)
    // -------------------------
    // AVX:_mm256_load_pd,_mm256_mul_pd,_mm256_hadd_pd,_mm256_extractf128_pd
    // SSE2: _mm_add_pd, _mm_sqrt_pd, _mm_cvtsd_f64
    auto ymm_v = _mm256_load_pd(vec.data());
    auto ymm_prod = _mm256_mul_pd(ymm_v, ymm_v);
    auto ymm_hsum = _mm256_hadd_pd(ymm_prod, ymm_prod);
    auto xmm_lo_sum = _mm256_extractf128_pd(ymm_hsum, 0);
    auto xmm_hi_sum = _mm256_extractf128_pd(ymm_hsum, 1);
    auto xmm_result = _mm_add_pd(xmm_lo_sum, xmm_hi_sum);
    return _mm_cvtsd_f64(xmm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_length_vec3(const ArrayBuffer<T>& vec) -> T {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_length_vec3(const ArrayBuffer<T>& vec) -> T {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    // Implementation based on this post: https://bit.ly/3lt3ts4
    // Instruction-sets required (AVX, SSE2)
    // -------------------------
    // AVX: _mm256_load_pd,_mm256_mul_pd,_mm256_hadd_pd,_mm256_extractf128_pd
    // SSE2: _mm_add_pd,_mm_sqrt_pd,_mm_cvtsd_f64
    auto ymm_v = _mm256_load_pd(vec.data());
    auto ymm_prod = _mm256_mul_pd(ymm_v, ymm_v);
    auto ymm_hsum = _mm256_hadd_pd(ymm_prod, ymm_prod);
    auto xmm_lo_sum = _mm256_extractf128_pd(ymm_hsum, 0);
    auto xmm_hi_sum = _mm256_extractf128_pd(ymm_hsum, 1);
    auto xmm_result = _mm_sqrt_pd(_mm_add_pd(xmm_lo_sum, xmm_hi_sum));
    return _mm_cvtsd_f64(xmm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_normalize_in_place_vec3(ArrayBuffer<T>& vec) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_normalize_in_place_vec3(ArrayBuffer<T>& vec) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto ymm_v = _mm256_load_pd(vec.data());
    auto ymm_prod = _mm256_mul_pd(ymm_v, ymm_v);
    // Construct the sum of squares into each double of a 256-bit register
    auto tmp_0 = _mm256_permute2f128_pd(ymm_prod, ymm_prod, 0x21);
    auto tmp_1 = _mm256_hadd_pd(ymm_prod, tmp_0);
    auto tmp_2 = _mm256_hadd_pd(tmp_1, tmp_1);  // here we have the {norm^2}
    // Construct a register with the norm in each entry (rsqrt quite imprecise)
    auto tmp_3 = _mm256_sqrt_pd(tmp_2);
    // Normalize the vector and store the result back
    auto ymm_normalized = _mm256_div_pd(ymm_v, tmp_3);
    _mm256_store_pd(vec.data(), ymm_normalized);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_dot_vec3(const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> T {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_dot_vec3(const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> T {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto ymm_lhs = _mm256_load_pd(lhs.data());
    auto ymm_rhs = _mm256_load_pd(rhs.data());
    auto ymm_prod = _mm256_mul_pd(ymm_lhs, ymm_rhs);
    auto ymm_hsum = _mm256_hadd_pd(ymm_prod, ymm_prod);
    auto xmm_lo_sum = _mm256_extractf128_pd(ymm_hsum, 0);
    auto xmm_hi_sum = _mm256_extractf128_pd(ymm_hsum, 1);
    auto xmm_result = _mm_add_pd(xmm_lo_sum, xmm_hi_sum);
    return _mm_cvtsd_f64(xmm_result);
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_cross_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                                 const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_cross_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                                 const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    // Implementation adapted from @ian_mallett (https://bit.ly/3lu6pVe)
    auto vec_a = _mm256_load_pd(lhs.data());
    auto vec_b = _mm256_load_pd(rhs.data());

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
    _mm256_store_pd(dst.data(), _mm256_sub_pd(_mm256_mul_pd(tmp_6a, tmp_4b),
                                              _mm256_mul_pd(tmp_4a, tmp_6b)));
    // @todo(wilbert): replace permutation madness with "permute4x64_pd" (AVX2)
}

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
