#pragma once

// clang-format off
#include <ios>
#include <cmath>
#include <string>
#include <algorithm>
#include <type_traits>

#include <tinymath/impl/vec4_t_scalar_impl.hpp>

#if defined(TINYMATH_SSE_ENABLED)
#include <tinymath/impl/vec4_t_sse_impl.hpp>
#endif

#if defined(TINYMATH_AVX_ENABLED)
#include <tinymath/impl/vec4_t_avx_impl.hpp>
#endif
// clang-format on

namespace tiny {
namespace math {

template <typename Scalar_T>
auto operator<<(std::ostream& output_stream, const Vector4<Scalar_T>& src)
    -> std::ostream& {
    output_stream << "(" << src.x() << ", " << src.y() << ", " << src.z()
                  << ", " << src.w() << ")";
    return output_stream;
}

template <typename Scalar_T>
auto operator>>(std::istream& input_stream, Vector4<Scalar_T>& dst)
    -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3iqAVgS
    Scalar_T x{};
    Scalar_T y{};
    Scalar_T z{};
    Scalar_T w{};

    input_stream.setf(std::ios_base::skipws);
    input_stream >> x >> y >> z >> w;
    if (!input_stream.fail()) {
        dst.x() = x;
        dst.y() = y;
        dst.z() = z;
        dst.w() = w;
    }

    return input_stream;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(Scalar_T x) {
    m_Elements[0] = x;
    m_Elements[1] = x;
    m_Elements[2] = x;
    m_Elements[3] = x;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(Scalar_T x, Scalar_T y) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = y;
    m_Elements[3] = y;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(Scalar_T x, Scalar_T y, Scalar_T z) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = z;
    m_Elements[3] = z;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(Scalar_T x, Scalar_T y, Scalar_T z, Scalar_T w) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = z;
    m_Elements[3] = w;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(const std::initializer_list<Scalar_T>& values) {
    // Complain in case we don't receive exactly 4 values
    assert(values.size() == Vector4<Scalar_T>::VECTOR_NDIM);
    // Just copy the whole data from the initializer list
    std::copy(values.begin(), values.end(), m_Elements.data());
}

template <typename Scalar_T>
auto Vector4<Scalar_T>::toString() const -> std::string {
    std::stringstream str_result;
    if (std::is_same<ElementType, float>()) {
        str_result << "Vector4f(" << x() << ", " << y() << ", " << z() << ", "
                   << w() << ")";
    } else if (std::is_same<ElementType, double>()) {
        str_result << "Vector4d(" << x() << ", " << y() << ", " << z() << ", "
                   << w() << ")";
    } else {
        str_result << "Vector4X(" << x() << ", " << y() << ", " << z() << ", "
                   << w() << ")";
    }
    return str_result.str();
}

// ***************************************************************************//
//     Specializations for single-precision floating numbers (float32_t)      //
// ***************************************************************************//
using Vec4f = Vector4<float32_t>;

template <>
TM_INLINE auto Vec4f::dot(const Vec4f& other) const -> float32_t {
#if defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_dot_v4f(elements(), other.elements());
#else
    return scalar::kernel_dot_v4f(elements(), other.elements());
#endif
}

template <>
TM_INLINE auto operator+(const Vec4f& lhs, const Vec4f& rhs) -> Vec4f {
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
TM_INLINE auto operator-(const Vec4f& lhs, const Vec4f& rhs) -> Vec4f {
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
TM_INLINE auto operator*(float32_t scale, const Vec4f& vec) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_v4f(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v4f(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Vec4f& vec, float32_t scale) -> Vec4f {
    Vec4f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_v4f(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v4f(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Vec4f& lhs, const Vec4f& rhs) -> Vec4f {
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
TM_INLINE auto operator==(const Vec4f& lhs, const Vec4f& rhs) -> bool {
    return scalar::kernel_compare_eq_v4f(lhs.elements(), rhs.elements());
}

template <>
TM_INLINE auto operator!=(const Vec4f& lhs, const Vec4f& rhs) -> bool {
    return !scalar::kernel_compare_eq_v4f(lhs.elements(), rhs.elements());
}

// ***************************************************************************//
//     Specializations for double-precision floating numbers (float64_t)      //
// ***************************************************************************//
using Vec4d = Vector4<float64_t>;

template <>
TM_INLINE auto Vec4d::dot(const Vec4d& other) const -> float64_t {
#if defined(TINYMATH_AVX_ENABLED)
    return avx::kernel_dot_v4d(elements(), other.elements());
#else
    return scalar::kernel_dot_v4d(elements(), other.elements());
#endif
}

template <>
TM_INLINE auto operator+(const Vec4d& lhs, const Vec4d& rhs) -> Vec4d {
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
TM_INLINE auto operator-(const Vec4d& lhs, const Vec4d& rhs) -> Vec4d {
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
TM_INLINE auto operator*(float64_t scale, const Vec4d& vec) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_v4d(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v4d(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Vec4d& vec, float64_t scale) -> Vec4d {
    Vec4d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_v4d(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v4d(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Vec4d& lhs, const Vec4d& rhs) -> Vec4d {
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
TM_INLINE auto operator==(const Vec4d& lhs, const Vec4d& rhs) -> bool {
    return scalar::kernel_compare_eq_v4d(lhs.elements(), rhs.elements());
}

template <>
TM_INLINE auto operator!=(const Vec4d& lhs, const Vec4d& rhs) -> bool {
    return !scalar::kernel_compare_eq_v4d(lhs.elements(), rhs.elements());
}

}  // namespace math
}  // namespace tiny
