#pragma once

#include <pybind11/pybind11.h>

#include <loco/math/common.hpp>
#include <conversions_py.hpp>

// clang-format off
#define VECTOR_BUFFER_PROTOCOL(T)                                           \
    .def(py::init([](const py::buffer& buff) -> Class {                     \
        py::buffer_info info = buff.request();                              \
        if (IsFloat32<T>::value &&                                          \
            (info.format != py::format_descriptor<T>::format())) {          \
            throw std::runtime_error(                                       \
                "Incompatible format: expected float (float32) array");     \
        }                                                                   \
        if (IsFloat64<T>::value &&                                          \
            (info.format != py::format_descriptor<T>::format())) {          \
            throw std::runtime_error(                                       \
                "Incompatible format: expected double (float64) array");    \
        }                                                                   \
        bool is_valid_shape = true;                                         \
        if (info.ndim == 1) {                                               \
            is_valid_shape = (info.shape[0] == Class::VECTOR_SIZE);         \
        } else if (info.ndim == 2) {                                        \
            is_valid_shape = (info.shape[0] == Class::VECTOR_SIZE ||        \
                              info.shape[1] == Class::VECTOR_SIZE);         \
        } else {                                                            \
            is_valid_shape = false;                                         \
        }                                                                   \
        if (!is_valid_shape) {                                              \
            throw std::runtime_error(                                       \
                "Incompatible shape: expected (, n), (1, n), (n, 1)");      \
        }                                                                   \
        Class vec;                                                          \
        memcpy(vec.data(), info.ptr, sizeof(T) * Class::VECTOR_SIZE);       \
        return vec;                                                         \
    }))                                                                     \
    .def_buffer([](Class& self) -> py::buffer_info {                        \
        return py::buffer_info(self.data(), sizeof(T),                      \
                               py::format_descriptor<T>::format(),          \
                               Class::VECTOR_NDIM,                          \
                               {Class::VECTOR_SIZE}, {sizeof(T)});          \
    })

#define MATRIX_BUFFER_PROTOCOL(Size, T)                                     \
    .def(py::init([](const py::buffer& buff) -> Class {                     \
        py::buffer_info info = buff.request();                              \
        if (IsFloat32<T>::value &&                                          \
            (info.format != py::format_descriptor<T>::format())) {          \
            throw std::runtime_error(                                       \
                "Incompatible format: expected float (float32) array");     \
        }                                                                   \
        if (IsFloat64<T>::value &&                                          \
            (info.format != py::format_descriptor<T>::format())) {          \
            throw std::runtime_error(                                       \
                "Incompatible format: expected double (float64) array");    \
        }                                                                   \
        Class mat;                                                          \
        if (info.ndim == Class::MATRIX_NDIM) {                              \
            if (info.shape[0] == Class::MATRIX_SIZE &&                      \
                info.shape[1] == Class::MATRIX_SIZE) {                      \
                memcpy(mat.data(), info.ptr,                                \
                       sizeof(T) * Class::BUFFER_SIZE);                     \
            } else {                                                        \
                throw std::runtime_error(                                   \
                    "Incompatible size: expected (" #Size ", " #Size ")");  \
            }                                                               \
        } else {                                                            \
            throw std::runtime_error(                                       \
                "Incompatible shape: expected (" #Size ", " #Size ")");     \
        }                                                                   \
        return mat;                                                         \
    }))                                                                     \
    .def_buffer([](Class& self) -> py::buffer_info {                        \
        return py::buffer_info(self.data(), sizeof(T),                      \
                               py::format_descriptor<T>::format(),          \
                               Class::MATRIX_NDIM,                          \
                               {Class::MATRIX_SIZE, Class::MATRIX_SIZE},    \
                               {sizeof(T), sizeof(T) * Class::MATRIX_SIZE});\
    })


#define VECTOR_PROPERTY(var) .def_property(#var,    \
    [](const Class& self) -> T                      \
        {                                           \
            return self.var();                      \
        },                                          \
    [](Class& self, T value)                        \
        {                                           \
            self.var() = value;                     \
        })

#define VECTOR_GETSET_ITEM(Size, Type)                      \
    .def("__getitem__",                                     \
    [](const Class& self, uint32_t index) -> Type           \
        {                                                   \
            if (index >= Size) {                            \
                throw py::index_error();                    \
            }                                               \
            return self[static_cast<uint32_t>(index)];      \
        })                                                  \
    .def("__setitem__",                                     \
    [](Class& self, uint32_t index, Type value) -> void     \
        {                                                   \
            if (index >= Size) {                            \
                throw py::index_error();                    \
            }                                               \
            self[index] = value;                            \
        })

#define MATRIX_GETSET_ITEM(Size, Type)                                      \
    .def("__getitem__",                                                     \
    [](const Class& self, uint32_t index) -> Column                         \
        {                                                                   \
            if (index >= Size) {                                            \
                throw py::index_error();                                    \
            }                                                               \
            return self[index];                                             \
        })                                                                  \
    .def("__getitem__",                                                     \
    [](const Class& self, uint32_t row_index, uint32_t col_index) -> Type   \
        {                                                                   \
            if (row_index >= Size || col_index >= Size) {                   \
                throw py::index_error();                                    \
            }                                                               \
            return self(row_index, col_index);                              \
        })                                                                  \
    .def("__setitem__",                                                     \
    [](Class& self, uint32_t index, const py::buffer& buff) -> void         \
        {                                                                   \
            if (index >= Size) {                                            \
                throw py::index_error();                                    \
            }                                                               \
            self[index] = buffer_to_vec##Size<Type>(buff);                  \
        })                                                                  \
    .def("__setitem__",                                                     \
    [](Class& self, uint32_t row_index, uint32_t col_index, Type value)     \
        {                                                                   \
            if (row_index >= Size || col_index >= Size) {                   \
                throw py::index_error();                                    \
            }                                                               \
            self(row_index, col_index) = value;                             \
        })

#define VECTOR_OPERATORS(Type)                                          \
    .def(py::self + py::self)                                           \
    .def(py::self - py::self)                                           \
    .def(py::self * py::self)                                           \
    .def("__mul__", [](const Class& self, Type scale) -> Class {        \
        return self * static_cast<double>(scale);                       \
    })                                                                  \
    .def("__rmul__", [](const Class& self, Type scale) -> Class {       \
        return static_cast<double>(scale) * self;                       \
    })                                                                  \
    .def("__eq__", [](const Class& lhs, const Class& rhs) -> bool {     \
        return lhs == rhs;                                              \
    })                                                                  \
    .def("__neq__", [](const Class& lhs, const Class& rhs) -> bool {    \
        return lhs != rhs;                                              \
    })

#define MATRIX_OPERATORS(Type)                                              \
    .def(py::self + py::self)                                               \
    .def(py::self - py::self)                                               \
    .def(py::self * py::self)                                               \
    .def("__mul__", [](const Class& self, Type scale) -> Class {            \
        return self * static_cast<double>(scale);                           \
    })                                                                      \
    .def("__rmul__", [](const Class& self, Type scale) -> Class {           \
        return static_cast<double>(scale) * self;                           \
    })                                                                      \
    .def("__mul__", [](const Class& self, const Column& rhs) -> Column {    \
        return self * rhs;                                                  \
    })                                                                      \
    .def("__eq__", [](const Class& lhs, const Class& rhs) -> bool {         \
        return lhs == rhs;                                                  \
    })                                                                      \
    .def("__neq__", [](const Class& lhs, const Class& rhs) -> bool {        \
        return lhs != rhs;                                                  \
    })


#define VECTOR_METHODS(Type)                                            \
    .def("dot", [](const Class& self, const Class& other) -> Type {     \
        return dot(self, other);                                        \
    })                                                                  \
    .def("norm", [](const Class& self) -> Type {                        \
        return norm(self);                                              \
    })                                                                  \
    .def("squareNorm", [](const Class& self) -> Type {                  \
        return squareNorm(self);                                        \
    })                                                                  \
    .def("normalize", [](const Class& self) -> Class {                  \
        return normalize(self);                                         \
    })                                                                  \
    .def("normalize_", [](Class& self) -> void {                        \
        normalize_in_place(self);                                       \
    })

// clang-format on
