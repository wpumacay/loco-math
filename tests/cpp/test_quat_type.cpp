#include <catch2/catch.hpp>
#include <type_traits>
#include <cmath>

#include <loco/math/quat_t_impl.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#endif

constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

static constexpr double ANGLE_MIN = -loco::math::PI;
static constexpr double ANGLE_MAX = loco::math::PI;

// NOLINTNEXTLINE
#define GenRandomAngle(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(ANGLE_MIN), \
                                   static_cast<Type>(ANGLE_MAX))))

template <typename T>
auto CheckAllClose(const loco::math::Quaternion<T>& quat, T w, T x, T y, T z)
    -> void {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    REQUIRE(std::abs(quat.w() - w) < EPSILON);
    REQUIRE(std::abs(quat.x() - x) < EPSILON);
    REQUIRE(std::abs(quat.y() - y) < EPSILON);
    REQUIRE(std::abs(quat.z() - z) < EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Quaternion class (quat_t) constructors",
                   "[quat_t][template]", loco::math::float32_t,
                   loco::math::float64_t) {
    using T = TestType;
    using Quaternion = loco::math::Quaternion<T>;
    using Vector3 = loco::math::Vector3<T>;

    SECTION("Default constructor") {
        Quaternion q;
        CheckAllClose<T>(q, 1.0, 0.0, 0.0, 0.0);
    }

    SECTION("From single scalar argument") {
        constexpr int NUM_SAMPLES = 32;
        auto val_w = GenRandomValue(T, NUM_SAMPLES);

        Quaternion q(val_w);
        CheckAllClose<T>(q, val_w, 0.0, 0.0, 0.0);
    }

    SECTION("From four scalar arguments, and from initializer_list") {
        constexpr int NUM_SAMPLES = 4;
        auto val_w = GenRandomValue(T, NUM_SAMPLES);
        auto val_x = GenRandomValue(T, NUM_SAMPLES);
        auto val_y = GenRandomValue(T, NUM_SAMPLES);
        auto val_z = GenRandomValue(T, NUM_SAMPLES);

        Quaternion q_1(val_w, val_x, val_y, val_z);
        Quaternion q_2 = {val_w, val_x, val_y, val_z};
        CheckAllClose<T>(q_1, val_w, val_x, val_y, val_z);
        CheckAllClose<T>(q_2, val_w, val_x, val_y, val_z);
    }

    SECTION("From axis-angle") {
        constexpr int NUM_SAMPLES = 4;
        auto val_angle = GenRandomAngle(T, NUM_SAMPLES);
        auto val_x = GenRandomValue(T, NUM_SAMPLES);
        auto val_y = GenRandomValue(T, NUM_SAMPLES);
        auto val_z = GenRandomValue(T, NUM_SAMPLES);

        auto length = std::sqrt(val_x * val_x + val_y * val_y + val_z * val_z);
        val_x /= length;
        val_y /= length;
        val_z /= length;
        Vector3 v(val_x, val_y, val_z);

        // Expected values
        auto half_angle = static_cast<T>(0.5) * val_angle;  // NOLINT
        auto sin_half = std::sin(half_angle);
        auto cos_half = std::cos(half_angle);

        auto expected_w = cos_half;
        auto expected_x = v.x() * sin_half;  // NOLINT
        auto expected_y = v.y() * sin_half;  // NOLINT
        auto expected_z = v.z() * sin_half;  // NOLINT

        Quaternion q(val_angle, v);
        CheckAllClose<T>(q, expected_w, expected_x, expected_y, expected_z);
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
