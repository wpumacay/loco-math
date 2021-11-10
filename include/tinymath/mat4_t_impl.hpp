#pragma once

// clang-format off
#include <ios>
#include <cmath>
#include <sstream>
#include <string>
#include <type_traits>

#include <tinymath/impl/mat4_t_scalar_impl.hpp>

#if defined(TINYMATH_SSE_ENABLED)
// #include <tinymath/impl/mat4_t_sse_impl.hpp>
#endif

#if defined(TINYMATH_AVX_ENABLED)
// #include <tinymath/impl/mat4_t_avx_impl.hpp>
#endif
// clang-format on

// @todo(wilbert): use std::enable_if and some traits to only specialize for
// types when there is either SSE or AVX support enabled (to avoid repetition)

namespace tiny {
namespace math {

template <typename T>
Matrix4<T>::Matrix4(T x00, T x01, T x02, T x03, T x10, T x11, T x12, T x13,
                    T x20, T x21, T x22, T x23, T x30, T x31, T x32, T x33) {
    auto& data = m_Elements;
    data[0][0] = x00;
    data[1][0] = x01;
    data[2][0] = x02;
    data[3][0] = x03;

    data[0][1] = x10;
    data[1][1] = x11;
    data[2][1] = x12;
    data[3][1] = x13;

    data[0][2] = x20;
    data[1][2] = x21;
    data[2][2] = x22;
    data[3][2] = x23;

    data[0][3] = x30;
    data[1][3] = x31;
    data[2][3] = x32;
    data[3][3] = x33;
}

template <typename T>
Matrix4<T>::Matrix4(T d0, T d1, T d2, T d3) {
    m_Elements[0][0] = d0;
    m_Elements[1][1] = d1;
    m_Elements[2][2] = d2;
    m_Elements[3][3] = d3;
}

template <typename T>
Matrix4<T>::Matrix4(const ColumnType& col0, const ColumnType& col1,
                    const ColumnType& col2, const ColumnType& col3) {
    m_Elements[0] = col0;
    m_Elements[1] = col1;
    m_Elements[2] = col2;
    m_Elements[3] = col3;
}

template <typename T>
auto Matrix4<T>::toString() const -> std::string {
    auto& data = m_Elements;
    std::stringstream sstr_result;

    sstr_result << "( " << data[0][0] << ", " << data[1][0] << ", "
                << data[2][0] << ", " << data[3][0] << "\n";
    sstr_result << "  " << data[0][1] << ", " << data[1][1] << ", "
                << data[2][1] << ", " << data[3][1] << "\n";
    sstr_result << "  " << data[0][2] << ", " << data[1][2] << ", "
                << data[2][2] << ", " << data[3][2] << "\n";
    sstr_result << "  " << data[0][3] << ", " << data[1][3] << ", "
                << data[2][3] << ", " << data[3][3] << " )";

    return sstr_result.str();
}

template <typename T>
auto Matrix4<T>::Identity() -> Matrix4<T> {
    // @todo(wilbert): use initializer list to create identity matrix
    return Matrix4<T>();
}

template <typename T>
auto Matrix4<T>::Zeros() -> Matrix4<T> {
    return Matrix4<T>();
}

// ***************************************************************************//
//     Specializations for single-precision floating numbers (float32_t)      //
// ***************************************************************************//
using Mat4f = Matrix4<float32_t>;

template <>
TM_INLINE auto Mat4f::transposeInPlace() -> void {
    // scalar::kernel_transpose_inplace_mat4<float32_t>(elements());
    scalar::kernel_transpose_inplace_mat4<float32_t>(elements());
}

template <>
TM_INLINE auto Mat4f::transpose() const -> Mat4f {
    Mat4f result = *this;
    scalar::kernel_transpose_inplace_mat4<float32_t>(result.elements());
    return result;
}

template <>
TM_INLINE auto operator+(const Mat4f& lhs, const Mat4f& rhs) -> Mat4f {
    Mat4f result;
#if defined(TINYMATH_AVX_ENABLED)
    // avx::kernel_sub_mat4f(result.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    // sse::kernel_sub_mat4f(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add_mat4<float32_t>(result.elements(), lhs.elements(),
                                       rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator-(const Mat4f& lhs, const Mat4f& rhs) -> Mat4f {
    Mat4f result;
#if defined(TINYMATH_AVX_ENABLED)
    // avx::kernel_sub_mat4f(result.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    // sse::kernel_sub_mat4f(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub_mat4<float32_t>(result.elements(), lhs.elements(),
                                       rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(float32_t scale, const Mat4f& mat) -> Mat4f {
    Mat4f result;
#if defined(TINYMATH_AVX_ENABLED)
    // avx::kernel_scale_mat4f(result.elements(), scale, mat.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    // sse::kernel_scale_mat4f(result.elements(), scale, mat.elements());
#else
    scalar::kernel_scale_mat4<float32_t>(result.elements(), scale,
                                         mat.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Mat4f& mat, float32_t scale) -> Mat4f {
    Mat4f result;
#if defined(TINYMATH_AVX_ENABLED)
    // avx::kernel_scale_mat4f(result.elements(), scale, mat.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    // sse::kernel_scale_mat4f(result.elements(), scale, mat.elements());
#else
    scalar::kernel_scale_mat4<float32_t>(result.elements(), scale,
                                         mat.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Mat4f& lhs, const Mat4f& rhs) -> Mat4f {
    Mat4f result;
#if defined(TINYMATH_AVX_ENABLED)
// avx::kernel_matmul_mat4f(result.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
// sse::kernel_matmul_mat4f(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_matmul_mat4<float32_t>(result.elements(), lhs.elements(),
                                          rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto hadamard(const Mat4f& lhs, const Mat4f& rhs) -> Mat4f {
    Mat4f result;
#if defined(TINYMATH_AVX_ENABLED)
// avx::kernel_hadamard_mat4f(result.elements(),lhs.elements(),rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
// sse::kernel_hadamard_mat4f(result.elements(),lhs.elements(),rhs.elements());
#else
    scalar::kernel_matmul_mat4<float32_t>(result.elements(), lhs.elements(),
                                          rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator==(const Mat4f& lhs, const Mat4f& rhs) -> bool {
    return scalar::kernel_compare_eq_mat4<float32_t>(lhs.elements(),
                                                     rhs.elements());
}

template <>
TM_INLINE auto operator!=(const Mat4f& lhs, const Mat4f& rhs) -> bool {
    return !scalar::kernel_compare_eq_mat4<float32_t>(lhs.elements(),
                                                      rhs.elements());
}

// ***************************************************************************//
//     Specializations for double-precision floating numbers (float64_t)      //
// ***************************************************************************//
using Mat4d = Matrix4<float64_t>;

template <>
TM_INLINE auto Mat4d::transposeInPlace() -> void {
    scalar::kernel_transpose_inplace_mat4<float64_t>(elements());
}

template <>
TM_INLINE auto Mat4d::transpose() const -> Mat4d {
    Mat4d result = *this;
    scalar::kernel_transpose_inplace_mat4<float64_t>(result.elements());
    return result;
}

template <>
TM_INLINE auto operator+(const Mat4d& lhs, const Mat4d& rhs) -> Mat4d {
    Mat4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // avx::kernel_sub_mat4d(result.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    // sse::kernel_sub_mat4d(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add_mat4<float64_t>(result.elements(), lhs.elements(),
                                       rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator-(const Mat4d& lhs, const Mat4d& rhs) -> Mat4d {
    Mat4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // avx::kernel_sub_mat4d(result.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    // sse::kernel_sub_mat4d(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub_mat4<float64_t>(result.elements(), lhs.elements(),
                                       rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(float64_t scale, const Mat4d& mat) -> Mat4d {
    Mat4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // avx::kernel_scale_mat4d(result.elements(), scale, mat.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    // sse::kernel_scale_mat4d(result.elements(), scale, mat.elements());
#else
    scalar::kernel_scale_mat4<float64_t>(result.elements(), scale,
                                         mat.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Mat4d& mat, float64_t scale) -> Mat4d {
    Mat4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // avx::kernel_scale_mat4d(result.elements(), scale, mat.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    // sse::kernel_scale_mat4d(result.elements(), scale, mat.elements());
#else
    scalar::kernel_scale_mat4<float64_t>(result.elements(), scale,
                                         mat.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator*(const Mat4d& lhs, const Mat4d& rhs) -> Mat4d {
    Mat4d result;
#if defined(TINYMATH_AVX_ENABLED)
// avx::kernel_matmul_mat4d(result.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
// sse::kernel_matmul_mat4d(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_matmul_mat4<float64_t>(result.elements(), lhs.elements(),
                                          rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto hadamard(const Mat4d& lhs, const Mat4d& rhs) -> Mat4d {
    Mat4d result;
#if defined(TINYMATH_AVX_ENABLED)
// avx::kernel_hadamard_mat4d(result.elements(),lhs.elements(),rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
// sse::kernel_hadamard_mat4d(result.elements(),lhs.elements(),rhs.elements());
#else
    scalar::kernel_matmul_mat4<float64_t>(result.elements(), lhs.elements(),
                                          rhs.elements());
#endif
    return result;
}

template <>
TM_INLINE auto operator==(const Mat4d& lhs, const Mat4d& rhs) -> bool {
    return scalar::kernel_compare_eq_mat4<float64_t>(lhs.elements(),
                                                     rhs.elements());
}

template <>
TM_INLINE auto operator!=(const Mat4d& lhs, const Mat4d& rhs) -> bool {
    return !scalar::kernel_compare_eq_mat4<float64_t>(lhs.elements(),
                                                      rhs.elements());
}

}  // namespace math
}  // namespace tiny
