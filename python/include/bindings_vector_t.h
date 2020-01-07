#pragma once

#include <bindings_common.h>
#include <vector_t.h>

namespace py = pybind11;

namespace tinymath
{

    void bindings_vector2( py::module& m );
    void bindings_vector3( py::module& m );
    void bindings_vector4( py::module& m );

}