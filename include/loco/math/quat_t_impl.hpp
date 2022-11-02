#pragma once

#include <loco/math/quat_t.hpp>
#include <loco/math/impl/quat_t_scalar_impl.hpp>
#include <loco/math/impl/quat_t_sse_impl.hpp>
#include <loco/math/impl/quat_t_avx_impl.hpp>

namespace loco {
namespace math {

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
