
#include <iostream>
#include <matrix_t.h>

int main()
{
    auto mat = tinymath::Matrix4f( { 4.0, 4.0, 5.0, 0.0,
                                     8.0, 4.0, 4.0, 7.0,
                                     4.0, 2.0, 8.0, 1.0,
                                     7.0, 7.0, 3.0, 1.0 } );

    std::cout << "mat:" << std::endl;
    std::cout << tinymath::toString( mat ) << std::endl;
    std::cout << "mat.inverse():" << std::endl;
    std::cout << tinymath::toString( mat.inverse() ) << std::endl;

    return 0;
}