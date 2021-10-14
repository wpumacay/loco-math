#include <tinymath/impl/vec4_t_scalar_impl.hpp>

#if defined(TINYMATH_SSE_ENABLED)
#include <tinymath/impl/vec4_t_sse_impl.hpp>
#endif

#if defined(TINYMATH_AVX_ENABLED)
#include <tinymath/impl/vec4_t_avx_impl.hpp>
#endif

#include <cmath>
#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {

// ***************************************************************************//
//     Specializations for single-precision floating numbers (float32_t)      //
// ***************************************************************************//
using Vec4f = Vector4<float32_t>;

template <>
auto Vec4f::dot(const Vec4f& other) const -> float32_t {
#if defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_dot_v4f(elements(), other.elements());
#else
    return scalar::kernel_dot_v4f(elements(), other.elements());
#endif
}

template <>
auto operator+(const Vec4f& lhs, const Vec4f& rhs) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    // SSE allows SIMD addition of 4-float packed vectors, so we use it here
    sse::kernel_add_v4f(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases (AVX registers require 8-floats)
    scalar::kernel_add_v4f(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator-(const Vec4f& lhs, const Vec4f& rhs) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    // SSE allows SIMD substraction of 4-float packed vectors, so we use it here
    sse::kernel_sub_v4f(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases (AVX registers require 8-floats)
    scalar::kernel_sub_v4f(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator*(float32_t scale, const Vec4f& vec) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_v4f(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v4f(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
auto operator*(const Vec4f& vec, float32_t scale) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_v4f(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v4f(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
auto operator*(const Vec4f& lhs, const Vec4f& rhs) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_hadamard_v4f(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_hadamard_v4f(result.elements(), lhs.elements(),
                                rhs.elements());
#endif
    return result;
};

template <>
auto operator==(const Vec4f& lhs, const Vec4f& rhs) -> bool {
    return scalar::kernel_compare_eq_v4f(lhs.elements(), rhs.elements());
}

template <>
auto operator!=(const Vec4f& lhs, const Vec4f& rhs) -> bool {
    return !scalar::kernel_compare_eq_v4f(lhs.elements(), rhs.elements());
}

// ***************************************************************************//
//     Specializations for double-precision floating numbers (float64_t)      //
// ***************************************************************************//
using Vec4d = Vector4<float64_t>;

template <>
auto Vec4d::dot(const Vec4d& other) const -> float64_t {
#if defined(TINYMATH_AVX_ENABLED)
    return avx::kernel_dot_v4d(elements(), other.elements());
#else
    return scalar::kernel_dot_v4d(elements(), other.elements());
#endif
}

template <>
auto operator+(const Vec4d& lhs, const Vec4d& rhs) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // AVX allows SIMD addition of 4-double packed vectors, so we use it
    avx::kernel_add_v4d(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases, SSE register width is not enough
    scalar::kernel_add_v4d(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator-(const Vec4d& lhs, const Vec4d& rhs) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // AVX allows SIMD substraction of 4-double packed vectors, so we use it
    avx::kernel_sub_v4d(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases, SSE register width is not enough
    scalar::kernel_sub_v4d(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator*(float64_t scale, const Vec4d& vec) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_v4d(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v4d(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
auto operator*(const Vec4d& vec, float64_t scale) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_v4d(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v4d(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
auto operator*(const Vec4d& lhs, const Vec4d& rhs) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_hadamard_v4d(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_hadamard_v4d(result.elements(), lhs.elements(),
                                rhs.elements());
#endif
    return result;
}

template <>
auto operator==(const Vec4d& lhs, const Vec4d& rhs) -> bool {
    return scalar::kernel_compare_eq_v4d(lhs.elements(), rhs.elements());
}

template <>
auto operator!=(const Vec4d& lhs, const Vec4d& rhs) -> bool {
    return !scalar::kernel_compare_eq_v4d(lhs.elements(), rhs.elements());
}

}  // namespace math
}  // namespace tiny
