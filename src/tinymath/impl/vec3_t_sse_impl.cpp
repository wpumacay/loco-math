#if defined(TINYMATH_SSE_ENABLED)

#include <smmintrin.h>
#include <xmmintrin.h>

#include <tinymath/impl/vec3_t_sse_impl.hpp>

namespace tiny {
namespace math {
namespace sse {

// ***************************************************************************//
//   Implementations for single-precision floating point numbers (float32_t)  //
// ***************************************************************************//
using Vec3f = Vector3<float32_t>;
using Array3f = Vec3f::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void {
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_result = _mm_add_ps(xmm_lhs, xmm_rhs);
    _mm_storeu_ps(dst.data(), xmm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void {
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_result = _mm_sub_ps(xmm_lhs, xmm_rhs);
    _mm_storeu_ps(dst.data(), xmm_result);
}

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v3f(Array3f& dst, float32_t scale, const Array3f& vec)
    -> void {
    auto xmm_scale = _mm_set1_ps(scale);
    auto xmm_vector = _mm_loadu_ps(vec.data());
    auto xmm_result = _mm_mul_ps(xmm_scale, xmm_vector);
    _mm_storeu_ps(dst.data(), xmm_result);
}

auto kernel_length_square_v3f(const Array3f& vec) -> float32_t {
    // Implementation based on this post: https://bit.ly/3FyZF0n
    constexpr int32_t COND_PROD_MASK = 0x71;
    auto xmm_v = _mm_loadu_ps(vec.data());
    return _mm_cvtss_f32(_mm_dp_ps(xmm_v, xmm_v, COND_PROD_MASK));
}

auto kernel_length_v3f(const Array3f& vec) -> float32_t {
    // Implementation based on this post: https://bit.ly/3FyZF0n
    constexpr int32_t COND_PROD_MASK = 0x71;
    auto xmm_v = _mm_loadu_ps(vec.data());
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(xmm_v, xmm_v, COND_PROD_MASK)));
}

auto kernel_dot_v3f(const Array3f& lhs, const Array3f& rhs) -> float32_t {
    constexpr int32_t COND_PROD_MASK = 0x71;
    auto xmm_lhs = _mm_loadu_ps(lhs.data());
    auto xmm_rhs = _mm_loadu_ps(rhs.data());
    auto xmm_cond_prod = _mm_dp_ps(xmm_lhs, xmm_rhs, COND_PROD_MASK);
    return _mm_cvtss_f32(xmm_cond_prod);
};

// NOLINTNEXTLINE(runtime/references)
auto kernel_cross_v3f(Array3f& dst, const Array3f& lhs, const Array3f& rhs)
    -> void {
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
    auto vec_0 = _mm_loadu_ps(lhs.data());  // a = {a[0], a[1], a[2], a[3]=0}
    auto vec_1 = _mm_loadu_ps(rhs.data());  // b = {b[0], b[1], b[2], b[3]=0}
    // tmp_0 = {a[1], a[2], a[0], 0}
    auto tmp_0 = _mm_shuffle_ps(vec_0, vec_0, MASK_A);
    // tmp_1 = {b[2], b[0], b[1], 0}
    auto tmp_1 = _mm_shuffle_ps(vec_1, vec_1, MASK_B);
    // tmp_2 = {a[2], a[0], a[1], 0}
    auto tmp_2 = _mm_shuffle_ps(vec_0, vec_0, MASK_B);
    // tmp_3 = {b[1], b[2], b[0], 0}
    auto tmp_3 = _mm_shuffle_ps(vec_1, vec_1, MASK_A);
    _mm_storeu_ps(dst.data(), _mm_sub_ps(_mm_mul_ps(tmp_0, tmp_1),
                                         _mm_mul_ps(tmp_2, tmp_3)));
}

}  // namespace sse
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_SSE_ENABLED
