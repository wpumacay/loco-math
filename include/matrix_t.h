#pragma once

#include <common.h>
#include <vector_t.h>

namespace tinymath
{

    /**
    *   @brief Matrix of 2x2 shape, stored in column major format
    */
    template< typename Scalar_T >
    class Matrix2
    {

    public :

        /**
        *   @brief Creates a 2x2 matrix initialized to an Identity matrix
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix2<float>();
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       // result:
        *       //  [ 1.0, 0.0
        *       //    0.0, 1.0 ]
        *   @endcode
        */
        Matrix2();

        /**
        *   @brief Creates a 2x2 matrix initialized with given elements
        *
        *   @param m00  Element at index (0,0) in the matrix
        *   @param m01  Element at index (0,1) in the matrix
        *   @param m10  Element at index (1,0) in the matrix
        *   @param m11  Element at index (1,1) in the matrix
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix2<float>( 1.0, 2.0
        *                                            3.0, 4.0 );
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       // result:
        *       //  [ 1.0, 2.0
        *       //    3.0, 4.0 ]
        *   @endcode
        */
        Matrix2( Scalar_T m00, Scalar_T m01,
                 Scalar_T m10, Scalar_T m11 );

        /**
        *   @brief Creates a 2x2 matrix initialized with given columns
        *
        *   @param col1 First column of the matrix
        *   @param col2 Second column of the matrix
        *
        *   Example:
        *   @code
        *       auto col1 = tinymath::Vector2<float>( 1.0, 3.0 );
        *       auto col2 = tinymath::Vector2<float>( 2.0, 4.0 );
        *       auto mat = tinymath::Matrix2<float>( col1, col2 );
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       // result:
        *       //  [ 1.0, 2.0
        *       //    3.0, 4.0 ]
        *   @endcode
        */
        Matrix2( const Vector2<Scalar_T>& col1, const Vector2<Scalar_T>& col2 );

        /**
        *   @brief Releases resources used for this matrix
        */
        ~Matrix2();

        /**
        *   @brief Returns the value at stored at requested index (row,col)
        *
        *   @param row  Requested row index
        *   @param col  Requested column index
        *   @return     Value stored at (row,col) index
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix2<float>( 1.0, 2.0,
        *                                            3.0, 4.0 );
        *       std::cout << "mat(0,0): " << std::to_string( mat(0,0) ) << std::endl;
        *       std::cout << "mat(0,1): " << std::to_string( mat(0,1) ) << std::endl;
        *       std::cout << "mat(1,0): " << std::to_string( mat(1,0) ) << std::endl;
        *       std::cout << "mat(1,1): " << std::to_string( mat(1,1) ) << std::endl;
        *       // result:
        *       // mat(0,0): 1.0
        *       // mat(0,1): 2.0
        *       // mat(1,0): 3.0
        *       // mat(1,1): 4.0
        *   @endcode
        */
        Scalar_T operator() ( size_t row, size_t col ) const;

        /**
        *   @brief Returns a modifiable reference to the value stored at index (row,col)
        *
        *   @param row  Requested row index
        *   @param col  Requested column index
        *   @return      Modifiable reference to the value at index (row,col)
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix2<float>( 1.0, 2.0,
        *                                            3.0, 4.0 );
        *       std::cout << "matrix (1):" << std::endl;
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       mat(0,0) = -1.0f;
        *       mat(1,0) += 1.0f;
        *       mat(0,1) -= 1.0f;
        *       mat(1,1) *= 2.0f;
        *       std::cout << "matrix (2):" << std::endl;
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       // result:
        *       // matrix (1):
        *       // [ 1.0, 2.0
        *       //   3.0, 4.0 ]
        *       // matrix (2):
        *       // [ -1.0, 1.0
        *       //    4.0, 8.0 ]
        *   @endcode
        */
        Scalar_T& operator() ( size_t row, size_t col );

    private :

        Scalar_T m_buff[4];
    };

    /**
    *   @brief Returns a string representation of the given 2x2 matrix
    *
    *   @param mat  Matrix whose string representation we want
    *   @return     The string representation of the given matrix
    */
    template< typename Scalar_T >
    std::string toString( const Matrix2<Scalar_T>& mat );

    /* @brief Matrix2 with float32 scalar-type */
    typedef Matrix2<float> Matrix2f;

    /* @brief Matrix2 with float64 (double) scalar type */
    typedef Matrix2<double> Matrix2d;

    template< typename Scalar_T >
    class Matrix3
    {

    public :


    private :

        Scalar_T m_buff[9];

    };


    template< typename Scalar_T >
    class Matrix4
    {

    public :

    private :

        Scalar_T m_buff[16];
    };

}

#include "../src/matrix_t_impl.hpp"