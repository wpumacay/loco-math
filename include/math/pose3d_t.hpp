#pragma once

#include <math/pose3d_t_decl.hpp>

#include <math/vec3_t.hpp>
#include <math/mat3_t.hpp>
#include <math/euler_t.hpp>
#include <math/quat_t.hpp>
#include <math/mat4_t.hpp>

namespace math {

template <typename T>
Pose3d<T>::Pose3d(const Vec3& pos, const Quat& quat) {
    this->position = pos;
    this->orientation = quat.normalized();
}

template <typename T>
Pose3d<T>::Pose3d(const Vec3& pos, const Euler<T>& euler) {
    this->position = pos;
    this->orientation.setFromEuler(euler).normalized();
}

template <typename T>
Pose3d<T>::Pose3d(const Vec3& pos, const Mat3& rotmat) {
    this->position = pos;
    this->orientation.setFromRotationMatrix(rotmat).normalized();
}

template <typename T>
Pose3d<T>::Pose3d(const Mat4& transform) {
    this->position = Vec3(transform[3]);
    this->orientation.setFromRotationMatrix(Mat3(transform)).normalized();
}

template <typename T>
auto Pose3d<T>::apply(const Vec3& rhs) const -> Vec3 {
    return this->position + this->orientation.rotate(rhs);
}

template <typename T>
auto Pose3d<T>::inverse() const -> Pose3d<T> {
    return Pose3d<T>(-this->position, this->orientation.inverse());
}

template <typename T>
auto Pose3d<T>::toMatrix() const -> Mat4 {
    return Mat4(this->position, this->orientation);
}

template <typename T>
auto Pose3d<T>::operator*(const Pose3d<T>& rhs) const -> Pose3d<T> {
    auto res_orientation = this->orientation * rhs->orientation;
    auto res_position =
        this->position + this->orientation.rotate(rhs->position);
    return Pose3d<T>(res_position, res_orientation);
}

}  // namespace math
