#pragma once

#include <pybind11/pybind11.h>

#include <loco/math/common.hpp>

// clang-format off
#define PROPERTY(var) .def_property(#var,   \
    [](const Class& self) -> T              \
        {                                   \
            return self.var();              \
        },                                  \
    [](Class& self, T value)                \
        {                                   \
            self.var() = value;             \
        })

#define GETSET_ITEM(Size, Type)                            \
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

#define OPERATORS(Type)                                                 \
    .def(py::self + py::self)                                           \
    .def(py::self - py::self)                                           \
    .def(py::self * py::self)                                           \
    .def("__mul__", [](const Class& self, Type scale) -> Class {        \
        return self * scale;                                            \
    })                                                                  \
    .def("__rmul__", [](const Class& self, Type scale) -> Class {       \
        return scale * self;                                            \
    })                                                                  \
    .def("__eq__", [](const Class& lhs, const Class& rhs) -> bool {     \
        return lhs == rhs;                                              \
    })                                                                  \
    .def("__neq__", [](const Class& lhs, const Class& rhs) -> bool {    \
        return lhs != rhs;                                              \
    })

#define METHODS(Type)                                                   \
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
