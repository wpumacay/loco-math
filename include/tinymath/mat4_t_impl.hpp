#pragma once

// clang-format off
#include <tinymath/mat4_t.hpp>
#include <tinymath/impl/mat4_t_scalar_impl.hpp>
#include <tinymath/impl/mat4_t_sse_impl.hpp>
#include <tinymath/impl/mat4_t_avx_impl.hpp>
// clang-format on

namespace tiny {
namespace math {

template <typename T>
using SFINAE_MAT4_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

/// \brief Returns the transpose of the given matrix
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto transpose(const Matrix4<T>& mat) -> Matrix4<T> {
    Matrix4<T> dst = mat;
    scalar::kernel_transpose_inplace_mat4<T>(dst.elements());
    return dst;
}

/// \brief Transposes the given matrix in-place
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto transposeInPlace(Matrix4<T>& mat) -> void {  // NOLINT
    scalar::kernel_transpose_inplace_mat4<T>(mat.elements());
}

/// \brief Returns the matrix-sum of the two given matrices
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto operator+(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_add_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_add_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

/// \brief Returns the matrix-difference of the two given matrices
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto operator-(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_sub_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_sub_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

/// \brief Returns the scaled version of the given matrix by the given factor
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto operator*(double scale, const Matrix4<T>& mat) -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_mat4<T>(dst.elements(), scale, mat.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_mat4<T>(dst.elements(), scale, mat.elements());
#else
    scalar::kernel_scale_mat4<T>(dst.elements(), scale, mat.elements());
#endif
    return dst;
}

/// \brief Returns the scaled version of the given matrix by the given factor
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto operator*(const Matrix4<T>& mat, double scale) -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_mat4<T>(dst.elements(), scale, mat.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_mat4<T>(dst.elements(), scale, mat.elements());
#else
    scalar::kernel_scale_mat4<T>(dst.elements(), scale, mat.elements());
#endif
    return dst;
}

/// \brief Returns the matrix product of the two given matrices
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto operator*(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_matmul_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_matmul_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_matmul_mat4<T>(dst.elements(), lhs.elements(),
                                  rhs.elements());
#endif
    return dst;
}

/// \brief Returns the matrix-vector product of the given operands
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto operator*(const Matrix4<T>& lhs_mat, const Vector4<T>& rhs_vec)
    -> Vector4<T> {
    Vector4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert): implement matmul mat4-vec4
#elif defined(TINYMATH_SSE_ENABLED)
    // @todo(wilbert): implement matmul mat4-vec4
#else
    scalar::kernel_matmul_vec_mat4<T>(dst.elements(), lhs_mat.elements(),
                                      rhs_vec.elements());
#endif
    return dst;
}

/// \brief Returns the element-wise product of the two given matrices
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto hadamard(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_hadamard_mat4<T>(dst.elements(), lhs.elements(),
                                 rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_hadamard_mat4<T>(dst.elements(), lhs.elements(),
                                 rhs.elements());
#else
    scalar::kernel_hadamard_mat4<T>(dst.elements(), lhs.elements(),
                                    rhs.elements());
#endif
    return dst;
}

/// \brief Checks if two given matrices are "equal" (within epsilon margin)
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto operator==(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> bool {
    return scalar::kernel_compare_eq_mat4<T>(lhs.elements(), rhs.elements());
}

/// \brief Checks if two given matrices are "not equal" (within epsilon margin)
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
TM_INLINE auto operator!=(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> bool {
    return !scalar::kernel_compare_eq_mat4<T>(lhs.elements(), rhs.elements());
}

}  // namespace math
}  // namespace tiny
