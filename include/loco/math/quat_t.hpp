#pragma once

// clang-format off
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

#include <loco/math/mat4_t.hpp>
#include <loco/math/vec3_t.hpp>

// clang-format on

namespace loco {
namespace math {

template <typename Scalar_T>
class Quaternion {
 public:
    /// Number of scalar dimensions of the quaternion
    constexpr static uint32_t QUAT_NDIM = 4;
    /// Number of scalars used in the storage of the vector
    constexpr static uint32_t BUFFER_COUNT = 4;
    /// Number of bytes allocated for the buffer of this quaternion
    constexpr static uint32_t BUFFER_SIZE = sizeof(Scalar_T) * BUFFER_COUNT;

    /// Typename of the vector
    using Type = Quaternion<Scalar_T>;
    /// Typename of the scalar used for the vector (float32, float64, etc.)
    using ElementType = Scalar_T;
    /// Typename of the internal storage used for the vector
    using BufferType = std::array<Scalar_T, BUFFER_COUNT>;

    // Some related types
    using Vec3 = Vector3<Scalar_T>;

    /// Constructs a zero-initialized vector
    Quaternion() = default;

    /// Constructs a real-valued quaternion
    /// \param real Real-value part of the quaternion
    explicit Quaternion(Scalar_T real) {
        m_Elements[0] = static_cast<Scalar_T>(0.0F);
        m_Elements[1] = static_cast<Scalar_T>(0.0F);
        m_Elements[2] = static_cast<Scalar_T>(0.0F);
        m_Elements[3] = real;
    }

    /// Constructs a quaternion given its 4 entries
    /// \param x_val Value of the first imaginary component
    /// \param y_val Value of the second imaginary component
    /// \param z_val Value of the third imaginary component
    /// \param w_val Value of the real-valued component
    explicit Quaternion(Scalar_T x_val, Scalar_T y_val, Scalar_T z_val,
                        Scalar_T w_val) {
        m_Elements[0] = x_val;
        m_Elements[1] = y_val;
        m_Elements[2] = z_val;
        m_Elements[3] = w_val;
    }

    /// Constructs a quaternion given an angle and an axis
    /// \param angle The angle of rotation in the representation
    /// \param axis The 3d vector representing the rotation axis
    explicit Quaternion(Scalar_T angle, const Vec3& axis) {
        const Scalar_T half_angle = 0.5 * angle;         // NOLINT
        const Scalar_T sin_half = std::sin(half_angle);  // NOLINT
        const Scalar_T cos_half = std::cos(half_angle);  // NOLINT
        m_Elements[0] = axis.x() * sin_half;
        m_Elements[1] = axis.x() * sin_half;
        m_Elements[2] = axis.x() * sin_half;
        m_Elements[3] = cos_half;
    }

    // cppcheck-suppress noExplicitConstructor
    /// Constructs a quaternion from a given list of the form {x, y, z, w}
    Quaternion(const std::initializer_list<Scalar_T>& values) {
        // Complain in case we don't receive exactly 4 values
        assert(values.size() == Quaternion<Scalar_T>::QUAT_NDIM);
        // Just copy the whole data from the initializer list
        std::copy(values.begin(), values.end(), m_Elements.data());
    }

    /// Returns a mutable reference to the imaginary x-component
    auto x() -> Scalar_T& { return m_Elements[0]; }

    /// Returns a mutable reference to the imaginary y-component
    auto y() -> Scalar_T& { return m_Elements[1]; }

    /// Returns a mutable reference to the imaginary z-component
    auto z() -> Scalar_T& { return m_Elements[2]; }

    /// Returns a mutable reference to the real w-component
    auto w() -> Scalar_T& { return m_Elements[3]; }

    /// Returns an unmutable reference to the imaginary x-component
    auto x() const -> const Scalar_T& { return m_Elements[0]; }

    /// Returns an unmutable reference to the imaginary y-component
    auto y() const -> const Scalar_T& { return m_Elements[1]; }

    /// Returns an unmutable reference to the imaginary z-component
    auto z() const -> const Scalar_T& { return m_Elements[2]; }

    /// Returns an unmutable reference to the real w-component
    auto w() const -> const Scalar_T& { return m_Elements[3]; }

    /// Returns a mutable reference to the storage of the quaternion
    auto elements() -> BufferType& { return m_Elements; }

    /// Returns an unmutable reference to the storage of the quaternion
    auto elements() const -> const BufferType& { return m_Elements; }

    /// Returns a pointer to the data of the underlying storage in use
    auto data() -> Scalar_T* { return m_Elements.data(); }

    /// Reeturns a const-pointer to the data of the underlying storage in use
    auto data() const -> const Scalar_T* { return m_Elements.data(); }

    /// Returns a printable string-representation of the vector
    auto toString() const -> std::string {
        std::stringstream str_result;
        if (std::is_same<ElementType, float>()) {
            str_result << "Quaternionf(" << x() << ", " << y() << ", " << z()
                       << ", " << w() << ")";
        } else if (std::is_same<ElementType, double>()) {
            str_result << "Quaterniond(" << x() << ", " << y() << ", " << z()
                       << ", " << w() << ")";
        } else {
            str_result << "QuaternionX(" << x() << ", " << y() << ", " << z()
                       << ", " << w() << ")";
        }
        return str_result.str();
    }

    /// Returns the number of dimensions of the vector (Vector4 <-> 4 scalars)
    static constexpr auto ndim() -> uint32_t { return QUAT_NDIM; }

    /// Returns the number of scalars used by the storage of the vector
    static constexpr auto buffer_count() -> uint32_t { return BUFFER_COUNT; }

    /// Returns the size (in bytes) of the vector
    static constexpr auto num_bytes_size() -> uint32_t { return sizeof(Type); }

    /// Returns the alignment (in bytes) of the vector
    static constexpr auto num_bytes_alignment() -> uint32_t {
        return alignof(Type);
    }

 private:
    /// Storage of the quaternion's entries in   (x, y, z, w) order
    alignas(BUFFER_SIZE) BufferType m_Elements = {0, 0, 0, 1};
};

}  // namespace math
}  // namespace loco
