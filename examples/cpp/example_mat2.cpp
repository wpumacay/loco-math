
#include <iostream>
#include <matrix_t.h>

int main()
{
    auto mat = tinymath::Matrix2f();
    mat(0,0) = -2.0;
    std::cout << "mat:" << std::endl;
    std::cout << tinymath::toString( mat ) << std::endl;
    auto mat2 = tinymath::Matrix2f( { 1.0f, 2.0f,
                                      3.0f, 4.0f } );
    std::cout << "mat2:" << std::endl;
    std::cout << tinymath::toString( mat2 ) << std::endl;
    std::cout << "mat2.inverse():" << std::endl;
    std::cout << tinymath::toString( mat2.inverse() ) << std::endl;

    return 0;
}