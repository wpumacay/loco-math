
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
            .def( py::init( []( py::array_t<tinymath::tfloat>& pyarray )
                {
                    auto bufferInfo = pyarray.request();
                    if ( bufferInfo.size != 2 )
                        throw std::runtime_error( "tinymath::Vector2 >>> incompatible array size, expected 2 floats" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    return new Vector2( bufferData[0], bufferData[1] );
                } ) )
            .def_buffer( []( Vector2& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.ptr(),
                        sizeof( tinymath::tfloat ),
                        py::format_descriptor< tinymath::tfloat >::format(),
                        1,
                        { 2 },
                        { sizeof( tinymath::tfloat ) }
                    );
                } )
            .def_property( "x", &Vector2::getX, &Vector2::setX )
            .def_property( "y", &Vector2::getY, &Vector2::setY )
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
            .def( py::init( []( py::array_t<tinymath::tfloat>& pyarray )
                {
                    auto bufferInfo = pyarray.request();
                    if ( bufferInfo.size != 3 )
                        throw std::runtime_error( "tinymath::Vector3 >>> incompatible array size, expected 3 floats" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    return new Vector3( bufferData[0], bufferData[1], bufferData[2] );
                } ) )
            .def_buffer( []( Vector3& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.ptr(),
                        sizeof( tinymath::tfloat ),
                        py::format_descriptor< tinymath::tfloat >::format(),
                        1,
                        { 3 },
                        { sizeof( tinymath::tfloat ) }
                    );
                } )
            .def_property( "x", &Vector3::getX, &Vector3::setX )
            .def_property( "y", &Vector3::getY, &Vector3::setY )
            .def_property( "z", &Vector3::getZ, &Vector3::setZ )
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
            .def( py::init( []( py::array_t<tinymath::tfloat>& pyarray )
                {
                    auto bufferInfo = pyarray.request();
                    if ( bufferInfo.size != 4 )
                        throw std::runtime_error( "tinymath::Vector4 >>> incompatible array size, expected 4 floats" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    return new Vector4( bufferData[0], bufferData[1], bufferData[2], bufferData[3] );
                } ) )
            .def_buffer( []( Vector4& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.ptr(),
                        sizeof( tinymath::tfloat ),
                        py::format_descriptor< tinymath::tfloat >::format(),
                        1,
                        { 4 },
                        { sizeof( tinymath::tfloat ) }
                    );
                } )
            .def_property( "x", &Vector4::getX, &Vector4::setX )
            .def_property( "y", &Vector4::getY, &Vector4::setY )
            .def_property( "z", &Vector4::getZ, &Vector4::setZ )
            .def_property( "w", &Vector4::getW, &Vector4::setW )
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