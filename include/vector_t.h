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
        Vector2( tfloat val );

        /**
        *   @brief Creates a 2d-vector with entries initialized to x and y given values
        *
        *   @param xval     Value for x component
        *   @param yval     Value for y component
        */
        Vector2( tfloat xval, tfloat yval );

        /**
        *   @brief Releases resources used for this vector
        */
        ~Vector2();

        /** 
        *   @brief Returns the length (2-norm) of this vector 
        *
        *   @return     The euclidean norm of the 2d-vector
        */
        tfloat length() const;

        /**
        *   @brief Returns the dot-product with a given vector
        *
        *   @param other    Vector with whom to take the dot product
        *   @return         The result of the dot product
        */
        tfloat dot( const Vector2& other ) const;

        /**
        *   @brief Converts this vector to a unit vector <b>in-place</b>
        */
        void normalize();

        /**
        *   @brief Returns the unit vector associated with this vector
        *
        *   @return         The unit vector associated with this vector
        */
        Vector2 normalized() const;

        /**
        *   @brief Scales this vector <b>in-place</b>, given scale values for each entry
        *
        *   @param xScale   Scale-factor for the x-entry
        *   @param yScale   Scale-factor for the y-entry
        */
        void scale( tfloat xScale, tfloat yScale );

        /**
        *   @brief Scales this vector <b>in-place</b>, given a 2d-vector with the scales of each entry
        *
        *   @param scale    2d-vector with the scale-factors for each entry
        */
        void scale( const Vector2& scale );

        /**
        *   @brief Returns a scaled version of this vector, given scale values for each entry
        *
        *   @param xScale   Scale-factor for the x-entry
        *   @param yScale   Scale-factor for the y-entry
        *   @return         The scaled version of this vector
        */
        Vector2 scaled( tfloat xScale, tfloat yScale ) const;

        /**
        *   @brief Returns a scaled-version of this vector, given a 2d-vector with the scales of each entry
        *
        *   @param scale    2d-vector with the scale-factors for each entry
        *   @return         The scaled version of this vector
        */
        Vector2 scaled( const Vector2& scale ) const;

        /**
        *   @brief Returns the X-component of this vector
        *
        *   @return     The value of the x-component of this vector
        */
        tfloat x() const { return m_buff[0]; }

        /**
        *   @brief Returns the X-component of this vector
        *
        *   @return     The value of the x-component of this vector
        */
        tfloat y() const { return m_buff[1]; }

        /**
        *   @brief Returns a modifiable reference to x-component of this vector
        *
        *   @return     The modifiable reference to the x-component of this vector
        */
        tfloat& x() { return m_buff[0]; }

        /**
        *   @brief Returns a modifiable reference to x-component of this vector
        *
        *   @return     The modifiable reference to the x-component of this vector
        */
        tfloat& y() { return m_buff[1]; }

        /**
        *   @brief Returns the value of the entry given by an index (0:x, 1:y)
        *
        *   @return     The value of the component given by the index
        */
        tfloat operator[] ( size_t indx ) const;

        /**
        *   @brief Returns a modifiable reference to an entry given by an index (0:x, 1:y)
        *
        *   @return     The modifiable reference to the component given by the index
        */
        tfloat& operator[] ( size_t indx );

        /**
        *   @brief Returns the value of the entry given by an index (0:x, 1:y)
        *
        *   @details
        *    This method is used for compatibility with eigen accessors, so eigen and tinymath
        *    can be swapped if required (if using the core eigen functionality)
        *
        *   @return     The value of the component given by the index
        */
        tfloat operator() ( size_t indx ) const;

        /**
        *   @brief Returns a modifiable reference to an entry given by an index (0:x, 1:y)
        *
        *   @details
        *    This method is used for compatibility with eigen accessors, so eigen and tinymath
        *    can be swapped if required (if using the core eigen functionality)
        *
        *   @return     The modifiable reference to the component given by the index
        */
        tfloat& operator() ( size_t indx );

        /**
        *   @brief Returns the vector-sum with a second vector
        *
        *   @param other    Vector used for the sum (second operand)
        *   @return         The resulting vector sum of both vectors
        */
        Vector2 operator+ ( const Vector2& other ) const;

        /**
        *   @brief Returns the vector-substraction with a second vector
        *
        *   @param other    Vector used for the substraction (second operand)
        *   @return         The resulting vector-substraction of both vectors
        */
        Vector2 operator- ( const Vector2& other ) const;

        /**
        *   @brief Returns the element-wise product with a second vector
        *
        *   @param other    Vector used for the product (second operand)
        *   @return         The vector resulting from the element-wise product of both vectors
        */
        Vector2 operator* ( const Vector2& other ) const;

        /**
        *   @brief Returns the pointer to the internal data of the vector
        *
        *   @return     Pointer to the internal memory buffer used for both [x,y] (in that order)
        */
        tfloat* data() { return m_buff; }

    private :

        /* @brief Buffer of memory for the entries of the vector */
        tfloat m_buff[2];

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
    Vector2 operator* ( const Vector2& vec, float val );

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
    Vector2 operator* ( float val, const Vector2& vec );

    /**
    *   @brief Returns a string representation of a given 2d-vector
    *
    *   @param vec  Vector whose string representation we want
    *   @return     The string representation of the given vector
    */
    std::string toString( const Vector2& vec );

    /**
    *   @brief Just a simple 3-dimensional vector implementation
    */
    class Vector3
    {

    public :

        Vector3();
        Vector3( tfloat val );
        Vector3( tfloat xval, tfloat yval, tfloat zval );
        Vector3( const Vector2& vec2, tfloat zval );
        ~Vector3();

        tfloat length() const;
        tfloat dot( const Vector3& other ) const;
        Vector3 cross( const Vector3& other ) const;
        void normalize();
        Vector3 normalized() const;
        void scale( tfloat xval, tfloat yval, tfloat zval );
        void scale( const Vector3& other );
        Vector3 scaled( tfloat xval, tfloat yval, tfloat zval ) const;
        Vector3 scaled( const Vector3& other ) const;

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

        tfloat operator() ( size_t indx ) const;
        tfloat& operator() ( size_t indx );

        Vector3 operator+ ( const Vector3& other ) const;
        Vector3 operator- ( const Vector3& other ) const;
        Vector3 operator* ( const Vector3& other ) const;

        tfloat* data() { return m_buff; }
    private :

        tfloat m_buff[3];

    };

    Vector3 operator* ( const Vector3& vec, float val );
    Vector3 operator* ( float val, const Vector3& vec );

    std::string toString( const Vector3& vec );


    /**
    *   @brief Just a simple 4-dimensional vector implementation
    */
    class Vector4
    {

    public :

        Vector4();
        Vector4( tfloat val );
        Vector4( tfloat xval, tfloat yval, tfloat zval, tfloat wval );
        Vector4( const Vector3& vec3, tfloat wval );
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

        tfloat operator() ( size_t indx ) const;
        tfloat& operator() ( size_t indx );

        Vector4 operator+ ( const Vector4& other ) const;
        Vector4 operator- ( const Vector4& other ) const;
        Vector4 operator* ( const Vector4& other ) const;

        tfloat* data() { return m_buff; }
    private :

        tfloat m_buff[4];

    };

    Vector4 operator* ( const Vector4& vec, float val );
    Vector4 operator* ( float val, const Vector4& vec );

    std::string toString( const Vector4& vec );

}