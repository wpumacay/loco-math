#pragma once

#include <bindings_common.h>
#include <transforms.h>

namespace py = pybind11;

namespace tinymath {
template <typename Scalar_T>
void bindings_transforms(py::module& m);
}

#include "../src/bindings_transforms_impl.hpp"
