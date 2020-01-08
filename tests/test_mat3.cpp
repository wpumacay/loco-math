
#include <iostream>
#include <matrix_t.h>

int main()
{
    auto mat = tinymath::Matrix3f( { 3.0f, 9.0f, 3.0f,
                                     9.0f, 0.0f, 3.0f,
                                     2.0f, 3.0f, 8.0f } );

    std::cout << "mat:" << std::endl;
    std::cout << tinymath::toString( mat ) << std::endl;
    std::cout << "mat.inverse():" << std::endl;
    std::cout << tinymath::toString( mat.inverse() ) << std::endl;

    return 0;
}