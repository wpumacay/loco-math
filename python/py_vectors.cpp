
#include <py_vectors.h>

namespace py = pybind11;

namespace tinymath
{

    void bindings_vector2( py::module& m )
    {
        py::class_< Vector2 >( m, "Vector2", py::buffer_protocol() )
            .def( py::init<>() )
            .def( py::init<tfloat>() )
            .def( py::init<tfloat,tfloat>() )
            .def( py::init( []( py::array_t<tinymath::tfloat>& pyarray )
                {
                    auto bufferInfo = pyarray.request();
                    if ( bufferInfo.size != 2 )
                        throw std::runtime_error( "tinymath::Vector2 >>> incompatible array size, expected 2 floats" );

                    auto bufferData = (tfloat*) bufferInfo.ptr;
                    return new Vector2( bufferData[0], bufferData[1] );
                } ) )
            .def_buffer( []( Vector2& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.ptr(),
                        sizeof(tfloat),
                        py::format_descriptor<tinymath::tfloat>::format(),
                        1,
                        { 2 },
                        { sizeof( tfloat ) }
                    );
                } )
            .def_property( "x", &Vector2::getX, &Vector2::setX )
            .def_property( "y", &Vector2::getY, &Vector2::setY )
            .def( "__repr__", []( const Vector2& self )
                {
                    return "vec2(" + tinymath::toString( self ) + ")";
                } );
    }

    void bindings_vector3( py::module& m )
    {
////         py::class_< Vector3 >( m, "Vector3" )
////             .def( py::init<>() )
////             .def( py::init<tfloat>() )
////             .def( py::init<tfloat,tfloat,tfloat>() )
////             .def( "__repr__", &Vector2::toString );
    }

    void bindings_vector4( py::module& m )
    {

    }

}