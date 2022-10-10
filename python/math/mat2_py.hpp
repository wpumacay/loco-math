#pragma once

#include <cstring>
#include <stdexcept>
#include <utility>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>

#include <loco/math/mat2_t_impl.hpp>

#include <common_py.hpp>
#include <conversions_py.hpp>

namespace py = pybind11;

namespace loco {
namespace math {

template <typename T>
using SFINAE_MAT2_BINDINGS = typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_MAT2_BINDINGS<T> = nullptr>
// NOLINTNEXTLINE
auto bindings_matrix2(py::module& m, const char* class_name) -> void {
    using Class = Matrix2<T>;
    using Column = typename Matrix2<T>::ColumnType;
    py::class_<Class>(m, class_name, py::buffer_protocol())
        .def(py::init())
        // clang-format off
        MATRIX_BUFFER_PROTOCOL(2, T)
        MATRIX_OPERATORS(T)
        // cppcheck-suppress constParameter
        MATRIX_GETSET_ITEM(2, T)
        // clang-format on
        .def("__repr__", [](const Class& self) -> py::str {
            return py::str("Matrix2{}(\n[{},\t{},\n {},\t{}])")
                .format(IsFloat32<T>::value ? "f" : "d", self(0, 0), self(0, 1),
                        self(1, 0), self(1, 1));
        });
}

}  // namespace math
}  // namespace loco
