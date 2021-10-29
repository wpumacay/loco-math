#pragma once

#include <common.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tinymath {

void bindings_common(py::module& m);

}
