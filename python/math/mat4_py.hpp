#pragma once

#include <cstring>
#include <stdexcept>
#include <utility>

#include <pybind11/buffer_info.h>
#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/pytypes.h>
#include <pybind11/numpy.h>
#include <pybind11/attr.h>

#include <loco/math/mat4_t_impl.hpp>

#include <common_py.hpp>
#include <conversions_py.hpp>

namespace py = pybind11;

namespace loco {
namespace math {

template <typename T>
using SFINAE_MAT4_BINDINGS = typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_MAT4_BINDINGS<T> = nullptr>
// NOLINTNEXTLINE
auto bindings_matrix4(py::module& m, const char* class_name) -> void {
    {
        using Class = Matrix4<T>;
        using Column = typename Matrix4<T>::ColumnType;
        py::class_<Class>(m, class_name, py::buffer_protocol())
            .def(py::init<>())
            .def(py::init<T, T, T, T>())
            .def(py::init<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T>())
            .def(py::init<Column, Column, Column, Column>())
            .def(py::init([](const py::buffer& buff) -> Class {
                py::buffer_info info = buff.request();
                if (IsFloat32<T>::value &&
                    info.format != py::format_descriptor<T>::format()) {
                    throw std::runtime_error(
                        "Incompatible format: expected float (float32) array");
                }
                if (IsFloat64<T>::value &&
                    info.format != py::format_descriptor<T>::format()) {
                    throw std::runtime_error(
                        "Incompatible format: expected double (float64) array");
                }
                Class mat;
                if (info.ndim == 2) {
                    if (info.shape[0] == 4 && info.shape[1] == 4) {
                        memcpy(mat.data(), info.ptr,
                               sizeof(T) * Class::BUFFER_SIZE);
                    } else {
                        throw std::runtime_error(
                            "Incompatible size: expected (4, 4)");
                    }
                } else {
                    throw std::runtime_error(
                        "Incompatible shape: expected (4, 4)");
                }
                return mat;
            }))
            .def_buffer([](Class& self) -> py::buffer_info {
                return py::buffer_info(
                    self.data(), sizeof(T), py::format_descriptor<T>::format(),
                    2, {Class::MATRIX_SIZE, Class::MATRIX_SIZE},
                    {sizeof(T), sizeof(T) * Class::MATRIX_SIZE});
            })
            .def("__getitem__",
                 [](const Class& self, uint32_t index) -> Column {
                     if (index >= Class::MATRIX_SIZE) {
                         throw py::index_error();
                     }
                     return self[index];
                 })
            .def("__setitem__",
                 [](Class& self, uint32_t index,
                    const py::buffer& buff) -> void {
                     if (index >= Class::MATRIX_SIZE) {
                         throw py::index_error();
                     }
                     self[index] = buffer_to_vec4<T>(buff);
                 })
            .def("__getitem__",
                 [](const Class& self, uint32_t row_index, uint32_t col_index)
                     -> T { return self(row_index, col_index); })
            .def("__setitem__",
                 // cppcheck-suppress constParameter
                 [](Class& self, uint32_t row_index, uint32_t col_index,
                    T value) -> void { self(row_index, col_index) = value; })
            .def("__repr__", [](const Class& self) -> py::str {
                return py::str(
                           "Matrix4{}([[{},\t{},\t{},\t{}],\n[{},\t{},\t{},\t{}"
                           "],\n"
                           "[{},\t{},\t{},\t{}],\n[{},\t{},\t{},\t{}]")
                    .format((IsFloat32<T>::value ? "f" : "d"), self(0, 0),
                            self(0, 1), self(0, 2), self(0, 3), self(1, 0),
                            self(1, 1), self(1, 2), self(1, 3), self(2, 0),
                            self(2, 1), self(2, 2), self(2, 3), self(3, 0),
                            self(3, 1), self(3, 2), self(3, 3));
            });
    }
}

}  // namespace math
}  // namespace loco
