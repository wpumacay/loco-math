
#include <vectors.h>

using namespace tinymath;

int main()
{
    Vector3 _vec1 = { 1.0f, 2.0f, 3.0f };
    std::cout << Vector2::toString( _vec1 ) << std::endl;

    _vec1[0] += 0.5f;
    _vec1[1] -= 1.5f;
    std::cout << Vector2::toString( _vec1 ) << std::endl;

    _vec1.z() = 10.5f;
    _vec1.y() += 5.5f;
    _vec1.x() += 0.5f;
    std::cout << Vector2::toString( _vec1 ) << std::endl;

    return 0;
}