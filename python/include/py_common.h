#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <common.h>

namespace py = pybind11;

namespace tinymath
{

    void bindings_common( py::module& m );

}