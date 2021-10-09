#include <tinymath/impl/vec3_t_scalar_impl.hpp>

#if defined(TINYMATH_SSE_ENABLED)
#include <tinymath/impl/vec3_t_sse_impl.hpp>
#endif

#if defined(TINYMATH_AVX_ENABLED)
#include <tinymath/impl/vec3_t_avx_impl.hpp>
#endif

#include <cmath>
#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {

// Specializations of operators for single-precision types (float32_t)
using Vec3f = Vector3<float32_t>;

template <>
auto Vec3f::length_square() const -> float32_t {
#if defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_length_square_v3f(elements());
#else
    return scalar::kernel_length_square_v3f(elements());
#endif
}

template <>
auto Vec3f::length() const -> float32_t {
#if defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_length_v3f(elements());
#else
    return std::sqrt(scalar::kernel_length_square_v3f(elements()));
#endif
}

template <>
auto operator+(const Vec3f& lhs, const Vec3f& rhs) -> Vec3f {
    Vec3f result;
#if defined(TINYMATH_SSE_ENABLED)
    // SSE allows SIMD addition of 4-float packed vectors, so we use it here
    sse::kernel_add_v3f(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases (AVX registers require 8-floats)
    scalar::kernel_add_v3f(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator-(const Vec3f& lhs, const Vec3f& rhs) -> Vec3f {
    Vec3f result;
#if defined(TINYMATH_SSE_ENABLED)
    // SSE allows SIMD substraction of 4-float packed vectors, so we use it here
    sse::kernel_sub_v3f(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases (AVX registers require 8-floats)
    scalar::kernel_sub_v3f(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator*(float32_t scale, const Vec3f& vec) -> Vec3f {
    Vec3f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_v3f(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v3f(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
auto operator*(const Vec3f& vec, float32_t scale) -> Vec3f {
    Vec3f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_v3f(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v3f(result.elements(), scale, vec.elements());
#endif
    return result;
}

// Specializations of operators for double-precision types (float64_t)
using Vec3d = Vector3<float64_t>;

template <>
auto Vec3d::length_square() const -> float64_t {
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert): define length-square with avx instructions (PR #3)
#else
    return scalar::kernel_length_square_v3d(elements());
#endif
}

template <>
auto Vec3d::length() const -> float64_t {
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert): define length with avx instructions (PR #3)
#else
    return std::sqrt(scalar::kernel_length_square_v3d(elements()));
#endif
}

template <>
auto operator+(const Vec3d& lhs, const Vec3d& rhs) -> Vec3d {
    Vec3d result;
#if defined(TINYMATH_AVX_ENABLED)
    // AVX allows SIMD addition of 4-double packed vectors, so we use it
    avx::kernel_add_v3d(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases, SSE register width is not enough
    scalar::kernel_add_v3d(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator-(const Vec3d& lhs, const Vec3d& rhs) -> Vec3d {
    Vec3d result;
#if defined(TINYMATH_AVX_ENABLED)
    // AVX allows SIMD substraction of 4-double packed vectors, so we use it
    avx::kernel_sub_v3d(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases, SSE register width is not enough
    scalar::kernel_sub_v3d(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
auto operator*(float64_t scale, const Vec3d& vec) -> Vec3d {
    Vec3d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_v3d(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v3d(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
auto operator*(const Vec3d& vec, float64_t scale) -> Vec3d {
    Vec3d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_v3d(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v3d(result.elements(), scale, vec.elements());
#endif
    return result;
}

}  // namespace math
}  // namespace tiny
