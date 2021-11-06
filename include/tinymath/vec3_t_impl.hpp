#pragma once

// clang-format off
#include <ios>
#include <cmath>
#include <string>
#include <cassert>
#include <algorithm>
#include <type_traits>

#include <tinymath/impl/vec3_t_scalar_impl.hpp>

#if defined(TINYMATH_SSE_ENABLED)
#include <tinymath/impl/vec3_t_sse_impl.hpp>
#endif

#if defined(TINYMATH_AVX_ENABLED)
#include <tinymath/impl/vec3_t_avx_impl.hpp>
#endif
// clang-format on

namespace tiny {
namespace math {

template <typename Scalar_T>
auto operator<<(std::ostream& output_stream, const Vector3<Scalar_T>& src)
    -> std::ostream& {
    output_stream << "(" << src.x() << ", " << src.y() << ", " << src.z()
                  << ")";
    return output_stream;
}

template <typename Scalar_T>
auto operator>>(std::istream& input_stream, Vector3<Scalar_T>& dst)
    -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3iqAVgS
    Scalar_T x{};
    Scalar_T y{};
    Scalar_T z{};

    input_stream.setf(std::ios_base::skipws);
    input_stream >> x >> y >> z;
    if (!input_stream.fail()) {
        dst.x() = x;
        dst.y() = y;
        dst.z() = z;
    }

    return input_stream;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x) {
    m_Elements[0] = x;
    m_Elements[1] = x;
    m_Elements[2] = x;
    m_Elements[3] = 0;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x, Scalar_T y) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = y;
    m_Elements[3] = 0;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x, Scalar_T y, Scalar_T z) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = z;
    m_Elements[3] = 0;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(const std::initializer_list<Scalar_T>& values) {
    // Complain in case we don't receive exactly 3 values
    assert(values.size() == Vector3<Scalar_T>::VECTOR_NDIM);
    // Just copy the whole data from the initializer list
    std::copy(values.begin(), values.end(), m_Elements.data());
}

template <typename Scalar_T>
auto Vector3<Scalar_T>::toString() const -> std::string {
    std::stringstream str_result;
    if (std::is_same<ElementType, float>()) {
        str_result << "Vector3f(" << x() << ", " << y() << ", " << z() << ")";
    } else if (std::is_same<ElementType, double>()) {
        str_result << "Vector3d(" << x() << ", " << y() << ", " << z() << ")";
    } else {
        str_result << "Vector3X(" << x() << ", " << y() << ", " << z() << ")";
    }
    return str_result.str();
}

// ***************************************************************************//
//     Specializations for single-precision floating numbers (float32_t)      //
// ***************************************************************************//
using Vec3f = Vector3<float32_t>;

template <>
TM_INLINE auto Vec3f::squaredNorm() const -> float32_t {
#if defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_length_square_v3f(elements());
#else
    return scalar::kernel_length_square_v3f(elements());
#endif
}

template <>
TM_INLINE auto Vec3f::norm() const -> float32_t {
#if defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_length_v3f(elements());
#else
    return std::sqrt(scalar::kernel_length_square_v3f(elements()));
#endif
}

template <>
TM_INLINE auto Vec3f::normalize() -> void {
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_normalize_in_place_v3f(elements());
#else
    scalar::kernel_normalize_in_place_v3f(elements());
#endif
}

template <>
TM_INLINE auto Vec3f::normalized() const -> Vec3f {
    auto result = *this;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_normalize_in_place_v3f(result.elements());
#else
    scalar::kernel_normalize_in_place_v3f(result.elements());
#endif
    return result;
}

template <>
TM_INLINE auto Vec3f::dot(const Vec3f& other) const -> float32_t {
#if defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_dot_v3f(elements(), other.elements());
#else
    return scalar::kernel_dot_v3f(elements(), other.elements());
#endif
}

template <>
TM_INLINE auto Vec3f::cross(const Vec3f& other) const -> Vec3f {
    Vec3f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_cross_v3f(result.elements(), elements(), other.elements());
#else
    scalar::kernel_cross_v3f(result.elements(), elements(), other.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator+(const Vec3f& lhs, const Vec3f& rhs) -> Vec3f {
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
TM_INLINE auto operator-(const Vec3f& lhs, const Vec3f& rhs) -> Vec3f {
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
TM_INLINE auto operator*(float32_t scale, const Vec3f& vec) -> Vec3f {
    Vec3f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_v3f(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v3f(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Vec3f& vec, float32_t scale) -> Vec3f {
    Vec3f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_v3f(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v3f(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Vec3f& lhs, const Vec3f& rhs) -> Vec3f {
    Vec3f result;
#if defined(TINYMATH_SSE_ENABLED)
    sse::kernel_hadamard_v3f(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_hadamard_v3f(result.elements(), lhs.elements(),
                                rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator==(const Vec3f& lhs, const Vec3f& rhs) -> bool {
    return scalar::kernel_compare_eq_v3f(lhs.elements(), rhs.elements());
}

template <>
TM_INLINE auto operator!=(const Vec3f& lhs, const Vec3f& rhs) -> bool {
    return !scalar::kernel_compare_eq_v3f(lhs.elements(), rhs.elements());
}

// ***************************************************************************//
//     Specializations for double-precision floating numbers (float64_t)      //
// ***************************************************************************//
using Vec3d = Vector3<float64_t>;

template <>
TM_INLINE auto Vec3d::squaredNorm() const -> float64_t {
#if defined(TINYMATH_AVX_ENABLED)
    return avx::kernel_length_square_v3d(elements());
#else
    return scalar::kernel_length_square_v3d(elements());
#endif
}

template <>
TM_INLINE auto Vec3d::norm() const -> float64_t {
#if defined(TINYMATH_AVX_ENABLED)
    return avx::kernel_length_v3d(elements());
#else
    return std::sqrt(scalar::kernel_length_square_v3d(elements()));
#endif
}

template <>
TM_INLINE auto Vec3d::normalize() -> void {
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_normalize_in_place_v3d(elements());
#else
    scalar::kernel_normalize_in_place_v3d(elements());
#endif
}

template <>
TM_INLINE auto Vec3d::normalized() const -> Vec3d {
    auto result = *this;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_normalize_in_place_v3d(result.elements());
#else
    scalar::kernel_normalize_in_place_v3d(result.elements());
#endif
    return result;
}

template <>
TM_INLINE auto Vec3d::dot(const Vec3d& other) const -> float64_t {
#if defined(TINYMATH_AVX_ENABLED)
    return avx::kernel_dot_v3d(elements(), other.elements());
#else
    return scalar::kernel_dot_v3d(elements(), other.elements());
#endif
}

template <>
TM_INLINE auto Vec3d::cross(const Vec3d& other) const -> Vec3d {
    Vec3d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_cross_v3d(result.elements(), elements(), other.elements());
#else
    scalar::kernel_cross_v3d(result.elements(), elements(), other.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator+(const Vec3d& lhs, const Vec3d& rhs) -> Vec3d {
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
TM_INLINE auto operator-(const Vec3d& lhs, const Vec3d& rhs) -> Vec3d {
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
TM_INLINE auto operator*(float64_t scale, const Vec3d& vec) -> Vec3d {
    Vec3d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_v3d(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v3d(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Vec3d& vec, float64_t scale) -> Vec3d {
    Vec3d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_v3d(result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_v3d(result.elements(), scale, vec.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Vec3d& lhs, const Vec3d& rhs) -> Vec3d {
    Vec3d result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_hadamard_v3d(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_hadamard_v3d(result.elements(), lhs.elements(),
                                rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator==(const Vec3d& lhs, const Vec3d& rhs) -> bool {
    return scalar::kernel_compare_eq_v3d(lhs.elements(), rhs.elements());
}

template <>
TM_INLINE auto operator!=(const Vec3d& lhs, const Vec3d& rhs) -> bool {
    return !scalar::kernel_compare_eq_v3d(lhs.elements(), rhs.elements());
}

}  // namespace math
}  // namespace tiny
