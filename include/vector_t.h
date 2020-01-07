#pragma once

#include <common.h>

namespace tinymath
{

    /**
    *   @brief Just a simple 2-dimensional vector implementation
    *
    *   @details
    *    Defines a 2d-vector with x-y entries, accessors for these entries, 
    *    math operators to combine them, and helper methods that implement
    *    some basic operations like dot-product, etc.
    */
    template< typename Scalar_T >
    class Vector2
    {

    public :

        /**
        *   @brief Creates an empty 2d-vector with all entries initialized to zeros
        *
        *   Example:
        *   @code
        *       auto vec = tinymath::Vector2();
        *       std::cout << "vec: " << tinymath::toString( vec ) << std::endl;
        *       // result:
        *       // vec: [0.0,0.0]
        *   @endcode
        */
        Vector2();

        /**
        *   @brief Creates a 2d-vector with all entries initialized to a given value
        *
        *   @param val      Value for all entries in the vector
        */
        Vector2( Scalar_T val );

        /**
        *   @brief Creates a 2d-vector with entries initialized to x and y given values
        *
        *   @param xval     Value for x component
        *   @param yval     Value for y component
        */
        Vector2( Scalar_T xval, Scalar_T yval );

        /**
        *   @brief Releases resources used for this vector
        */
        ~Vector2();

        /** 
        *   @brief Returns the length (2-norm) of this vector 
        *
        *   @return     The euclidean norm of the 2d-vector
        */
        Scalar_T length() const;

        /**
        *   @brief Returns the dot-product with a given vector
        *
        *   @param other    Vector with whom to take the dot product
        *   @return         The result of the dot product
        */
        Scalar_T dot( const Vector2<Scalar_T>& other ) const;

        /**
        *   @brief Converts this vector to a unit vector <b>in-place</b>
        */
        void normalize();

        /**
        *   @brief Returns the unit vector associated with this vector
        *
        *   @return         The unit vector associated with this vector
        */
        Vector2<Scalar_T> normalized() const;

        /**
        *   @brief Scales this vector <b>in-place</b>, given scale values for each entry
        *
        *   @param xScale   Scale-factor for the x-entry
        *   @param yScale   Scale-factor for the y-entry
        */
        void scale( Scalar_T xScale, Scalar_T yScale );

        /**
        *   @brief Scales this vector <b>in-place</b>, given a 2d-vector with the scales of each entry
        *
        *   @param scale    2d-vector with the scale-factors for each entry
        */
        void scale( const Vector2<Scalar_T>& scale );

        /**
        *   @brief Returns a scaled version of this vector, given scale values for each entry
        *
        *   @param xScale   Scale-factor for the x-entry
        *   @param yScale   Scale-factor for the y-entry
        *   @return         The scaled version of this vector
        */
        Vector2<Scalar_T> scaled( Scalar_T xScale, Scalar_T yScale ) const;

        /**
        *   @brief Returns a scaled-version of this vector, given a 2d-vector with the scales of each entry
        *
        *   @param scale    2d-vector with the scale-factors for each entry
        *   @return         The scaled version of this vector
        */
        Vector2<Scalar_T> scaled( const Vector2<Scalar_T>& scale ) const;

        /**
        *   @brief Returns the X-component of this vector
        *
        *   @return     The value of the x-component of this vector
        */
        Scalar_T x() const { return m_buff[0]; }

        /**
        *   @brief Returns the X-component of this vector
        *
        *   @return     The value of the x-component of this vector
        */
        Scalar_T y() const { return m_buff[1]; }

        /**
        *   @brief Returns a modifiable reference to x-component of this vector
        *
        *   @return     The modifiable reference to the x-component of this vector
        */
        Scalar_T& x() { return m_buff[0]; }

        /**
        *   @brief Returns a modifiable reference to x-component of this vector
        *
        *   @return     The modifiable reference to the x-component of this vector
        */
        Scalar_T& y() { return m_buff[1]; }

        /**
        *   @brief Returns the value of the entry given by an index (0:x, 1:y)
        *
        *   @return     The value of the component given by the index
        */
        Scalar_T operator[] ( size_t indx ) const;

        /**
        *   @brief Returns a modifiable reference to an entry given by an index (0:x, 1:y)
        *
        *   @return     The modifiable reference to the component given by the index
        */
        Scalar_T& operator[] ( size_t indx );

        /**
        *   @brief Returns the value of the entry given by an index (0:x, 1:y)
        *
        *   @details
        *    This method is used for compatibility with eigen accessors, so eigen and tinymath
        *    can be swapped if required (if using the core eigen functionality)
        *
        *   @return     The value of the component given by the index
        */
        Scalar_T operator() ( size_t indx ) const;

        /**
        *   @brief Returns a modifiable reference to an entry given by an index (0:x, 1:y)
        *
        *   @details
        *    This method is used for compatibility with eigen accessors, so eigen and tinymath
        *    can be swapped if required (if using the core eigen functionality)
        *
        *   @return     The modifiable reference to the component given by the index
        */
        Scalar_T& operator() ( size_t indx );

        /**
        *   @brief Returns the vector-sum with a second vector
        *
        *   @param other    Vector used for the sum (second operand)
        *   @return         The resulting vector sum of both vectors
        */
        Vector2<Scalar_T> operator+ ( const Vector2<Scalar_T>& other ) const;

        /**
        *   @brief Returns the vector-substraction with a second vector
        *
        *   @param other    Vector used for the substraction (second operand)
        *   @return         The resulting vector-substraction of both vectors
        */
        Vector2<Scalar_T> operator- ( const Vector2<Scalar_T>& other ) const;

        /**
        *   @brief Returns the element-wise product with a second vector
        *
        *   @param other    Vector used for the product (second operand)
        *   @return         The vector resulting from the element-wise product of both vectors
        */
        Vector2<Scalar_T> operator* ( const Vector2<Scalar_T>& other ) const;

        /**
        *   @brief Returns the pointer to the internal data of the vector
        *
        *   @return     Pointer to the internal memory buffer used for both [x,y] (in that order)
        */
        Scalar_T* data() { return m_buff; }

    private :

        /* @brief Buffer of memory for the entries of the vector */
        Scalar_T m_buff[2];

    };

    /**
    *   @brief Vector-scalar product operator
    *
    *   @details
    *    Returns the vector-scalar product of a vector and a float value. This effectively
    *    scales the vector by the given value (all entries) and returns a new vector.
    *
    *   @see tinymath::Vector2::scaled
    *
    *   @return     The resulting vector-scalar product
    */
    template< typename Scalar_T >
    Vector2<Scalar_T> operator* ( const Vector2<Scalar_T>& vec, Scalar_T val );

    /**
    *   @brief Scalar-vector product operator
    *
    *   @details
    *    Essentially the same as the vector-scalar product, but with the order reversed to
    *    allow easier usage.
    *
    *   @see tinymath::Vector2::scaled
    *
    *   @return     The resulting vector-scalar product
    */
    template< typename Scalar_T >
    Vector2<Scalar_T> operator* ( Scalar_T val, const Vector2<Scalar_T>& vec );

    /**
    *   @brief Returns a string representation of a given 2d-vector
    *
    *   @param vec  Vector whose string representation we want
    *   @return     The string representation of the given vector
    */
    template< typename Scalar_T>
    std::string toString( const Vector2<Scalar_T>& vec );

    /* @brief Vector2 with float32 scalar-type */
    typedef Vector2<float> Vector2f;

    /* @brief Vector2 with float64 (double) scalar type */
    typedef Vector2<double> Vector2d;

    /**
    *   @brief Just a simple 3-dimensional vector implementation
    */
    template< typename Scalar_T >
    class Vector3
    {

    public :

        Vector3();
        Vector3( Scalar_T val );
        Vector3( Scalar_T xval, Scalar_T yval, Scalar_T zval );
        Vector3( const Vector2<Scalar_T>& vec2, Scalar_T zval );
        ~Vector3();

        Scalar_T length() const;
        Scalar_T dot( const Vector3<Scalar_T>& other ) const;
        Vector3<Scalar_T> cross( const Vector3<Scalar_T>& other ) const;
        void normalize();
        Vector3<Scalar_T> normalized() const;
        void scale( Scalar_T xval, Scalar_T yval, Scalar_T zval );
        void scale( const Vector3<Scalar_T>& other );
        Vector3<Scalar_T> scaled( Scalar_T xval, Scalar_T yval, Scalar_T zval ) const;
        Vector3<Scalar_T> scaled( const Vector3<Scalar_T>& other ) const;

        Scalar_T x() const { return m_buff[0]; }
        Scalar_T y() const { return m_buff[1]; }
        Scalar_T z() const { return m_buff[2]; }

        Scalar_T& x() { return m_buff[0]; }
        Scalar_T& y() { return m_buff[1]; }
        Scalar_T& z() { return m_buff[2]; }

        void setX( Scalar_T xval ) { m_buff[0] = xval; }
        void setY( Scalar_T yval ) { m_buff[1] = yval; }
        void setZ( Scalar_T zval ) { m_buff[2] = zval; }

        Scalar_T getX() const { return m_buff[0]; }
        Scalar_T getY() const { return m_buff[1]; }
        Scalar_T getZ() const { return m_buff[2]; }

        Scalar_T operator[] ( size_t indx ) const;
        Scalar_T& operator[] ( size_t indx );

        Scalar_T operator() ( size_t indx ) const;
        Scalar_T& operator() ( size_t indx );

        Vector3<Scalar_T> operator+ ( const Vector3<Scalar_T>& other ) const;
        Vector3<Scalar_T> operator- ( const Vector3<Scalar_T>& other ) const;
        Vector3<Scalar_T> operator* ( const Vector3<Scalar_T>& other ) const;

        Scalar_T* data() { return m_buff; }
    private :

        Scalar_T m_buff[3];

    };

    template< typename Scalar_T >
    Vector3<Scalar_T> operator* ( const Vector3<Scalar_T>& vec, Scalar_T val );

    template< typename Scalar_T >
    Vector3<Scalar_T> operator* ( Scalar_T val, const Vector3<Scalar_T>& vec );

    template< typename Scalar_T >
    std::string toString( const Vector3<Scalar_T>& vec );

    /* @brief Vector3 with float32 scalar-type */
    typedef Vector3<float> Vector3f;

    /* @brief Vector3 with float64 (double) scalar type */
    typedef Vector3<double> Vector3d;

    /**
    *   @brief Just a simple 4-dimensional vector implementation
    */
    template< typename Scalar_T >
    class Vector4
    {

    public :

        Vector4();
        Vector4( Scalar_T val );
        Vector4( Scalar_T xval, Scalar_T yval, Scalar_T zval, Scalar_T wval );
        Vector4( const Vector3<Scalar_T>& vec3, Scalar_T wval );
        ~Vector4();

        Scalar_T x() const { return m_buff[0]; }
        Scalar_T y() const { return m_buff[1]; }
        Scalar_T z() const { return m_buff[2]; }
        Scalar_T w() const { return m_buff[3]; }

        Scalar_T& x() { return m_buff[0]; }
        Scalar_T& y() { return m_buff[1]; }
        Scalar_T& z() { return m_buff[2]; }
        Scalar_T& w() { return m_buff[3]; }

        void setX( Scalar_T xval ) { m_buff[0] = xval; }
        void setY( Scalar_T yval ) { m_buff[1] = yval; }
        void setZ( Scalar_T zval ) { m_buff[2] = zval; }
        void setW( Scalar_T wval ) { m_buff[3] = wval; }

        Scalar_T getX() const { return m_buff[0]; }
        Scalar_T getY() const { return m_buff[1]; }
        Scalar_T getZ() const { return m_buff[2]; }
        Scalar_T getW() const { return m_buff[3]; }

        Scalar_T operator[] ( size_t indx ) const;
        Scalar_T& operator[] ( size_t indx );

        Scalar_T operator() ( size_t indx ) const;
        Scalar_T& operator() ( size_t indx );

        Vector4<Scalar_T> operator+ ( const Vector4<Scalar_T>& other ) const;
        Vector4<Scalar_T> operator- ( const Vector4<Scalar_T>& other ) const;
        Vector4<Scalar_T> operator* ( const Vector4<Scalar_T>& other ) const;

        Scalar_T* data() { return m_buff; }
    private :

        Scalar_T m_buff[4];

    };

    template< typename Scalar_T >
    Vector4<Scalar_T> operator* ( const Vector4<Scalar_T>& vec, Scalar_T val );

    template< typename Scalar_T >
    Vector4<Scalar_T> operator* ( Scalar_T val, const Vector4<Scalar_T>& vec );

    template< typename Scalar_T >
    std::string toString( const Vector4<Scalar_T>& vec );

    /* @brief Vector4 with float32 scalar-type */
    typedef Vector4<float> Vector4f;

    /* @brief Vector4 with float64 (double) scalar type */
    typedef Vector4<double> Vector4d;
}

#include "../src/vector_t_impl.hpp"