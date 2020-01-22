#pragma once

#include <bindings_common.h>
#include <vector_t.h>

namespace py = pybind11;

namespace tinymath
{
    // conversion from vector to numpy array
    template< typename Scalar_T, size_t SizeN >
    py::array_t<Scalar_T> vector_to_nparray( const Vector<Scalar_T,SizeN>& vec );

    // conversion from numpy array to vector
    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> nparray_to_vector( const py::array_t<Scalar_T>& vecarr );

    template< typename Scalar_T, size_t SizeN >
    void bindings_vector( py::module& m, const std::string& className );
}

#include "../src/bindings_vector_t_impl.hpp"