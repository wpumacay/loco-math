#pragma once

#if defined(TINYMATH_SSE_ENABLED)

#include <emmintrin.h>
#include <smmintrin.h>
#include <xmmintrin.h>

#include <tinymath/vec3_t.hpp>
#include <type_traits>

/**
 * SSE instruction sets required for each kernel:
 *
 * - kernel_add_v3f                 : SSE
 * - kernel_sub_v3f                 : SSE
 * - kernel_scale_v3f               : SSE
 * - kernel_hadamard_v3f            : SSE
 * - kernel_length_square_v3f       : SSE4.1 (_mm_dp_ps)
 * - kernel_length_v3f              : SSE4.1 (_mm_dp_ps)
 * - kernel_normalize_in_place_v3f  : SSE4.1 (_mm_dp_ps)
 * - kernel_dot_v3f                 : SSE4.1 (_mm_dp_ps)
 * - kernel_cross_v3f               : SSE
 */

namespace tiny {
namespace math {
namespace sse {

template <typename T>
using ArrayBuffer = typename Vector3<T>::BufferType;

template <typename T>
constexpr int32_t VECTOR_NDIM = Vector3<T>::VECTOR_NDIM;

template <typename T>
constexpr int32_t BUFFER_SIZE = Vector3<T>::BUFFER_SIZE;

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_add_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    // All elements of the buffer (4xf32, recall padding for alignment) fit into
    // a single xmm register (128-bits <=> 4xfloat32)
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_add_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    // Vector buffer contains 4xfloat64 <=> 256 bits <=> 32 bytes; however, xmm
    // registers are only 16 bytes wide. We'll just unroll the loop once (make
    // the point-wise operation twice on the registers, using lo-hi parts). Note
    // that we also require support for SSE2 to use the appropriate intrinsics
    // @todo(wilbert): try using static_cast and pointer-arithmetic replacements
    auto xmm_lhs_lo = _mm_load_pd(lhs.data());
    auto xmm_lhs_hi = _mm_load_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_load_pd(rhs.data());
    auto xmm_rhs_hi = _mm_load_pd(rhs.data() + 2);
    auto xmm_result_lo = _mm_add_pd(xmm_lhs_lo, xmm_rhs_lo);
    auto xmm_result_hi = _mm_add_pd(xmm_lhs_hi, xmm_rhs_hi);
    _mm_store_pd(dst.data(), xmm_result_lo);
    _mm_store_pd(dst.data() + 2, xmm_result_hi);
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_sub_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_result = _mm_sub_ps(xmm_lhs, xmm_rhs);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_sub_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto xmm_lhs_lo = _mm_load_pd(lhs.data());
    auto xmm_lhs_hi = _mm_load_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_load_pd(rhs.data());
    auto xmm_rhs_hi = _mm_load_pd(rhs.data() + 2);
    auto xmm_result_lo = _mm_sub_pd(xmm_lhs_lo, xmm_rhs_lo);
    auto xmm_result_hi = _mm_sub_pd(xmm_lhs_hi, xmm_rhs_hi);
    _mm_store_pd(dst.data(), xmm_result_lo);
    _mm_store_pd(dst.data() + 2, xmm_result_hi);
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_scale_vec3(ArrayBuffer<T>& dst, T scale,
                                 const ArrayBuffer<T>& vec) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
    auto xmm_scale = _mm_set1_ps(scale);
    auto xmm_vector = _mm_load_ps(vec.data());
    auto xmm_result = _mm_mul_ps(xmm_scale, xmm_vector);
    _mm_store_ps(dst.data(), xmm_result);
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_scale_vec3(ArrayBuffer<T>& dst, T scale,
                                 const ArrayBuffer<T>& vec) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto xmm_scale = _mm_set1_pd(scale);
    auto xmm_vector_lo = _mm_load_pd(vec.data());
    auto xmm_vector_hi = _mm_load_pd(vec.data() + 2);
    auto xmm_result_lo = _mm_mul_pd(xmm_scale, xmm_vector_lo);
    auto xmm_result_hi = _mm_mul_pd(xmm_scale, xmm_vector_hi);
    _mm_store_pd(dst.data(), xmm_result_lo);
    _mm_store_pd(dst.data() + 2, xmm_result_hi);
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_hadamard_vec3(ArrayBuffer<T>& dst,
                                    const ArrayBuffer<T>& lhs,
                                    const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    _mm_store_ps(dst.data(), _mm_mul_ps(xmm_lhs, xmm_rhs));
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_hadamard_vec3(ArrayBuffer<T>& dst,
                                    const ArrayBuffer<T>& lhs,
                                    const ArrayBuffer<T>& rhs) -> void {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    auto xmm_lhs_lo = _mm_load_pd(lhs.data());
    auto xmm_lhs_hi = _mm_load_pd(lhs.data() + 2);
    auto xmm_rhs_lo = _mm_load_pd(rhs.data());
    auto xmm_rhs_hi = _mm_load_pd(rhs.data() + 2);
    _mm_store_pd(dst.data(), _mm_mul_pd(xmm_lhs_lo, xmm_rhs_lo));
    _mm_store_pd(dst.data() + 2, _mm_mul_pd(xmm_lhs_hi, xmm_rhs_hi));
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_length_square_vec3(const ArrayBuffer<T>& vec) -> T {
    static_assert(std::is_same<float, T>::value, "We must be using f32");
    // @todo(wilbert)
}

template <typename T,
          typename std::enable_if<CpuHasSSE<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_length_square_vec3(const ArrayBuffer<T>& vec) -> T {
    static_assert(std::is_same<double, T>::value, "We must be using f64");
    // @todo(wilbert)
}

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//
using Vec3f = Vector3<float32_t>;
using Array3f = Vec3f::BufferType;

TM_INLINE auto kernel_length_square_v3f(const Array3f& vec) -> float32_t {
    // Implementation based on this post: https://bit.ly/3FyZF0n
    constexpr int32_t COND_PROD_MASK = 0x71;
    auto xmm_v = _mm_load_ps(vec.data());
    return _mm_cvtss_f32(_mm_dp_ps(xmm_v, xmm_v, COND_PROD_MASK));
}

TM_INLINE auto kernel_length_v3f(const Array3f& vec) -> float32_t {
    // Implementation based on this post: https://bit.ly/3FyZF0n
    constexpr int32_t COND_PROD_MASK = 0x71;
    auto xmm_v = _mm_load_ps(vec.data());
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(xmm_v, xmm_v, COND_PROD_MASK)));
}

TM_INLINE auto kernel_normalize_in_place_v3f(Array3f& vec) -> void {
    // Implementation based on this post: https://bit.ly/3FyZF0n
    constexpr int32_t COND_PROD_MASK = 0x7f;
    auto xmm_v = _mm_load_ps(vec.data());
    auto xmm_sums = _mm_dp_ps(xmm_v, xmm_v, COND_PROD_MASK);
    auto xmm_r_sqrt_sums = _mm_sqrt_ps(xmm_sums);
    auto xmm_v_norm = _mm_div_ps(xmm_v, xmm_r_sqrt_sums);
    _mm_store_ps(vec.data(), xmm_v_norm);
}

TM_INLINE auto kernel_dot_v3f(const Array3f& lhs, const Array3f& rhs)
    -> float32_t {
    constexpr int32_t COND_PROD_MASK = 0x71;
    auto xmm_lhs = _mm_load_ps(lhs.data());
    auto xmm_rhs = _mm_load_ps(rhs.data());
    auto xmm_cond_prod = _mm_dp_ps(xmm_lhs, xmm_rhs, COND_PROD_MASK);
    return _mm_cvtss_f32(xmm_cond_prod);
};

TM_INLINE auto kernel_cross_v3f(Array3f& dst, const Array3f& lhs,
                                const Array3f& rhs) -> void {
    // Implementation adapted from @ian_mallett (https://bit.ly/3lu6pVe)
    constexpr auto MASK_A = tiny::math::ShuffleMask<3, 0, 2, 1>::value;
    constexpr auto MASK_B = tiny::math::ShuffleMask<3, 1, 0, 2>::value;
    // Recall that the dot product of two 3d-vectors a and b given by:
    // a = {a[0], a[1], a[2], a[3]=0}, b = {b[0], b[1], b[2], b[3]=0}
    // has as resulting expression:
    // a (x) b = [a[1] * b[2] - a[2] * b[1],
    //            a[2] * b[0] - a[0] * b[2],
    //            a[0] * b[1] - a[1] * b[0],
    //                        0            ]
    auto vec_0 = _mm_load_ps(lhs.data());  // a = {a[0], a[1], a[2], a[3]=0}
    auto vec_1 = _mm_load_ps(rhs.data());  // b = {b[0], b[1], b[2], b[3]=0}
    // tmp_0 = {a[1], a[2], a[0], 0}
    auto tmp_0 = _mm_shuffle_ps(vec_0, vec_0, MASK_A);
    // tmp_1 = {b[2], b[0], b[1], 0}
    auto tmp_1 = _mm_shuffle_ps(vec_1, vec_1, MASK_B);
    // tmp_2 = {a[2], a[0], a[1], 0}
    auto tmp_2 = _mm_shuffle_ps(vec_0, vec_0, MASK_B);
    // tmp_3 = {b[1], b[2], b[0], 0}
    auto tmp_3 = _mm_shuffle_ps(vec_1, vec_1, MASK_A);
    _mm_store_ps(dst.data(), _mm_sub_ps(_mm_mul_ps(tmp_0, tmp_1),
                                        _mm_mul_ps(tmp_2, tmp_3)));
}

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
