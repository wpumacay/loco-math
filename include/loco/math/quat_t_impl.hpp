#pragma once

#include <loco/math/quat_t.hpp>
#include <loco/math/impl/quat_t_scalar_impl.hpp>
#include <loco/math/impl/quat_t_sse_impl.hpp>
#include <loco/math/impl/quat_t_avx_impl.hpp>

namespace loco {
namespace math {

template <typename T>
using SFINAE_QUAT_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

/// Returns the square of the length of this quaternion
template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto squareNorm(const Quaternion<T>& quat) -> T {
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_length_square_quat<T>(quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_length_square_quat<T>(quat.elements());
#else
    return scalar::kernel_length_square_quat<T>(quat.elements())
#endif
}

/// Returns the length of this quaternion
template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto norm(const Quaternion<T>& quat) -> T {
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_length_quat<T>(quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_length_quat<T>(quat.elements());
#else
    return std::sqrt(scalar::kernel_length_square_quat<T>(quat.elements()));
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

}  // namespace math
}  // namespace loco
