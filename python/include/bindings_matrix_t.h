#pragma once

#include <bindings_common.h>
#include <matrix_t.h>

namespace py = pybind11;

namespace tinymath
{
    // conversion from matrix to numpy array
    template< typename Scalar_T, size_t SizeN >
    py::array_t<Scalar_T> matrix_to_nparray( const Matrix<Scalar_T,SizeN>& mat );

    // conversion from numpy array to matrix
    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T,SizeN> nparray_to_matrix( const py::array_t<Scalar_T>& matarr );

    template< typename Scalar_T, size_t SizeN >
    void bindings_matrix( py::module& m, const std::string& className );
}

#include "../src/bindings_matrix_t_impl.hpp"