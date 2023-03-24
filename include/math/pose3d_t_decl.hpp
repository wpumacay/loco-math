#pragma once

#include <sstream>
#include <string>

#include <math/common.hpp>

#include <math/vec3_t_decl.hpp>
#include <math/vec4_t_decl.hpp>
#include <math/mat3_t_decl.hpp>
#include <math/mat4_t_decl.hpp>
#include <math/euler_t_decl.hpp>

namespace math {
template <typename Scalar_T>
class Matrix3;

template <typename Scalar_T>
class Euler;

template <typename Scalar_T>
class Quaternion;
}  // namespace math

namespace math {

template <typename Scalar_T>
class Pose3d {
 public:
    using Vec3 = ::math::Vector3<Scalar_T>;
    using Vec4 = ::math::Vector4<Scalar_T>;
    using Quat = ::math::Quaternion<Scalar_T>;
    using Mat3 = ::math::Matrix3<Scalar_T>;
    using Mat4 = ::math::Matrix4<Scalar_T>;

    /// The position component of this pose
    Vec3 position;
    /// The orientation component of this pose
    Quat orientation;

    Pose3d() = default;

    explicit Pose3d(const Vec3& pos, const Quat& quat);

    explicit Pose3d(const Vec3& pos, const Euler<Scalar_T>& euler);

    explicit Pose3d(const Vec3& pos, const Mat3& mat);

    explicit Pose3d(const Mat4& transform);

    /// Transforms the given vector by using this pose
    LM_INLINE auto apply(const Vec3& rhs) const -> Vec3;

    /// Returns the inverse of this pose
    LM_INLINE auto inverse() const -> Pose3d<Scalar_T>;

    /// Returns a 4x4 matrix equivalent to this pose
    LM_INLINE auto toMatrix() const -> Mat4;

    /// Composes the given pose with this pose
    LM_INLINE auto operator*(const Pose3d<Scalar_T>& rhs) const
        -> Pose3d<Scalar_T>;

    /// Applies this transform to the given vector
    LM_INLINE auto operator*(const Vec3& rhs) const -> Vec3;

    /// Returns a printable string representation of this pose
    auto toString() const -> std::string {
        std::stringstream str_result;
        str_result << "Pose3d(pos=" << this->position.toString() << ", ";
        str_result << "rot=" << this->orientation.toString() << ")";
        return str_result.str();
    }
};

}  // namespace math
