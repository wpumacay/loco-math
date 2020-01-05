
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
            .def( "__init__", []( Vector2& self, py::buffer buf )
                {
                    auto bufferInfo = buf.request();
                } )
            .def_buffer( []( Vector2& self ) -> py::buffer_info
                {
                    return py::buffer_info(
                        self.ptr(),
                        sizeof(tfloat),
                        py::format_descriptor<float>::format(),
                        1,
                        { 2 },
                        { sizeof( tfloat ) }
                    );
                } )
            .def_property( "x", &Vector2::setX, &Vector2::getX )
            .def_property( "y", &Vector2::setY, &Vector2::getY )
            .def_property( "z", &Vector2::setZ, &Vector2::getZ )
            .def( "__repr__", &Vector2::toString );
    }

    void bindings_vector3( py::module& m )
    {
        py::class_< Vector3 >( m, "Vector3" )
            .def( py::init<>() )
            .def( py::init<tfloat>() )
            .def( py::init<tfloat,tfloat,tfloat>() )
            .def( "__repr__", &Vector2::toString );
    }

}