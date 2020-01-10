
#include <bindings_all.h>

PYBIND11_MODULE( tinymath, m )
{
    // commond bindings
    tinymath::bindings_common( m );
    // vector_t bindings
    tinymath::bindings_vector<float, 2>( m, "Vector2f" );
    tinymath::bindings_vector<double, 2>( m, "Vector2d" );
    tinymath::bindings_vector<float, 3>( m, "Vector3f" );
    tinymath::bindings_vector<double, 3>( m, "Vector3d" );
    tinymath::bindings_vector<float, 4>( m, "Vector4f" );
    tinymath::bindings_vector<double, 4>( m, "Vector4d" );
    // matrix_t bindings
    tinymath::bindings_matrix<float, 2>( m, "Matrix2f" );
    tinymath::bindings_matrix<double, 2>( m, "Matrix2d" );
    tinymath::bindings_matrix<float, 3>( m, "Matrix3f" );
    tinymath::bindings_matrix<double, 3>( m, "Matrix3d" );
    tinymath::bindings_matrix<float, 4>( m, "Matrix4f" );
    tinymath::bindings_matrix<double, 4>( m, "Matrix4d" );
}