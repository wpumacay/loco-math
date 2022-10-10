#pragma once

#include <istream>
#include <loco/math/mat3_t.hpp>
#include <loco/math/impl/mat3_t_scalar_impl.hpp>
#include <loco/math/impl/mat3_t_sse_impl.hpp>
#include <loco/math/impl/mat3_t_avx_impl.hpp>

namespace loco {
namespace math {

template <typename T>
using SFINAE_MAT3_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

/// Returns the tranpose of the given matrix
template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto transpoe(const Matrix3<T>& mat) -> Matrix3<T> {
    Matrix3<T> dst = mat;
    scalar::kernel_transpose_inplace_mat3<T>(dst.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto tranposeInPlace(Matrix3<T>& mat) -> void {  // NOLINT
    scalar::kernel_transpose_inplace_mat3<T>(mat.elements());
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator+(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> Matrix3<T> {
    Matrix3<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_add_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_add_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator-(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> Matrix3<T> {
    Matrix3<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    sse::kernel_sub_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_sub_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator*(double scale, const Matrix3<T>& mat) -> Matrix3<T> {
    Matrix3<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    sse::kernel_scale_mat3(dst.elements(), static_cast<T>(scale),
                           mat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_scale_mat3<T>(dst.elements(), static_cast<T>(scale),
                              mat.elements());
#else
    scalar::kernel_scale_mat3<T>(dst.elements(), static_cast<T>(scale),
                                 mat.elements());
#endif
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix3<T>& mat, double scale) -> Matrix3<T> {
    Matrix3<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    sse::kernel_scale_mat3(dst.elements(), static_cast<T>(scale),
                           mat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_scale_mat3<T>(dst.elements(), static_cast<T>(scale),
                              mat.elements());
#else
    scalar::kernel_scale_mat3<T>(dst.elements(), static_cast<T>(scale),
                                 mat.elements());
#endif
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> Matrix3<T> {
    Matrix3<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    sse::kernel_matmul_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_matmul_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_matmul_mat3<T>(dst.elements(), lhs.elements(),
                                  rhs.elements());
#endif
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix3<T>& lhs_mat, const Vector3<T>& rhs_vec)
    -> Vector3<T> {
    Vector3<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    sse::kernel_matmul_vec_mat3<T>(dst.elements(), lhs_mat.elements(),
                                   rhs_vec.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_matmul_vec_mat3<T>(dst.elements(), lhs_mat.elements(),
                                   rhs_vec.elements());
#else
    scalar::kernel_matmul_vec_mat3<T>(dst.elements(), lhs_mat.elements(),
                                      rhs_vec.elements());
#endif
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto hadamard(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> Matrix3<T> {
    Matrix3<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    sse::kernel_hadamard_mat3<T>(dst.elements(), lhs.elements(),
                                 rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_hadamard_mat3<T>(dst.elements(), lhs.elements(),
                                 rhs.elements());
#else
    scalar::kernel_hadamard_mat3<T>(dst.elements(), lhs.elements(),
                                    rhs.elements());
#endif
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator==(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> bool {
    return scalar::kernel_compare_eq_mat3<T>(lhs.elements(), rhs.elements());
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator!=(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> bool {
    return !scalar::kernel_compare_eq_mat3<T>(lhs.elements(), rhs.elements());
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
auto operator<<(std::ostream& output_stream, const Matrix3<T>& src)
    -> std::ostream& {
    constexpr int PRECISION_DIGITS = 10;
    output_stream << std::setprecision(PRECISION_DIGITS);
    output_stream << "(" << src(0, 0) << ", " << src(0, 1) << ", " << src(0, 2)
                  << ",\n";
    output_stream << " " << src(1, 0) << ", " << src(1, 1) << ", " << src(1, 2)
                  << ",\n";
    output_stream << " " << src(2, 0) << ", " << src(2, 1) << ", " << src(2, 2)
                  << ")";
    return output_stream;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
auto operator>>(std::istream& input_stream, Matrix3<T>& dst) -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3MPgPcW
    input_stream.setf(std::ios_base::skipws);
    // Temporary place to store the inputs given by the user
    std::array<T, Matrix3<T>::BUFFER_SIZE> mat;
    // Get these many items/elements from the input stream (row-major order)
    // NOLINTNEXTLINE
    input_stream >> mat[0] >> mat[1] >> mat[2] >> mat[3] >> mat[4] >> mat[5] >>
        mat[6] >> mat[7] >> mat[8];  // NOLINT
    if (!input_stream.fail()) {
        dst(0, 0) = mat[0];
        dst(0, 1) = mat[1];
        dst(0, 2) = mat[2];

        dst(1, 0) = mat[3];
        dst(1, 1) = mat[4];
        dst(1, 2) = mat[5];  // NOLINT

        dst(2, 0) = mat[6];  // NOLINT
        dst(2, 1) = mat[7];  // NOLINT
        dst(2, 2) = mat[8];  // NOLINT
    }
    return input_stream;
}

}  // namespace math
}  // namespace loco
