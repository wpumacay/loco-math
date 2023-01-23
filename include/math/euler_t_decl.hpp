#pragma once

#include <ios>
#include <array>
#include <cmath>
#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <type_traits>

#include <math/mat3_t_decl.hpp>
#include <math/mat4_t_decl.hpp>
#include <math/quat_t_decl.hpp>

namespace math {

template <typename Scalar_T>
class Matrix3;

template <typename Scalar_T>
class Matrix4;

template <typename Scalar_T>
class Quaternion;

template <typename Scalar_T>
class Euler {
 public:
    /// Number of scalar dimensions of the Euler angles representation
    constexpr static uint32_t EULER_SIZE = 3;
    /// Number of scalars used in the storage of the Euler angles
    constexpr static uint32_t BUFFER_COUNT = 3;
    /// Number of bytes allocated for the buffer of the Euler angles
    constexpr static uint32_t BUFFER_SIZE = sizeof(Scalar_T) * BUFFER_COUNT;

    /// Typename of the Euler angles representation
    using Type = Euler<Scalar_T>;
    /// Typename of the scalar used for the angles (float32, float64, etc.)
    using ElementType = Scalar_T;
    /// Typename of the internal storage used
    using BufferType = std::array<Scalar_T, 3>;

    /// Possible ordering (Tait-Bryan angles)
    enum class Order {
        XYZ,
        YZX,
        ZXY,
        XZY,
        YXZ,
        ZYX,
    };

    /// Possible conventions, either INTRINSIC or EXTRINSIC
    enum class Convention {
        INTRINSIC,
        EXTRINSIC,
    };

    /// \brief Angle of rotation around the X-axis
    Scalar_T x = static_cast<Scalar_T>(0.0);  // NOLINT
    /// \brief Angle of rotation around the Y-axis
    Scalar_T y = static_cast<Scalar_T>(0.0);  // NOLINT
    /// \brief Angle of rotation around the Z-axis
    Scalar_T z = static_cast<Scalar_T>(0.0);  // NOLINT

    /// \brief Returns the internal order used for the elemental rotations
    ///
    /// The order property for this set of Euler angles is used to define in
    /// which order are the elemental rotations taken (rotations around the
    /// X, Y, and Z axes). The default used is XYZ, which states that the
    /// rotations taken to generate the total rotation is the X, Y, Z, i.e.
    /// first we rotate around the X axis by an angle given by the .x()
    /// component of the Euler angles, then around the Y axis by an angle given
    /// by the .y() component of the Euler angles, and finally a rotation around
    /// the Z-axis by an angle given by the .z() component of the Euler angles.
    Order order = Order::XYZ;  // NOLINT

    /// \brief Returns the convention used by this set of Euler angles
    ///
    /// The convention property is used to define what we use as reference for
    /// the elemental rotations. This could be either INTRINSIC (rotations are
    /// taken w.r.t the rotating body frame), or EXTRINSIC (rotations are taken
    /// w.r.t. the fixed world frame). The default used is INTRINSIC, which
    /// states that we take the rotations around the axes while they are being
    /// rotated. For example, if we used ordering XYZ, we would rotate first
    /// around the X axis. Then the next rotation taken around the Y-axis would
    /// be performed around the new Y-axis after the first rotation was taken;
    /// we then rotate around the Z-axis in a similar way, around the new Z-axis
    /// defined after we have rotated around the Y-axis previously.
    Convention convention = Convention::INTRINSIC;  // NOLINT

    // Aliases for some related types we'll use
    using Mat3 = Matrix3<Scalar_T>;
    using Mat4 = Matrix4<Scalar_T>;
    using Quat = Quaternion<Scalar_T>;

    /// Constructs a set of Euler angles with all zero entries
    Euler() = default;

    /// Constructs a set of Euler angles from the given configuration
    /// \param[in] x Euler angle associated with a rotation around the X axis
    /// \param[in] y Euler angle associated with a rotation around the Y axis
    /// \param[in] z Euler angle associated with a rotation around the Z axis
    /// \param[in] order Order used for representating this set of Euler angles
    /// \param[in] convention Convention used for the representation
    Euler(Scalar_T x, Scalar_T y, Scalar_T z, Order order = Order::XYZ,
          Convention convention = Convention::INTRINSIC) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->order = order;
        this->convention = convention;
    }

    /// Returns the set of Euler angles associated with the given 3x3 matrix
    auto fromRotationMatrix(Mat3 matrix) -> Euler<Scalar_T>;

    /// Returns the set of Euler angles associated with the given 4x4 matrix
    auto fromRotationMatrix(Mat4 matrix) -> Euler<Scalar_T>;

    /// Returns the set of Euler angles associated with the given quaternion
    auto fromQuaternion(Quat quaternion) -> Euler<Scalar_T>;
};

}  // namespace math
