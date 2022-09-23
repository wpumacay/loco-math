#pragma once

#include <loco/math/mat2_t.hpp>
#include <loco/math/impl/mat2_t_scalar_impl.hpp>
#include <loco/math/impl/mat2_t_sse_impl.hpp>
#include <loco/math/impl/mat2_t_avx_impl.hpp>

namespace loco {
namespace math {

/// Returns the tranpose of the given matrix
template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto transpose(const Matrix2<T>& mat) -> Matrix2<T> {
    Matrix2<T> dst = mat;
    scalar::kernel_transpose_inplace_mat2<T>(dst.elements());
    return dst;
}

/// Transposes the given matrix in place
template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto transposeInPlace(Matrix2<T>& mat) -> void {  // NOLINT
    scalar::kernel_transpose_inplace_mat2<T>(mat.elements());
}

/// Returns the matrix sum of the two given matrices
template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto operator+(const Matrix2<T>& lhs, const Matrix2<T>& rhs)
    -> Matrix2<T> {
    Matrix2<T> dst;
    scalar::kernel_add_mat2<T>(dst.elements(), lhs.elements(), rhs.elements());
    return dst;
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto operator-(const Matrix2<T>& lhs, const Matrix2<T>& rhs)
    -> Matrix2<T> {
    Matrix2<T> dst;
    scalar::kernel_sub_mat2<T>(dst.elements(), lhs.elements(), rhs.elements());
    return dst;
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto operator*(double scale, const Matrix2<T>& mat) -> Matrix2<T> {
    Matrix2<T> dst;
    scalar::kernel_scale_mat2(dst.elements(), static_cast<T>(scale),
                              mat.elements());
    return dst;
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix2<T>& mat, double scale) -> Matrix2<T> {
    Matrix2<T> dst;
    scalar::kernel_scale_mat2(dst.elements(), static_cast<T>(scale),
                              mat.elements());
    return dst;
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix2<T>& lhs, const Matrix2<T>& rhs)
    -> Matrix2<T> {
    Matrix2<T> dst;
    scalar::kernel_matmul_mat2<T>(dst.elements(), lhs.elements(),
                                  rhs.elements());
    return dst;
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix2<T>& lhs_mat, const Vector2<T>& rhs_vec)
    -> Vector2<T> {
    Vector2<T> dst;
    scalar::kernel_matmul_vec_mat2<T>(dst.elements(), lhs_mat.elements(),
                                      rhs_vec.elements());
    return dst;
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto hadamard(const Matrix2<T>& lhs, const Matrix2<T>& rhs)
    -> Matrix2<T> {
    Matrix2<T> dst;
    scalar::kernel_hadamard_mat2<T>(dst.elements(), lhs.elements(),
                                    rhs.elements());
    return dst;
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto operator==(const Matrix2<T>& lhs, const Matrix2<T>& rhs)
    -> bool {
    return scalar::kernel_compare_eq_mat2<T>(lhs.elements(), rhs.elements());
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
LM_INLINE auto operator!=(const Matrix2<T>& lhs, const Matrix2<T>& rhs)
    -> bool {
    return !scalar::kernel_compare_eq_mat2<T>(lhs.elements(), rhs.elements());
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
auto operator<<(std::ostream& output_stream, const Matrix2<T>& src)
    -> std::ostream& {
    constexpr int PRECISION_DIGITS = 10;
    output_stream << std::setprecision(PRECISION_DIGITS);
    output_stream << "( " << src[0][0] << ", " << src[1][0] << '\n';
    output_stream << "  " << src[0][1] << ", " << src[1][1] << " )";
    return output_stream;
}

template <typename T, SFINAE_MAT2_GUARD<T> = nullptr>
auto operator>>(std::istream& input_stream, Matrix2<T>& dst) -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3MPgPcW
    input_stream.setf(std::ios_base::skipws);
    // Temporary place to store the inputs given by the user
    std::array<T, Matrix2<T>::BUFFER_SIZE> mat;
    // Get these many items/elements from the input stream
    input_stream >> mat[0] >> mat[1] >> mat[2] >> mat[3];
    if (!input_stream.fail()) {
        dst(0, 0) = mat[0];
        dst(0, 1) = mat[1];
        dst(1, 0) = mat[2];
        dst(1, 1) = mat[3];
    }
    return input_stream;
}

}  // namespace math
}  // namespace loco
