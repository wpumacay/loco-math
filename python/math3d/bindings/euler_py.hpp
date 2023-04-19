#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <common_py.hpp>
#include <conversions_py.hpp>

namespace py = pybind11;

namespace math {

// NOLINTNEXTLINE
auto bindings_euler_enums(py::module& m) -> void {
    py::enum_<::math::euler::Order>(m, "eOrder")
        .value("XYZ", ::math::euler::Order::XYZ)
        .value("YZX", ::math::euler::Order::YZX)
        .value("ZXY", ::math::euler::Order::ZXY)
        .value("XZY", ::math::euler::Order::XZY)
        .value("YXZ", ::math::euler::Order::YXZ)
        .value("ZYX", ::math::euler::Order::ZYX);

    py::enum_<::math::euler::Convention>(m, "eConvention")
        .value("INTRINSIC", ::math::euler::Convention::INTRINSIC)
        .value("EXTRINSIC", ::math::euler::Convention::EXTRINSIC);
}

template <typename T>
using SFINAE_EULER_BINDINGS =
    typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_EULER_BINDINGS<T> = nullptr>
// NOLINTNEXTLINE
auto bindings_euler(py::module& m, const char* class_name) -> void {
    using Vec3 = ::math::Vector3<T>;
    using Mat3 = ::math::Matrix3<T>;
    using Mat4 = ::math::Matrix4<T>;
    using Quat = ::math::Quaternion<T>;

    using Class = ::math::Euler<T>;
    py::class_<Class>(m, class_name)
        .def(py::init<>())
        .def(py::init<T, T, T>())
        .def(py::init<Mat3>())
        .def(py::init<Mat4>())
        .def(py::init<Quat>())
        .def(py::init<Vec3, T>())
        .def_readwrite("order", &Class::order)
        .def_readwrite("convention", &Class::convention)
        .def_readwrite("x", &Class::x)
        .def_readwrite("y", &Class::y)
        .def_readwrite("z", &Class::z)
        .def(
            "setFromRotationMatrix",
            [](Class& self, const py::array_t<T>& mat3_np) -> void {
                self.setFromRotationMatrix(::math::nparray_to_mat3<T>(mat3_np));
            })
        .def("setFromTransform",
             [](Class& self, const py::array_t<T>& mat4_np) -> void {
                 self.setFromTransform(::math::nparray_to_mat4<T>(mat4_np));
             })
        .def("setFromQuaternion",
             [](Class& self, const py::array_t<T>& quat_np) -> void {
                 auto quat_v4 = ::math::nparray_to_vec4<T>(quat_np);
                 self.setFromQuaternion(
                     Quat(quat_v4.x(), quat_v4.y(), quat_v4.z(), quat_v4.w()));
             })
        .def("setFromAxisAngle",
             [](Class& self, const py::array_t<T>& axis_np, T angle) -> void {
                 auto axis_v4 = ::math::nparray_to_vec3<T>(axis_np);
                 self.setFromAxisAngle(axis_v4, angle);
             })
        .def("__repr__", [](const Class& self) -> py::str {
            return py::str(
                       "Euler({}, {}, {}, dtype={}, order={}, convention={})")
                .format(self.x, self.y, self.z,
                        (IsFloat32<T>::value ? "float32" : "float64"),
                        ::math::euler::ToString(self.order),
                        ::math::euler::ToString(self.convention));
        });
}

}  // namespace math
