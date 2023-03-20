#pragma once

#include <math/pose3d_t_decl.hpp>

namespace math {

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
