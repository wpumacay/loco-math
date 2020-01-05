
#include <vectors.h>

namespace tinymath
{

    //////////////////////////////////////////////////////////////////////////
    //                              Vector2                                 //
    //////////////////////////////////////////////////////////////////////////

    Vector2::Vector2()
    {
        m_buff[0] = 0.0f;
        m_buff[1] = 0.0f;
    }

    Vector2::Vector2( tfloat val )
    {
        m_buff[0] = val;
        m_buff[1] = val;
    }

    Vector2::Vector2( tfloat xval, tfloat yval )
    {
        m_buff[0] = xval;
        m_buff[1] = yval;
    }

    Vector2::~Vector2()
    {
        // nothing to release manually
    }

    tfloat Vector2::operator[] ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 1 );

        return m_buff[indx];
    }

    tfloat& Vector2::operator[] ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 1 );

        return m_buff[indx];
    }

    Vector2 Vector2::operator+ ( const Vector2& other )
    {
        return { m_buff[0] + other.m_buff[0],
                 m_buff[1] + other.m_buff[1] };
    }

    Vector2 Vector2::operator- ( const Vector2& other )
    {
        return { m_buff[0] - other.m_buff[0],
                 m_buff[1] - other.m_buff[1] };
    }

    Vector2 Vector2::operator* ( const Vector2& other )
    {
        return { m_buff[0] * other.m_buff[0],
                 m_buff[1] * other.m_buff[1] };
    }

    Vector2 operator* ( const Vector2& vec, float val )
    {
        return { vec.x() * val, vec.y() * val };
    }

    Vector2 operator* ( float val, const Vector2& vec )
    {
        return { vec.x() * val, vec.y() * val };
    }

    std::string toString( const Vector2& vec )
    {
        return std::string( "[ " ) + std::to_string( vec.x() ) +
               std::string( ", " ) + std::to_string( vec.y() ) + std::string( " ]" );
    }

    //////////////////////////////////////////////////////////////////////////
    //                              Vector3                                 //
    //////////////////////////////////////////////////////////////////////////

    Vector3::Vector3()
    {
        m_buff[0] = 0.0f;
        m_buff[1] = 0.0f;
        m_buff[2] = 0.0f;
    }

    Vector3::Vector3( tfloat val )
    {
        m_buff[0] = val;
        m_buff[1] = val;
        m_buff[2] = val;
    }

    Vector3::Vector3( tfloat xval, tfloat yval, tfloat zval )
    {
        m_buff[0] = xval;
        m_buff[1] = yval;
        m_buff[2] = zval;
    }

    Vector3::~Vector3()
    {
        // nothing to release manually
    }

    tfloat Vector3::operator[] ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 2 );

        return m_buff[indx];
    }

    tfloat& Vector3::operator[] ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 2 );

        return m_buff[indx];
    }

    Vector3 Vector3::operator+ ( const Vector3& other )
    {
        return { m_buff[0] + other.m_buff[0],
                 m_buff[1] + other.m_buff[1],
                 m_buff[2] + other.m_buff[2] };
    }

    Vector3 Vector3::operator- ( const Vector3& other )
    {
        return { m_buff[0] - other.m_buff[0],
                 m_buff[1] - other.m_buff[1],
                 m_buff[2] - other.m_buff[2] };
    }

    Vector3 Vector3::operator* ( const Vector3& other )
    {
        return { m_buff[0] * other.m_buff[0],
                 m_buff[1] * other.m_buff[1],
                 m_buff[2] * other.m_buff[2] };
    }

    Vector3 operator* ( const Vector3& vec, float val )
    {
        return { vec.x() * val, vec.y() * val, vec.z() * val };
    }

    Vector3 operator* ( float val, const Vector3& vec )
    {
        return { vec.x() * val, vec.y() * val, vec.z() * val };
    }

    std::string toString( const Vector3& vec )
    {
        return std::string( "[ " ) + std::to_string( vec.x() ) +
               std::string( ", " ) + std::to_string( vec.y() ) +
               std::string( ", " ) + std::to_string( vec.z() ) + std::string( " ]" );
    }

    //////////////////////////////////////////////////////////////////////////
    //                              Vector4                                 //
    //////////////////////////////////////////////////////////////////////////

    Vector4::Vector4()
    {
        m_buff[0] = 0.0f;
        m_buff[1] = 0.0f;
        m_buff[2] = 0.0f;
        m_buff[3] = 0.0f;
    }

    Vector4::Vector4( tfloat val )
    {
        m_buff[0] = val;
        m_buff[1] = val;
        m_buff[2] = val;
        m_buff[3] = val;
    }

    Vector4::Vector4( tfloat xval, tfloat yval, tfloat zval, tfloat wval )
    {
        m_buff[0] = xval;
        m_buff[1] = yval;
        m_buff[2] = zval;
        m_buff[3] = wval;
    }

    Vector4::~Vector4()
    {
        // nothing to release manually
    }

    tfloat Vector4::operator[] ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 3 );

        return m_buff[indx];
    }

    tfloat& Vector4::operator[] ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 3 );

        return m_buff[indx];
    }

    Vector4 Vector4::operator+ ( const Vector4& other )
    {
        return { m_buff[0] + other.m_buff[0],
                 m_buff[1] + other.m_buff[1],
                 m_buff[2] + other.m_buff[2],
                 m_buff[3] + other.m_buff[3] };
    }

    Vector4 Vector4::operator- ( const Vector4& other )
    {
        return { m_buff[0] - other.m_buff[0],
                 m_buff[1] - other.m_buff[1],
                 m_buff[2] - other.m_buff[2],
                 m_buff[3] - other.m_buff[3] };
    }

    Vector4 Vector4::operator* ( const Vector4& other )
    {
        return { m_buff[0] * other.m_buff[0],
                 m_buff[1] * other.m_buff[1],
                 m_buff[2] * other.m_buff[2],
                 m_buff[3] * other.m_buff[3] };
    }

    Vector4 operator* ( const Vector4& vec, float val )
    {
        return { vec.x() * val, vec.y() * val, vec.z() * val, vec.w() * val };
    }

    Vector4 operator* ( float val, const Vector4& vec )
    {
        return { vec.x() * val, vec.y() * val, vec.z() * val, vec.w() * val };
    }

    std::string toString( const Vector4& vec )
    {
        return std::string( "[ " ) + std::to_string( vec.x() ) +
               std::string( ", " ) + std::to_string( vec.y() ) +
               std::string( ", " ) + std::to_string( vec.z() ) +
               std::string( ", " ) + std::to_string( vec.w() ) + std::string( " ]" );
    }

}