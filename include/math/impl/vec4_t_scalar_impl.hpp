#pragma once

#include <cmath>

#include "../vec4_t_decl.hpp"
#include "math/common.hpp"

// NOLINTNEXTLINE
namespace math {
namespace scalar {

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
MATH3D_INLINE auto kernel_add_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                                   const Vec4Buffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Vector4<T>::VECTOR_SIZE; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

template <typename T>
MATH3D_INLINE auto kernel_sub_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                                   const Vec4Buffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Vector4<T>::VECTOR_SIZE; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

template <typename T>
MATH3D_INLINE auto kernel_scale_vec4(Vec4Buffer<T>& dst, T scale,
                                     const Vec4Buffer<T>& vec) -> void {
    for (uint32_t i = 0; i < Vector4<T>::VECTOR_SIZE; ++i) {
        dst[i] = scale * vec[i];
    }
}

template <typename T>
MATH3D_INLINE auto kernel_hadamard_vec4(Vec4Buffer<T>& dst,
                                        const Vec4Buffer<T>& lhs,
                                        const Vec4Buffer<T>& rhs) -> void {
    for (uint32_t i = 0; i < Vector4<T>::VECTOR_SIZE; ++i) {
        dst[i] = lhs[i] * rhs[i];
    }
}

template <typename T>
MATH3D_INLINE auto kernel_length_square_vec4(const Vec4Buffer<T>& vec) -> T {
    T accum = static_cast<T>(0.0);
    for (uint32_t i = 0; i < Vector4<T>::VECTOR_SIZE; ++i) {
        accum += vec[i] * vec[i];
    }
    return accum;
}

template <typename T>
MATH3D_INLINE auto kernel_normalize_in_place_vec4(Vec4Buffer<T>& vec) -> void {
    auto length = std::sqrt(kernel_length_square_vec4<T>(vec));
    for (uint32_t i = 0; i < Vector4<T>::VECTOR_SIZE; ++i) {
        vec[i] /= length;
    }
}

template <typename T>
MATH3D_INLINE auto kernel_dot_vec4(const Vec4Buffer<T>& lhs,
                                   const Vec4Buffer<T>& rhs) -> T {
    T accum = static_cast<T>(0.0);
    for (uint32_t i = 0; i < Vector4<T>::VECTOR_SIZE; ++i) {
        accum += lhs[i] * rhs[i];
    }
    return accum;
}

template <typename T>
MATH3D_INLINE auto kernel_compare_eq_vec4(const Vec4Buffer<T>& lhs,
                                          const Vec4Buffer<T>& rhs) -> bool {
    for (uint32_t i = 0; i < Vector4<T>::VECTOR_SIZE; ++i) {
        if (std::abs(lhs[i] - rhs[i]) >= static_cast<T>(math::EPS)) {
            return false;
        }
    }
    return true;
}

template <typename T>
MATH3D_INLINE auto kernel_lerp_vec4(Vec4Buffer<T>& dst,
                                    const Vec4Buffer<T>& vec_a,
                                    const Vec4Buffer<T>& vec_b, T alpha)
    -> void {
    dst[0] = (1 - alpha) * vec_a[0] + alpha * vec_b[0];
    dst[1] = (1 - alpha) * vec_a[1] + alpha * vec_b[1];
    dst[2] = (1 - alpha) * vec_a[2] + alpha * vec_b[2];
    dst[3] = (1 - alpha) * vec_a[3] + alpha * vec_b[3];
}

}  // namespace scalar
}  // namespace math
