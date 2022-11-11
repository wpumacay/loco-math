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
    using Quaternion = math::Quaternion<T>;

    SECTION("Default constructor") {
        Quaternion q;
        FuncAllClose<T>(q, 1.0, 0.0, 0.0, 0.0);
    }

    SECTION("From single scalar argument") {
        constexpr int NUM_SAMPLES = 32;
        auto val_w = GenRandomValue(T, NUM_SAMPLES);

        Quaternion q(val_w);
        FuncAllClose<T>(q, val_w, 0.0, 0.0, 0.0);
    }

    SECTION("From four scalar arguments, and from initializer_list") {
        constexpr int NUM_SAMPLES = 4;
        auto val_w = GenRandomValue(T, NUM_SAMPLES);
        auto val_x = GenRandomValue(T, NUM_SAMPLES);
        auto val_y = GenRandomValue(T, NUM_SAMPLES);
        auto val_z = GenRandomValue(T, NUM_SAMPLES);

        Quaternion q_1(val_w, val_x, val_y, val_z);
        Quaternion q_2 = {val_w, val_x, val_y, val_z};
        FuncAllClose<T>(q_1, val_w, val_x, val_y, val_z);
        FuncAllClose<T>(q_2, val_w, val_x, val_y, val_z);
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
