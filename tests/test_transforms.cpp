
#include <transforms.h>

int main()
{
    auto rotmat = tinymath::Matrix3f( { 0.5000000, -0.1464466,  0.8535534,
                                        0.5000000,  0.8535534, -0.1464466,
                                        -0.7071068,  0.5000000,  0.5000000 } );
    std::cout << "rotmat: " << std::endl;
    std::cout << tinymath::toString( rotmat ) << std::endl;
    std::cout << "euler: " << std::endl;
    std::cout << tinymath::toString( tinymath::euler( rotmat ) ) << std::endl;
    std::cout << "quaternion: " << std::endl;
    std::cout << tinymath::toString( tinymath::quaternion( rotmat ) ) << std::endl;
    std::cout << "axis-angle: " << std::endl;
    auto _axis_angle = tinymath::axisAngle( rotmat );
    auto _axis = _axis_angle.first;
    auto _angle = _axis_angle.second;
    std::cout << "axis: " << tinymath::toString( _axis ) << std::endl;
    std::cout << "angle: " << _angle << std::endl;

    std::cout << "from-euler: " << std::endl;
    tinymath::Vector3f euler = { 0.7853982, 0.7853981, 0.7853982 };
    std::cout << tinymath::toString( tinymath::rotation( euler ) ) << std::endl;
    std::cout << "from-quaternion: " << std::endl;
    tinymath::Vector4f quat = { 0.1913417, 0.4619398, 0.1913417, 0.8446232 };
    std::cout << tinymath::toString( tinymath::rotation( quat ) ) << std::endl;
    std::cout << "from-axis-angle: " << std::endl;
    tinymath::Vector3f axis = { 0.3574067, 0.8628562, 0.3574067 };
    std::cout << tinymath::toString( tinymath::rotation( axis, 1.1298708 ) ) << std::endl;

    return 0;
}