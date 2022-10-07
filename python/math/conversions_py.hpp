#pragma once

#include <stdexcept>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/pytypes.h>

#include <loco/math/vec2_t_impl.hpp>
#include <loco/math/vec3_t_impl.hpp>
#include <loco/math/vec4_t_impl.hpp>
#include <string>
#include "loco/math/common.hpp"

namespace py = pybind11;

namespace loco {
namespace math {

template <typename T>
using SFINAE_CONVERSIONS_BINDINGS =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto vec2_to_nparray(const Vector2<T>& vec) -> py::array_t<T> {
    auto array_np = py::array_t<T>(Vector2<T>::VECTOR_SIZE);
    memcpy(array_np.request().ptr, vec.data(), sizeof(Vector2<T>));
    return array_np;
}

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto vec3_to_nparray(const Vector3<T>& vec) -> py::array_t<T> {
    auto array_np = py::array_t<T>(Vector3<T>::VECTOR_SIZE);
    memcpy(array_np.request().ptr, vec.data(), sizeof(Vector3<T>));
    return array_np;
}

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto vec4_to_nparray(const Vector4<T>& vec) -> py::array_t<T> {
    auto array_np = py::array_t<T>(Vector4<T>::VECTOR_SIZE);
    memcpy(array_np.request().ptr, vec.data(), sizeof(Vector4<T>));
    return array_np;
}

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto nparray_to_vec2(const py::array_t<T>& array_np) -> Vector2<T> {
    auto array_buffer_info = array_np.request();
    if (array_buffer_info.size != Vector2<T>::VECTOR_SIZE) {
        throw std::runtime_error("Incompatible array size, expected " +
                                 std::to_string(Vector2<T>::VECTOR_SIZE) +
                                 " elements");
    }

    Vector2<T> vec;
    memcpy(vec.data(), array_buffer_info.ptr, sizeof(Vector2<T>));
    return vec;
}

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto nparray_to_vec3(const py::array_t<T>& array_np) -> Vector3<T> {
    auto array_buffer_info = array_np.request();
    if (array_buffer_info.size != Vector3<T>::VECTOR_SIZE) {
        throw std::runtime_error("Incompatible array size, expected " +
                                 std::to_string(Vector3<T>::VECTOR_SIZE) +
                                 " elements");
    }

    Vector3<T> vec;
    memcpy(vec.data(), array_buffer_info.ptr, sizeof(Vector3<T>));
    return vec;
}

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto nparray_to_vec4(const py::array_t<T>& array_np) -> Vector4<T> {
    auto array_buffer_info = array_np.request();
    if (array_buffer_info.size != Vector4<T>::VECTOR_SIZE) {
        throw std::runtime_error("Incompatible array size, expected " +
                                 std::to_string(Vector4<T>::VECTOR_SIZE) +
                                 " elements");
    }

    Vector4<T> vec;
    memcpy(vec.data(), array_buffer_info.ptr, sizeof(Vector4<T>));
    return vec;
}

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto buffer_to_vec4(const py::buffer& buff) -> Vector4<T> {
    py::buffer_info info = buff.request();
    if (IsFloat32<T>::value &&
        (info.format != py::format_descriptor<T>::format())) {
        throw std::runtime_error(
            "Incompatible format: expected float (float32) array");
    }
    if (IsFloat64<T>::value &&
        (info.format != py::format_descriptor<T>::format())) {
        throw std::runtime_error(
            "Incompatible format: expected double (float64) array");
    }
    // NOLINTNEXTLINE TODO(wilbert): cppcheck might be giving a false positive?
    bool is_valid_shape;
    if (info.ndim == 1) {
        is_valid_shape = (info.shape[0] == Vector4<T>::VECTOR_SIZE);
    } else if (info.ndim == 2) {
        is_valid_shape = (info.shape[0] == Vector4<T>::VECTOR_SIZE ||
                          info.shape[1] == Vector4<T>::VECTOR_SIZE);
    } else {
        is_valid_shape = false;
    }
    if (!is_valid_shape) {
        throw std::runtime_error(
            "Incompatible shape: expected (,n), (1,n), (n,1)");
    }
    Vector4<T> vec;
    memcpy(vec.data(), info.ptr, sizeof(T) * Vector4<T>::VECTOR_SIZE);
    return vec;
}

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto buffer_to_vec3(const py::buffer& buff) -> Vector3<T> {
    py::buffer_info info = buff.request();
    if (IsFloat32<T>::value &&
        (info.format != py::format_descriptor<T>::format())) {
        throw std::runtime_error(
            "Incompatible format: expected float (float32) array");
    }
    if (IsFloat64<T>::value &&
        (info.format != py::format_descriptor<T>::format())) {
        throw std::runtime_error(
            "Incompatible format: expected double (float64) array");
    }
    // NOLINTNEXTLINE TODO(wilbert): cppcheck might be giving a false positive?
    bool is_valid_shape;
    if (info.ndim == 1) {
        is_valid_shape = (info.shape[0] == Vector3<T>::VECTOR_SIZE);
    } else if (info.ndim == 2) {
        is_valid_shape = (info.shape[0] == Vector3<T>::VECTOR_SIZE ||
                          info.shape[1] == Vector3<T>::VECTOR_SIZE);
    } else {
        is_valid_shape = false;
    }
    if (!is_valid_shape) {
        throw std::runtime_error(
            "Incompatible shape: expected (,n), (1,n), (n,1)");
    }
    Vector3<T> vec;
    memcpy(vec.data(), info.ptr, sizeof(T) * Vector3<T>::VECTOR_SIZE);
    return vec;
}

template <typename T, SFINAE_CONVERSIONS_BINDINGS<T> = nullptr>
inline auto buffer_to_vec2(const py::buffer& buff) -> Vector2<T> {
    py::buffer_info info = buff.request();
    if (IsFloat32<T>::value &&
        (info.format != py::format_descriptor<T>::format())) {
        throw std::runtime_error(
            "Incompatible format: expected float (float32) array");
    }
    if (IsFloat64<T>::value &&
        (info.format != py::format_descriptor<T>::format())) {
        throw std::runtime_error(
            "Incompatible format: expected double (float64) array");
    }
    // NOLINTNEXTLINE TODO(wilbert): cppcheck might be giving a false positive?
    bool is_valid_shape;
    if (info.ndim == 1) {
        is_valid_shape = (info.shape[0] == Vector2<T>::VECTOR_SIZE);
    } else if (info.ndim == 2) {
        is_valid_shape = (info.shape[0] == Vector2<T>::VECTOR_SIZE ||
                          info.shape[1] == Vector2<T>::VECTOR_SIZE);
    } else {
        is_valid_shape = false;
    }
    if (!is_valid_shape) {
        throw std::runtime_error(
            "Incompatible shape: expected (,n), (1,n), (n,1)");
    }
    Vector2<T> vec;
    memcpy(vec.data(), info.ptr, sizeof(T) * Vector2<T>::VECTOR_SIZE);
    return vec;
}

}  // namespace math
}  // namespace loco
