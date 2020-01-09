
#include <bindings_vector_t.h>

namespace py = pybind11;

namespace tinymath
{
    template< typename Scalar_T >
    void bindings_vector2( py::module& m, const std::string& modName )
    {
        py::class_< Vector2<Scalar_T> >( m, modName.c_str(), py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init<Scalar_T>() )
            .def( py::init<Scalar_T, Scalar_T>() )
            .def( py::init( []( py::array_t<Scalar_T>& vec2arr )
                {
                    auto bufferInfo = vec2arr.request();
                    if ( bufferInfo.size != 2 )
                        throw std::runtime_error( "tinymath::Vector2 >>> incompatible array size, expected 2 floats" );

                    auto bufferData = (Scalar_T*) bufferInfo.ptr;
                    return new Vector2<Scalar_T>( bufferData[0], bufferData[1] );
                } ) )
            .def_buffer( []( Vector2<Scalar_T>& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.data(),
                        sizeof( Scalar_T ),
                        py::format_descriptor< Scalar_T >::format(),
                        1,
                        { 2 },
                        { sizeof( Scalar_T ) }
                    );
                } )
            .def_property( "x",
                []( const Vector2<Scalar_T>& self ) -> Scalar_T
                    {
                        return self.x();
                    }, 
                []( Vector2<Scalar_T>& self, Scalar_T xval )
                    {
                        self.x() = xval;
                    } )
            .def_property( "y", 
                []( const Vector2<Scalar_T>& self ) -> Scalar_T
                    {
                        return self.y();
                    }, 
                []( Vector2<Scalar_T>& self, Scalar_T yval )
                    {
                        self.y() = yval;
                    } )
            .def( "length", &Vector2<Scalar_T>::length )
            .def( "dot", &Vector2<Scalar_T>::dot )
            .def( "normalize", &Vector2<Scalar_T>::normalize )
            .def( "normalized", &Vector2<Scalar_T>::normalized )
            .def( "scale", (void (Vector2<Scalar_T>::*)(Scalar_T, Scalar_T)) &Vector2<Scalar_T>::scale )
            .def( "scale", (void (Vector2<Scalar_T>::*)(const Vector2<Scalar_T>&)) &Vector2<Scalar_T>::scale )
            .def( "scaled", (Vector2<Scalar_T> (Vector2<Scalar_T>::*)(Scalar_T, Scalar_T) const) &Vector2<Scalar_T>::scaled )
            .def( "scaled", (Vector2<Scalar_T> (Vector2<Scalar_T>::*)(const Vector2<Scalar_T>&) const) &Vector2<Scalar_T>::scaled )
            .def( "__add__", []( const Vector2<Scalar_T>& v1, const Vector2<Scalar_T>& v2 ) -> Vector2<Scalar_T> { return v1 + v2; } )
            .def( "__sub__", []( const Vector2<Scalar_T>& v1, const Vector2<Scalar_T>& v2 ) -> Vector2<Scalar_T> { return v1 - v2; } )
            .def( "__mul__", []( const Vector2<Scalar_T>& v1, const Vector2<Scalar_T>& v2 ) -> Vector2<Scalar_T> { return v1 * v2; } )
            .def( "__mul__", []( const Vector2<Scalar_T>& vec, Scalar_T val ) -> Vector2<Scalar_T> { return val * vec; } )
            .def( "__rmul__", []( const Vector2<Scalar_T>& vec, Scalar_T val ) -> Vector2<Scalar_T> { return val * vec; } )
            .def( "__getitem__", []( const Vector2<Scalar_T>& self, ssize_t index )
                {
                    if ( index > 1 ) 
                        throw py::index_error();
                    return self[index];
                } )
            .def( "__setitem__", []( Vector2<Scalar_T>& self, ssize_t index, Scalar_T v )
                {
                    if ( index > 1 )
                        throw py::index_error();
                    self[index] = v;
                } )
            .def( "__repr__", []( const Vector2<Scalar_T>& self )
                {
                    return "vec2(" + tinymath::toString( self ) + ")";
                } );
    }

    template< typename Scalar_T >
    void bindings_vector3( py::module& m, const std::string& modName )
    {
        py::class_< Vector3<Scalar_T> >( m, modName.c_str(), py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init<Scalar_T>() )
            .def( py::init<Scalar_T, Scalar_T, Scalar_T>() )
            .def( py::init( []( py::array_t<Scalar_T>& vec2arr, Scalar_T zval )
                {
                    auto bufferInfo = vec2arr.request();
                    if ( bufferInfo.size != 2 )
                        throw std::runtime_error( "tinymath::Vector3 >>> incompatible array size, expected 2 floats for xy components" );

                    auto bufferData = (Scalar_T*) bufferInfo.ptr;
                    return new Vector3<Scalar_T>( bufferData[0], bufferData[1], zval );
                } ) )
            .def( py::init( []( py::array_t<Scalar_T>& vec3arr )
                {
                    auto bufferInfo = vec3arr.request();
                    if ( bufferInfo.size != 3 )
                        throw std::runtime_error( "tinymath::Vector3 >>> incompatible array size, expected 3 floats" );

                    auto bufferData = (Scalar_T*) bufferInfo.ptr;
                    return new Vector3<Scalar_T>( bufferData[0], bufferData[1], bufferData[2] );
                } ) )
            .def_buffer( []( Vector3<Scalar_T>& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.data(),
                        sizeof( Scalar_T ),
                        py::format_descriptor< Scalar_T >::format(),
                        1,
                        { 3 },
                        { sizeof( Scalar_T ) }
                    );
                } )
            .def_property( "x", []( const Vector3<Scalar_T>& self ) -> Scalar_T { return self.x(); }, 
                                []( Vector3<Scalar_T>& self, Scalar_T xval ) { self.x() = xval; } )
            .def_property( "y", []( const Vector3<Scalar_T>& self ) -> Scalar_T { return self.y(); }, 
                                []( Vector3<Scalar_T>& self, Scalar_T yval ) { self.y() = yval; } )
            .def_property( "z",  []( const Vector3<Scalar_T>& self ) -> Scalar_T { return self.z(); }, 
                                []( Vector3<Scalar_T>& self, Scalar_T zval ) { self.z() = zval; } )
            .def( "length", &Vector3<Scalar_T>::length )
            .def( "dot", &Vector3<Scalar_T>::dot )
            .def( "cross", &Vector3<Scalar_T>::cross )
            .def( "normalize", &Vector3<Scalar_T>::normalize )
            .def( "normalized", &Vector3<Scalar_T>::normalized )
            .def( "scale", (void (Vector3<Scalar_T>::*)(Scalar_T, Scalar_T, Scalar_T)) &Vector3<Scalar_T>::scale )
            .def( "scale", (void (Vector3<Scalar_T>::*)(const Vector3<Scalar_T>&)) &Vector3<Scalar_T>::scale )
            .def( "scaled", (Vector3<Scalar_T> (Vector3<Scalar_T>::*)(Scalar_T, Scalar_T, Scalar_T) const) &Vector3<Scalar_T>::scaled )
            .def( "scaled", (Vector3<Scalar_T> (Vector3<Scalar_T>::*)(const Vector3<Scalar_T>&) const) &Vector3<Scalar_T>::scaled )
            .def( "__add__", []( const Vector3<Scalar_T>& v1, const Vector3<Scalar_T>& v2 ) -> Vector3<Scalar_T> { return v1 + v2; } )
            .def( "__sub__", []( const Vector3<Scalar_T>& v1, const Vector3<Scalar_T>& v2 ) -> Vector3<Scalar_T> { return v1 - v2; } )
            .def( "__mul__", []( const Vector3<Scalar_T>& v1, const Vector3<Scalar_T>& v2 ) -> Vector3<Scalar_T> { return v1 * v2; } )
            .def( "__mul__", []( const Vector3<Scalar_T>& vec, Scalar_T val ) -> Vector3<Scalar_T> { return val * vec; } )
            .def( "__rmul__", []( const Vector3<Scalar_T>& vec, Scalar_T val ) -> Vector3<Scalar_T> { return val * vec; } )
            .def( "__getitem__", []( const Vector3<Scalar_T>& self, ssize_t index )
                {
                    if ( index > 2 )
                        throw py::index_error();
                    return self[index];
                } )
            .def( "__setitem__", []( Vector3<Scalar_T>& self, ssize_t index, Scalar_T v )
                {
                    if ( index > 2 )
                        throw py::index_error();
                    self[index] = v;
                } )
            .def( "__repr__", []( const Vector3<Scalar_T>& self)
                {
                    return "vec3(" + tinymath::toString( self ) + ")";
                } );
    }

    template< typename Scalar_T >
    void bindings_vector4( py::module& m, const std::string& modName )
    {
        py::class_< Vector4<Scalar_T> >( m, modName.c_str(), py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init<Scalar_T>() )
            .def( py::init<Scalar_T, Scalar_T, Scalar_T, Scalar_T>() )
            .def( py::init( []( py::array_t<Scalar_T>& vec3arr, Scalar_T wval )
                {
                    auto bufferInfo = vec3arr.request();
                    if ( bufferInfo.size != 3 )
                        throw std::runtime_error( "tinymath::Vector4 >>> incompatible array size, expected 3 floats for xyz components" );

                    auto bufferData = (Scalar_T*) bufferInfo.ptr;
                    return new Vector4<Scalar_T>( bufferData[0], bufferData[1], bufferData[2], wval );
                } ) )
            .def( py::init( []( py::array_t<Scalar_T>& vec4arr )
                {
                    auto bufferInfo = vec4arr.request();
                    if ( bufferInfo.size != 4 )
                        throw std::runtime_error( "tinymath::Vector4 >>> incompatible array size, expected 4 floats" );

                    auto bufferData = (Scalar_T*) bufferInfo.ptr;
                    return new Vector4<Scalar_T>( bufferData[0], bufferData[1], bufferData[2], bufferData[3] );
                } ) )
            .def_buffer( []( Vector4<Scalar_T>& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.data(),
                        sizeof( Scalar_T ),
                        py::format_descriptor< Scalar_T >::format(),
                        1,
                        { 4 },
                        { sizeof( Scalar_T ) }
                    );
                } )
            .def_property( "x", []( const Vector4<Scalar_T>& self ) -> Scalar_T { return self.x(); }, 
                                []( Vector4<Scalar_T>& self, Scalar_T xval ) { self.x() = xval; } )
            .def_property( "y", []( const Vector4<Scalar_T>& self ) -> Scalar_T { return self.y(); }, 
                                []( Vector4<Scalar_T>& self, Scalar_T yval ) { self.y() = yval; } )
            .def_property( "z", []( const Vector4<Scalar_T>& self ) -> Scalar_T { return self.z(); }, 
                                []( Vector4<Scalar_T>& self, Scalar_T zval ) { self.z() = zval; } )
            .def_property( "w", []( const Vector4<Scalar_T>& self ) -> Scalar_T { return self.w(); }, 
                                []( Vector4<Scalar_T>& self, Scalar_T wval ) { self.w() = wval; } )
            .def( "__add__", []( const Vector4<Scalar_T>& v1, const Vector4<Scalar_T>& v2 ) -> Vector4<Scalar_T> { return v1 + v2; } )
            .def( "__sub__", []( const Vector4<Scalar_T>& v1, const Vector4<Scalar_T>& v2 ) -> Vector4<Scalar_T> { return v1 - v2; } )
            .def( "__mul__", []( const Vector4<Scalar_T>& v1, const Vector4<Scalar_T>& v2 ) -> Vector4<Scalar_T> { return v1 * v2; } )
            .def( "__mul__", []( const Vector4<Scalar_T>& vec, Scalar_T val ) -> Vector4<Scalar_T> { return val * vec; } )
            .def( "__rmul__", []( const Vector4<Scalar_T>& vec, Scalar_T val ) -> Vector4<Scalar_T> { return val * vec; } )
            .def( "__getitem__", []( const Vector4<Scalar_T>& self, ssize_t index )
                {
                    if ( index > 3 )
                        throw py::index_error();
                    return self[index];
                } )
            .def( "__setitem__", []( Vector4<Scalar_T>& self, ssize_t index, Scalar_T v )
                {
                    if ( index > 3 )
                        throw py::index_error();
                    self[index] = v;
                } )
            .def( "__repr__", []( const Vector4<Scalar_T>& self)
                {
                    return "vec4(" + tinymath::toString( self ) + ")";
                } );
    }

}