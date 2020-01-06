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

        void setX( tfloat xval ) { m_buff[0] = xval; }
        void setY( tfloat yval ) { m_buff[1] = yval; }

        tfloat getX() const { return m_buff[0]; }
        tfloat getY() const { return m_buff[1]; }

        tfloat operator[] ( size_t indx ) const;
        tfloat& operator[] ( size_t indx );

        Vector2 operator+ ( const Vector2& other ) const;
        Vector2 operator- ( const Vector2& other ) const;
        Vector2 operator* ( const Vector2& other ) const;

        tfloat* ptr() { return m_buff; }

    private :

        tfloat m_buff[2];

    };

    Vector2 operator* ( const Vector2& vec, float val );
    Vector2 operator* ( float val, const Vector2& vec );

    std::string toString( const Vector2& vec );

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

        void setX( tfloat xval ) { m_buff[0] = xval; }
        void setY( tfloat yval ) { m_buff[1] = yval; }
        void setZ( tfloat zval ) { m_buff[2] = zval; }

        tfloat getX() const { return m_buff[0]; }
        tfloat getY() const { return m_buff[1]; }
        tfloat getZ() const { return m_buff[2]; }

        tfloat operator[] ( size_t indx ) const;
        tfloat& operator[] ( size_t indx );

        Vector3 operator+ ( const Vector3& other ) const;
        Vector3 operator- ( const Vector3& other ) const;
        Vector3 operator* ( const Vector3& other ) const;

        tfloat* ptr() { return m_buff; }
    private :

        tfloat m_buff[3];

    };

    Vector3 operator* ( const Vector3& vec, float val );
    Vector3 operator* ( float val, const Vector3& vec );

    std::string toString( const Vector3& vec );

    //////////////////////////////////////////////////////////////////////////
    //                              Vector4                                 //
    //////////////////////////////////////////////////////////////////////////

    class Vector4
    {

    public :

        Vector4();
        Vector4( tfloat val );
        Vector4( tfloat x, tfloat y, tfloat z, tfloat w );
        ~Vector4();

        tfloat x() const { return m_buff[0]; }
        tfloat y() const { return m_buff[1]; }
        tfloat z() const { return m_buff[2]; }
        tfloat w() const { return m_buff[3]; }

        tfloat& x() { return m_buff[0]; }
        tfloat& y() { return m_buff[1]; }
        tfloat& z() { return m_buff[2]; }
        tfloat& w() { return m_buff[3]; }

        void setX( tfloat xval ) { m_buff[0] = xval; }
        void setY( tfloat yval ) { m_buff[1] = yval; }
        void setZ( tfloat zval ) { m_buff[2] = zval; }
        void setW( tfloat wval ) { m_buff[3] = wval; }

        tfloat getX() const { return m_buff[0]; }
        tfloat getY() const { return m_buff[1]; }
        tfloat getZ() const { return m_buff[2]; }
        tfloat getW() const { return m_buff[3]; }

        tfloat operator[] ( size_t indx ) const;
        tfloat& operator[] ( size_t indx );

        Vector4 operator+ ( const Vector4& other ) const;
        Vector4 operator- ( const Vector4& other ) const;
        Vector4 operator* ( const Vector4& other ) const;

        tfloat* ptr() { return m_buff; }
    private :

        tfloat m_buff[4];

    };

    Vector4 operator* ( const Vector4& vec, float val );
    Vector4 operator* ( float val, const Vector4& vec );

    std::string toString( const Vector4& vec );

}