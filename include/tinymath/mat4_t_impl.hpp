#pragma once

// clang-format off
#include <ios>
#include <cmath>
#include <sstream>
#include <string>
#include <type_traits>

// @todo(wilbert): include kernels here
#include <tinymath/mat4_t.hpp>

// clang-format on

namespace tiny {
namespace math {

// clang-format off
template <typename T>
Matrix4<T>::Matrix4(T x00, T x01, T x02, T x03,
                    T x10, T x11, T x12, T x13,
                    T x20, T x21, T x22, T x23,
                    T x30, T x31, T x32, T x33) {
    auto& data = m_Elements;
    data[0][0] = x00; data[1][0] = x01; data[2][0] = x02; data[3][0] = x03;
    data[0][1] = x10; data[1][1] = x11; data[2][1] = x12; data[3][1] = x13;
    data[0][2] = x20; data[1][2] = x21; data[2][2] = x22; data[3][2] = x23;
    data[0][3] = x30; data[1][3] = x31; data[2][3] = x32; data[3][3] = x33;
}
// clang-format on

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

// ***************************************************************************//
//     Specializations for single-precision floating numbers (float32_t)      //
// ***************************************************************************//
using Mat4f = Matrix4<float32_t>;

template <>
TM_INLINE auto Mat4f::transposeInPlace() -> void {
#if defined(TINYMATH_SSE_ENABLED)
    // scalar::kernel_transpose_matrix_in_place_m4f(elements());
#else
    // sse::kernel_transpose_matrix_in_place_m4f(elements());
#endif
}

template <>
TM_INLINE auto Mat4f::transpose() const -> Mat4f {
    Mat4f result;
#if defined(TINYMATH_SSE_ENABLED)
    // scalar::kernel_transpose_matrix_in_place_m4f(result.elements());
#else
    // sse::kernel_transpose_matrix_in_place_m4f(result.elements());
#endif
    return result;
}

// ***************************************************************************//
//     Specializations for double-precision floating numbers (float64_t)      //
// ***************************************************************************//
using Mat4d = Matrix4<float64_t>;

template <>
TM_INLINE auto Mat4d::transposeInPlace() -> void {
#if defined(TINYMATH_AVX_ENABLED)
    // scalar::kernel_transpose_matrix_in_place_m4d(elements());
#else
    // avx::kernel_transpose_matrix_in_place_m4d(elements());
#endif
}

template <>
TM_INLINE auto Mat4d::transpose() const -> Mat4d {
    Mat4d result;
#if defined(TINYMATH_AVX_ENABLED)
    // scalar::kernel_transpose_matrix_in_place_m4d(result.elements());
#else
    // avx::kernel_transpose_matrix_in_place_m4d(result.elements());
#endif
    return result;
}

}  // namespace math
}  // namespace tiny
