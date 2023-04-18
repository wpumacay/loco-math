#include <catch2/catch.hpp>
#include <math/euler_t.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#pragma clang diagnostic ignored "-Wdouble-promotion"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4305)
#endif

constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
auto FuncAllClose(const math::Euler<T>& euler, T x, T y, T z) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);
    // clang-format off
    return FuncClose<T>(euler.x, x, EPSILON) &&
           FuncClose<T>(euler.y, y, EPSILON) &&
           FuncClose<T>(euler.z, z, EPSILON);
    // clang-format on
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Euler class (euler_t) constructors", "[euler_t][template]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Euler = math::Euler<T>;
    using Mat3 = math::Matrix3<T>;
    using Mat4 = math::Matrix4<T>;
    using Quat = math::Quaternion<T>;

    SECTION("Default constructor") {
        Euler e;
        REQUIRE(FuncAllClose<T>(e, 0.0, 0.0, 0.0));
        // Default setting for order is Order::XYZ
        REQUIRE(e.order == ::math::euler::Order::XYZ);
        // Default setting for convention is Convention::INTRINSIC
        REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
    }

    SECTION("From single scalar argument") {
        constexpr int NUM_SAMPLES = 8;
        auto val_x = GenRandomValue(T, NUM_SAMPLES);
        auto val_y = GenRandomValue(T, NUM_SAMPLES);
        auto val_z = GenRandomValue(T, NUM_SAMPLES);

        Euler e(val_x, val_y, val_z);
        REQUIRE(FuncAllClose<T>(e, val_x, val_y, val_z));
        REQUIRE(e.order == ::math::euler::Order::XYZ);
        REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
    }

    SECTION("From quaternion") {
        // q = (w, x, y, z) = (1.0, 0.0, 0.0, 0.0)
        // ea = (0.0, 0.0, 0.0, XYZ, INTRINSIC)
        {
            Quat q(1.0, 0.0, 0.0, 0.0);
            Euler e(q);
            REQUIRE(FuncAllClose<T>(e, 0.0, 0.0, 0.0));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }

        // q = (cos(t/2), sin(t/2), 0.0, 0.0) (rot. angle t around x-axis)
        {
            auto angle = math::PI / 4.0;
            auto cos_half = std::cos(angle / 2.0);
            auto sin_half = std::sin(angle / 2.0);
            Quat q(cos_half, sin_half, 0.0, 0.0);
            Euler e(q);
            REQUIRE(FuncAllClose<T>(e, angle, 0.0, 0.0));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }

        // q = (cos(t/2), 0.0, sin(t/2), 0.0) (rot. angle t around y-axis)
        {
            auto angle = math::PI / 4.0;
            auto cos_half = std::cos(angle / 2.0);
            auto sin_half = std::sin(angle / 2.0);
            Quat q(cos_half, 0.0, sin_half, 0.0);
            Euler e(q);
            REQUIRE(FuncAllClose<T>(e, 0.0, angle, 0.0));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }

        // q = (cos(t/2), 0.0, 0.0, sin(t/2)) (rot. angle t around z-axis)
        {
            auto angle = math::PI / 4.0;
            auto cos_half = std::cos(angle / 2.0);
            auto sin_half = std::sin(angle / 2.0);
            Quat q(cos_half, 0.0, 0.0, sin_half);
            Euler e(q);
            REQUIRE(FuncAllClose<T>(e, 0.0, 0.0, angle));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }
    }

    SECTION("From 3x3 rotation matrix") {
        // Rot_x(45°) (rotation of 45° around the x-axis)
        // e = (PI / 4, 0.0, 0.0, XYZ, INTRINSIC)
        {
            auto angle = ::math::PI / 4.0;
            Mat3 rotmat = Mat3::RotationX(angle);
            Euler e(rotmat);
            REQUIRE(FuncAllClose<T>(e, angle, 0.0, 0.0));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }

        // Rot_y(45°) (rotation of 45° around the y-axis)
        // e = (0.0, PI / 4, 0.0, XYZ, INTRINSIC)
        {
            auto angle = ::math::PI / 4.0;
            Mat3 rotmat = Mat3::RotationY(angle);
            Euler e(rotmat);
            REQUIRE(FuncAllClose<T>(e, 0.0, angle, 0.0));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }

        // Rot_z(45°) (rotation of 45° around the z-axis)
        // e = (0.0, 0.0, PI / 4, XYZ, INTRINSIC)
        {
            auto angle = ::math::PI / 4.0;
            Mat3 rotmat = Mat3::RotationZ(angle);
            Euler e(rotmat);
            REQUIRE(FuncAllClose<T>(e, 0.0, 0.0, angle));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }
    }

    SECTION("From 4x4 transform matrix") {
        // Rot_x(45°) (rotation of 45° around the x-axis)
        // e = (PI / 4, 0.0, 0.0, XYZ, INTRINSIC)
        {
            auto angle = ::math::PI / 4.0;
            Mat4 rotmat = Mat4::RotationX(angle);
            Euler e(rotmat);
            REQUIRE(FuncAllClose<T>(e, angle, 0.0, 0.0));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }

        // Rot_y(45°) (rotation of 45° around the y-axis)
        // e = (0.0, PI / 4, 0.0, XYZ, INTRINSIC)
        {
            auto angle = ::math::PI / 4.0;
            Mat4 rotmat = Mat4::RotationY(angle);
            Euler e(rotmat);
            REQUIRE(FuncAllClose<T>(e, 0.0, angle, 0.0));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }

        // Rot_z(45°) (rotation of 45° around the z-axis)
        // e = (0.0, 0.0, PI / 4, XYZ, INTRINSIC)
        {
            auto angle = ::math::PI / 4.0;
            Mat4 rotmat = Mat4::RotationZ(angle);
            Euler e(rotmat);
            REQUIRE(FuncAllClose<T>(e, 0.0, 0.0, angle));
            REQUIRE(e.order == ::math::euler::Order::XYZ);
            REQUIRE(e.convention == ::math::euler::Convention::INTRINSIC);
        }
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif
