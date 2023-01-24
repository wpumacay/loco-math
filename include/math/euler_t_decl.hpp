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
    using Mat3 = Matrix3<Scalar_T>;
    using Mat4 = Matrix4<Scalar_T>;
    using Quat = Quaternion<Scalar_T>;

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

    /// Constructs a set of Euler angles with all zero entries
    Euler() = default;

    /// Constructs a set of Euler angles from the given configuration
    /// \param[in] x Euler angle associated with a rotation around the X axis
    /// \param[in] y Euler angle associated with a rotation around the Y axis
    /// \param[in] z Euler angle associated with a rotation around the Z axis
    /// \param[in] order Order used for the representation
    /// \param[in] convention Convention used for the representation
    explicit Euler(Scalar_T x, Scalar_T y, Scalar_T z, Order order = Order::XYZ,
                   Convention convention = Convention::INTRINSIC) {
        this->order = order;
        this->convention = convention;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /// Constructs a set of Euler angles from the given 3x3 rotation matrix
    /// \param[in] matrix A 3x3 rotation matrix given by the user
    /// \param[in] order Order used for the representation
    /// \param[in] convention Convention used for the representation
    explicit Euler(const Mat3& matrix, Order order = Order::XYZ,
                   Convention convention = Convention::INTRINSIC) {
        this->order = order;
        this->convention = convention;
        setFromRotationMatrix(matrix);
    }

    /// Constructs a set of Euler angles from the given 4x4 transform matrix
    /// \param[in] matrix A 4x4 transform matrix given by the user
    /// \param[in] order Order used for the representation
    /// \param[in] convention Convention used for the representation
    explicit Euler(const Mat4& matrix, Order order = Order::XYZ,
                   Convention convention = Convention::INTRINSIC) {
        this->order = order;
        this->convention = convention;
        setFromRotationMatrix(matrix);
    }

    /// Constructs a set of Euler angles from the given quaternion
    /// \param[in] quaternion A quaternion given by the user
    /// \param[in] order Order used for the representation
    /// \param[in] convention Convention used for the representation
    explicit Euler(const Quat& quaternion, Order order = Order::XYZ,
                   Convention convention = Convention::INTRINSIC) {
        this->order = order;
        this->convention = convention;
        setFromQuaternion(quaternion);
    }

    /// Updates this set of Euler angles with the given 3x3 rotation matrix
    auto setFromRotationMatrix(const Mat3& matrix) -> void;

    /// Updates this set of Euler angles with the given 4x4 transform matrix
    auto setFromRotationMatrix(const Mat4& matrix) -> void;

    /// Updates this set of Euler angles with the given quaternion
    auto setFromQuaternion(const Quat& quaternion) -> void;
};

}  // namespace math
