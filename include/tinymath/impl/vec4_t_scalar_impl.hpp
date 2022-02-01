#pragma once

#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

template <typename T>
using ArrayBuffer = typename Vector4<T>::BufferType;

template <typename T>
constexpr int32_t VECTOR_NDIM = Vector4<T>::VECTOR_NDIM;

template <typename T>
constexpr int32_t BUFFER_SIZE = Vector4<T>::BUFFER_SIZE;

// NOLINTNEXTLINE
#define COMPILE_TIME_CHECKS_VEC4_SCALAR(T)                                \
    {                                                                     \
        static_assert(BUFFER_SIZE<T> == 4,                                \
                      "Must use 4 elements for the internal buffer");     \
        static_assert(VECTOR_NDIM<T> == 4,                                \
                      "Must use 4 elements for the vector elements");     \
        static_assert(                                                    \
            sizeof(Vector4<T>) == sizeof(std::array<T, BUFFER_SIZE<T>>),  \
            "Must use exactly this many bytes of storage");               \
        static_assert(                                                    \
            alignof(Vector4<T>) == sizeof(std::array<T, BUFFER_SIZE<T>>), \
            "Must be aligned to its corresponding size");                 \
    }

template <typename T>
using SFINAE_VEC4_SCALAR_GUARD =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec4(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_SCALAR(T)
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_vec4(ArrayBuffer<T>& dst, const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_SCALAR(T)
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_vec4(ArrayBuffer<T>& dst, T scale,
                                 const ArrayBuffer<T>& vec) -> void {
    COMPILE_TIME_CHECKS_VEC4_SCALAR(T)
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_vec4(ArrayBuffer<T>& dst,
                                    const ArrayBuffer<T>& lhs,
                                    const ArrayBuffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_SCALAR(T)
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] * rhs[i];
    }
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_dot_vec4(const ArrayBuffer<T>& lhs,
                               const ArrayBuffer<T>& rhs) -> T {
    COMPILE_TIME_CHECKS_VEC4_SCALAR(T)
    T accum = static_cast<T>(0.0);
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        accum += lhs[i] * rhs[i];
    }
    return accum;
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_compare_eq_vec4(const ArrayBuffer<T>& lhs,
                                      const ArrayBuffer<T>& rhs) -> bool {
    COMPILE_TIME_CHECKS_VEC4_SCALAR(T)
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        if (std::abs(lhs[i] - rhs[i]) >= tiny::math::EPS<T>) {
            return false;
        }
    }
    return true;
}

}  // namespace scalar
}  // namespace math
}  // namespace tiny
