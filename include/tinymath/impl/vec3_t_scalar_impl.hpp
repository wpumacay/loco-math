#pragma once

#include <cmath>
#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

template <typename T>
using ArrayBuffer = typename Vector3<T>::BufferType;

template <typename T>
constexpr int32_t NUM_ELEMENTS = Vector3<T>::VECTOR_NDIM;

template <typename T>
TM_INLINE auto kernel_add_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    for (int32_t i = 0; i < NUM_ELEMENTS<T>; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

template <typename T>
TM_INLINE auto kernel_sub_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    for (int32_t i = 0; i < NUM_ELEMENTS<T>; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

template <typename T>
TM_INLINE auto kernel_scale_vec3(ArrayBuffer<T>& dst, T scale,
                                 const ArrayBuffer<T>& vec) -> void {
    for (int32_t i = 0; i < NUM_ELEMENTS<T>; ++i) {
        dst[i] = scale * vec[i];
    }
}

template <typename T>
TM_INLINE auto kernel_hadamard_vec3(ArrayBuffer<T>& dst,
                                    const ArrayBuffer<T>& lhs,
                                    const ArrayBuffer<T>& rhs) -> void {
    for (int32_t i = 0; i < NUM_ELEMENTS<T>; ++i) {
        dst[i] = lhs[i] * rhs[i];
    }
}

template <typename T>
TM_INLINE auto kernel_length_square_vec3(const ArrayBuffer<T>& vec) -> T {
    T accum = static_cast<T>(0.0);
    for (int32_t i = 0; i < NUM_ELEMENTS<T>; ++i) {
        accum += vec[i] * vec[i];
    }
    return accum;
}

template <typename T>
TM_INLINE auto kernel_normalize_in_place_vec3(ArrayBuffer<T>& vec) -> void {
    auto length = std::sqrt(kernel_length_square_vec3<T>(vec));
    for (int32_t i = 0; i < NUM_ELEMENTS<T>; ++i) {
        vec[i] /= length;
    }
}

template <typename T>
TM_INLINE auto kernel_dot_vec3(const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> T {
    T accum = static_cast<T>(0.0);
    for (int32_t i = 0; i < NUM_ELEMENTS<T>; ++i) {
        accum += lhs[i] * rhs[i];
    }
    return accum;
}

template <typename T>
TM_INLINE auto kernel_compare_eq_vec3(const ArrayBuffer<T>& lhs,
                                      const ArrayBuffer<T>& rhs) -> bool {
    for (int32_t i = 0; i < NUM_ELEMENTS<T>; ++i) {
        if (std::abs(lhs[i] - rhs[i]) >= tiny::math::EPS<T>) {
            return false;
        }
    }
    return true;
}

template <typename T>
TM_INLINE auto kernel_cross_vec3(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                                 const ArrayBuffer<T>& rhs) -> void {
    // v.x =  v1.y  *  v2.z  -  v1.z  *  v2.y
    dst[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    // v.y =  v1.z  *  v2.x  -  v1.x  *  v2.z
    dst[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    // v.z =  v1.x  *  v2.y  -  v1.y  *  v2.x
    dst[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
