
#include <bindings_vector_t.h>

namespace py = pybind11;

namespace tinymath
{
    template< typename Scalar_T, size_t SizeN >
    void bindings_vector( py::module& m, const std::string& modName )
    {
        py::class_< Vector<Scalar_T,SizeN> >( m, modName.c_str(), py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init<Scalar_T>() )
            .def( py::init( []( py::array_t<Scalar_T>& vecarr )
                {
                    auto bufferInfo = vecarr.request();
                    if ( bufferInfo.size != SizeN )
                    {
                        throw std::runtime_error( std::string( "tinymath::Vector >>> incompatible array size, expected " ) +
                                                  std::to_string( SizeN ) + " floats" );
                    }

                    auto bufferData = (Scalar_T*) bufferInfo.ptr;
                    auto vecData = std::vector<Scalar_T>( SizeN, 0.0 );
                    for ( size_t i = 0; i < SizeN; i++ )
                        vecData[i] = bufferData[i];
                    return new Vector<Scalar_T,SizeN>( vecData );
                } ) )
            .def_buffer( []( Vector<Scalar_T,SizeN>& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.data(),
                        sizeof( Scalar_T ),
                        py::format_descriptor< Scalar_T >::format(),
                        1,
                        { SizeN },
                        { sizeof( Scalar_T ) }
                    );
                } )
            .def_property( "x",
                []( const Vector<Scalar_T,SizeN>& self ) -> Scalar_T
                    {
                        return self.x();
                    }, 
                []( Vector<Scalar_T,SizeN>& self, Scalar_T xval )
                    {
                        self.x() = xval;
                    } )
            .def_property( "y", 
                []( const Vector<Scalar_T,SizeN>& self ) -> Scalar_T
                    {
                        return self.y();
                    }, 
                []( Vector<Scalar_T,SizeN>& self, Scalar_T yval )
                    {
                        self.y() = yval;
                    } )
            .def_property( "z",
                []( const Vector<Scalar_T,SizeN>& self ) -> Scalar_T
                    {
                        return self.z();
                    },
                []( Vector<Scalar_T,SizeN>& self, Scalar_T zval )
                    {
                        self.z() = zval;
                    } )
            .def_property( "w",
                []( const Vector<Scalar_T,SizeN>& self ) -> Scalar_T
                    {
                        return self.w();
                    },
                []( Vector<Scalar_T,SizeN>& self, Scalar_T wval )
                    {
                        self.w() = wval;
                    } )
            .def( "length", &Vector<Scalar_T,SizeN>::length )
            .def( "dot", &Vector<Scalar_T,SizeN>::dot )
            .def( "normalize", &Vector<Scalar_T,SizeN>::normalize )
            .def( "normalized", &Vector<Scalar_T,SizeN>::normalized )
            .def( "scale", (void (Vector<Scalar_T,SizeN>::*)(Scalar_T)) &Vector<Scalar_T,SizeN>::scale )
            .def( "scale", (void (Vector<Scalar_T,SizeN>::*)(const Vector<Scalar_T,SizeN>&)) &Vector<Scalar_T,SizeN>::scale )
            .def( "scaled", (Vector<Scalar_T,SizeN> (Vector<Scalar_T,SizeN>::*)(Scalar_T) const) &Vector<Scalar_T,SizeN>::scaled )
            .def( "scaled", (Vector<Scalar_T,SizeN> (Vector<Scalar_T,SizeN>::*)(const Vector<Scalar_T,SizeN>&) const) &Vector<Scalar_T,SizeN>::scaled )
            .def( "__add__", []( const Vector<Scalar_T,SizeN>& v1, const Vector<Scalar_T,SizeN>& v2 ) -> Vector<Scalar_T,SizeN> { return v1 + v2; } )
            .def( "__sub__", []( const Vector<Scalar_T,SizeN>& v1, const Vector<Scalar_T,SizeN>& v2 ) -> Vector<Scalar_T,SizeN> { return v1 - v2; } )
            .def( "__mul__", []( const Vector<Scalar_T,SizeN>& v1, const Vector<Scalar_T,SizeN>& v2 ) -> Vector<Scalar_T,SizeN> { return v1 * v2; } )
            .def( "__mul__", []( const Vector<Scalar_T,SizeN>& vec, Scalar_T val ) -> Vector<Scalar_T,SizeN> { return val * vec; } )
            .def( "__rmul__", []( const Vector<Scalar_T,SizeN>& vec, Scalar_T val ) -> Vector<Scalar_T,SizeN> { return val * vec; } )
            .def( "__getitem__", []( const Vector<Scalar_T,SizeN>& self, ssize_t index )
                {
                    if ( index > 1 ) 
                        throw py::index_error();
                    return self[index];
                } )
            .def( "__setitem__", []( Vector<Scalar_T,SizeN>& self, ssize_t index, Scalar_T v )
                {
                    if ( index > 1 )
                        throw py::index_error();
                    self[index] = v;
                } )
            .def( "__repr__", []( const Vector<Scalar_T,SizeN>& self )
                {
                    return "vec(" + tinymath::toString( self ) + ")";
                } );
    }

}