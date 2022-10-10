#pragma once

#include <cstring>
#include <stdexcept>
#include <utility>

#include <pybind11/attr.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>

#include <loco/math/mat3_t_impl.hpp>

#include <common_py.hpp>
#include <conversions_py.hpp>

namespace py = pybind11;

namespace loco {
namespace math {

template <typename T>
using SFINAE_MAT3_BINDINGS = typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_MAT3_BINDINGS<T> = nullptr>
// NOLINTNEXTLINE
auto bindings_matrix3(py::module& m, const char* class_name) -> void {
    using Class = Matrix3<T>;
    using Column = typename Matrix3<T>::ColumnType;
    py::class_<Class>(m, class_name, py::buffer_protocol())
        .def(py::init<>())
        .def(py::init<T, T, T>())
        .def(py::init<T, T, T, T, T, T, T, T, T>())
        .def(py::init<Column, Column, Column>())
        // clang-format off
        MATRIX_BUFFER_PROTOCOL(3, T)
        MATRIX_OPERATORS(T)
        // cppcheck-suppress constParameter
        MATRIX_GETSET_ITEM(3, T)
        // clang-format on
        .def("__repr__", [](const Class& self) -> py::str {
            // clang-format off
            return py::str("Matrix3{}([[{},\t{},\t{}],\n"
                           "          [{},\t{},\t{}],\n"
                           "          [{},\t{},\t{}]])")
                .format(IsFloat32<T>::value ? "f" : "d",
                    self(0, 0), self(0, 1), self(0, 2),
                    self(1, 0), self(1, 1), self(1, 2),
                    self(2, 0), self(2, 1), self(2, 2));

            // clang-format on
        });
}

}  // namespace math
}  // namespace loco
