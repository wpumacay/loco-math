#pragma once

#include <loco/math/quat_t.hpp>
#include <loco/math/impl/quat_t_scalar_impl.hpp>
#include <loco/math/impl/quat_t_sse_impl.hpp>
#include <loco/math/impl/quat_t_avx_impl.hpp>

namespace loco {
namespace math {

template <typename T>
using SFINAE_QUAT_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

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
LM_INLINE auto operator*(T scale, const Quaternion<T>& quat) -> Quaternion<T> {
    Quaternion<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_scale_quat<T>(dst.elements(), scale, quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_scale_quat<T>(dst.elements(), scale, quat.elements());
#else
    scalar::kernel_scale_quat<T>(dst.elements(), scale, quat.elements());
#endif
    return dst;
}

template <typename T, SFINAE_QUAT_GUARD<T> = nullptr>
LM_INLINE auto operator*(const Quaternion<T>& quat, T scale) -> Quaternion<T> {
    Quaternion<T> dst;
#if defined(LOCOMATH_AVX_ENABLED)
    avx::kernel_scale_quat<T>(dst.elements(), scale, quat.elements());
#elif defined(LOCOMATH_SSE_ENABLED)
    sse::kernel_scale_quat<T>(dst.elements(), scale, quat.elements());
#else
    scalar::kernel_scale_quat<T>(dst.elements(), scale, quat.elements());
#endif
    return dst;
}

}  // namespace math
}  // namespace loco
