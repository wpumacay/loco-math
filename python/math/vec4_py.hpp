#pragma once

#include <cstring>
#include <stdexcept>
#include <utility>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>
#include <pybind11/attr.h>

#include <loco/math/vec4_t_impl.hpp>

#include <common_py.hpp>

namespace py = pybind11;

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4127)
#endif

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
            .def(py::init<T, T, T, T>())
            // clang-format off
            VECTOR_BUFFER_PROTOCOL(T)
            VECTOR_PROPERTY(x)
            VECTOR_PROPERTY(y)
            VECTOR_PROPERTY(z)
            VECTOR_PROPERTY(w)
            VECTOR_OPERATORS(T)
            VECTOR_METHODS(T)
            VECTOR_GETSET_ITEM(4, T)
            // clant-format on
            // NOLINTNEXTLINE
            .def_property_readonly("ndim", [](const Class&) {
                return Class::VECTOR_NDIM;
            })
            // NOLINTNEXTLINE
            .def_property_readonly("shape", [](const Class&) {
                return std::pair<uint32_t, uint32_t>(1, 4);
            })
            .def("__repr__", [](const Class& self) -> py::str {
                return py::str("Vector4{}(x={}, y={}, z={}, w={})")
                    .format((IsFloat32<T>::value ? "f" : "d"), self.x(),
                            self.y(), self.z(), self.w());
            });
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}  // namespace math
}  // namespace loco
