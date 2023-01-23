#include <catch2/catch.hpp>
#include <math/euler_t.hpp>

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

    SECTION("Default constructor") {
        Euler e;
        REQUIRE(FuncAllClose<T>(e, 0.0, 0.0, 0.0));
        // Default setting for order is Order::XYZ
        REQUIRE(e.order == Euler::Order::XYZ);
        // Default setting for convention is Convention::INTRINSIC
        REQUIRE(e.convention == Euler::Convention::INTRINSIC);
    }

    SECTION("From single scalar argument") {
        constexpr int NUM_SAMPLES = 8;
        auto val_x = GenRandomValue(T, NUM_SAMPLES);
        auto val_y = GenRandomValue(T, NUM_SAMPLES);
        auto val_z = GenRandomValue(T, NUM_SAMPLES);

        Euler e(val_x, val_y, val_z);
        REQUIRE(FuncAllClose<T>(e, val_x, val_y, val_z));
        REQUIRE(e.order == Euler::Order::XYZ);
        REQUIRE(e.convention == Euler::Convention::INTRINSIC);
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
