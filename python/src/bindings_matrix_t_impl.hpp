
#include <bindings_matrix_t.h>

namespace py = pybind11;

namespace tinymath
{
    template< typename Scalar_T, size_t SizeN >
    void bindings_matrix( py::module& m, const std::string& modName )
    {
        py::class_< Matrix<Scalar_T,SizeN> >( m, modName.c_str(), py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init( []( py::array_t<Scalar_T>& matarr )
                {
                    auto bufferInfo = matarr.request();
                    if ( bufferInfo.ndim != 2 )
                    {
                        throw std::runtime_error( "tinymath::Matrix >>> incompatible array dimensions, expected \
                                                   2 dimensions, but got " + std::to_string( bufferInfo.ndim ) + "|." );
                    }
                    if ( bufferInfo.shape[0] != SizeN || bufferInfo.shape[1] != SizeN )
                    {
                        throw std::runtime_error( "tinymath::Matrix >>> incompatible array size, expected \
                                                   ( " + std::to_string( SizeN ) + "," + std::to_string( SizeN ) + "), but got \
                                                   ( " + std::to_string( bufferInfo.shape[0] ) + "," + std::to_string( bufferInfo.shape[1] ) + ") instead." );
                    }

                    auto bufferData = (Scalar_T*) bufferInfo.ptr;
                    auto matData = std::vector<Scalar_T>( SizeN * SizeN, 0.0 );
                    for ( size_t i = 0; i < bufferInfo.size; i++ )
                        matData[i] = ((Scalar_T) bufferData[i]);
                    auto matrix = new Matrix<Scalar_T,SizeN>( matData );
                    return matrix;
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
            .def( "__add__", []( const Matrix<Scalar_T,SizeN>& m1, const Matrix<Scalar_T,SizeN>& m2 ) -> Matrix<Scalar_T,SizeN> { return m1 + m2; } )
            .def( "__sub__", []( const Matrix<Scalar_T,SizeN>& m1, const Matrix<Scalar_T,SizeN>& m2 ) -> Matrix<Scalar_T,SizeN> { return m1 + m2; } )
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
    }

}