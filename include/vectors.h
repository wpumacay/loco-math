#pragma once

#include <common.h>

namespace tinymath
{

    //////////////////////////////////////////////////////////////////////////
    //                              Vector2                                 //
    //////////////////////////////////////////////////////////////////////////

    class Vector2
    {

    public :

        Vector2();
        Vector2( tfloat val );
        Vector2( tfloat xval, tfloat yval );
        ~Vector2();

        tfloat x() const { return m_buff[0]; }
        tfloat y() const { return m_buff[1]; }

        tfloat& x() { return m_buff[0]; }
        tfloat& y() { return m_buff[1]; }

        tfloat operator[] ( size_t indx ) const;
        tfloat& operator[] ( size_t indx );

        void setX( tfloat xval ) { m_buff[0] = xval; }
        void setY( tfloat xval ) { m_buff[1] = yval; }
        void setZ( tfloat xval ) { m_buff[2] = zval; }

        tfloat getX() const { return m_buff[0]; }
        tfloat getY() const { return m_buff[1]; }
        tfloat getZ() const { return m_buff[2]; }

        std::string toString( const Vector2& vec ) const;

        tfloat* ptr() { return m_buff; }

    private :

        tfloat m_buff[3];

    };

    //// Vector2 operator+ ( const Vector2& v1, const Vector2& v2 );
    //// Vector2 operator- ( const Vector2& v1, const Vector2& v2 );
    //// Vector2 operator* ( const Vector2& v1, const Vector2& v2 );

    //////////////////////////////////////////////////////////////////////////
    //                              Vector3                                 //
    //////////////////////////////////////////////////////////////////////////

    class Vector3
    {

    public :

        Vector3();
        Vector3( tfloat val );
        Vector3( tfloat x, tfloat y, tfloat z );
        ~Vector3();

        tfloat x() const { return m_buff[0]; }
        tfloat y() const { return m_buff[1]; }
        tfloat z() const { return m_buff[2]; }

        tfloat& x() { return m_buff[0]; }
        tfloat& y() { return m_buff[1]; }
        tfloat& z() { return m_buff[2]; }

        tfloat operator[] ( size_t indx ) const;
        tfloat& operator[] ( size_t indx );

        std::string toString( const Vector3& vec ) const;

    private :

        tfloat m_buff[3];

    };

}