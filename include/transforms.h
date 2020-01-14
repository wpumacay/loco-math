#pragma once

#include <vector_t.h>
#include <matrix_t.h>

namespace tinymath
{

    /**
    *   @brief Converts a given 3x3 rotation matrix to a quaternion
    *
    *   @param rotmat   3x3 rotation matrix
    *   @return         4-d vector representing the quaternion
    */
    template< typename Scalar_T >
    Vector<Scalar_T, 4> quaternion( const Matrix<Scalar_T, 3>& rotmat );

    /**
    *   @brief Converts a given 3x3 rotation matrix to its euler angle (zyx intrinsic) representation
    *
    *   @param rotmat   3x3 rotation matrix
    *   @return         3-d vector representing the zyx euler angles
    */
    template< typename Scalar_T >
    Vector<Scalar_T, 3> euler( const Matrix<Scalar_T, 3>& rotmat );

    /**
    *   @brief Converts a given 3x3 rotation matrix to its axis-angle representation
    *
    *   @param rotmat   3x3 rotation matrix
    *   @return         Axis and angle as an std::pair
    */
    template< typename Scalar_T >
    std::pair< Vector<Scalar_T, 3>, Scalar_T > axisAngle( const Matrix<Scalar_T, 3>& rotmat );

    /**
    *   @brief Converts from euler angles to a 3x3 rotation matrix
    *
    *   @param ezyx     Vector-3 representing the euler angles (zyx convention) to convert
    *   @return         3x3 rotation matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotation( const Vector<Scalar_T, 3>& ezyx );

    /**
    *   @brief Converts from quaternion to a 3x3 rotation matrix
    *
    *   @param quat     Vector-4 representing the quaternion
    *   @return         3x3 rotation matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotation( const Vector<Scalar_T, 4>& quat );

    /**
    *   @brief Converts from axis-angle to a 3x3 rotation matrix
    *
    *   @param axis     Vector-3 representing the axis of rotation
    *   @param angle    Angle of rotation along the given axis
    *   @¶eturn         3x3 rotation matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotation( const Vector<Scalar_T, 3>& axis, tfloat angle );

    /**
    *   @brief Creates a 3x3 rotation matrix for a rotation around the x-axis
    *
    *   @param angle    Angle of rotation along the x-axis
    *   @return         3x3 rotation matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotationX( tfloat angle );

    /**
    *   @brief Creates a 3x3 rotation matrix for a rotation around the y-axis
    *
    *   @param angle    Angle of rotation along the y-axis
    *   @return         3x3 rotation matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotationY( tfloat angle );

    /**
    *   @brief Creates a 3x3 rotation matrix for a rotation around the z-axis
    *
    *   @param angle    Angle of rotation along the z-axis
    *   @return         3x3 rotation matrix
    */
    template< typename Scalar_T >
    Matrix<Scalar_T, 3> rotationZ( tfloat angle );

    /**
    *   @brief Computes the cross product of two 3-dim vectors
    *
    *   @param vec1     First 3-dim vector operand
    *   @param vec2     Second 3-dim vector operand
    *   @return         The resulting cross product as a 3-dim vector
    */
    template< typename Scalar_T >
    Vector<Scalar_T, 3> cross( const Vector<Scalar_T, 3>& vec1, const Vector<Scalar_T, 3>& vec2 );

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

}

#include "../src/transforms_impl.hpp"