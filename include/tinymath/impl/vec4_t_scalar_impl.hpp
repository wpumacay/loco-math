#pragma once

#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

template <typename T>
using Vec4Buffer = typename Vector4<T>::BufferType;

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_VEC4_SCALAR() -> void {
    static_assert(Vector4<T>::BUFFER_SIZE == 4,
                  "Must use 4 elements for the internal buffer");
    static_assert(Vector4<T>::VECTOR_NDIM == 4,
                  "Must use 4 elements for the vector elements");
    static_assert(
        sizeof(Vector4<T>) == sizeof(std::array<T, Vector4<T>::BUFFER_SIZE>),
        "Must use exactly this many bytes of storage");
    static_assert(
        alignof(Vector4<T>) == sizeof(std::array<T, Vector4<T>::BUFFER_SIZE>),
        "Must be aligned to its corresponding size");
}

template <typename T>
using SFINAE_VEC4_SCALAR_GUARD =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_SCALAR<T>();
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_vec4(Vec4Buffer<T>& dst, const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_SCALAR<T>();
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_vec4(Vec4Buffer<T>& dst, T scale,
                                 const Vec4Buffer<T>& vec) -> void {
    COMPILE_TIME_CHECKS_VEC4_SCALAR<T>();
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_vec4(Vec4Buffer<T>& dst,
                                    const Vec4Buffer<T>& lhs,
                                    const Vec4Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC4_SCALAR<T>();
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] * rhs[i];
    }
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_dot_vec4(const Vec4Buffer<T>& lhs,
                               const Vec4Buffer<T>& rhs) -> T {
    COMPILE_TIME_CHECKS_VEC4_SCALAR<T>();
    T accum = static_cast<T>(0.0);
    for (int32_t i = 0; i < Vector4<T>::VECTOR_NDIM; ++i) {
        accum += lhs[i] * rhs[i];
    }
    return accum;
}

template <typename T, SFINAE_VEC4_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_compare_eq_vec4(const Vec4Buffer<T>& lhs,
                                      const Vec4Buffer<T>& rhs) -> bool {
    COMPILE_TIME_CHECKS_VEC4_SCALAR<T>();
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
