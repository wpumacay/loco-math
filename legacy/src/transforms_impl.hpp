
#include <transforms.h>

namespace tinymath
{

    // @source: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
    template< typename Scalar_T >
    Vector<Scalar_T, 4> quaternion( const Matrix<Scalar_T, 3>& rotmat )
    {
        Vector<Scalar_T, 4> _resQuat;

        auto m00 = rotmat( 0, 0 );
        auto m11 = rotmat( 1, 1 );
        auto m22 = rotmat( 2, 2 );
        auto trace = m00 + m11 + m22;

        if ( trace > 0 )
        {
            auto t = std::sqrt( trace + 1 ) * 2.0;

            _resQuat.x() = ( rotmat( 2, 1 ) - rotmat( 1, 2 ) ) / t;
            _resQuat.y() = ( rotmat( 0, 2 ) - rotmat( 2, 0 ) ) / t;
            _resQuat.z() = ( rotmat( 1, 0 ) - rotmat( 0, 1 ) ) / t;
            _resQuat.w() = 0.25 * t;
        }
        else if ( ( m00 > m11 ) && ( m00 > m22 ) )
        {
            auto t = std::sqrt( 1 + m00 - m11 - m22 ) * 2;

            _resQuat.x() = 0.25 * t;
            _resQuat.y() = ( rotmat( 0, 1 ) + rotmat( 1, 0 ) ) / t;
            _resQuat.z() = ( rotmat( 0, 2 ) + rotmat( 2, 0 ) ) / t;
            _resQuat.w() = ( rotmat( 2, 1 ) - rotmat( 1, 2 ) ) / t;
        }
        else if ( m11 > m22 )
        {
            auto t = std::sqrt( 1 + m11 - m00 - m22 ) * 2;

            _resQuat.x() = ( rotmat( 0, 1 ) + rotmat( 1, 0 ) ) / t;
            _resQuat.y() = 0.25 * t;
            _resQuat.z() = ( rotmat( 1, 2 ) + rotmat( 2, 1 ) ) / t;
            _resQuat.w() = ( rotmat( 0, 2 ) - rotmat( 2, 0 ) ) / t;
        }
        else
        {
            auto t = std::sqrt( 1 + m22 - m00 - m11 ) * 2;

            _resQuat.x() = ( rotmat( 0, 2 ) + rotmat( 2, 0 ) ) / t;
            _resQuat.y() = ( rotmat( 1, 2 ) + rotmat( 2, 1 ) ) / t;
            _resQuat.z() = 0.25 * t;
            _resQuat.w() = ( rotmat( 1, 0 ) - rotmat( 0, 1 ) ) / t;
        }

        return _resQuat;
    }
    template< typename Scalar_T >
    Vector<Scalar_T, 4> quaternion( const Matrix<Scalar_T, 4>& transform )
    {
        Vector<Scalar_T, 4> _resQuat;

        auto m00 = transform( 0, 0 );
        auto m11 = transform( 1, 1 );
        auto m22 = transform( 2, 2 );
        auto trace = m00 + m11 + m22;

        if ( trace > 0 )
        {
            auto t = std::sqrt( trace + 1 ) * 2.0;

            _resQuat.x() = ( transform( 2, 1 ) - transform( 1, 2 ) ) / t;
            _resQuat.y() = ( transform( 0, 2 ) - transform( 2, 0 ) ) / t;
            _resQuat.z() = ( transform( 1, 0 ) - transform( 0, 1 ) ) / t;
            _resQuat.w() = 0.25 * t;
        }
        else if ( ( m00 > m11 ) && ( m00 > m22 ) )
        {
            auto t = std::sqrt( 1 + m00 - m11 - m22 ) * 2;

            _resQuat.x() = 0.25 * t;
            _resQuat.y() = ( transform( 0, 1 ) + transform( 1, 0 ) ) / t;
            _resQuat.z() = ( transform( 0, 2 ) + transform( 2, 0 ) ) / t;
            _resQuat.w() = ( transform( 2, 1 ) - transform( 1, 2 ) ) / t;
        }
        else if ( m11 > m22 )
        {
            auto t = std::sqrt( 1 + m11 - m00 - m22 ) * 2;

            _resQuat.x() = ( transform( 0, 1 ) + transform( 1, 0 ) ) / t;
            _resQuat.y() = 0.25 * t;
            _resQuat.z() = ( transform( 1, 2 ) + transform( 2, 1 ) ) / t;
            _resQuat.w() = ( transform( 0, 2 ) - transform( 2, 0 ) ) / t;
        }
        else
        {
            auto t = std::sqrt( 1 + m22 - m00 - m11 ) * 2;

            _resQuat.x() = ( transform( 0, 2 ) + transform( 2, 0 ) ) / t;
            _resQuat.y() = ( transform( 1, 2 ) + transform( 2, 1 ) ) / t;
            _resQuat.z() = 0.25 * t;
            _resQuat.w() = ( transform( 1, 0 ) - transform( 0, 1 ) ) / t;
        }

        return _resQuat;
    }

    // @todo: deal with special cases (-cosB instead of +cosB, ...)
    // @source: https://github.com/mrdoob/three.js/blob/master/src/math/Euler.js
    template< typename Scalar_T >
    Vector<Scalar_T, 3> euler( const Matrix<Scalar_T, 3>& rotmat )
    {
        // euler zyx intrinsic :
        // Rot = Rz * Ry * Rx
        Vector<Scalar_T, 3> _resEuler;

        auto m00 = rotmat( 0, 0 );
        auto m10 = rotmat( 1, 0 );
        auto m20 = rotmat( 2, 0 );
        auto m21 = rotmat( 2, 1 );
        auto m22 = rotmat( 2, 2 );

        _resEuler.x() = std::atan2( m21, m22 );
        _resEuler.y() = std::atan2( -m20, std::sqrt( m00 * m00 + m10 * m10 ) );
        _resEuler.z() = std::atan2( m10, m00 );

        return _resEuler;
    }
    template< typename Scalar_T >
    Vector<Scalar_T, 3> euler( const Matrix<Scalar_T, 4>& transform )
    {
        // euler zyx intrinsic :
        // Rot = Rz * Ry * Rx
        Vector<Scalar_T, 3> _resEuler;

        auto m00 = transform( 0, 0 );
        auto m10 = transform( 1, 0 );
        auto m20 = transform( 2, 0 );
        auto m21 = transform( 2, 1 );
        auto m22 = transform( 2, 2 );

        _resEuler.x() = std::atan2( m21, m22 );
        _resEuler.y() = std::atan2( -m20, std::sqrt( m00 * m00 + m10 * m10 ) );
        _resEuler.z() = std::atan2( m10, m00 );

        return _resEuler;
    }

    // @todo: handle singularities (angle = 0° or 180°)
    // @source: https://en.wikipedia.org/wiki/Rotation_matrix#Conversion_from_and_to_axis%E2%80%93angle
    template< typename Scalar_T >
    std::pair< Vector<Scalar_T, 3>, Scalar_T > axisAngle( const Matrix<Scalar_T, 3>& rotmat )
    {
        Vector<Scalar_T, 3> _axis; 
        Scalar_T _angle;

        auto _trace = rotmat( 0, 0 ) + rotmat( 1, 1 ) + rotmat( 2, 2 );
        _angle = std::acos( ( _trace - 1 ) / 2 );

        _axis.x() = rotmat( 2, 1 ) - rotmat( 1, 2 );
        _axis.y() = rotmat( 0, 2 ) - rotmat( 2, 0 );
        _axis.z() = rotmat( 1, 0 ) - rotmat( 0, 1 );
        _axis.normalize();

        return { _axis, _angle };
    }
    template< typename Scalar_T >
    std::pair< Vector<Scalar_T, 3>, Scalar_T > axisAngle( const Matrix<Scalar_T, 4>& transform )
    {
        Vector<Scalar_T, 3> _axis; 
        Scalar_T _angle;

        auto _trace = transform( 0, 0 ) + transform( 1, 1 ) + transform( 2, 2 );
        _angle = std::acos( ( _trace - 1 ) / 2 );

        _axis.x() = transform( 2, 1 ) - transform( 1, 2 );
        _axis.y() = transform( 0, 2 ) - transform( 2, 0 );
        _axis.z() = transform( 1, 0 ) - transform( 0, 1 );
        _axis.normalize();

        return { _axis, _angle };
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotation( const Vector<Scalar_T, 3>& ezyx )
    {
        Matrix<Scalar_T, 3> _resRotMatrix;

        auto _cz = std::cos( ezyx.z() );
        auto _sz = std::sin( ezyx.z() );
        auto _cy = std::cos( ezyx.y() );
        auto _sy = std::sin( ezyx.y() );
        auto _cx = std::cos( ezyx.x() );
        auto _sx = std::sin( ezyx.x() );

        _resRotMatrix( 0, 0 ) = _cz * _cy;
        _resRotMatrix( 1, 0 ) = _sz * _cy;
        _resRotMatrix( 2, 0 ) = -_sy;

        _resRotMatrix( 0, 1 ) = _cz * _sy * _sx - _sz * _cx;
        _resRotMatrix( 1, 1 ) = _cz * _cx + _sz * _sy * _sx;
        _resRotMatrix( 2, 1 ) = _cy * _sx;

        _resRotMatrix( 0, 2 ) = _sz * _sx + _cz * _sy * _cx;
        _resRotMatrix( 1, 2 ) = _sz * _sy * _cx - _cz * _sx;
        _resRotMatrix( 2, 2 ) = _cy * _cx;

        return _resRotMatrix;
    }

    // @source: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix
    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotation( const Vector<Scalar_T, 4>& quat )
    {
        auto _qi = quat.x();
        auto _qj = quat.y();
        auto _qk = quat.z();
        auto _qr = quat.w();

        auto _n = sqrt( _qr * _qr + _qi * _qi + _qj * _qj + _qk * _qk );

        auto _s = 1.0 / ( _n * _n );

        Matrix<Scalar_T, 4> _resRotMatrix;

        _resRotMatrix( 0, 0 ) = 1.0 - 2.0 * _s * ( _qj * _qj + _qk * _qk );
        _resRotMatrix( 1, 0 ) = 2.0 * _s * ( _qi * _qj + _qk * _qr );
        _resRotMatrix( 2, 0 ) = 2.0 * _s * ( _qi * _qk - _qj * _qr );

        _resRotMatrix( 0, 1 ) = 2.0 * _s * ( _qi * _qj - _qk * _qr );
        _resRotMatrix( 1, 1 ) = 1.0 - 2.0 * _s * ( _qi * _qi + _qk * _qk );
        _resRotMatrix( 2, 1 ) = 2.0 * _s * ( _qj * _qk + _qi * _qr );

        _resRotMatrix( 0, 2 ) = 2.0 * _s * ( _qi * _qk + _qj * _qr );
        _resRotMatrix( 1, 2 ) = 2.0 * _s * ( _qj * _qk - _qi * _qr );
        _resRotMatrix( 2, 2 ) = 1.0 - 2.0 * _s * ( _qi * _qi + _qj * _qj );

        return _resRotMatrix;
    }

    // @source: https://github.com/mrdoob/three.js/blob/master/src/math/Quaternion.js
    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotation( const Vector<Scalar_T, 3>& axis, tfloat angle )
    {
        auto s = std::sin( angle / 2.0 );
        auto quat = Vector<Scalar_T, 4>();

        quat.x() = axis.x() * s;
        quat.y() = axis.y() * s;
        quat.z() = axis.z() * s;
        quat.w() = std::cos( angle / 2.0 );

        return rotation( quat );
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotationX( tfloat angle )
    {
        Matrix<Scalar_T, 3> _resRotMatrix;

        auto cs = std::cos( angle );
        auto sn = std::sin( angle );

        _resRotMatrix( 1, 1 ) = cs; _resRotMatrix( 1, 2 ) = -sn;
        _resRotMatrix( 2, 1 ) = sn; _resRotMatrix( 2, 2 ) = cs;

        return _resRotMatrix;
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotationY( tfloat angle )
    {
        Matrix<Scalar_T, 3> _resRotMatrix;

        auto cs = std::cos( angle );
        auto sn = std::sin( angle );

        _resRotMatrix( 0, 0 ) = cs; _resRotMatrix( 0, 2 ) = sn;
        _resRotMatrix( 2, 0 ) = -sn; _resRotMatrix( 2, 2 ) = cs;

        return _resRotMatrix;
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotationZ( tfloat angle )
    {
        Matrix<Scalar_T, 3> _resRotMatrix;

        auto cs = std::cos( angle );
        auto sn = std::sin( angle );

        _resRotMatrix( 0, 0 ) = cs; _resRotMatrix( 0, 1 ) = -sn;
        _resRotMatrix( 1, 0 ) = sn; _resRotMatrix( 1, 1 ) = cs;

        return _resRotMatrix;
    }

    template< typename Scalar_T >
    Vector<Scalar_T, 3> cross( const Vector<Scalar_T, 3>& vec1, const Vector<Scalar_T, 3>& vec2 )
    {
        Vector<Scalar_T, 3> _resCross;

        _resCross.x() =  vec1.y() * vec2.z() - vec2.y() * vec1.z();
        _resCross.y() = -vec1.x() * vec2.z() + vec2.x() * vec1.z();
        _resCross.z() =  vec1.x() * vec2.y() - vec2.x() * vec1.y();

        return _resCross;
    }

}
