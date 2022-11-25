#pragma once

#include <cmath>

#include <math/mat3_t_decl.hpp>

#include <math/impl/mat3_t_scalar_impl.hpp>
#include <math/impl/mat3_t_sse_impl.hpp>
#include <math/impl/mat3_t_avx_impl.hpp>

#include <math/quat_t.hpp>

namespace math {

// ***************************************************************************//
//                       Factory functions implementation                     //
// ***************************************************************************//

template <typename T>
auto Matrix3<T>::FromQuaternion(Quaternion<T> quat) -> Matrix3<T> {
    // Just in case, make sure the quaternion is normalized
    normalize_in_place<T>(quat);

    // TODO(wilbert): Should we get x, y, and z first, to avoid lots of accesses
    auto xx = quat.x() * quat.x();
    auto yy = quat.y() * quat.y();
    auto zz = quat.z() * quat.z();
    auto xy = quat.x() * quat.y();
    auto wz = quat.w() * quat.z();
    auto xz = quat.x() * quat.z();
    auto wy = quat.w() * quat.y();
    auto yz = quat.y() * quat.z();
    auto wx = quat.w() * quat.x();

    // clang-format off
    return Matrix3<T>(
        static_cast<T>(1.0) - static_cast<T>(2.0) * (yy + zz),
        static_cast<T>(2.0) * (xy - wz),
        static_cast<T>(2.0) * (xz + wy),
        static_cast<T>(2.0) * (xy + wz),
        static_cast<T>(1.0) - static_cast<T>(2.0) * (xx + zz),
        static_cast<T>(2.0) * (yz - wx),
        static_cast<T>(2.0) * (xz - wy),
        static_cast<T>(2.0) * (yz + wx),
        static_cast<T>(1.0) - static_cast<T>(2.0) * (xx + yy));
    // clang-format on
}

template <typename T>
auto Matrix3<T>::RotationX(T angle) -> Matrix3<T> {
    auto cos_t = std::cos(angle);
    auto sin_t = std::sin(angle);
    // clang-format off
    return Matrix3<T>(
        1.0, 0.0, 0.0,
        0.0, cos_t, -sin_t,
        0.0, sin_t, cos_t);
    // clang-format on
}

template <typename T>
auto Matrix3<T>::RotationY(T angle) -> Matrix3<T> {
    auto cos_t = std::cos(angle);
    auto sin_t = std::sin(angle);
    // clang-format off
    return Matrix3<T>(
        cos_t, 0.0, sin_t,
          0.0, 1.0,   0.0,
       -sin_t, 0.0, cos_t);
    // clang-format on
}

template <typename T>
auto Matrix3<T>::RotationZ(T angle) -> Matrix3<T> {
    auto cos_t = std::cos(angle);
    auto sin_t = std::sin(angle);
    // clang-format off
    return Matrix3<T>(
        cos_t, -sin_t, 0.0,
        sin_t,  cos_t, 0.0,
          0.0,    0.0, 1.0);
    // clang-format on
}

template <typename T>
auto Matrix3<T>::Scale(T scale_x, T scale_y, T scale_z) -> Matrix3<T> {
    // clang-format off
    return Matrix3<T>(
        scale_x,     0.0,     0.0,
            0.0, scale_y,     0.0,
            0.0,     0.0, scale_z);
    // clang-format on
}

template <typename T>
auto Matrix3<T>::Scale(const Vector3<T>& scale) -> Matrix3<T> {
    // clang-format off
    return Matrix3<T>(
        scale.x(),       0.0,       0.0,
              0.0, scale.y(),       0.0,
              0.0,       0.0, scale.z());
    // clang-format on
}

template <typename T>
auto Matrix3<T>::Identity() -> Matrix3<T> {
    // clang-format off
    return Matrix3<T>(
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0);
    // clang-format on
}

template <typename T>
auto Matrix3<T>::Zeros() -> Matrix3<T> {
    return Matrix3<T>();
}

// ***************************************************************************//
//                       Matrix Methods implementation                        //
// ***************************************************************************//

template <typename T>
using SFINAE_MAT3_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

/// Returns the tranpose of the given matrix
template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto transpose(const Matrix3<T>& mat) -> Matrix3<T> {
    Matrix3<T> dst = mat;
    scalar::kernel_transpose_inplace_mat3<T>(dst.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto tranposeInPlace(Matrix3<T>& mat) -> void {  // NOLINT
    scalar::kernel_transpose_inplace_mat3<T>(mat.elements());
}

/// Returns the trace (sum of diagonal elements) of the matrix
template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto trace(const Matrix3<T>& mat) -> T {
    return scalar::kernel_trace_mat3<T>(mat.elements());
}

/// Returns the determinant of the matrix
template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto determinant(const Matrix3<T>& mat) -> T {
    return scalar::kernel_determinant_mat3<T>(mat.elements());
}

/// Returns the inverse of the matrix
template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto inverse(const Matrix3<T>& mat) -> Matrix3<T> {
    Matrix3<T> dst;
    scalar::kernel_inverse_mat3<T>(dst.elements(), mat.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator+(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> Matrix3<T> {
    Matrix3<T> dst;
    scalar::kernel_add_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator-(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> Matrix3<T> {
    Matrix3<T> dst;
    scalar::kernel_sub_mat3<T>(dst.elements(), lhs.elements(), rhs.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator*(double scale, const Matrix3<T>& mat) -> Matrix3<T> {
    Matrix3<T> dst;
    scalar::kernel_scale_mat3<T>(dst.elements(), static_cast<T>(scale),
                                 mat.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix3<T>& mat, double scale) -> Matrix3<T> {
    Matrix3<T> dst;
    scalar::kernel_scale_mat3<T>(dst.elements(), static_cast<T>(scale),
                                 mat.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> Matrix3<T> {
    Matrix3<T> dst;
    scalar::kernel_matmul_mat3<T>(dst.elements(), lhs.elements(),
                                  rhs.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Matrix3<T>& lhs_mat, const Vector3<T>& rhs_vec)
    -> Vector3<T> {
    Vector3<T> dst;
    scalar::kernel_matmul_vec_mat3<T>(dst.elements(), lhs_mat.elements(),
                                      rhs_vec.elements());
    return dst;
}

template <typename T, SFINAE_MAT3_GUARD<T> = nullptr>
LM_INLINE auto hadamard(const Matrix3<T>& lhs, const Matrix3<T>& rhs)
    -> Matrix3<T> {
    Matrix3<T> dst;
    scalar::kernel_hadamard_mat3<T>(dst.elements(), lhs.elements(),
                                    rhs.elements());
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
