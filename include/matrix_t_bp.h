#pragma once

#include <common.h>
#include <vector_t.h>

namespace tinymath
{

    /**
    *   @brief Matrix of 2x2 shape, stored in column major format
    */
    template< typename Scalar_T, size_t SizeN >
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
        *   @brief Sets the components of the matrix to the Identity matrix of dimensions (2x2)
        */
        void setIdentity();

        /**
        *   @brief Returns the transpose of this matrix
        *
        *   @return     Transposed version of this matrix
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix2<float>( 1.0, 2.0,
        *                                            3.0, 4.0 );
        *       std::cout << "matrix: " << std::endl;
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       std::cout << "matrix.transpose(): " << std::endl;
        *       std::cout << tinymath::toString( mat.transpose() ) << std::endl;
        *       // result:
        *       // matrix:
        *       // [ 1.0, 2.0
        *       //   3.0, 4.0 ]
        *       // matrix.transpose():
        *       // [ 1.0, 3.0
        *       //   2.0, 4.0 ]
        *   @endcode
        */
        Matrix2<Scalar_T> transpose() const;

        /**
        *   @brief Returns the inverse of this matrix
        *
        *   @return     Inverse of this matrix
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix2<float>( 1.0, 2.0,
        *                                            3.0, 4.0 );
        *       std::cout << "matrix: " << std::endl;
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       std::cout << "matrix.inverse(): " << std::endl;
        *       std::cout << tinymath::toString( mat.inverse() ) << std::endl;
        *       // result:
        *       // matrix:
        *       // [ 1.0, 2.0
        *       //   3.0, 4.0 ]
        *       // matrix.inverse():
        *       // [ -2.0, 1.0
        *       //   1.5, -0.5 ]
        *   @endcode
        */
        Matrix2<Scalar_T> inverse() const;

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

        /**
        *   @brief Returns the row at the given index
        *
        *   @param index    Index of the requested row
        *   @return         A Vector2 representing the requested row
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix2<float>( 1.0, 2.0,
        *                                            3.0, 4.0 );
        *       std::cout << "row(0): " << mat.row(0) << std::endl;
        *       std::cout << "row(1): " << mat.row(1) << std::endl;
        *       // result:
        *       // row(0): [1.0, 2.0]
        *       // row(1): [3.0, 4.0]
        *   @endcode
        */
        Vector2<Scalar_T> row( size_t index ) const;

        /**
        *   @brief Return the column at the given index
        *
        *   @param index    Index of the requested column
        *   @return         A Vector2 representing the requested column
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix2<float>( 1.0, 2.0,
        *                                            3.0, 4.0 );
        *       std::cout << "col(0): " << mat.col(0) << std::endl;''
        *       std::cout << "col(1): " << mat.col(1) << std::endl;
        *       // result:
        *       // col(0): [1.0, 3.0]
        *       // col(1): [2.0, 4.0]
        *   @endcode
        */
        Vector2<Scalar_T> col( size_t index ) const;

        /**
        *   @brief Returns the matrix-addition with a second matrix
        *
        *   @param other    Second operand for the sum
        *   @return         Result of the matrix-addition
        */
        Matrix2<Scalar_T> operator+ ( const Matrix2<Scalar_T>& other ) const;

        /**
        *   @brief Returns the matrix-subtraction with a second matrix
        *
        *   @param other    Second operand for the subtraction
        *   @return         Result of the matrix-subtraction
        */
        Matrix2<Scalar_T> operator- ( const Matrix2<Scalar_T>& other ) const;

        /**
        *   @brief Returns the matrix-multiplication with a second matrix
        *
        *   @param other    Second operand for the multiplication (to the right)
        *   @return         Result of the matrix-multiplication
        */
        Matrix2<Scalar_T> operator* ( const Matrix2<Scalar_T>& other ) const;

        /**
        *   @brief Returns the matrix-vector multiplication with a given vector (to the right)
        *
        *   @param vec  Vector operand applied to the right
        *   @return     The resulting vector from the multiplication
        */
        Vector2<Scalar_T> operator* ( const Vector2<Scalar_T>& vec ) const;

        /**
        *   @brief Returns a pointer to the internal data of the matrix
        *
        *   @return     Pointer to the internal memory buffer used to store the elements of the matrix
        */
        Scalar_T* data() { return m_buff; }

    private :

        /** @brief Buffer of memory for the entries of the matrix */
        Scalar_T m_buff[SizeN * SizeN];
    };

    /**
    *   @brief Matrix-scalar product operator
    *
    *   @param mat  Matrix operand
    *   @param val  Scalar factor applied elementwise to the matrix
    *   @return     The resulting elementwise matrix-scalar product
    */
    template< typename Scalar_T >
    Matrix2<Scalar_T> operator* ( const Matrix2<Scalar_T>& mat, Scalar_T val );

    /**
    *   @brief Scalar-matrix product operator
    *
    *   @param val  Scalar factor applied elementwise to the matrix
    *   @param matr Matrix operand
    *   @return     The resulting elementwise scalar-matrix product
    */
    template< typename Scalar_T >
    Matrix2<Scalar_T> operator* ( Scalar_T val, const Matrix2<Scalar_T>& mat );

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