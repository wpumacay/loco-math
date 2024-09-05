#pragma once

#include <cmath>

#include "../vec2_t_decl.hpp"

namespace math {
namespace scalar {

template <typename T>
using Vec2Buffer = typename Vector2<T>::BufferType;

template <typename T>
MATH3D_INLINE auto kernel_add_vec2(Vec2Buffer<T>& dst, const Vec2Buffer<T>& lhs,
                                   const Vec2Buffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Vector2<T>::VECTOR_SIZE; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

template <typename T>
MATH3D_INLINE auto kernel_sub_vec2(Vec2Buffer<T>& dst, const Vec2Buffer<T>& lhs,
                                   const Vec2Buffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Vector2<T>::VECTOR_SIZE; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

template <typename T>
MATH3D_INLINE auto kernel_scale_vec2(Vec2Buffer<T>& dst, T scale,
                                     const Vec2Buffer<T>& vec) -> void {
    for (uint32_t i = 0; i < Vector2<T>::VECTOR_SIZE; ++i) {
        dst[i] = scale * vec[i];
    }
}

template <typename T>
MATH3D_INLINE auto kernel_hadamard_vec2(Vec2Buffer<T>& dst,
                                        const Vec2Buffer<T>& lhs,
                                        const Vec2Buffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Vector2<T>::VECTOR_SIZE; ++i) {
        dst[i] = lhs[i] * rhs[i];
    }
}

template <typename T>
MATH3D_INLINE auto kernel_length_square_vec2(const Vec2Buffer<T>& vec) -> T {
    T accum = static_cast<T>(0.0);
    for (uint32_t i = 0; i < Vector2<T>::VECTOR_SIZE; ++i) {
        accum += vec[i] * vec[i];
    }
    return accum;
}

template <typename T>
MATH3D_INLINE auto kernel_normalize_in_place_vec2(Vec2Buffer<T>& vec) -> void {
    auto length = std::sqrt(kernel_length_square_vec2<T>(vec));
    for (uint32_t i = 0; i < Vector2<T>::VECTOR_SIZE; ++i) {
        vec[i] /= length;
    }
}

template <typename T>
MATH3D_INLINE auto kernel_dot_vec2(const Vec2Buffer<T>& lhs,
                                   const Vec2Buffer<T>& rhs) -> T {
    T accum = static_cast<T>(0.0);
    for (uint32_t i = 0; i < Vector2<T>::VECTOR_SIZE; ++i) {
        accum += lhs[i] * rhs[i];
    }
    return accum;
}

template <typename T>
MATH3D_INLINE auto kernel_compare_eq_vec2(const Vec2Buffer<T>& lhs,
                                          const Vec2Buffer<T>& rhs) -> bool {
    for (uint32_t i = 0; i < Vector2<T>::VECTOR_SIZE; ++i) {
        if (std::abs(lhs[i] - rhs[i]) >= static_cast<T>(math::EPS)) {
            return false;
        }
    }
    return true;
}

template <typename T>
MATH3D_INLINE auto kernel_lerp_vec2(Vec2Buffer<T>& dst,
                                    const Vec2Buffer<T>& vec_a,
                                    const Vec2Buffer<T>& vec_b, T alpha)
    -> void {
    dst[0] = (1 - alpha) * vec_a[0] + alpha * vec_b[0];
    dst[1] = (1 - alpha) * vec_a[1] + alpha * vec_b[1];
}

}  // namespace scalar
}  // namespace math
