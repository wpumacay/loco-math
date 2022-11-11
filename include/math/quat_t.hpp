#pragma once

#include <cmath>

#include <math/quat_t_decl.hpp>

#include <math/impl/quat_t_scalar_impl.hpp>
#include <math/impl/quat_t_sse_impl.hpp>
#include <math/impl/quat_t_avx_impl.hpp>

#include <math/vec3_t.hpp>

namespace loco {
namespace math {

// ***************************************************************************//
//                       Factory functions implementation                     //
// ***************************************************************************//

template <typename T>
auto Quaternion<T>::RotationX(T angle) -> Quaternion<T> {
    auto cos_half = std::cos(angle / static_cast<T>(2.0));
    auto sin_half = std::sin(angle / static_cast<T>(2.0));
    return Quaternion<T>(cos_half, sin_half, 0, 0);
}

template <typename T>
auto Quaternion<T>::RotationY(T angle) -> Quaternion<T> {
    auto cos_half = std::cos(angle / static_cast<T>(2.0));
    auto sin_half = std::sin(angle / static_cast<T>(2.0));
    return Quaternion<T>(cos_half, 0, sin_half, 0);
}

template <typename T>
auto Quaternion<T>::RotationZ(T angle) -> Quaternion<T> {
    auto cos_half = std::cos(angle / static_cast<T>(2.0));
    auto sin_half = std::sin(angle / static_cast<T>(2.0));
    return Quaternion<T>(cos_half, 0, 0, sin_half);
}

template <typename T>
auto Quaternion<T>::FromAxisAngle(Vector3<T> axis, T angle) -> Quaternion<T> {
    // Just in case, make sure the axis is normalized
    normalize_in_place<T>(axis);

    auto cos_half = std::cos(angle / static_cast<T>(2.0));
    auto sin_half = std::sin(angle / static_cast<T>(2.0));
    return Quaternion<T>(cos_half, sin_half * axis.x(), sin_half * axis.y(),
                         sin_half * axis.z());
}

template <typename T>
auto Quaternion<T>::FromRotationMatrix(Matrix3<T> matrix) -> Quaternion<T> {
    auto m00 = matrix(0, 0);
    auto m01 = matrix(0, 1);
    auto m02 = matrix(0, 2);

    auto m10 = matrix(1, 0);
    auto m11 = matrix(1, 1);
    auto m12 = matrix(1, 2);

    auto m20 = matrix(2, 0);
    auto m21 = matrix(2, 1);
    auto m22 = matrix(2, 2);

    Quaternion<T> quat;
    auto trace = m00 + m11 + m22;
    if (trace > 0) {
        // The trace is valid, so we can do the algebra around solving for w
        auto s = static_cast<T>(0.5) / std::sqrt(trace + static_cast<T>(1.0));

        quat.w() = static_cast<T>(0.25) / s;
        quat.x() = (m21 - m12) * s;
        quat.y() = (m02 - m20) * s;
        quat.z() = (m10 - m01) * s;
    } else if ((m00 > m11) && (m00 > m22)) {
        // m00 is the dominant term, so do the algebra around solving for x
        auto s = static_cast<T>(2.0) *
                 std::sqrt(static_cast<T>(1.0) + m00 - m11 - m22);

        quat.w() = (m21 - m12) / s;
        quat.x() = static_cast<T>(0.25) * s;
        quat.y() = (m01 + m10) / s;
        quat.z() = (m02 + m20) / s;
    } else if (m11 > m22) {
        // m11 is the dominant term, so do the algebra around solving for y
        auto s = static_cast<T>(2.0) *
                 std::sqrt(static_cast<T>(1.0) + m11 - m00 - m22);

        quat.w() = (m02 - m20) / s;
        quat.x() = (m01 + m10) / s;
        quat.y() = static_cast<T>(0.25) * s;
        quat.z() = (m12 + m21) / s;
    } else {
        // m22 is the dominant term, so do the algebra around solving for z
        auto s = static_cast<T>(2.0) *
                 std::sqrt(static_cast<T>(1.0) + m22 - m00 - m11);

        quat.w() = (m10 - m01) / s;
        quat.x() = (m02 + m20) / s;
        quat.y() = (m12 + m21) / s;
        quat.z() = static_cast<T>(0.25) * s;
    }

    return quat;
}

template <typename T>
auto Quaternion<T>::FromRotationMatrix(Matrix4<T> matrix) -> Quaternion<T> {
    auto m00 = matrix(0, 0);
    auto m01 = matrix(0, 1);
    auto m02 = matrix(0, 2);

    auto m10 = matrix(1, 0);
    auto m11 = matrix(1, 1);
    auto m12 = matrix(1, 2);

    auto m20 = matrix(2, 0);
    auto m21 = matrix(2, 1);
    auto m22 = matrix(2, 2);

    Quaternion<T> quat;
    auto trace = m00 + m11 + m22;
    if (trace > 0) {
        // The trace is valid, so we can do the algebra around solving for w
        auto s = static_cast<T>(0.5) / std::sqrt(trace + static_cast<T>(1.0));

        quat.w() = static_cast<T>(0.25) / s;
        quat.x() = (m21 - m12) * s;
        quat.y() = (m02 - m20) * s;
        quat.z() = (m10 - m01) * s;
    } else if ((m00 > m11) && (m00 > m22)) {
        // m00 is the dominant term, so do the algebra around solving for x
        auto s = static_cast<T>(2.0) *
                 std::sqrt(static_cast<T>(1.0) + m00 - m11 - m22);

        quat.w() = (m21 - m12) / s;
        quat.x() = static_cast<T>(0.25) * s;
        quat.y() = (m01 + m10) / s;
        quat.z() = (m02 + m20) / s;
    } else if (m11 > m22) {
        // m11 is the dominant term, so do the algebra around solving for y
        auto s = static_cast<T>(2.0) *
                 std::sqrt(static_cast<T>(1.0) + m11 - m00 - m22);

        quat.w() = (m02 - m20) / s;
        quat.x() = (m01 + m10) / s;
        quat.y() = static_cast<T>(0.25) * s;
        quat.z() = (m12 + m21) / s;
    } else {
        // m22 is the dominant term, so do the algebra around solving for z
        auto s = static_cast<T>(2.0) *
                 std::sqrt(static_cast<T>(1.0) + m22 - m00 - m11);

        quat.w() = (m10 - m01) / s;
        quat.x() = (m02 + m20) / s;
        quat.y() = (m12 + m21) / s;
        quat.z() = static_cast<T>(0.25) * s;
    }

    return quat;
}

// ***************************************************************************//
//                      Quaternion Methods implementation                     //
// ***************************************************************************//

template <typename T>
using SFINAE_QUAT_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

/// Returns the square of the length of the given quaternion
template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto squareNorm(const Quaternion<T>& quat) -> T {
#if defined(LOCOMATH_AVX_ENABLED)
    return avx::kernel_length_square_quat<T>(quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    return sse::kernel_length_square_quat<T>(quat.elements());
#else
    return scalar::kernel_length_square_quat<T>(quat.elements());
#endif
}

/// Returns the length of the given quaternion
template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto norm(const Quaternion<T>& quat) -> T {
#if defined(LOCOMATH_AVX_ENABLED)
    return avx::kernel_length_quat<T>(quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    return sse::kernel_length_quat<T>(quat.elements());
#else
    return std::sqrt(scalar::kernel_length_square_quat<T>(quat.elements()));
#endif
}

/// Returns a normalized version of the given quaternion
template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto normalize(const Quaternion<T>& quat) -> Quaternion<T> {
    Quaternion<T> quat_normalized = quat;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_normalize_in_place_quat<T>(quat_normalized.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_normalize_in_place_quat<T>(quat_normalized.elements());
#else
    scalar::kernel_normalize_in_place_quat<T>(quat_normalized.elements());
#endif
    return quat_normalized;
}

/// Normalizes in place the given quaternion
template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto normalize_in_place(Quaternion<T>& quat) -> void {  // NOLINT
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_normalize_in_place_quat<T>(quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_normalize_in_place_quat<T>(quat.elements());
#else
    scalar::kernel_normalize_in_place_quat<T>(quat.elements());
#endif
}

template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto operator+(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
    -> Quaternion<T> {
    Quaternion<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_add_quat<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_add_quat<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add_quat<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto operator-(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
    -> Quaternion<T> {
    Quaternion<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_sub_quat<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_sub_quat<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub_quat<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto operator*(double scale, const Quaternion<T>& quat)
    -> Quaternion<T> {
    Quaternion<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_scale_quat<T>(dst.elements(), static_cast<T>(scale),
                              quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_scale_quat<T>(dst.elements(), static_cast<T>(scale),
                              quat.elements());
#else
    scalar::kernel_scale_quat<T>(dst.elements(), static_cast<T>(scale),
                                 quat.elements());
#endif
    return dst;
}

template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Quaternion<T>& quat, double scale)
    -> Quaternion<T> {
    Quaternion<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_scale_quat<T>(dst.elements(), static_cast<T>(scale),
                              quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_scale_quat<T>(dst.elements(), static_cast<T>(scale),
                              quat.elements());
#else
    scalar::kernel_scale_quat<T>(dst.elements(), static_cast<T>(scale),
                                 quat.elements());
#endif
    return dst;
}

template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
    -> Quaternion<T> {
    Quaternion<T> dst;
    scalar::kernel_quatmul_quat<T>(dst.elements(), lhs.elements(),
                                   rhs.elements());
    return dst;
}

template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto operator==(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
    -> bool {
    return scalar::kernel_compare_eq_quat<T>(lhs.elements(), rhs.elements());
}

template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto operator!=(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
    -> bool {
    return !scalar::kernel_compare_eq_quat<T>(lhs.elements(), rhs.elements());
}

}  // namespace math
}  // namespace loco
