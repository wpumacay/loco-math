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

#define GET_SET_ITEM(Size, Type)                            \
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

// clang-format on
