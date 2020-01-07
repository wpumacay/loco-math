
#include <py_vectors.h>

namespace py = pybind11;

namespace tinymath
{

    void bindings_vector2( py::module& m )
    {
        py::class_< Vector2 >( m, "Vector2", py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init<tinymath::tfloat>() )
            .def( py::init<tinymath::tfloat, tinymath::tfloat>() )
            .def( py::init( []( py::array_t<tinymath::tfloat>& vec2arr )
                {
                    auto bufferInfo = vec2arr.request();
                    if ( bufferInfo.size != 2 )
                        throw std::runtime_error( "tinymath::Vector2 >>> incompatible array size, expected 2 floats" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    return new Vector2( bufferData[0], bufferData[1] );
                } ) )
            .def_buffer( []( Vector2& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.data(),
                        sizeof( tinymath::tfloat ),
                        py::format_descriptor< tinymath::tfloat >::format(),
                        1,
                        { 2 },
                        { sizeof( tinymath::tfloat ) }
                    );
                } )
            .def_property( "x",
                []( const Vector2& self ) -> tinymath::tfloat
                    {
                        return self.x();
                    }, 
                []( Vector2& self, tinymath::tfloat xval )
                    {
                        self.x() = xval;
                    } )
            .def_property( "y", 
                []( const Vector2& self ) -> tinymath::tfloat
                    {
                        return self.y();
                    }, 
                []( Vector2& self, tinymath::tfloat yval )
                    {
                        self.y() = yval;
                    } )
            .def( "length", &Vector2::length )
            .def( "dot", &Vector2::dot )
            .def( "normalize", &Vector2::normalize )
            .def( "normalized", &Vector2::normalized )
            .def( "scale", (void (Vector2::*)(tfloat, tfloat)) &Vector2::scale )
            .def( "scale", (void (Vector2::*)(const Vector2&)) &Vector2::scale )
            .def( "scaled", (Vector2 (Vector2::*)(tfloat, tfloat) const) &Vector2::scaled )
            .def( "scaled", (Vector2 (Vector2::*)(const Vector2&) const) &Vector2::scaled )
            .def( "__add__", []( const Vector2& v1, const Vector2& v2 ) -> Vector2 { return v1 + v2; } )
            .def( "__sub__", []( const Vector2& v1, const Vector2& v2 ) -> Vector2 { return v1 - v2; } )
            .def( "__mul__", []( const Vector2& v1, const Vector2& v2 ) -> Vector2 { return v1 * v2; } )
            .def( "__mul__", []( const Vector2& vec, float val ) -> Vector2 { return val * vec; } )
            .def( "__rmul__", []( const Vector2& vec, float val ) -> Vector2 { return val * vec; } )
            .def( "__getitem__", []( const Vector2& self, ssize_t index )
                {
                    if ( index > 1 ) 
                        throw py::index_error();
                    return self[index];
                } )
            .def( "__setitem__", []( Vector2& self, ssize_t index, tinymath::tfloat v )
                {
                    if ( index > 1 )
                        throw py::index_error();
                    self[index] = v;
                } )
            .def( "__repr__", []( const Vector2& self )
                {
                    return "vec2(" + tinymath::toString( self ) + ")";
                } );
    }

    void bindings_vector3( py::module& m )
    {
        py::class_< Vector3 >( m, "Vector3", py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init<tinymath::tfloat>() )
            .def( py::init<tinymath::tfloat, tinymath::tfloat, tinymath::tfloat>() )
            .def( py::init( []( py::array_t<tinymath::tfloat>& vec2arr, tinymath::tfloat zval )
                {
                    auto bufferInfo = vec2arr.request();
                    if ( bufferInfo.size != 2 )
                        throw std::runtime_error( "tinymath::Vector3 >>> incompatible array size, expected 2 floats for xy components" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    return new Vector3( bufferData[0], bufferData[1], zval );
                } ) )
            .def( py::init( []( py::array_t<tinymath::tfloat>& vec3arr )
                {
                    auto bufferInfo = vec3arr.request();
                    if ( bufferInfo.size != 3 )
                        throw std::runtime_error( "tinymath::Vector3 >>> incompatible array size, expected 3 floats" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    return new Vector3( bufferData[0], bufferData[1], bufferData[2] );
                } ) )
            .def_buffer( []( Vector3& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.data(),
                        sizeof( tinymath::tfloat ),
                        py::format_descriptor< tinymath::tfloat >::format(),
                        1,
                        { 3 },
                        { sizeof( tinymath::tfloat ) }
                    );
                } )
            .def_property( "x", []( const Vector3& self ) -> tfloat { return self.x(); }, 
                                []( Vector3& self, tfloat xval ) { self.x() = xval; } )
            .def_property( "y", []( const Vector3& self ) -> tfloat { return self.y(); }, 
                                []( Vector3& self, tfloat yval ) { self.y() = yval; } )
            .def_property( "z",  []( const Vector3& self ) -> tfloat { return self.z(); }, 
                                []( Vector3& self, tfloat zval ) { self.z() = zval; } )
            .def( "length", &Vector3::length )
            .def( "dot", &Vector3::dot )
            .def( "cross", &Vector3::cross )
            .def( "normalize", &Vector3::normalize )
            .def( "normalized", &Vector3::normalized )
            .def( "scale", (void (Vector3::*)(tfloat, tfloat, tfloat)) &Vector3::scale )
            .def( "scale", (void (Vector3::*)(const Vector3&)) &Vector3::scale )
            .def( "scaled", (Vector3 (Vector3::*)(tfloat, tfloat, tfloat) const) &Vector3::scaled )
            .def( "scaled", (Vector3 (Vector3::*)(const Vector3&) const) &Vector3::scaled )
            .def( "__add__", []( const Vector3& v1, const Vector3& v2 ) -> Vector3 { return v1 + v2; } )
            .def( "__sub__", []( const Vector3& v1, const Vector3& v2 ) -> Vector3 { return v1 - v2; } )
            .def( "__mul__", []( const Vector3& v1, const Vector3& v2 ) -> Vector3 { return v1 * v2; } )
            .def( "__mul__", []( const Vector3& vec, float val ) -> Vector3 { return val * vec; } )
            .def( "__rmul__", []( const Vector3& vec, float val ) -> Vector3 { return val * vec; } )
            .def( "__getitem__", []( const Vector3& self, ssize_t index )
                {
                    if ( index > 2 )
                        throw py::index_error();
                    return self[index];
                } )
            .def( "__setitem__", []( Vector3& self, ssize_t index, tinymath::tfloat v )
                {
                    if ( index > 2 )
                        throw py::index_error();
                    self[index] = v;
                } )
            .def( "__repr__", []( const Vector3& self)
                {
                    return "vec3(" + tinymath::toString( self ) + ")";
                } );
    }

    void bindings_vector4( py::module& m )
    {
        py::class_< Vector4 >( m, "Vector4", py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init<tinymath::tfloat>() )
            .def( py::init<tinymath::tfloat, tinymath::tfloat, tinymath::tfloat, tinymath::tfloat>() )
            .def( py::init( []( py::array_t<tinymath::tfloat>& vec3arr, tinymath::tfloat wval )
                {
                    auto bufferInfo = vec3arr.request();
                    if ( bufferInfo.size != 3 )
                        throw std::runtime_error( "tinymath::Vector4 >>> incompatible array size, expected 3 floats for xyz components" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    return new Vector4( bufferData[0], bufferData[1], bufferData[2], wval );
                } ) )
            .def( py::init( []( py::array_t<tinymath::tfloat>& vec4arr )
                {
                    auto bufferInfo = vec4arr.request();
                    if ( bufferInfo.size != 4 )
                        throw std::runtime_error( "tinymath::Vector4 >>> incompatible array size, expected 4 floats" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    return new Vector4( bufferData[0], bufferData[1], bufferData[2], bufferData[3] );
                } ) )
            .def_buffer( []( Vector4& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.data(),
                        sizeof( tinymath::tfloat ),
                        py::format_descriptor< tinymath::tfloat >::format(),
                        1,
                        { 4 },
                        { sizeof( tinymath::tfloat ) }
                    );
                } )
            .def_property( "x", []( const Vector4& self ) -> tfloat { return self.x(); }, 
                                []( Vector4& self, tfloat xval ) { self.x() = xval; } )
            .def_property( "y", []( const Vector4& self ) -> tfloat { return self.y(); }, 
                                []( Vector4& self, tfloat yval ) { self.y() = yval; } )
            .def_property( "z", []( const Vector4& self ) -> tfloat { return self.z(); }, 
                                []( Vector4& self, tfloat zval ) { self.z() = zval; } )
            .def_property( "w", []( const Vector4& self ) -> tfloat { return self.w(); }, 
                                []( Vector4& self, tfloat wval ) { self.w() = wval; } )
            .def( "__add__", []( const Vector4& v1, const Vector4& v2 ) -> Vector4 { return v1 + v2; } )
            .def( "__sub__", []( const Vector4& v1, const Vector4& v2 ) -> Vector4 { return v1 - v2; } )
            .def( "__mul__", []( const Vector4& v1, const Vector4& v2 ) -> Vector4 { return v1 * v2; } )
            .def( "__mul__", []( const Vector4& vec, float val ) -> Vector4 { return val * vec; } )
            .def( "__rmul__", []( const Vector4& vec, float val ) -> Vector4 { return val * vec; } )
            .def( "__getitem__", []( const Vector4& self, ssize_t index )
                {
                    if ( index > 3 )
                        throw py::index_error();
                    return self[index];
                } )
            .def( "__setitem__", []( Vector4& self, ssize_t index, tinymath::tfloat v )
                {
                    if ( index > 3 )
                        throw py::index_error();
                    self[index] = v;
                } )
            .def( "__repr__", []( const Vector4& self)
                {
                    return "vec4(" + tinymath::toString( self ) + ")";
                } );
    }

}