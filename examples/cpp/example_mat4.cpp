
#include <iostream>
#include <matrix_t.h>
#include <transforms.h>

int main()
{
    auto mat = tinymath::Matrix4f( { 4.0, 4.0, 5.0, 0.0,
                                     8.0, 4.0, 4.0, 7.0,
                                     4.0, 2.0, 8.0, 1.0,
                                     7.0, 7.0, 3.0, 1.0 } );

    std::cout << "mat:" << std::endl;
    std::cout << tinymath::toString( mat ) << std::endl;
    std::cout << "inverse( mat ):" << std::endl;
    std::cout << tinymath::toString( tinymath::inverse( mat ) ) << std::endl;
    std::cout << "col0: " << std::endl;
    std::cout << tinymath::toString( mat(0) ) << std::endl;
    std::cout << "vec3(col0): " << std::endl;
    std::cout << tinymath::toString( tinymath::Vector3f( mat( 0 ) ) ) << std::endl;
    std::cout << "mat3(mat): " << std::endl;
    std::cout << tinymath::toString( tinymath::Matrix3f( mat ) ) << std::endl;

    return 0;
}