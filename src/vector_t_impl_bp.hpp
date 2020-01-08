
#include <vector_t.h>

namespace tinymath
{

    //////////////////////////////////////////////////////////////////////////
    //                              Vector2                                 //
    //////////////////////////////////////////////////////////////////////////

    template< typename Scalar_T >
    Vector2<Scalar_T>::Vector2()
    {
        m_buff[0] = 0.0f;
        m_buff[1] = 0.0f;
    }

    template< typename Scalar_T >
    Vector2<Scalar_T>::Vector2( Scalar_T val )
    {
        m_buff[0] = val;
        m_buff[1] = val;
    }

    template< typename Scalar_T >
    Vector2<Scalar_T>::Vector2( Scalar_T xval, Scalar_T yval )
    {
        m_buff[0] = xval;
        m_buff[1] = yval;
    }

    template< typename Scalar_T >
    Vector2<Scalar_T>::~Vector2()
    {
        // nothing to release manually
    }

    template< typename Scalar_T >
    Scalar_T Vector2<Scalar_T>::length() const
    {
        return std::sqrt( m_buff[0] * m_buff[0] + m_buff[1] * m_buff[1] );
    }

    template< typename Scalar_T >
    Scalar_T Vector2<Scalar_T>::dot( const Vector2<Scalar_T>& other ) const
    {
        return m_buff[0] * other.m_buff[0] + m_buff[1] * other.m_buff[1];
    }

    template< typename Scalar_T >
    void Vector2<Scalar_T>::normalize()
    {
        auto len = length();
        m_buff[0] /= len;
        m_buff[1] /= len;
        m_buff[2] /= len;
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Vector2<Scalar_T>::normalized() const
    {
        auto len = length();
        return { m_buff[0] / len, m_buff[1] / len };
    }

    template< typename Scalar_T >
    void Vector2<Scalar_T>::scale( Scalar_T xval, Scalar_T yval )
    {
        m_buff[0] *= xval;
        m_buff[1] *= yval;
    }

    template< typename Scalar_T >
    void Vector2<Scalar_T>::scale( const Vector2<Scalar_T>& other )
    {
        m_buff[0] *= other.m_buff[0];
        m_buff[1] *= other.m_buff[1];
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Vector2<Scalar_T>::scaled( Scalar_T xval, Scalar_T yval ) const
    {
        return { m_buff[0] * xval, m_buff[1] * yval };
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Vector2<Scalar_T>::scaled( const Vector2<Scalar_T>& other ) const
    {
        return { m_buff[0] * other.m_buff[0], m_buff[1] * other.m_buff[1] };
    }

    template< typename Scalar_T >
    Scalar_T Vector2<Scalar_T>::operator[] ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 1 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T& Vector2<Scalar_T>::operator[] ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 1 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T Vector2<Scalar_T>::operator() ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 1 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T& Vector2<Scalar_T>::operator() ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 1 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Vector2<Scalar_T>::operator+ ( const Vector2<Scalar_T>& other ) const
    {
        return { m_buff[0] + other.m_buff[0],
                 m_buff[1] + other.m_buff[1] };
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Vector2<Scalar_T>::operator- ( const Vector2<Scalar_T>& other ) const
    {
        return { m_buff[0] - other.m_buff[0],
                 m_buff[1] - other.m_buff[1] };
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Vector2<Scalar_T>::operator* ( const Vector2<Scalar_T>& other ) const
    {
        return { m_buff[0] * other.m_buff[0],
                 m_buff[1] * other.m_buff[1] };
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> operator* ( const Vector2<Scalar_T>& vec, Scalar_T val )
    {
        return { vec.x() * val, vec.y() * val };
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> operator* ( Scalar_T val, const Vector2<Scalar_T>& vec )
    {
        return { vec.x() * val, vec.y() * val };
    }

    template< typename Scalar_T >
    std::string toString( const Vector2<Scalar_T>& vec )
    {
        return std::string( "[ " ) + std::to_string( vec.x() ) +
               std::string( ", " ) + std::to_string( vec.y() ) + std::string( " ]" );
    }

    //////////////////////////////////////////////////////////////////////////
    //                              Vector3                                 //
    //////////////////////////////////////////////////////////////////////////

    template< typename Scalar_T >
    Vector3<Scalar_T>::Vector3()
    {
        m_buff[0] = 0.0f;
        m_buff[1] = 0.0f;
        m_buff[2] = 0.0f;
    }

    template< typename Scalar_T >
    Vector3<Scalar_T>::Vector3( Scalar_T val )
    {
        m_buff[0] = val;
        m_buff[1] = val;
        m_buff[2] = val;
    }

    template< typename Scalar_T >
    Vector3<Scalar_T>::Vector3( Scalar_T xval, Scalar_T yval, Scalar_T zval )
    {
        m_buff[0] = xval;
        m_buff[1] = yval;
        m_buff[2] = zval;
    }

    template< typename Scalar_T >
    Vector3<Scalar_T>::Vector3( const Vector2<Scalar_T>& vec2, Scalar_T zval )
    {
        m_buff[0] = vec2.x();
        m_buff[1] = vec2.y();
        m_buff[2] = zval;
    }

    template< typename Scalar_T >
    Vector3<Scalar_T>::~Vector3()
    {
        // nothing to release manually
    }

    template< typename Scalar_T >
    Scalar_T Vector3<Scalar_T>::length() const
    {
        return std::sqrt( m_buff[0] * m_buff[0] + m_buff[1] * m_buff[1] + m_buff[2] * m_buff[2] );
    }

    template< typename Scalar_T >
    Scalar_T Vector3<Scalar_T>::dot( const Vector3<Scalar_T>& other ) const
    {
        return m_buff[0] * other.m_buff[0] + m_buff[1] * other.m_buff[1] + m_buff[2] * other.m_buff[2];
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> Vector3<Scalar_T>::cross( const Vector3<Scalar_T>& other ) const
    {
        return { m_buff[1] * other.m_buff[2] - other.m_buff[1] * m_buff[2],
                -m_buff[0] * other.m_buff[2] + other.m_buff[0] * m_buff[2],
                 m_buff[0] * other.m_buff[1] - other.m_buff[0] * m_buff[1] };
    }

    template< typename Scalar_T >
    void Vector3<Scalar_T>::normalize()
    {
        auto len = length();
        m_buff[0] /= len;
        m_buff[1] /= len;
        m_buff[2] /= len;
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> Vector3<Scalar_T>::normalized() const
    {
        auto len = length();
        return { m_buff[0] / len, m_buff[1] / len, m_buff[2] / len };
    }

    template< typename Scalar_T >
    void Vector3<Scalar_T>::scale( Scalar_T xval, Scalar_T yval, Scalar_T zval )
    {
        m_buff[0] *= xval;
        m_buff[1] *= yval;
        m_buff[2] *= zval;
    }

    template< typename Scalar_T >
    void Vector3<Scalar_T>::scale( const Vector3<Scalar_T>& other )
    {
        m_buff[0] *= other.m_buff[0];
        m_buff[1] *= other.m_buff[1];
        m_buff[2] *= other.m_buff[2];
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> Vector3<Scalar_T>::scaled( Scalar_T xval, Scalar_T yval, Scalar_T zval ) const
    {
        return { m_buff[0] * xval, m_buff[1] * yval, m_buff[2] * zval };
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> Vector3<Scalar_T>::scaled( const Vector3<Scalar_T>& other ) const
    {
        return { m_buff[0] * other.m_buff[0], m_buff[1] * other.m_buff[1], m_buff[2] * other.m_buff[2] };
    }

    template< typename Scalar_T >
    Scalar_T Vector3<Scalar_T>::operator[] ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 2 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T& Vector3<Scalar_T>::operator[] ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 2 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T Vector3<Scalar_T>::operator() ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 2 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T& Vector3<Scalar_T>::operator() ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 2 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> Vector3<Scalar_T>::operator+ ( const Vector3<Scalar_T>& other ) const
    {
        return { m_buff[0] + other.m_buff[0],
                 m_buff[1] + other.m_buff[1],
                 m_buff[2] + other.m_buff[2] };
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> Vector3<Scalar_T>::operator- ( const Vector3<Scalar_T>& other ) const
    {
        return { m_buff[0] - other.m_buff[0],
                 m_buff[1] - other.m_buff[1],
                 m_buff[2] - other.m_buff[2] };
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> Vector3<Scalar_T>::operator* ( const Vector3<Scalar_T>& other ) const
    {
        return { m_buff[0] * other.m_buff[0],
                 m_buff[1] * other.m_buff[1],
                 m_buff[2] * other.m_buff[2] };
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> operator* ( const Vector3<Scalar_T>& vec, Scalar_T val )
    {
        return { vec.x() * val, vec.y() * val, vec.z() * val };
    }

    template< typename Scalar_T >
    Vector3<Scalar_T> operator* ( Scalar_T val, const Vector3<Scalar_T>& vec )
    {
        return { vec.x() * val, vec.y() * val, vec.z() * val };
    }

    template< typename Scalar_T >
    std::string toString( const Vector3<Scalar_T>& vec )
    {
        return std::string( "[ " ) + std::to_string( vec.x() ) +
               std::string( ", " ) + std::to_string( vec.y() ) +
               std::string( ", " ) + std::to_string( vec.z() ) + std::string( " ]" );
    }

    //////////////////////////////////////////////////////////////////////////
    //                              Vector4                                 //
    //////////////////////////////////////////////////////////////////////////

    template< typename Scalar_T >
    Vector4<Scalar_T>::Vector4()
    {
        m_buff[0] = 0.0f;
        m_buff[1] = 0.0f;
        m_buff[2] = 0.0f;
        m_buff[3] = 0.0f;
    }

    template< typename Scalar_T >
    Vector4<Scalar_T>::Vector4( Scalar_T val )
    {
        m_buff[0] = val;
        m_buff[1] = val;
        m_buff[2] = val;
        m_buff[3] = val;
    }

    template< typename Scalar_T >
    Vector4<Scalar_T>::Vector4( Scalar_T xval, Scalar_T yval, Scalar_T zval, Scalar_T wval )
    {
        m_buff[0] = xval;
        m_buff[1] = yval;
        m_buff[2] = zval;
        m_buff[3] = wval;
    }

    template< typename Scalar_T >
    Vector4<Scalar_T>::Vector4( const Vector3<Scalar_T>& vec3, Scalar_T wval )
    {
        m_buff[0] = vec3.x();
        m_buff[1] = vec3.y();
        m_buff[2] = vec3.z();
        m_buff[3] = wval;
    }

    template< typename Scalar_T >
    Vector4<Scalar_T>::~Vector4()
    {
        // nothing to release manually
    }

    template< typename Scalar_T >
    Scalar_T Vector4<Scalar_T>::operator[] ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 3 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T& Vector4<Scalar_T>::operator[] ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 3 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T Vector4<Scalar_T>::operator() ( size_t indx ) const
    {
        assert( indx >= 0 );
        assert( indx <= 3 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Scalar_T& Vector4<Scalar_T>::operator() ( size_t indx )
    {
        assert( indx >= 0 );
        assert( indx <= 3 );

        return m_buff[indx];
    }

    template< typename Scalar_T >
    Vector4<Scalar_T> Vector4<Scalar_T>::operator+ ( const Vector4<Scalar_T>& other ) const
    {
        return { m_buff[0] + other.m_buff[0],
                 m_buff[1] + other.m_buff[1],
                 m_buff[2] + other.m_buff[2],
                 m_buff[3] + other.m_buff[3] };
    }

    template< typename Scalar_T >
    Vector4<Scalar_T> Vector4<Scalar_T>::operator- ( const Vector4<Scalar_T>& other ) const
    {
        return { m_buff[0] - other.m_buff[0],
                 m_buff[1] - other.m_buff[1],
                 m_buff[2] - other.m_buff[2],
                 m_buff[3] - other.m_buff[3] };
    }

    template< typename Scalar_T >
    Vector4<Scalar_T> Vector4<Scalar_T>::operator* ( const Vector4<Scalar_T>& other ) const
    {
        return { m_buff[0] * other.m_buff[0],
                 m_buff[1] * other.m_buff[1],
                 m_buff[2] * other.m_buff[2],
                 m_buff[3] * other.m_buff[3] };
    }

    template< typename Scalar_T >
    Vector4<Scalar_T> operator* ( const Vector4<Scalar_T>& vec, Scalar_T val )
    {
        return { vec.x() * val, vec.y() * val, vec.z() * val, vec.w() * val };
    }

    template< typename Scalar_T >
    Vector4<Scalar_T> operator* ( Scalar_T val, const Vector4<Scalar_T>& vec )
    {
        return { vec.x() * val, vec.y() * val, vec.z() * val, vec.w() * val };
    }

    template< typename Scalar_T >
    std::string toString( const Vector4<Scalar_T>& vec )
    {
        return std::string( "[ " ) + std::to_string( vec.x() ) +
               std::string( ", " ) + std::to_string( vec.y() ) +
               std::string( ", " ) + std::to_string( vec.z() ) +
               std::string( ", " ) + std::to_string( vec.w() ) + std::string( " ]" );
    }

}