#pragma once

#include <loco/math/quat_t.hpp>
#include <type_traits>

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
    for (uint32_t i = 0; i < Quaternion<T>::QUAT_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

template <typename T, SFINAE_QUAT_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_quat(QuatBuffer<T>& dst, const QuatBuffer<T>& lhs,
                               const QuatBuffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Quaternion<T>::QUAT_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

template <typename T, SFINAE_QUAT_SCALAR_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_quat(QuatBuffer<T>& dst, T scale,
                                 const QuatBuffer<T>& quat) -> void {
    for (uint32_t i = 0; i < Quaternion<T>::QUAT_NDIM; ++i) {
        dst[i] = scale * quat[i];
    }
}

}  // namespace scalar
}  // namespace math
}  // namespace loco
