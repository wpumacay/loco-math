
#include <iostream>
#include <matrix_t.h>

int main()
{
    auto mat = tinymath::Matrix2f();
    mat(0,0) = -2.0;
    std::cout << tinymath::toString( mat ) << std::endl;

    return 0;
}