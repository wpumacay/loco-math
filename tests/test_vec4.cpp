
#include <vector_t.h>

int main()
{
    std::cout << "Vector4: Constructors and element-access **************************" << std::endl;
    tinymath::Vector4f _vec = { 1.0f, 2.0f, 3.0f, 4.0f };
    std::cout << tinymath::toString( _vec ) << std::endl;

    _vec[0] += 1.1f;
    _vec[1] += 0.6f;
    _vec[2] += 0.3f;
    _vec[3] += 0.1f;
    std::cout << tinymath::toString( _vec ) << std::endl;

    _vec.x() += 10.0f;
    _vec.y() -= 10.0f;
    _vec.z() *= 2.0f;
    _vec.w() /= 3.0f;
    std::cout << tinymath::toString( _vec ) << std::endl;

    std::cout << "Vector4: math operators *******************************************" << std::endl;
    tinymath::Vector4f _vec1 = { 0.5f, 1.5f, 2.0f, 2.5f };
    tinymath::Vector4f _vec2 = { 1.1f, 2.2f, 3.3f, 4.4f };
    std::cout << "v1 : " << tinymath::toString( _vec1 ) << std::endl;
    std::cout << "v2 : " << tinymath::toString( _vec2 ) << std::endl;
    std::cout << "v1 + v2 :" << tinymath::toString( _vec1 + _vec2 ) << std::endl;
    std::cout << "v1 - v2 :" << tinymath::toString( _vec1 - _vec2 ) << std::endl;
    std::cout << "v1 * v2 :" << tinymath::toString( _vec1 * _vec2 ) << std::endl;
    std::cout << "2*v1 : " << tinymath::toString( 2.0f * _vec1 ) << std::endl;
    std::cout << "v2*3 : " << tinymath::toString( 3.0f * _vec2 ) << std::endl;
    std::cout << "2*v1 + 3*v2 : " << tinymath::toString( 2.0f * _vec1 + 3.0f * _vec2 ) << std::endl;

    return 0;
}