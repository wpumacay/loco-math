#pragma once

// Adapted from ThreeJS Spherical Coordinates helper
// https://github.com/mrdoob/three.js/blob/dev/src/math/Spherical.js
//
// The convention we use is different to the one used by three.js, as we usually
// deal with physics simulations that define the up direction as Z. Moreover, we
// will make use of the convention used in mathematics, which defines the polar
// angle "phi" as the angle between the positive Z-axis and the defined line
// segment OP, and the azimuthal angle "theta" as the angle between the positive
// X-axis and the projection of the line segment OP into the XY plane

#include <cmath>
#include <string>
#include <initializer_list>

#include <math/common.hpp>
#include <math/vec3_t_decl.hpp>

#define CLAMP(x, min_x, max_x) std::max(std::min(x, max_x), min_x)

namespace math {

template <typename Scalar_T>
class SphericalCoords {
 public:
    SphericalCoords() = default;

    explicit SphericalCoords(Scalar_T rho, Scalar_T theta, Scalar_T phi);

    auto Set(Scalar_T rho, Scalar_T theta, Scalar_T phi) -> void {
        m_Rho = rho;
        m_Theta = theta;
        m_Phi = phi;
    }

    auto SetFromCartesian(const Vector3<Scalar_T>& vec) -> void {
        SetFromCartesian(vec.x(), vec.y(), vec.z());
    }

    auto SetFromCartesian(Scalar_T x, Scalar_T y, Scalar_T z) -> void {
        m_Rho = std::sqrt(x * x + y * y + z * z);
        constexpr auto EPS_RADIUS = static_cast<Scalar_T>(1e-10);
        if (m_Rho < EPS_RADIUS) {
            m_Theta = static_cast<Scalar_T>(0.0);
            m_Phi = static_cast<Scalar_T>(0.0);
        } else {
            m_Theta = std::atan2(y, x);
            constexpr auto MIN_RATIO = static_cast<Scalar_T>(-1.0);
            constexpr auto MAX_RATIO = static_cast<Scalar_T>(1.0);
            m_Phi = std::acos(CLAMP(z / m_Rho, MIN_RATIO, MAX_RATIO));
        }
    }

    auto GetCartesian() const -> Vector3<Scalar_T> {
        const auto sin_theta = std::sin(m_Theta);  // NOLINT
        const auto cos_theta = std::cos(m_Theta);  // NOLINT
        const auto sin_phi = std::sin(m_Phi);      // NOLINT
        const auto cos_phi = std::cos(m_Phi);      // NOLINT

        auto x = m_Rho * cos_theta * sin_phi;
        auto y = m_Rho * sin_theta * sin_phi;
        auto z = m_Rho * cos_phi;

        return {x, y, z};
    }

    auto MakeSafe() -> void {
        // Restrict phi to be between EPS and PI-EPS
        m_Phi = CLAMP(m_Phi, static_cast<Scalar_T>(math::EPS),
                      static_cast<Scalar_T>(math::PI - math::EPS));
    }

    auto rho() const -> Scalar_T { return m_Rho; }

    auto theta() const -> Scalar_T { return m_Theta; }

    auto phi() const -> Scalar_T { return m_Phi; }

 private:
    /// The distance from the origin to the end point
    Scalar_T m_Rho = static_cast<Scalar_T>(0.0);
    /// The polar angle (measured w.r.t. the positive Z-axis)
    Scalar_T m_Theta = static_cast<Scalar_T>(0.0);
    /// The azimuthal angle (measured w.r.t. the positive X-axis)
    Scalar_T m_Phi = static_cast<Scalar_T>(0.0);
};

}  // namespace math
