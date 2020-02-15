#pragma once

#include <common.h>

namespace tinymath
{

    /**
    *   @brief Just a simple N-dimensional vector implementation
    *
    *   @details
    *    Defines an n-dim vector with x-y entries, accessors for these entries, 
    *    math operators to combine them, and helper methods that implement
    *    some basic operations like dot-product, etc.
    *
    *   @tparam Scalar_T    Type used for the values stored in the vector (float|double)
    *   @tparam SizeN       Dimensionality of the vector
    */
    template< typename Scalar_T, size_t SizeN >
    class Vector
    {

    public :

        /**
        *   @brief Creates an empty n-dim vector with all entries initialized to zeros
        *
        *   Example:
        *   @code
        *       auto vec = tinymath::Vector<float, 2>();
        *       std::cout << "vec: " << tinymath::toString( vec ) << std::endl;
        *   @endcode
        *
        *   Output:
        *   ```
        *   vec: [0.0, 0.0]
        *   ```
        */
        Vector();

        /**
        *   @brief Creates an n-dim vector with all entries initialized to a given value
        *
        *   @param val      Value for all entries in the vector
        *
        *   Example:
        *   @code
        *       auto vec = tinymath::Vector<float, 3>( 1.0f );
        *       std::cout << "vec: " << tinymath::toString( vec ) << std::endl;
        *   @endcode
        *
        *   Output:
        *   ```
        *   vec: [1.0, 1.0, 1.0]
        *   ```
        */
        Vector( tfloat val );

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        // @hacks: custom constructors for special 2d, 3d and 4d cases (avoid for-loops)

        /**
        *   @brief Tries to create an n-dim vector with the given entries
        *
        *   @param x    x-component of the n-dim vector
        *   @param y    y-component (if applicable) of the n-dim vector
        */
        Vector( tfloat x, tfloat y );

        /**
        *   @brief Tries to create an n-dim vector with the given entries
        *
        *   @param x    x-component of the n-dim vector
        *   @param y    y-component of the n-dim vector
        *   @param z    z-component (if applicable) of the n-dim vector
        */
        Vector( tfloat x, tfloat y, tfloat z );

        /**
        *   @brief Tries to create an n-dim vector with the given entries
        *
        *   @param x    x-component of the n-dim vector
        *   @param y    y-component of the n-dim vector
        *   @param z    z-component (if applicable) of the n-dim vector
        *   @param w    w-component (if applicable) of the n-dim vector
        */
        Vector( tfloat x, tfloat y, tfloat z, tfloat w );
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

        /**
        *   @brief Creates an n-dim vector from a list of given values
        *
        *   @param values   Initializer list with the values for the vector
        *
        *   Example:
        *   @code
        *       tinymath::Vector<float, 3> vec = { 1.0f, 2.0f, 3.0f };
        *       std::cout << "vec: " << tinymath::toString( vec ) << std::endl;
        *   @endcode
        *
        *   Output:
        *   ```
        *   vec: [1.0, 2.0, 3.0]
        *   ```
        */
        Vector( std::initializer_list<Scalar_T> values );

        /**
        *   @brief Creates an n-dim vector from a std::vector of given values
        *
        *   @param values   std::vector with the values for the vector
        *
        *   Example:
        *   @code
        *       std::vector<float> vec_values = { 1.0f, 2.0f, 3.0f };
        *       auto vec = tinymath::Vector<float, 3>( vec_values );
        *       std::cout << "vec: " << tinymath::toString( vec ) << std::endl;
        *   @endcode
        *
        *   Output:
        *   ```
        *   vec: [1.0, 2.0, 3.0]
        *   ```
        */
        Vector( const std::vector<Scalar_T>& values );

        /**
        *   @brief Creates an n-dim vector from an (n+1)-dim vector
        *
        *   @param vec  (n+1) dimensional vector whose first n components we want
        *
        *   Example:
        *   @code
        *       tinymath::Vector<float, 4> vec4 = { 4.0f, 3.0f, 2.0f, 1.0f };
        *       auto vec3 = tinymath::Vector<float, 3>( vec4 );
        *       std::cout << "vec4: " << tinymath::toString( vec4 ) << std::endl;
        *       std::cout << "vec3: " << tinymath::toString( vec3 ) << std::endl;
        *   @endcode
        */
        Vector( const Vector<Scalar_T,SizeN+1>& vec );

        /**
        *   @brief Creates an n-dim vector from an (n-1) dim vector and a given value for the last component
        *
        *   @param vec  (n-1) dimensional vector with the first (n-1) components we want
        *   @param last Value of the last component of the vector
        *
        *   Example:
        *   @code
        *
        *   @endcode
        */
        Vector( const Vector<Scalar_T,SizeN-1>& vec, tfloat last );

        /**
        *   @brief Releases resources used for this vector
        */
        ~Vector();

        /** 
        *   @brief Returns the length (2-norm) of this vector 
        *
        *   @return     The euclidean norm of the n-dim vector
        */
        Scalar_T length() const;

        /**
        *   @brief Returns the dot-product with a given vector
        *
        *   @param other    Vector with whom to take the dot product
        *   @return         The result of the dot product
        */
        Scalar_T dot( const Vector<Scalar_T,SizeN>& other ) const;

        /**
        *   @brief Converts this vector to a unit vector <b>in-place</b>
        */
        void normalize();

        /**
        *   @brief Returns the unit vector associated with this vector
        *
        *   @return         The unit vector associated with this vector
        */
        Vector<Scalar_T,SizeN> normalized() const;

        /**
        *   @brief Scales this vector <b>in-place</b>, given a scale value applied to each entry
        *
        *   @param val    Scale factor applied to each entry
        */
        void scale( tfloat val );

        /**
        *   @brief Scales this vector <b>in-place</b>, given an n-dim vector with the scales of each entry
        *
        *   @param scale    n-dim vector with the scale-factors for each entry
        */
        void scale( const Vector<Scalar_T,SizeN>& scale );

        /**
        *   @brief Returns a scaled-version of this vector, given a scale value applied to each entry
        *
        *   @param val      Scale factor applied to each entry
        *   @return         The scaled version of this vector
        */
        Vector<Scalar_T,SizeN> scaled( tfloat val ) const;

        /**
        *   @brief Returns a scaled-version of this vector, given an n-dim vector with the scales of each entry
        *
        *   @param scale    n-dim vector with the scale-factors for each entry
        *   @return         The scaled version of this vector
        */
        Vector<Scalar_T,SizeN> scaled( const Vector<Scalar_T,SizeN>& scale ) const;

        /**
        *   @brief Returns the x-component of this vector
        *
        *   @return     The value of the x-component of this vector
        */
        Scalar_T x() const;

        /**
        *   @brief Returns the y-component of this vector
        *
        *   @return     The value of the y-component of this vector
        */
        Scalar_T y() const;

        /**
        *   @brief Returns the z-component of this vector
        *
        *   @return     The value of the z-component of this vector
        */
        Scalar_T z() const;


        /**
        *   @brief Returns the w-component of this vector
        *
        *   @return     The value of the w-component of this vector
        */
        Scalar_T w() const;

        /**
        *   @brief Returns a modifiable reference to x-component of this vector
        *
        *   @return     The modifiable reference to the x-component of this vector
        */
        Scalar_T& x();

        /**
        *   @brief Returns a modifiable reference to y-component of this vector
        *
        *   @return     The modifiable reference to the y-component of this vector
        */
        Scalar_T& y();

        /**
        *   @brief Returns a modifiable reference to z-component of this vector
        *
        *   @return     The modifiable reference to the z-component of this vector
        */
        Scalar_T& z();

        /**
        *   @brief Returns a modifiable reference to w-component of this vector
        *
        *   @return     The modifiable reference to the w-component of this vector
        */
        Scalar_T& w();

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
        Vector<Scalar_T,SizeN> operator+ ( const Vector<Scalar_T,SizeN>& other ) const;

        /**
        *   @brief Returns the vector-subtraction with a second vector
        *
        *   @param other    Vector used for the subtraction (second operand)
        *   @return         The resulting vector-subtraction of both vectors
        */
        Vector<Scalar_T,SizeN> operator- ( const Vector<Scalar_T,SizeN>& other ) const;

        /**
        *   @brief Returns the elementwise product with a second vector
        *
        *   @param other    Vector used for the product (second operand)
        *   @return         The vector resulting from the elementwise product of both vectors
        */
        Vector<Scalar_T,SizeN> operator* ( const Vector<Scalar_T,SizeN>& other ) const;

        /**
        *   @brief Returns a mutable reference to the internal data of the vector
        *
        *   @return     Pointer to the internal memory buffer used for the elements (in order)
        */
        Scalar_T* data() { return m_buff; }

        /**
        *   @brief Returns a const-reference to the internal data of the vector
        *
        *   @return     Const-Pointer to the internal memory buffer used for the elements (in order)
        */
        const Scalar_T* data() const { return m_buff; }

    private :

        /** @brief Buffer of memory for the entries of the vector */
        Scalar_T m_buff[SizeN];

    };

    /**
    *   @brief Vector-scalar product operator
    *
    *   @details
    *    Returns the vector-scalar product of a vector and a float value. This effectively
    *    scales the vector by the given value (all entries) and returns a new vector.
    *
    *   @see tinymath::Vector::scaled
    *
    *   @param vec  Vector operand to be scaled
    *   @param val  Scalar factor applied to each element
    *   @return     The resulting vector-scalar product
    */
    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> operator* ( const Vector<Scalar_T,SizeN>& vec, tfloat val );

    /**
    *   @brief Scalar-vector product operator
    *
    *   @details
    *    Essentially the same as the vector-scalar product, but with the order reversed to
    *    allow easier usage.
    *
    *   @see tinymath::Vector::scaled
    *
    *   @param val  Scalar factor applied to each element
    *   @param vec  Vector operand to be scaled
    *   @return     The resulting vector-scalar product
    */
    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> operator* ( tfloat val, const Vector<Scalar_T,SizeN>& vec );

    /**
    *   @brief Returns the negative of the given vector
    *
    *   @param vec  Vector whose negative we want
    *   @return     The resulting negative of the vector
    */
    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> operator- ( const Vector<Scalar_T,SizeN>& vec );

    /**
    *   @brief Returns whether or not both given vector are "equal" (distance close at most by eps=1e-6)
    *
    *   @param v1   First vector operand for the comparison
    *   @param v2   Second vector operatod for the comparison
    *   @return     True if both vector are close up to eps=1e-6, False otherwise
    */
    template< typename Scalar_T, size_t SizeN >
    bool operator== ( const Vector<Scalar_T,SizeN>& v1, const Vector<Scalar_T,SizeN>& v2 );

    /**
    *   @brief Returns whether or not both given vector are "different" (distance apart at least by eps=1e-6)
    *
    *   @param v1   First vector operand for the comparison
    *   @param v2   Second vector operatod for the comparison
    *   @return     True if both vector are apart at least by eps=1e-6, False otherwise
    */
    template< typename Scalar_T, size_t SizeN >
    bool operator!= ( const Vector<Scalar_T,SizeN>& v1, const Vector<Scalar_T,SizeN>& v2 );

    /**
    *   @brief Returns a string representation of a given n-dim vector
    *
    *   @param vec  Vector whose string representation we want
    *   @return     The string representation of the given vector
    */
    template< typename Scalar_T, size_t SizeN >
    std::string toString( const Vector<Scalar_T,SizeN>& vec );

    /**
    *   @brief Checks if all vector elements are close up to a certain margin
    *
    *   @param vec1     First vector operand to compare
    *   @param vec2     Second vector operand to compare
    *   @param margin   Margin for comparison of the elements
    *   @return         Whether or not the vectors have all elements close
    */
    template< typename Scalar_T, size_t SizeN >
    bool allclose( const Vector<Scalar_T,SizeN>& vec1, const Vector<Scalar_T,SizeN>& vec2, Scalar_T tolerance = TINYMATH_EPS );

    /* @brief Vector2 with float32 scalar-type */
    typedef Vector<float, 2> Vector2f;
    /* @brief Vector2 with float64 (double) scalar type */
    typedef Vector<double, 2> Vector2d;

    /* @brief Vector3 with float32 scalar-type */
    typedef Vector<float, 3> Vector3f;
    /* @brief Vector3 with float64 (double) scalar type */
    typedef Vector<double, 3> Vector3d;

    /* @brief Vector4 with float32 scalar-type */
    typedef Vector<float, 4> Vector4f;
    /* @brief Vector4 with float64 (double) scalar type */
    typedef Vector<double, 4> Vector4d;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

    /**********************************************************************************************/
    /*                                    Custom functions                                        */
    /**********************************************************************************************/

    // Specializations for custom constructors (float32)
    template<>
    Vector<float, 2>::Vector( tfloat x, tfloat y );
    template<>
    Vector<float, 3>::Vector( tfloat x, tfloat y, tfloat z );
    template<>
    Vector<float, 4>::Vector( tfloat x, tfloat y, tfloat z, tfloat w );

    // Specializations for custom constructors (float64)
    template<>
    Vector<double, 2>::Vector( tfloat x, tfloat y );
    template<>
    Vector<double, 3>::Vector( tfloat x, tfloat y, tfloat z );
    template<>
    Vector<double, 4>::Vector( tfloat x, tfloat y, tfloat z, tfloat w );

    // Template-specializations of value-getters for x,y,z,w

    template<>
    float Vector<float, 2>::x() const;
    template<>
    float Vector<float, 2>::y() const;
    template<>
    float Vector<float, 3>::x() const;
    template<>
    float Vector<float, 3>::y() const;
    template<>
    float Vector<float, 3>::z() const;
    template<>
    float Vector<float, 4>::x() const;
    template<>
    float Vector<float, 4>::y() const;
    template<>
    float Vector<float, 4>::z() const;
    template<>
    float Vector<float, 4>::w() const;

    template<>
    double Vector<double, 2>::x() const;
    template<>
    double Vector<double, 2>::y() const;
    template<>
    double Vector<double, 3>::x() const;
    template<>
    double Vector<double, 3>::y() const;
    template<>
    double Vector<double, 3>::z() const;
    template<>
    double Vector<double, 4>::x() const;
    template<>
    double Vector<double, 4>::y() const;
    template<>
    double Vector<double, 4>::z() const;
    template<>
    double Vector<double, 4>::w() const;

    // Template-specializations of reference-getters for x,y,z,w

    template<>
    float& Vector<float, 2>::x();
    template<>
    float& Vector<float, 2>::y();
    template<>
    float& Vector<float, 3>::x();
    template<>
    float& Vector<float, 3>::y();
    template<>
    float& Vector<float, 3>::z();
    template<>
    float& Vector<float, 4>::x();
    template<>
    float& Vector<float, 4>::y();
    template<>
    float& Vector<float, 4>::z();
    template<>
    float& Vector<float, 4>::w();

    template<>
    double& Vector<double, 2>::x();
    template<>
    double& Vector<double, 2>::y();
    template<>
    double& Vector<double, 3>::x();
    template<>
    double& Vector<double, 3>::y();
    template<>
    double& Vector<double, 3>::z();
    template<>
    double& Vector<double, 4>::x();
    template<>
    double& Vector<double, 4>::y();
    template<>
    double& Vector<double, 4>::z();
    template<>
    double& Vector<double, 4>::w();

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
}

#include "../src/vector_t_impl.hpp"