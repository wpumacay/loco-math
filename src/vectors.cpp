
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

    std::string Vector2::toString( const Vector2& vec ) const
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

    std::string Vector3::toString( const Vector3& vec ) const
    {
        return std::string( "[ " ) + std::to_string( vec.x() ) +
               std::string( ", " ) + std::to_string( vec.y() ) +
               std::string( ", " ) + std::to_string( vec.z() ) + std::string( " ]" );
    }

}