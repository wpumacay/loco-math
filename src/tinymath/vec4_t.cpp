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

// Specializations of operators for single-precision types (float32_t)
using Vec4f = Vector4<float32_t>;

template <>
auto operator+(const Vec4f& lhs, const Vec4f& rhs) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    // SSE allows SIMD addition of 4-float packed vectors, so we use it here
    sse::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases (AVX registers require 8-floats)
    scalar::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator-(const Vec4f& lhs, const Vec4f& rhs) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    // SSE allows SIMD substraction of 4-float packed vectors, so we use it here
    sse::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases (AVX registers require 8-floats)
    scalar::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator*(float32_t scale, const Vec4f& vec) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
auto operator*(const Vec4f& vec, float32_t scale) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale(result.elements(), scale, vec.elements());
#endif
    return result;
}

// Specializations of operators for double-precision types (float64_t)
using Vec4d = Vector4<float64_t>;

template <>
auto operator+(const Vec4d& lhs, const Vec4d& rhs) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // AVX allows SIMD addition of 4-double packed vectors, so we use it
    avx::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases, SSE register width is not enough
    scalar::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator-(const Vec4d& lhs, const Vec4d& rhs) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // AVX allows SIMD substraction of 4-double packed vectors, so we use it
    avx::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases, SSE register width is not enough
    scalar::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator*(float64_t scale, const Vec4d& vec) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
auto operator*(const Vec4d& vec, float64_t scale) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale(result.elements(), scale, vec.elements());
#endif
    return result;
}

}  // namespace math
}  // namespace tiny
