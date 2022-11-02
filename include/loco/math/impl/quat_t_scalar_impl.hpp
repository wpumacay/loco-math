#pragma once

#include <cmath>
#include <loco/math/quat_t.hpp>
#include "loco/math/common.hpp"

namespace loco {
namespace math {
namespace scalar {

template <typename T>
using QuatBuffer = typename Quaternion<T>::BufferType;

template <typename T>
using SFINAE_QUAT_SCALAR_GUARD =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_QUAT_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_quat(QuatBuffer<T>& dst, const QuatBuffer<T>& lhs,
                               const QuatBuffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Quaternion<T>::QUAT_SIZE; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

template <typename T, SFINAE_QUAT_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_quat(QuatBuffer<T>& dst, const QuatBuffer<T>& lhs,
                               const QuatBuffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Quaternion<T>::QUAT_SIZE; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

template <typename T, SFINAE_QUAT_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_quat(QuatBuffer<T>& dst, T scale,
                                 const QuatBuffer<T>& quat) -> void {
    for (uint32_t i = 0; i < Quaternion<T>::QUAT_SIZE; ++i) {
        dst[i] = scale * quat[i];
    }
}

template <typename T, SFINAE_QUAT_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_length_square_quat(const QuatBuffer<T>& quat) -> T {
    return quat[0] * quat[0] + quat[1] * quat[1] + quat[2] * quat[2] +
           quat[3] * quat[3];
}

template <typename T, SFINAE_QUAT_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_normalize_in_place_quat(QuatBuffer<T>& quat) -> T {
    auto length = std::sqrt(kernel_length_square_quat<T>(quat));
    for (uint32_t i = 0; i < Quaternion<T>::QUAT_SIZE; ++i) {
        quat[i] /= length;
    }
}

template <typename T, SFINAE_QUAT_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_compare_eq_quat(const QuatBuffer<T>& lhs,
                                      const QuatBuffer<T>& rhs) -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    for (uint32_t i = 0; i < Quaternion<T>::QUAT_SIZE; ++i) {
        if (std::abs(lhs[i] - rhs[i]) >= EPSILON) {
            return false;
        }
    }
    return true;
}

}  // namespace scalar
}  // namespace math
}  // namespace loco
