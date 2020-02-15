#pragma once

#include <common.h>
#include <vector_t.h>

namespace tinymath
{

    /**
    *   @brief Matrix of 2x2 shape, stored in column major format
    */
    template< typename Scalar_T, size_t SizeN >
    class Matrix
    {

    public :

        /**
        *   @brief Creates an N x N matrix initialized to an Identity matrix
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 2>();
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       // result:
        *       //  [ 1.0, 0.0
        *       //    0.0, 1.0 ]
        *   @endcode
        */
        Matrix();

        /**
        *   @brief Creates an N x N matrix initialized with elements from an std::vector in row-major order
        *
        *   @details
        *   Elements are given in row-major order to allow the user to initialize the matrix
        *   in a more familiar way, but the elements are placed to their appropriate position
        *   in the column-major memory buffer during initialization.
        *
        *   @param elements Elements of the matrix (in row-major order)
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 2>( { 1.0, 2.0,
        *                                                3.0, 4.0 } );
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       // result:
        *       //  [ 1.0, 2.0
        *       //    3.0, 4.0 ]
        *   @endcode
        */
        Matrix( const std::vector<Scalar_T>& elements );

        /**
        *   @brief Creates an N x N matrix from an (N+1)x(N+1) matrix by grabbing its upper-left section
        *
        *   @param mat  (N+1)x(N+1) matrix whose upper-left section we want
        *
        *   Example:
        *   @code
        *
        *   @endcode
        */
        Matrix( const Matrix<Scalar_T,SizeN+1>& mat );

        /**
        *   @brief Creates an N x N matrix from an  (N-1)x(N-1) matrix (upper-left section)
        *
        *   @param mat  (N-1)x(N-1) matrix whose upper-left section we want
        */
        Matrix( const Matrix<Scalar_T,SizeN-1>& mat );

        /**
        *   @brief Creates an N x N matrix from an (N-1)x(N-1) matrix (upper-left section) and an (N-1) vector (last-column)
        *
        *   @details
        *   This constructor is mainly used to create transformation matrices (4x4) from 3x3 rotation
        *   matrices and 3x1 position vectors. It will work for other matrix sizes, but the main usage
        *   is for 4x4 transformation matrices.
        */
        Matrix( const Matrix<Scalar_T,SizeN-1>& mat, const Vector<Scalar_T,SizeN-1>& vec );

        /**
        *   @brief Releases resources used for this matrix
        */
        ~Matrix();

        /**
        *   @brief Sets the components of the matrix to the Identity matrix with same dimensions
        */
        void setIdentity();

        /**
        *   @brief Sets the components of the matrix to the Zero matrix with same dimensions
        */
        void setZero();

        /**
        *   @brief Transposes this matrix in-place
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 2>( { 1.0, 2.0,
        *                                                3.0, 4.0 } );
        *       std::cout << "matrix: " << std::endl;
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       mat.transpose_();
        *       std::cout << "matrix: " << std::endl;
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       // result:
        *       // matrix:
        *       // [ 1.0, 2.0
        *       //   3.0, 4.0 ]
        *       // matrix:
        *       // [ 1.0, 3.0
        *       //   2.0, 4.0 ]
        *   @endcode
        */
        void transpose_();

        /**
        *   @brief Returns the transpose of this matrix
        *
        *   @return     Transposed version of this matrix
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 2>( { 1.0, 2.0,
        *                                                3.0, 4.0 } );
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
        Matrix<Scalar_T,SizeN> transpose() const;

        /**
        *   @brief Returns the inverse of this matrix
        *
        *   @return     Inverse of this matrix
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 2>( { 1.0, 2.0,
        *                                                3.0, 4.0 } );
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
        Matrix<Scalar_T,SizeN> inverse() const;

        /**
        *   @brief Returns the value at stored at requested index (row,col)
        *
        *   @param row  Requested row index
        *   @param col  Requested column index
        *   @return     Value stored at (row,col) index
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 2>( { 1.0, 2.0,
        *                                                3.0, 4.0 } );
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
        *       auto mat = tinymath::Matrix<float, 2>( { 1.0, 2.0,
        *                                                3.0, 4.0 } );
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
        *   @brief Returns the column at the given index
        *
        *   @param index    Index of the requested column
        *   @return         A Vector representing the requested column
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 3>( { 1.0, 2.0, 3.0,
        *                                                4.0, 5.0, 6.0,
        *                                                7.0, 8.0, 9.0 } );
        *       auto col0 = mat(0);
        *       std::cout << "matrix:" << std::endl;
        *       std::cout << tinymath::toString( mat ) << std::endl;
        *       std::cout << "column(0):" << std::endl;
        *       std::cout << tinymath::toString( col0 ) << std::endl;
        *   @endcode
        */
        Vector<Scalar_T,SizeN> operator() ( size_t index );

        /**
        *   @brief Returns the row at the given index
        *
        *   @param index    Index of the requested row
        *   @return         A Vector representing the requested row
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 2>( { 1.0, 2.0,
        *                                                3.0, 4.0 } );
        *       std::cout << "row(0): " << mat.row(0) << std::endl;
        *       std::cout << "row(1): " << mat.row(1) << std::endl;
        *       // result:
        *       // row(0): [1.0, 2.0]
        *       // row(1): [3.0, 4.0]
        *   @endcode
        */
        Vector<Scalar_T,SizeN> row( size_t index ) const;

        /**
        *   @brief Return the column at the given index
        *
        *   @param index    Index of the requested column
        *   @return         A Vector representing the requested column
        *
        *   Example:
        *   @code
        *       auto mat = tinymath::Matrix<float, 2>( 1.0, 2.0,
        *                                            3.0, 4.0 );
        *       std::cout << "col(0): " << mat.col(0) << std::endl;''
        *       std::cout << "col(1): " << mat.col(1) << std::endl;
        *       // result:
        *       // col(0): [1.0, 3.0]
        *       // col(1): [2.0, 4.0]
        *   @endcode
        */
        Vector<Scalar_T,SizeN> col( size_t index ) const;

        /**
        *   @brief Sets the values of the column of a matrix from a column vector of same size
        *
        *   @param vec      Vector representing the column values to be set
        *   @param index    Index of the column to be set
        */
        void set( const Vector<Scalar_T,SizeN>& vec, size_t index );

        /**
        *   @brief Sets part of the column of a matrix from a column vector of size (N-1)
        *
        *   @param vec      Vector representing the (n-1) column values to be set
        *   @param index    Index of the column to be set
        */
        void set( const Vector<Scalar_T,SizeN-1>& vec, size_t index );

        /**
        *   @brief Sets the upper-left section of a matrix from a (N-1)x(N-1) matrix
        *
        *   @param mat      Matrix representing the (n-1)x(n-1) upper-left section to be set
        */
        void set( const Matrix<Scalar_T,SizeN-1>& mat );

        /**
        *   @brief Returns the matrix-addition with a second matrix
        *
        *   @param other    Second operand for the sum
        *   @return         Result of the matrix-addition
        */
        Matrix<Scalar_T,SizeN> operator+ ( const Matrix<Scalar_T,SizeN>& other ) const;

        /**
        *   @brief Returns the matrix-subtraction with a second matrix
        *
        *   @param other    Second operand for the subtraction
        *   @return         Result of the matrix-subtraction
        */
        Matrix<Scalar_T,SizeN> operator- ( const Matrix<Scalar_T,SizeN>& other ) const;

        /**
        *   @brief Returns the matrix-multiplication with a second matrix
        *
        *   @param other    Second operand for the multiplication (to the right)
        *   @return         Result of the matrix-multiplication
        */
        Matrix<Scalar_T,SizeN> operator* ( const Matrix<Scalar_T,SizeN>& other ) const;

        /**
        *   @brief Returns the matrix-vector multiplication with a given vector (to the right)
        *
        *   @param vec  Vector operand applied to the right
        *   @return     The resulting vector from the multiplication
        */
        Vector<Scalar_T,SizeN> operator* ( const Vector<Scalar_T,SizeN>& vec ) const;

        /**
        *   @brief Returns a mutable reference to the internal data of the matrix
        *
        *   @return     Pointer to the internal memory buffer used to store the elements of the matrix
        */
        Scalar_T* data() { return m_buff; }

        /**
        *   @brief Returns a const-reference to the internal data of the matrix
        *
        *   @return     Const-Pointer to the internal memory buffer used to store the elements of the matrix
        */
        const Scalar_T* data() const { return m_buff; }

    private :

        /** @brief Helper value-getter (for internal usage) of a given element */
        Scalar_T _get( size_t row, size_t col ) const;

        /** @brief Helper value-setter (for internal usage) of a given element */
        void _set( size_t row, size_t col, Scalar_T val );

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
    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T,SizeN> operator* ( const Matrix<Scalar_T,SizeN>& mat, tfloat val );

    /**
    *   @brief Scalar-matrix product operator
    *
    *   @param val  Scalar factor applied elementwise to the matrix
    *   @param mat  Matrix operand
    *   @return     The resulting elementwise scalar-matrix product
    */
    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T,SizeN> operator* ( tfloat val, const Matrix<Scalar_T,SizeN>& mat );

    /**
    *   @brief Returns a string representation of the given 2x2 matrix
    *
    *   @param mat  Matrix whose string representation we want
    *   @return     The string representation of the given matrix
    */
    template< typename Scalar_T, size_t SizeN >
    std::string toString( const Matrix<Scalar_T,SizeN>& mat );

    /**
    *   @brief Checks if all matrix elements are close up to a certain margin
    *
    *   @param mat1     First matrix operand to compare
    *   @param mat2     Second matrix operand to compare
    *   @param margin   Margin for comparison of the elements
    *   @return         Whether or not the matrices have all elements close
    */
    template< typename Scalar_T, size_t SizeN >
    bool allclose( const Matrix<Scalar_T,SizeN >& mat1, const Matrix<Scalar_T,SizeN>& mat2, Scalar_T tolerance = TINYMATH_EPS );

    /**
    *   @brief Computes the inverse of a given 2x2 matrix
    *
    *   @param mat      Matrix to be inverted
    *   @return         Inverse of the given 2x2 matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 2 > inverse( const Matrix<Scalar_T, 2>& mat );

    /**
    *   @brief Computes the inverse of a given 3x3 matrix
    *
    *   @param mat      Matrix to be inverted
    *   @return         Inverse of the given 3x3 matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 3 > inverse( const Matrix<Scalar_T, 3>& mat );

    /**
    *   @brief Computes the inverse of a given 4x4 matrix
    *
    *   @param mat      Matrix to be inverted
    *   @return         Inverse of the given 4x4 matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 4 > inverse( const Matrix<Scalar_T, 4>& mat );

    /* @brief Matrix2 with float32 scalar-type */
    typedef Matrix<float, 2> Matrix2f;
    /* @brief Matrix2 with float64 (double) scalar type */
    typedef Matrix<double, 2> Matrix2d;

    /* @brief Matrix3 with float32 scalar-type */
    typedef Matrix<float, 3> Matrix3f;
    /* @brief Matrix3 with float64 (double) scalar type */
    typedef Matrix<double, 3> Matrix3d;

    /* @brief Matrix4 with float32 scalar-type */
    typedef Matrix<float, 4> Matrix4f;
    /* @brief Matrix4 with float64 (double) scalar type */
    typedef Matrix<double, 4> Matrix4d;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

    /**********************************************************************************************/
    /*                                    Custom functions                                        */
    /**********************************************************************************************/

    // Inverse function specializations for mat2s,mat3s and mat4s

    template<>
    Matrix<float,2> Matrix<float,2>::inverse() const;
    template<>
    Matrix<float,3> Matrix<float,3>::inverse() const;
    template<>
    Matrix<float,4> Matrix<float,4>::inverse() const;

    template<>
    Matrix<double,2> Matrix<double,2>::inverse() const;
    template<>
    Matrix<double,3> Matrix<double,3>::inverse() const;
    template<>
    Matrix<double,4> Matrix<double,4>::inverse() const;

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
}

#include "../src/matrix_t_impl.hpp"