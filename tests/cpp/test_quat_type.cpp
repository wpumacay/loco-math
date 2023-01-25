#include <catch2/catch.hpp>
#include <math/quat_t.hpp>

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

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
auto FuncAllClose(const math::Quaternion<T>& quat, T w, T x, T y, T z) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);
    return FuncClose<T>(quat.w(), w, EPSILON) &&
           FuncClose<T>(quat.x(), x, EPSILON) &&
           FuncClose<T>(quat.y(), y, EPSILON) &&
           FuncClose<T>(quat.z(), z, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Quaternion class (quat_t) constructors",
                   "[quat_t][template]", math::float32_t, math::float64_t) {
    using T = TestType;
    using Quat = math::Quaternion<T>;
    using Euler = math::Euler<T>;

    SECTION("Default constructor") {
        Quat q;
        FuncAllClose<T>(q, 1.0, 0.0, 0.0, 0.0);
    }

    SECTION("From single scalar argument") {
        constexpr int NUM_SAMPLES = 32;
        auto val_w = GenRandomValue(T, NUM_SAMPLES);

        Quat q(val_w);
        FuncAllClose<T>(q, val_w, 0.0, 0.0, 0.0);
    }

    SECTION("From four scalar arguments, and from initializer_list") {
        constexpr int NUM_SAMPLES = 4;
        auto val_w = GenRandomValue(T, NUM_SAMPLES);
        auto val_x = GenRandomValue(T, NUM_SAMPLES);
        auto val_y = GenRandomValue(T, NUM_SAMPLES);
        auto val_z = GenRandomValue(T, NUM_SAMPLES);

        Quat q_1(val_w, val_x, val_y, val_z);
        Quat q_2 = {val_w, val_x, val_y, val_z};
        FuncAllClose<T>(q_1, val_w, val_x, val_y, val_z);
        FuncAllClose<T>(q_2, val_w, val_x, val_y, val_z);
    }

    SECTION("From Euler angles") {
        // ea = (0.0, 0.0, 0.0, XYZ, INTRINSIC)
        // q = (w, x, y, z) = (1.0, 0.0, 0.0, 0.0)
        {
            Euler e(0.0, 0.0, 0.0, Euler::Order::XYZ,
                    Euler::Convention::INTRINSIC);
            Quat q(e);
            REQUIRE(FuncAllClose<T>(q, 1.0, 0.0, 0.0, 0.0));
        }

        // ea = (t, 0.0, 0.0, XYZ, INTRINSIC)
        // q = (cos(t/2), sint(t/2), 0.0, 0.0)
        {
            auto angle = math::PI / 4.0;
            Euler e(angle, 0.0, 0.0);
            Quat q(e);
            auto cos_half = std::cos(angle / 2.0);
            auto sin_half = std::sin(angle / 2.0);
            REQUIRE(FuncAllClose<T>(q, cos_half, sin_half, 0.0, 0.0));
        }

        // ea = (0.0, t, 0.0, XYZ, INTRINSIC)
        // q = (cos(t/2), 0.0, sin(t/2), 0.0)
        {
            auto angle = math::PI / 4.0;
            Euler e(0.0, angle, 0.0);
            Quat q(e);
            auto cos_half = std::cos(angle / 2.0);
            auto sin_half = std::sin(angle / 2.0);
            REQUIRE(FuncAllClose<T>(q, cos_half, 0.0, sin_half, 0.0));
        }

        // ea = (0.0, 0.0, t, XYZ, INTRINSIC)
        // q = (cos(t/2), 0.0, 0.0, sin(t/2))
        {
            auto angle = math::PI / 4.0;
            Euler e(0.0, 0.0, angle);
            Quat q(e);
            auto cos_half = std::cos(angle / 2.0);
            auto sin_half = std::sin(angle / 2.0);
            REQUIRE(FuncAllClose<T>(q, cos_half, 0.0, 0.0, sin_half));
        }
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
