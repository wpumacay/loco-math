
#include <bindings_all.h>

PYBIND11_MODULE( tinymath, m )
{
    // commond bindings
    tinymath::bindings_common( m );
    // vectors bindings
    tinymath::bindings_vector<float, 2>( m, "Vector2f" );
    tinymath::bindings_vector<double, 2>( m, "Vector2d" );
    tinymath::bindings_vector<float, 3>( m, "Vector3f" );
    tinymath::bindings_vector<double, 3>( m, "Vector3d" );
    tinymath::bindings_vector<float, 4>( m, "Vector4f" );
    tinymath::bindings_vector<double, 4>( m, "Vector4d" );
}