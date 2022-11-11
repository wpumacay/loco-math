#include <catch2/catch.hpp>
#include <math/vec2_t.hpp>

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
auto FuncAllClose(const loco::math::Vector2<T>& vec, T x, T y) -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    return FuncClose(vec.x(), x, EPSILON) && FuncClose(vec.y(), y, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector2 class (vec2_t) type", "[vec2_t][template]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Vector2 = loco::math::Vector2<T>;

    SECTION("Default constructor") {
        Vector2 v;
        REQUIRE(FuncAllClose<T>(v, 0.0, 0.0));
    }

    SECTION("From single scalar argument") {
        auto val_x = GenRandomValue(T, 100);

        Vector2 v(val_x);
        REQUIRE(FuncAllClose<T>(v, val_x, val_x));
    }

    SECTION(
        "From two scalar arguments, from initializer_list, or using "
        "comma-initializer") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);

        Vector2 v_1(val_x, val_y);
        Vector2 v_2 = {val_x, val_y};
        Vector2 v_3;
        // cppcheck-suppress constStatement
        v_3 << val_x, val_y;

        REQUIRE(FuncAllClose<T>(v_1, val_x, val_y));
        REQUIRE(FuncAllClose<T>(v_2, val_x, val_y));
        REQUIRE(FuncAllClose<T>(v_3, val_x, val_y));
    }

    SECTION("Accessors .x(), .y()") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);

        Vector2 v;
        v.x() = val_x;
        v.y() = val_y;

        REQUIRE(FuncAllClose<T>(v, val_x, val_y));
    }

    SECTION("Accessors [index]") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);

        Vector2 v;
        v[0] = val_x;
        v[1] = val_y;
        REQUIRE(FuncAllClose<T>(v, val_x, val_y));
    }
}
