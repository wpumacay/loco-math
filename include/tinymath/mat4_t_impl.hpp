#pragma once

// clang-format off
#include <ios>
#include <cmath>
#include <sstream>
#include <string>
#include <type_traits>

#include <tinymath/impl/mat4_t_scalar_impl.hpp>
#include <tinymath/impl/mat4_t_sse_impl.hpp>
#include <tinymath/impl/mat4_t_avx_impl.hpp>
#include "tinymath/common.hpp"

// clang-format on

// @todo(wilbert): refactor SFINAE usage to avoid extra duplication (should be
// able to dispatch from a single declaration). Either use "if constexpr(c++17)"
// or dispatch SSE-AVX specific kernels in their own implementation headers

// @todo(wilbert): also, I think I don't quite understand SFINAE as much as I
// should, cause the type* = nullptr is just a fix I found. I think I was
// supposed to use enable_if on the return type side, as Eigen does in its
// codebase (which gets a little verbose, but still works)

// SFINAE implementation based on these resources:
// * https://youtu.be/Vkck4EU2lOU
// * https://akrzemi1.wordpress.com/examples/overloading-enable_if/
// * https://youtu.be/ybaE9qlhHvw

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
//                     Dispatch operator for matrix addition                  //
// ***************************************************************************//

template <typename Scalar_T,
          typename std::enable_if<IsScalar<Scalar_T>::value>::type* = nullptr>
TM_INLINE auto operator+(const Matrix4<Scalar_T>& lhs,
                         const Matrix4<Scalar_T>& rhs) -> Matrix4<Scalar_T> {
    Matrix4<Scalar_T> result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_add_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                   rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_add_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                   rhs.elements());
#else
    scalar::kernel_add_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                      rhs.elements());
#endif
    return result;
}

// ***************************************************************************//
//                   Dispatch operator for matrix substraction                //
// ***************************************************************************//

template <typename Scalar_T,
          typename std::enable_if<IsScalar<Scalar_T>::value>::type* = nullptr>
TM_INLINE auto operator-(const Matrix4<Scalar_T>& lhs,
                         const Matrix4<Scalar_T>& rhs) -> Matrix4<Scalar_T> {
    Matrix4<Scalar_T> result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_sub_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                   rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_sub_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                   rhs.elements());
#else
    scalar::kernel_sub_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                      rhs.elements());
#endif
    return result;
}

// ***************************************************************************//
//                Dispatch operator for scalar-matrix product                 //
// ***************************************************************************//

template <typename Scalar_T,
          typename std::enable_if<IsScalar<Scalar_T>::value>::type* = nullptr>
TM_INLINE auto operator*(double scale, const Matrix4<Scalar_T>& mat)
    -> Matrix4<Scalar_T> {
    Matrix4<Scalar_T> result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_mat4<Scalar_T>(result.elements(), scale, mat.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_mat4<Scalar_T>(result.elements(), scale, mat.elements());
#else
    scalar::kernel_scale_mat4<Scalar_T>(result.elements(), scale,
                                        mat.elements());
#endif
    return result;
}

// ***************************************************************************//
//                Dispatch operator for matrix-scalar product                 //
// ***************************************************************************//

template <typename Scalar_T,
          typename std::enable_if<IsScalar<Scalar_T>::value>::type* = nullptr>
TM_INLINE auto operator*(const Matrix4<Scalar_T>& mat, double scale)
    -> Matrix4<Scalar_T> {
    Matrix4<Scalar_T> result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_mat4<Scalar_T>(result.elements(), scale, mat.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_mat4<Scalar_T>(result.elements(), scale, mat.elements());
#else
    scalar::kernel_scale_mat4<Scalar_T>(result.elements(), scale,
                                        mat.elements());
#endif
    return result;
}

// ***************************************************************************//
//                Dispatch operator for matrix-matrix product                 //
// ***************************************************************************//

template <typename Scalar_T,
          typename std::enable_if<IsScalar<Scalar_T>::value>::type* = nullptr>
TM_INLINE auto operator*(const Matrix4<Scalar_T>& lhs,
                         const Matrix4<Scalar_T>& rhs) -> Matrix4<Scalar_T> {
    Matrix4<Scalar_T> result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_matmul_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                      rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_matmul_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                      rhs.elements());
#else
    scalar::kernel_matmul_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                         rhs.elements());
#endif
    return result;
}

// ***************************************************************************//
//             Dispatch operator for element-wise matrix product              //
// ***************************************************************************//

template <typename Scalar_T,
          typename std::enable_if<IsScalar<Scalar_T>::value>::type* = nullptr>
TM_INLINE auto hadamard(const Matrix4<Scalar_T>& lhs,
                        const Matrix4<Scalar_T>& rhs) -> Matrix4<Scalar_T> {
    Matrix4<Scalar_T> result;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_hadamard_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                        rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_hadamard_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                        rhs.elements());
#else
    scalar::kernel_hadamard_mat4<Scalar_T>(result.elements(), lhs.elements(),
                                           rhs.elements());
#endif
    return result;
}

// ***************************************************************************//
//                  Dispatch matrix comparison operators                      //
// ***************************************************************************//

template <typename Scalar_T,
          typename std::enable_if<IsScalar<Scalar_T>::value>::type* = nullptr>
TM_INLINE auto operator==(const Matrix4<Scalar_T>& lhs,
                          const Matrix4<Scalar_T>& rhs) -> bool {
    return scalar::kernel_compare_eq_mat4<Scalar_T>(lhs.elements(),
                                                    rhs.elements());
}

template <typename Scalar_T,
          typename std::enable_if<IsScalar<Scalar_T>::value>::type* = nullptr>
TM_INLINE auto operator!=(const Matrix4<Scalar_T>& lhs,
                          const Matrix4<Scalar_T>& rhs) -> bool {
    return !scalar::kernel_compare_eq_mat4<Scalar_T>(lhs.elements(),
                                                     rhs.elements());
}

}  // namespace math
}  // namespace tiny
