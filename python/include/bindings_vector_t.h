#pragma once

#include <bindings_common.h>
#include <vector_t.h>

namespace py = pybind11;

namespace tinymath
{
    template< typename Scalar_T, size_t SizeN >
    void bindings_vector( py::module& m, const std::string& modName );
}

#include "../src/bindings_vector_t_impl.hpp"