#pragma once

#include <cstring>
#include <stdexcept>
#include <utility>

#include <pybind11/buffer_info.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>
#include <pybind11/attr.h>
#include <pybind11/detail/common.h>

#include <loco/math/vec2_t_impl.hpp>

#include <common_py.hpp>

namespace py = pybind11;

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

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
            VECTOR_BUFFER_PROTOCOL(T)
            VECTOR_PROPERTY(x)
            VECTOR_PROPERTY(y)
            VECTOR_OPERATORS(T)
            VECTOR_METHODS(T)
            VECTOR_GETSET_ITEM(2, T)
            // clant-format on
            // NOLINTNEXTLINE
            .def_property_readonly("ndim", [](const Class& self) {
                return Class::VECTOR_NDIM;
            })
            // NOLINTNEXTLINE
            .def_property_readonly("shape", [](const Class& self) {
                return std::pair<uint32_t, uint32_t>(1, 2);
            })
            .def("__repr__", [](const Class& self) -> py::str {
                return py::str("Vector2{}(x={}, y={})")
                    .format((IsFloat32<T>::value ? "f" : "d"), self.x(),
                            self.y());
            });
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

}  // namespace math
}  // namespace loco
