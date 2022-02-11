#pragma once

#include <cmath>
#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace scalar {

template <typename T>
using Vec3Buffer = typename Vector3<T>::BufferType;

template <typename T>
constexpr auto COMPILE_TIME_CHECKS_VEC3_SCALAR() -> int {
    static_assert(Vector3<T>::BUFFER_SIZE == 4,
                  "Must use 4 elements for the internal buffer");
    static_assert(Vector3<T>::VECTOR_NDIM == 3,
                  "Must use 4 elements for the vector elements");
    static_assert(
        sizeof(Vector3<T>) == sizeof(std::array<T, Vector3<T>::BUFFER_SIZE>),
        "Must use exactly this many bytes of storage");
    static_assert(
        alignof(Vector3<T>) == sizeof(std::array<T, Vector3<T>::BUFFER_SIZE>),
        "Must be aligned to its corresponding size");
    return 0;
}

template <typename T>
using SFINAE_VEC3_SCALAR_GUARD =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_add_vec3(Vec3Buffer<T>& dst, const Vec3Buffer<T>& lhs,
                               const Vec3Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
    for (int32_t i = 0; i < Vector3<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] + rhs[i];
    }
}

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_sub_vec3(Vec3Buffer<T>& dst, const Vec3Buffer<T>& lhs,
                               const Vec3Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
    for (int32_t i = 0; i < Vector3<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] - rhs[i];
    }
}

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_scale_vec3(Vec3Buffer<T>& dst, T scale,
                                 const Vec3Buffer<T>& vec) -> void {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
    for (int32_t i = 0; i < Vector3<T>::VECTOR_NDIM; ++i) {
        dst[i] = scale * vec[i];
    }
}

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_hadamard_vec3(Vec3Buffer<T>& dst,
                                    const Vec3Buffer<T>& lhs,
                                    const Vec3Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
    for (int32_t i = 0; i < Vector3<T>::VECTOR_NDIM; ++i) {
        dst[i] = lhs[i] * rhs[i];
    }
}

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_length_square_vec3(const Vec3Buffer<T>& vec) -> T {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
    T accum = static_cast<T>(0.0);
    for (int32_t i = 0; i < Vector3<T>::VECTOR_NDIM; ++i) {
        accum += vec[i] * vec[i];
    }
    return accum;
}

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_normalize_in_place_vec3(Vec3Buffer<T>& vec) -> void {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
    auto length = std::sqrt(kernel_length_square_vec3<T>(vec));
    for (int32_t i = 0; i < Vector3<T>::VECTOR_NDIM; ++i) {
        vec[i] /= length;
    }
}

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_dot_vec3(const Vec3Buffer<T>& lhs,
                               const Vec3Buffer<T>& rhs) -> T {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
    T accum = static_cast<T>(0.0);
    for (int32_t i = 0; i < Vector3<T>::VECTOR_NDIM; ++i) {
        accum += lhs[i] * rhs[i];
    }
    return accum;
}

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_compare_eq_vec3(const Vec3Buffer<T>& lhs,
                                      const Vec3Buffer<T>& rhs) -> bool {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
    for (int32_t i = 0; i < Vector3<T>::VECTOR_NDIM; ++i) {
        if (std::abs(lhs[i] - rhs[i]) >= tiny::math::EPS<T>) {
            return false;
        }
    }
    return true;
}

template <typename T, SFINAE_VEC3_SCALAR_GUARD<T> = nullptr>
TM_INLINE auto kernel_cross_vec3(Vec3Buffer<T>& dst, const Vec3Buffer<T>& lhs,
                                 const Vec3Buffer<T>& rhs) -> void {
    COMPILE_TIME_CHECKS_VEC3_SCALAR<T>();
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
