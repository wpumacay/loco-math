#pragma once

#include <bindings_common.h>
#include <matrix_t.h>

namespace py = pybind11;

namespace tinymath
{
    template< typename Scalar_T, size_t SizeN >
    void bindings_matrix( py::module& m, const std::string& modName );
}

#include "../src/bindings_matrix_t_impl.hpp"