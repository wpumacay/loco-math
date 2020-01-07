#pragma once

#include <bindings_common.h>
#include <vector_t.h>

namespace py = pybind11;

namespace tinymath
{
    template< typename Scalar_T >
    void bindings_vector2( py::module& m, const std::string& modName );

    template< typename Scalar_T >
    void bindings_vector3( py::module& m, const std::string& modName );

    template< typename Scalar_T >
    void bindings_vector4( py::module& m, const std::string& modName );

}

#include "../src/bindings_vector_t_impl.hpp"