
#include <vectors.h>

int main()
{
    tinymath::Vector2 _vec = { 1.0f, 2.0f };
    std::cout << tinymath::toString( _vec ) << std::endl;

    _vec[0] += 1.1f;
    _vec[1] += 0.6f;
    std::cout << tinymath::toString( _vec ) << std::endl;

    _vec.x() += 10.0f;
    _vec.y() -= 10.0f;
    std::cout << tinymath::toString( _vec ) << std::endl;

    tinymath::Vector2 _vec1 = { 0.5f, 1.5f };
    tinymath::Vector2 _vec2 = { 1.1f, 2.2f };
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