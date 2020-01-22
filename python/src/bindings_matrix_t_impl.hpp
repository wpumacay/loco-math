
#include <bindings_matrix_t.h>

namespace py = pybind11;

namespace tinymath
{
    template< typename Scalar_T, size_t SizeN >
    py::array_t<Scalar_T> matrix_to_nparray( const Matrix<Scalar_T,SizeN>& mat )
    {
        return py::array( py::buffer_info( const_cast<Scalar_T*>( mat.data() ), // const is safe, as array will just copy data
                                           sizeof( Scalar_T ),
                                           py::format_descriptor<Scalar_T>::format(),
                                           2,
                                           { SizeN, SizeN },
                                           { sizeof( Scalar_T ), sizeof( Scalar_T ) * SizeN } ) );
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T,SizeN> nparray_to_matrix( const py::array_t<Scalar_T>& matarr )
    {
        auto bufferInfo = matarr.request();
        if ( bufferInfo.ndim != 2 )
        {
            throw std::runtime_error( "tinymath::nparray_to_matrix >>> incompatible array dimensions, expected \
                                       2 dimensions, but got " + std::to_string( bufferInfo.ndim ) + "." );
        }
        if ( bufferInfo.shape[0] != SizeN || bufferInfo.shape[1] != SizeN )
        {
            throw std::runtime_error( "tinymath::nparray_to_matrix >>> incompatible array size, expected \
                                       ( " + std::to_string( SizeN ) + "," + std::to_string( SizeN ) + "), but got \
                                       ( " + std::to_string( bufferInfo.shape[0] ) + "," + std::to_string( bufferInfo.shape[1] ) + ") instead." );
        }

        auto bufferData = bufferInfo.ptr;
        auto matData = std::vector<Scalar_T>( SizeN * SizeN, 0.0 );
        memcpy( matData.data(), bufferData, SizeN * SizeN * sizeof( Scalar_T ) );
        auto matrix = Matrix<Scalar_T,SizeN>( matData );
        return matrix;
    }

    template< typename Scalar_T, size_t SizeN >
    void bindings_matrix( py::module& m, const std::string& className )
    {
        py::class_< Matrix<Scalar_T,SizeN> >( m, className.c_str(), py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init( []( py::array_t<Scalar_T>& matarr )
                {
                    auto bufferInfo = matarr.request();
                    if ( bufferInfo.ndim != 2 )
                    {
                        throw std::runtime_error( "tinymath::Matrix >>> incompatible array dimensions, expected \
                                                   2 dimensions, but got " + std::to_string( bufferInfo.ndim ) + "." );
                    }
                    if ( bufferInfo.shape[0] < SizeN || bufferInfo.shape[1] < SizeN )
                    {
                        throw std::runtime_error( "tinymath::Matrix >>> incompatible array size, expected at least \
                                                   ( " + std::to_string( SizeN ) + "," + std::to_string( SizeN ) + "), but got \
                                                   ( " + std::to_string( bufferInfo.shape[0] ) + "," + std::to_string( bufferInfo.shape[1] ) + ") instead." );
                    }

                    auto bufferData = (Scalar_T*) bufferInfo.ptr;
                    auto matData = std::vector<Scalar_T>( SizeN * SizeN, 0.0 );
                    for ( size_t i = 0; i < SizeN; i++ )
                        for ( size_t j = 0; j < SizeN; j++ )
                            matData[j + i * SizeN] = ((Scalar_T) bufferData[j + i * bufferInfo.shape[1]]);
                    auto matrix = new Matrix<Scalar_T,SizeN>( matData );
                    return matrix;
                } ) )
            .def( py::init( []( py::array_t<Scalar_T>& matarr, py::array_t<Scalar_T>& vecarr )
                {
                    auto matBufferInfo = matarr.request();
                    if ( matBufferInfo.ndim != 2 )
                    {
                        throw std::runtime_error( "tinymath::Matrix >>> incompatible array dimensions, expected \
                                                   2 dimensions, but got " + std::to_string( matBufferInfo.ndim ) + "|." );
                    }
                    if ( matBufferInfo.shape[0] != (SizeN-1) || matBufferInfo.shape[1] != (SizeN-1) )
                    {
                        throw std::runtime_error( "tinymath::Matrix >>> incompatible array size, expected exactly \
                                                   ( " + std::to_string( SizeN - 1 ) + "," + std::to_string( SizeN - 1 ) + "), but got \
                                                   ( " + std::to_string( matBufferInfo.shape[0] ) + "," + std::to_string( matBufferInfo.shape[1] ) + ") instead for \
                                                   (n-1)x(n-1) upper-left section of the matrix." );
                    }
                    auto vecBufferInfo = vecarr.request();
                    if ( vecBufferInfo.size != (SizeN-1) )
                    {
                        throw std::runtime_error( "tinymath::Vector >>> incompatible array size, expected exactly " +
                                                  std::to_string( SizeN - 1 ) + " elements for top (n-1) portion of the last column." );
                    }

                    auto matBufferData = (Scalar_T*) matBufferInfo.ptr;
                    auto matData = std::vector<Scalar_T>( (SizeN-1) * (SizeN-1), 0.0 );
                    for ( size_t i = 0; i < (SizeN-1) * (SizeN-1); i++ ) // @todo: change for memcpy
                            matData[i] = matBufferData[i];
                    auto matrixPart = Matrix<Scalar_T,SizeN-1>( matData );

                    auto vecBufferData = (Scalar_T*) vecBufferInfo.ptr;
                    auto vecData = std::vector<Scalar_T>( (SizeN-1), 0.0 );
                    for ( size_t i = 0; i < (SizeN-1); i++ ) // @todo: change for memcpy
                        vecData[i] = vecBufferData[i];
                    auto vecPart = Vector<Scalar_T,SizeN-1>( vecData );

                    return new Matrix<Scalar_T,SizeN>( matrixPart, vecPart );
                } ) )
            .def_buffer( []( Matrix<Scalar_T,SizeN>& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.data(),
                        sizeof( Scalar_T ),
                        py::format_descriptor<Scalar_T>::format(),
                        2,
                        { SizeN, SizeN },
                        { sizeof( Scalar_T ), sizeof( Scalar_T ) * SizeN }
                    );
                } )
            .def( "setIdentity", &Matrix<Scalar_T,SizeN>::setIdentity )
            .def( "setZero", &Matrix<Scalar_T,SizeN>::setZero )
            .def( "transpose_", &Matrix<Scalar_T,SizeN>::transpose_ )
            .def( "transpose", &Matrix<Scalar_T,SizeN>::transpose )
            .def( "inverse", &Matrix<Scalar_T,SizeN>::inverse )
            .def( "row", &Matrix<Scalar_T,SizeN>::row )
            .def( "col", &Matrix<Scalar_T,SizeN>::col )
            .def( "set", ( void ( Matrix<Scalar_T,SizeN>::* )( const Matrix<Scalar_T,SizeN-1>& ) ) &Matrix<Scalar_T,SizeN>::set )
            .def( "set", ( void ( Matrix<Scalar_T,SizeN>::* )( const Vector<Scalar_T,SizeN-1>&, size_t ) ) &Matrix<Scalar_T,SizeN>::set )
            .def( "set", ( void ( Matrix<Scalar_T,SizeN>::* )( const Vector<Scalar_T,SizeN>&, size_t ) ) &Matrix<Scalar_T,SizeN>::set )
            .def_property_readonly( "nrows", []( const Matrix<Scalar_T,SizeN>& m ) -> size_t { return SizeN; } )
            .def_property_readonly( "ncols", []( const Matrix<Scalar_T,SizeN>& m ) -> size_t { return SizeN; } )
            .def_property_readonly( "ndims", []( const Matrix<Scalar_T,SizeN>& m ) -> size_t { return 2; } )
            .def_property_readonly( "shape", []( const Matrix<Scalar_T,SizeN>& m ) -> std::pair<size_t,size_t> { return { SizeN, SizeN }; } )
            .def( "__add__", []( const Matrix<Scalar_T,SizeN>& m1, const Matrix<Scalar_T,SizeN>& m2 ) -> Matrix<Scalar_T,SizeN> { return m1 + m2; } )
            .def( "__sub__", []( const Matrix<Scalar_T,SizeN>& m1, const Matrix<Scalar_T,SizeN>& m2 ) -> Matrix<Scalar_T,SizeN> { return m1 - m2; } )
            .def( "__mul__", []( const Matrix<Scalar_T,SizeN>& m1, const Matrix<Scalar_T,SizeN>& m2 ) -> Matrix<Scalar_T,SizeN> { return m1 * m2; } )
            .def( "__mul__", []( const Matrix<Scalar_T,SizeN>& m, const Vector<Scalar_T,SizeN>& vec ) -> Vector<Scalar_T,SizeN> { return m * vec; } )
            .def( "__rmul__", []( const Vector<Scalar_T,SizeN>& vec, const Matrix<Scalar_T,SizeN>& m ) { throw std::runtime_error( "tinymath::Matrix::__mul__(vec,mat) invalid column vector - matrix operation" ); } )
            .def( "__mul__", []( const Matrix<Scalar_T,SizeN>& m, Scalar_T val ) -> Matrix<Scalar_T,SizeN> { return m * val; } )
            .def( "__rmul__", []( const Matrix<Scalar_T,SizeN>& m, Scalar_T val ) -> Matrix<Scalar_T,SizeN> { return m * val; } )
            .def( "__getitem__", []( const Matrix<Scalar_T,SizeN>& self, const std::pair<ssize_t,ssize_t>& ij )
                {
                    if ( ij.first >= SizeN || ij.second >= SizeN )
                        throw py::index_error();
                    return self(ij.first, ij.second);
                } )
            .def( "__setitem__", []( Matrix<Scalar_T,SizeN>& self, const std::pair<ssize_t,ssize_t>& ij, Scalar_T val )
                {
                    if ( ij.first >= SizeN || ij.second >= SizeN )
                        throw py::index_error();
                    self(ij.first, ij.second) = val;
                } )
            .def( "__repr__", []( const Matrix<Scalar_T,SizeN>& self )
                {
                    return "matrix(\n\r" + tinymath::toString( self ) + ")";
                } );
        m.def( "inverse", static_cast< Matrix<Scalar_T,2> (*)( const Matrix<Scalar_T,2>& ) >( &tinymath::inverse<Scalar_T> ) );
        m.def( "inverse", static_cast< Matrix<Scalar_T,3> (*)( const Matrix<Scalar_T,3>& ) >( &tinymath::inverse<Scalar_T> ) );
        m.def( "inverse", static_cast< Matrix<Scalar_T,4> (*)( const Matrix<Scalar_T,4>& ) >( &tinymath::inverse<Scalar_T> ) );
        m.def( ( className + "_to_nparray" ).c_str(), &tinymath::matrix_to_nparray<Scalar_T,SizeN> );
        m.def( ( "nparray_to_" + className ).c_str(), &tinymath::nparray_to_matrix<Scalar_T,SizeN> );
    }

}