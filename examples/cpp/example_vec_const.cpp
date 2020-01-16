
#include <vector_t.h>
#include <matrix_t.h>
#include <transforms.h>

typedef tinymath::Vector3f Vec3;

int main()
{
    Vec3 v1 = { 0.0f, 0.1f, 0.2f };
    Vec3 v2 = { 0.0f, 0.1000000000001f, 0.20000000000002f };

    if ( ( v1 - v2 ) == Vec3( { 0.0f, 0.0f, 0.0f } ) )
        std::cout << "equal!!!" << std::endl;
    else
        std::cout << "not equal" << std::endl;

    //// std::array<Vec3, 3> arr = { Vec3( { 1.0f, 0.0f, 0.0f } ), Vec3( { 0.0f, 1.0f, 0.0f } ), Vec3( { 0.0f, 0.0f, 1.0f } ) };
    //// for ( size_t i = 0; i < arr.size(); i++ )
    ////     std::cout << "vec-in-arr: " << tinymath::toString( arr[i] ) << std::endl;

    Vec3 arr[3] = { Vec3( { 1.0f, 0.0f, 0.0f } ), Vec3( { 0.0f, 1.0f, 0.0f } ), Vec3( { 0.0f, 0.0f, 1.0f } ) };
    for ( size_t i = 0; i < 3; i++ )
        std::cout << "vec-in-arr-2: " << tinymath::toString( arr[i] ) << std::endl;

    Vec3 _v( 1.0f, 0.0f, 0.0f );
    std::cout << "v: " << tinymath::toString( _v ) << std::endl;

    tinymath::Vector<float, 5> _vfunky;
    std::cout << "vfunky: " << tinymath::toString( _vfunky ) << std::endl;

    return 0;
}