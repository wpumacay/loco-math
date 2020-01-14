
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

    template< typename Scalar_T >
    Matrix<Scalar_T, 2 > inverse( const Matrix<Scalar_T, 2>& mat )
    {
        auto m00 = mat( 0, 0 ); auto m01 = mat( 0, 1 );
        auto m10 = mat( 1, 0 ); auto m11 = mat( 1, 1 );

        auto det = m00 * m11 - m10 * m01;
        return Matrix<Scalar_T, 2>( { m11 / det, -m01 / det,
                                      -m10 / det, m00 / det } );
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 3 > inverse( const Matrix<Scalar_T, 3>& mat )
    {
        Matrix<Scalar_T, 3> _resmat;

        auto m00 = mat( 0, 0 ); auto m01 = mat( 0, 1 ); auto m02 = mat( 0, 2 );
        auto m10 = mat( 1, 0 ); auto m11 = mat( 1, 1 ); auto m12 = mat( 1, 2 );
        auto m20 = mat( 2, 0 ); auto m21 = mat( 2, 1 ); auto m22 = mat( 2, 2 );

        // calculate some intermediate values - cofactors
        auto _c00 = ( m11 * m22 - m21 * m12 );
        auto _c10 = -( m01 * m22 - m21 * m02 );
        auto _c20 = ( m01 * m12 - m11 * m02 );

        auto _c01 = -( m10 * m22 - m20 * m12 );
        auto _c11 = ( m00 * m22 - m20 * m02 );
        auto _c21 = -( m00 * m12 - m10 * m02 );

        auto _c02 = ( m10 * m21 - m20 * m11 );
        auto _c12 = -( m00 * m21 - m20 * m01 );
        auto _c22 = ( m00 * m11 - m10 * m01 );

        auto _det = m00 * _c00 + m10 * _c10 + m20 * _c20;
        auto _invdet = 1 / _det;

        // Generate the inverse in-place using the transpose of the cofactors matrix
        _resmat( 0, 0 ) =_c00 * _invdet;
        _resmat( 0, 1 ) =_c10 * _invdet;
        _resmat( 0, 2 ) =_c20 * _invdet;

        _resmat( 1, 0 ) = _c01 * _invdet;
        _resmat( 1, 1 ) = _c11 * _invdet;
        _resmat( 1, 2 ) = _c21 * _invdet;

        _resmat( 2, 0 ) = _c02 * _invdet;
        _resmat( 2, 1 ) = _c12 * _invdet;
        _resmat( 2, 2 ) = _c22 * _invdet;

        return _resmat;
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 4 > inverse( const Matrix<Scalar_T, 4>& mat )
    {
        Matrix<Scalar_T, 4> _resmat;

        auto m00 = mat( 0, 0 ); auto m01 = mat( 0, 1 );
        auto m10 = mat( 1, 0 ); auto m11 = mat( 1, 1 );
        auto m20 = mat( 2, 0 ); auto m21 = mat( 2, 1 );
        auto m30 = mat( 3, 0 ); auto m31 = mat( 3, 1 );

        auto m02 = mat( 0, 2 ); auto m03 = mat( 0, 3 );
        auto m12 = mat( 1, 2 ); auto m13 = mat( 1, 3 );
        auto m22 = mat( 2, 2 ); auto m23 = mat( 2, 3 );
        auto m32 = mat( 3, 2 ); auto m33 = mat( 3, 3 );

        // Calculate some intermediate values - "minors" of order 2
        auto _m2323 = m22 * m33 - m32 * m23;
        auto _m1323 = m12 * m33 - m32 * m13;
        auto _m0323 = m02 * m33 - m32 * m03;
        auto _m1223 = m12 * m23 - m22 * m13;
        auto _m0223 = m02 * m23 - m22 * m03;
        auto _m0123 = m02 * m13 - m12 * m03;

        auto _m1201 = m10 * m21 - m20 * m11;
        auto _m1301 = m10 * m31 - m30 * m11;
        auto _m2301 = m20 * m31 - m30 * m21;
        auto _m0201 = m00 * m21 - m20 * m01;
        auto _m0301 = m00 * m31 - m30 * m01;
        auto _m0101 = m00 * m11 - m10 * m01;

        auto _det = m00 * ( m11 * _m2323 - m21 * _m1323 + m31 * _m1223 ) -
                    m10 * ( m01 * _m2323 - m21 * _m0323 + m31 * _m0223 ) +
                    m20 * ( m01 * _m1323 - m11 * _m0323 + m31 * _m0123 ) - 
                    m30 * ( m01 * _m1223 - m11 * _m0223 + m21 * _m0123 );

        auto _invdet = 1 / _det;

        // Generate transpose of "cofactors" matrix ( also divide by determinant ) in place
        _resmat( 0, 0 ) = ( m11 * _m2323 - m21 * _m1323 + m31 * _m1223 ) *  _invdet;
        _resmat( 0, 1 ) = ( m01 * _m2323 - m21 * _m0323 + m31 * _m0223 ) * -_invdet;
        _resmat( 0, 2 ) = ( m01 * _m1323 - m11 * _m0323 + m31 * _m0123 ) *  _invdet;
        _resmat( 0, 3 ) = ( m01 * _m1223 - m11 * _m0223 + m21 * _m0123 ) * -_invdet;

        _resmat( 1, 0 ) = ( m10 * _m2323 - m20 * _m1323 + m30 * _m1223 ) * -_invdet;
        _resmat( 1, 1 ) = ( m00 * _m2323 - m20 * _m0323 + m30 * _m0223 ) *  _invdet;
        _resmat( 1, 2 ) = ( m00 * _m1323 - m10 * _m0323 + m30 * _m0123 ) * -_invdet;
        _resmat( 1, 3 ) = ( m00 * _m1223 - m10 * _m0223 + m20 * _m0123 ) *  _invdet;

        _resmat( 2, 0 ) = ( m33 * _m1201 - m23 * _m1301 + m13 * _m2301 ) *  _invdet;
        _resmat( 2, 1 ) = ( m33 * _m0201 - m23 * _m0301 + m03 * _m2301 ) * -_invdet;
        _resmat( 2, 2 ) = ( m33 * _m0101 - m13 * _m0301 + m03 * _m1301 ) *  _invdet;
        _resmat( 2, 3 ) = ( m23 * _m0101 - m13 * _m0201 + m03 * _m1201 ) * -_invdet;

        _resmat( 3, 0 ) = ( m32 * _m1201 - m22 * _m1301 + m12 * _m2301 ) * -_invdet;
        _resmat( 3, 1 ) = ( m32 * _m0201 - m22 * _m0301 + m02 * _m2301 ) *  _invdet;
        _resmat( 3, 2 ) = ( m32 * _m0101 - m12 * _m0301 + m02 * _m1301 ) * -_invdet;
        _resmat( 3, 3 ) = ( m22 * _m0101 - m12 * _m0201 + m02 * _m1201 ) *  _invdet;

        return _resmat;
    }

}
