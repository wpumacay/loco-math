#include <cmath>
#include <random>

#include <catch2/catch.hpp>
#include <math/pose3d_t.hpp>

#include <common_math_generators.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Pose3d class (pose3d_t) constructors",
                   "[pose3d_t][template", ::math::float32_t,
                   ::math::float64_t) {
    using T = TestType;
    using Pose = ::math::Pose3d<T>;
    using Quat = ::math::Quaternion<T>;
    using Vec3 = ::math::Vector3<T>;

    SECTION("Default constructor") {
        Pose X;  // NOLINT
        REQUIRE(X.position == Vec3(0.0, 0.0, 0.0));
        REQUIRE(X.orientation == Quat(1.0, 0.0, 0.0, 0.0));
    }

    SECTION("From position(Vec3) and orientation(Quat)") {
        auto position = GENERATE(take(10, ::math::random_vec3<T>(-10.0, 10.0)));
        auto orientation = GENERATE(take(10, ::math::random_quaternion<T>()));

        Pose X(position, orientation);  // NOLINT
        // Position should be copied directly to the pose object
        REQUIRE(X.position == position);
        // Orientation normalized to ensure it represents a rotation
        REQUIRE(std::abs(X.orientation.length() - 1.0) < 1e-5);
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
