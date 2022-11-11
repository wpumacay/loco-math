#include <catch2/catch.hpp>
#include <math/vec3_t.hpp>

constexpr double RANGE_MIN = -1000.0;
constexpr double RANGE_MAX = 1000.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
auto FuncAllClose(const loco::math::Vector3<T>& vec, T x, T y, T z) -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    return FuncClose<T>(vec.x(), x, EPSILON) &&
           FuncClose<T>(vec.y(), y, EPSILON) && FuncClose(vec.z(), z, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector3 class (vec3_t) type", "[vec3_t][template]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Vector3 = loco::math::Vector3<T>;

    SECTION("Default constructor") {
        Vector3 v;
        REQUIRE(FuncAllClose<T>(v, 0.0, 0.0, 0.0));
    }

    SECTION("From single scalar argument") {
        auto val_x = GenRandomValue(T, 100);

        Vector3 v(val_x);
        REQUIRE(FuncAllClose<T>(v, val_x, val_x, val_x));
    }

    SECTION("From two scalar arguments") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);

        Vector3 v(val_x, val_y);
        REQUIRE(FuncAllClose<T>(v, val_x, val_y, val_y));
    }

    SECTION(
        "From three scalar arguments, from initializer_list, or using "
        "comma-initializer") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        auto val_z = GenRandomValue(T, 10);

        Vector3 v_1(val_x, val_y, val_z);
        Vector3 v_2 = {val_x, val_y, val_z};
        Vector3 v_3;
        // cppcheck-suppress constStatement
        v_3 << val_x, val_y, val_z;

        REQUIRE(FuncAllClose<T>(v_1, val_x, val_y, val_z));
        REQUIRE(FuncAllClose<T>(v_2, val_x, val_y, val_z));
        REQUIRE(FuncAllClose<T>(v_3, val_x, val_y, val_z));
    }

    SECTION("Accessors .x(), .y(), .z()") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        auto val_z = GenRandomValue(T, 10);

        Vector3 v;
        v.x() = val_x;
        v.y() = val_y;
        v.z() = val_z;

        REQUIRE(FuncAllClose<T>(v, val_x, val_y, val_z));
    }

    SECTION("Accessors [index]") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        auto val_z = GenRandomValue(T, 10);

        Vector3 v;
        v[0] = val_x;
        v[1] = val_y;
        v[2] = val_z;
        REQUIRE(FuncAllClose<T>(v, val_x, val_y, val_z));
    }
}
