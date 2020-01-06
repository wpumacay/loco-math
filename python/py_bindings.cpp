
#include <py_bindings.h>

PYBIND11_MODULE( tinymath, m )
{
    // commond bindings
    tinymath::bindings_common( m );
    // vectors bindings
    tinymath::bindings_vector2( m );
    tinymath::bindings_vector3( m );
    tinymath::bindings_vector4( m );
}