#pragma once

// clang-format off
#include <loco/math/mat4_t.hpp>
#include <loco/math/impl/mat4_t_scalar_impl.hpp>
#include <loco/math/impl/mat4_t_sse_impl.hpp>
#include <loco/math/impl/mat4_t_avx_impl.hpp>
// clang-format on

namespace loco {
namespace math {

template <typename T>
using SFINAE_MAT4_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

/// \brief Returns the transpose of the given matrix
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto transpose(const Matrix4<T>& mat) -> Matrix4<T> {
    Matrix4<T> dst = mat;
    scalar::kernel_transpose_inplace_mat4<T>(dst.elements());
    return dst;
}

/// \brief Transposes the given matrix in-place
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto transposeInPlace(Matrix4<T>& mat) -> void {  // NOLINT
    scalar::kernel_transpose_inplace_mat4<T>(mat.elements());
}

/// \brief Returns the matrix-sum of the two given matrices
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto operator+(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_add_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_add_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

/// \brief Returns the matrix-difference of the two given matrices
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto operator-(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_sub_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_sub_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

/// \brief Returns the scaled version of the given matrix by the given factor
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto operator*(double scale, const Matrix4<T>& mat) -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_scale_mat4<T>(dst.elements(), static_cast<T>(scale),
                              mat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_scale_mat4<T>(dst.elements(), static_cast<T>(scale),
                              mat.elements());
#else
    scalar::kernel_scale_mat4<T>(dst.elements(), static_cast<T>(scale),
                                 mat.elements());
#endif
    return dst;
}

/// \brief Returns the scaled version of the given matrix by the given factor
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix4<T>& mat, double scale) -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_scale_mat4<T>(dst.elements(), static_cast<T>(scale),
                              mat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_scale_mat4<T>(dst.elements(), static_cast<T>(scale),
                              mat.elements());
#else
    scalar::kernel_scale_mat4<T>(dst.elements(), static_cast<T>(scale),
                                 mat.elements());
#endif
    return dst;
}

/// \brief Returns the matrix product of the two given matrices
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_matmul_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_matmul_mat4<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_matmul_mat4<T>(dst.elements(), lhs.elements(),
                                  rhs.elements());
#endif
    return dst;
}

/// \brief Returns the matrix-vector product of the given operands
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix4<T>& lhs_mat, const Vector4<T>& rhs_vec)
    -> Vector4<T> {
#if defined(LOCOMATH_AVX_ENABLED)
    Vector4<T> dst;
    avx::kernel_matmul_vec_mat4<T>(dst.elements(), lhs_mat.elements(),
                                   rhs_vec.elements());
    return dst;
#elif defined(LOCOMATH_SSE_ENABLED)
    Vector4<T> dst;
    sse::kernel_matmul_vec_mat4<T>(dst.elements(), lhs_mat.elements(),
                                   rhs_vec.elements());
    return dst;
#else
    return scalar::kernel_matmul_vec_mat4<T>(lhs_mat.elements(),
                                             rhs_vec.elements());
#endif
}

/// \brief Returns the element-wise product of the two given matrices
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto hadamard(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> Matrix4<T> {
    Matrix4<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_hadamard_mat4<T>(dst.elements(), lhs.elements(),
                                 rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
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
LM_INLINE auto operator==(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> bool {
    return scalar::kernel_compare_eq_mat4<T>(lhs.elements(), rhs.elements());
}

/// \brief Checks if two given matrices are "not equal" (within epsilon margin)
template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
LM_INLINE auto operator!=(const Matrix4<T>& lhs, const Matrix4<T>& rhs)
    -> bool {
    return !scalar::kernel_compare_eq_mat4<T>(lhs.elements(), rhs.elements());
}

template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
auto operator<<(std::ostream& output_stream, const Matrix4<T>& src)
    -> std::ostream& {
    constexpr int PRECISION_DIGITS = 10;
    output_stream << std::setprecision(PRECISION_DIGITS);
    output_stream << "( " << src[0][0] << ", " << src[1][0] << ", " << src[2][0]
                  << ", " << src[3][0] << "\n";
    output_stream << "  " << src[0][1] << ", " << src[1][1] << ", " << src[2][1]
                  << ", " << src[3][1] << "\n";
    output_stream << "  " << src[0][2] << ", " << src[1][2] << ", " << src[2][2]
                  << ", " << src[3][2] << "\n";
    output_stream << "  " << src[0][3] << ", " << src[1][3] << ", " << src[2][3]
                  << ", " << src[3][3] << " )";
    return output_stream;
}

template <typename T, SFINAE_MAT4_GUARD<T> = nullptr>
auto operator>>(std::istream& input_stream, Matrix4<T>& dst) -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3MPgPcW
    input_stream.setf(std::ios_base::skipws);
    // Temporary place to store the inputs given by the user
    std::array<T, Matrix4<T>::BUFFER_SIZE> d;
    // clang-format off
    // Get these many items/elements from the input stream
    input_stream >> d[0]  >> d[1]  >> d[2]  >> d[3]   // NOLINT
                 >> d[4]  >> d[5]  >> d[6]  >> d[7]   // NOLINT
                 >> d[8]  >> d[9]  >> d[10] >> d[11]  // NOLINT
                 >> d[12] >> d[13] >> d[14] >> d[15]; // NOLINT
    // clang-format on
    if (!input_stream.fail()) {
        // clang-format off
        // NOLINTNEXTLINE
        dst(0,0) = d[0];  dst(0,1) = d[1];  dst(0,2) = d[2];  dst(0,3) = d[3];
        // NOLINTNEXTLINE
        dst(1,0) = d[4];  dst(1,1) = d[5];  dst(1,2) = d[6];  dst(1,3) = d[7];
        // NOLINTNEXTLINE
        dst(2,0) = d[8];  dst(2,1) = d[9];  dst(2,2) = d[10]; dst(2,3) = d[11];
        // NOLINTNEXTLINE
        dst(3,0) = d[12]; dst(3,1) = d[13]; dst(3,2) = d[14]; dst(3,3) = d[15];
        // clang-format on
    }
    return input_stream;
}

}  // namespace math
}  // namespace loco
