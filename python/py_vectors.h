#pragma once

#include <py_common.h>
#include <vectors.h>

namespace py = pybind11;

namespace tinymath
{

    void bindings_vector2( py::module& m );
    void bindings_vector3( py::module& m );

}