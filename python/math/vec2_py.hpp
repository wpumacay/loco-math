#pragma once

#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>
#include <pybind11/attr.h>

#include <loco/math/vec2_t_impl.hpp>

#include <common_py.hpp>

namespace py = pybind11;

////    py::class_<Vector2<T>>(m, class_name, py::buffer_protocol())
////        .def(py::init([](py::buffer buff) {  // NOLINT
////            py::buffer_info info = buff.request();
////
////            py::print("itemsize=", info.itemsize, "format=", info.format,
////                      "ndim=", info.ndim);
////            for (uint32_t i = 0; i < info.shape.size(); ++i) {
////                py::print("shape(", i, ")=", info.shape[i]);
////            }
////            for (uint32_t i = 0; i < info.strides.size(); ++i) {
////                py::print("stride(", i, ")=", info.strides[i]);
////            }
////
////            return Vector2<T>();
////        }));

namespace loco {
namespace math {

template <typename T>
using SFINAE_VEC2_BINDINGS = typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_VEC2_BINDINGS<T> = nullptr>
// NOLINTNEXTLINE
auto bindings_vector2(py::module& m, const char* class_name) -> void {
    {
        using Class = Vector2<T>;
        py::class_<Class>(m, class_name, py::buffer_protocol())
            .def(py::init<>())
            .def(py::init<T>())
            .def(py::init<T, T>())
            // clang-format off
            PROPERTY(x)
            PROPERTY(y)
            GET_SET_ITEM(Class::VECTOR_NDIM, T)
            .def(py::self + py::self)
            .def(py::self - py::self)
            .def(py::self * py::self)
            .def("__mul__", [](const Class& self, T scale) -> Class {
                return self * scale;
            })
            .def("__rmul__", [](const Class& self, T scale) -> Class {
                return self * scale;
            })
            // clant-format on
            .def("__repr__", [](const Class& self) -> py::str {
                return py::str("Vector2{}(x={}, y={})")
                    .format((IsFloat32<T>::value ? "f" : "d"), self.x(),
                            self.y());
            });
    }
}  // namespace math

}  // namespace math
}  // namespace loco
