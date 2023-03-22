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
    using Mat3 = ::math::Matrix3<T>;
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

    SECTION("From position(Vec3) and rotatio matrix(Mat3)") {
        auto position = GENERATE(take(4, ::math::random_vec3<T>(-10.0, 10.0)));
        auto angle =
            GENERATE(take(4, random(-::math::PI / 2.0, ::math::PI / 2.0)));

        SECTION("Using an x-axis rotation matrix") {
            auto rotmat = Mat3::RotationX(angle);
            Pose X(position, rotmat);  // NOLINT
            // Position should be copied directly to the pose object
            REQUIRE(X.position == position);
            // Orientation is transformed internally into a unit quaternion
            REQUIRE(std::abs(X.orientation.length() - 1.0) < 1e-5);
            // Make sure that our orientation is (as created above) a rotation
            // quaternion around the x axis
            REQUIRE(X.orientation == Quat::RotationX(angle));
        }

        SECTION("Using a y-axis rotation matrix") {
            auto rotmat = Mat3::RotationY(angle);
            Pose X(position, rotmat);  // NOLINT
            // Position should be copied directly to the pose object
            REQUIRE(X.position == position);
            // Orientation is transformed internally into a unit quaternion
            REQUIRE(std::abs(X.orientation.length() - 1.0) < 1e-5);
            // Make sure that our orientation is (as created above) a rotation
            // quaternion around the y axis
            REQUIRE(X.orientation == Quat::RotationY(angle));
        }

        SECTION("Using a z-axis rotation matrix") {
            auto rotmat = Mat3::RotationZ(angle);
            Pose X(position, rotmat);  // NOLINT
            // Position should be copied directly to the pose object
            REQUIRE(X.position == position);
            // Orientation is transformed internally into a unit quaternion
            REQUIRE(std::abs(X.orientation.length() - 1.0) < 1e-5);
            // Make sure that our orientation is (as created above) a rotation
            // quaternion around the z axis
            REQUIRE(X.orientation == Quat::RotationZ(angle));
        }
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
