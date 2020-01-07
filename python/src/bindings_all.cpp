
#include <bindings_all.h>

PYBIND11_MODULE( tinymath, m )
{
    // commond bindings
    tinymath::bindings_common( m );
    // vectors bindings
    tinymath::bindings_vector2<float>( m, "Vector2f" );
    tinymath::bindings_vector2<double>( m, "Vector2d" );
    tinymath::bindings_vector3<float>( m, "Vector3f" );
    tinymath::bindings_vector3<double>( m, "Vector3d" );
    tinymath::bindings_vector4<float>( m, "Vector4f" );
    tinymath::bindings_vector4<double>( m, "Vector4d" );
}