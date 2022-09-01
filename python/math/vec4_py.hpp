#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>
#include <pybind11/attr.h>

#include <loco/math/vec4_t_impl.hpp>

#include <common_py.hpp>

namespace py = pybind11;

namespace loco {
namespace math {

template <typename T>
using SFINAE_VEC4_BINDINGS = typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_VEC4_BINDINGS<T> = nullptr>
// NOLINTNEXTLINE
auto bindings_vector4(py::module& m, const char* class_name) -> void {
    {
        using Class = Vector4<T>;
        py::class_<Class>(m, class_name, py::buffer_protocol())
            .def(py::init<>())
            .def(py::init<T>())
            .def(py::init<T, T>())
            .def(py::init<T, T, T>())
            // clang-format off
            PROPERTY(x)
            PROPERTY(y)
            PROPERTY(z)
            PROPERTY(w)
            OPERATORS(T)
            METHODS(T)
            GETSET_ITEM(Class::VECTOR_NDIM, T)
            // clant-format on
            .def("__repr__", [](const Class& self) -> py::str {
                return py::str("Vector4{}(x={}, y={}, z={}, w={})")
                    .format((IsFloat32<T>::value ? "f" : "d"), self.x(),
                            self.y(), self.z(), self.w());
            });
    }
}

}  // namespace math
}  // namespace loco
