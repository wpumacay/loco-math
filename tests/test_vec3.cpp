
#include <vector_t.h>

int main()
{
    std::cout << "Vector3: Constructors and element-access **************************" << std::endl;
    tinymath::Vector3f _vec = { 1.0f, 2.0f, 3.0f };
    std::cout << tinymath::toString( _vec ) << std::endl;

    _vec[0] += 1.1f;
    _vec[1] += 0.6f;
    _vec[2] += 0.3f;
    std::cout << tinymath::toString( _vec ) << std::endl;

    _vec.x() += 10.0f;
    _vec.y() -= 10.0f;
    _vec.z() *= 2.0f;
    std::cout << tinymath::toString( _vec ) << std::endl;

    std::cout << "Vector3: math operators *******************************************" << std::endl;
    tinymath::Vector3f _vec1 = { 0.5f, 1.5f, 2.0f };
    tinymath::Vector3f _vec2 = { 1.1f, 2.2f, 3.3f };
    std::cout << "v1 : " << tinymath::toString( _vec1 ) << std::endl;
    std::cout << "v2 : " << tinymath::toString( _vec2 ) << std::endl;
    std::cout << "v1 + v2 :" << tinymath::toString( _vec1 + _vec2 ) << std::endl;
    std::cout << "v1 - v2 :" << tinymath::toString( _vec1 - _vec2 ) << std::endl;
    std::cout << "v1 * v2 :" << tinymath::toString( _vec1 * _vec2 ) << std::endl;
    std::cout << "2*v1 : " << tinymath::toString( 2.0f * _vec1 ) << std::endl;
    std::cout << "v2*3 : " << tinymath::toString( 3.0f * _vec2 ) << std::endl;
    std::cout << "2*v1 + 3*v2 : " << tinymath::toString( 2.0f * _vec1 + 3.0f * _vec2 ) << std::endl;

    std::cout << "Vector3: helper methods *******************************************" << std::endl;
    tinymath::Vector3f _vec3 = { 0.3f, 0.4f, 0.5f };
    tinymath::Vector3f _vec4 = { 1.0f, 2.0f, 3.0f };
    std::cout << "v3: " << tinymath::toString( _vec3 ) << std::endl;
    std::cout << "v4: " << tinymath::toString( _vec4 ) << std::endl;
    std::cout << "v3.length(): " << std::to_string( _vec3.length() ) << std::endl;
    std::cout << "v4.length(): " << std::to_string( _vec4.length() ) << std::endl;
    std::cout << "v3.normalized(): " << tinymath::toString( _vec3.normalized() ) << std::endl;
    std::cout << "v4.normalized(): " << tinymath::toString( _vec4.normalized() ) << std::endl;
    std::cout << "v3.scaled({2.0,3.0,4.0}): " << tinymath::toString( _vec3.scaled( { 2.0f, 3.0f, 4.0f } ) ) << std::endl;
    std::cout << "v4.scaled({0.5,0.25,0.125}): " << tinymath::toString( _vec4.scaled( { 0.5f, 0.25f, 0.125f } ) ) << std::endl;

    return 0;
}