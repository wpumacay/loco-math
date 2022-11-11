#include <catch2/catch.hpp>
#include <math/vec4_t.hpp>

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
auto FuncAllClose(const loco::math::Vector4<T>& vec, T x, T y, T z, T w)
    -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    return FuncClose<T>(vec.x(), x, EPSILON) &&
           FuncClose<T>(vec.y(), y, EPSILON) &&
           FuncClose<T>(vec.z(), z, EPSILON) &&
           FuncClose<T>(vec.w(), w, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector4 class (vec4_t) constructors", "[vec4_t][template]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Vector4 = loco::math::Vector4<T>;

    // Checking the correctness of the constructors

    SECTION("Default constructor") {
        Vector4 v;
        REQUIRE(FuncAllClose<T>(v, 0.0, 0.0, 0.0, 0.0));
    }

    SECTION("From single scalar argument") {
        auto val_x = GenRandomValue(T, 100);

        Vector4 v(val_x);

        REQUIRE(FuncAllClose<T>(v, val_x, val_x, val_x, val_x));
    }

    SECTION("From two scalar arguments") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);

        Vector4 v(val_x, val_y);

        REQUIRE(FuncAllClose<T>(v, val_x, val_y, val_y, val_y));
    }

    SECTION("From three scalar arguments") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        auto val_z = GenRandomValue(T, 10);

        Vector4 v(val_x, val_y, val_z);

        REQUIRE(FuncAllClose<T>(v, val_x, val_y, val_z, val_z));
    }

    SECTION(
        "From four scalar arguments, from initializer_list, or using "
        "comma-initializer") {
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto val_w = GenRandomValue(T, 4);

        Vector4 v_1(val_x, val_y, val_z, val_w);
        Vector4 v_2 = {val_x, val_y, val_z, val_w};
        Vector4 v_3;
        // cppcheck-suppress constStatement
        v_3 << val_x, val_y, val_z, val_w;

        REQUIRE(FuncAllClose<T>(v_1, val_x, val_y, val_z, val_w));
        REQUIRE(FuncAllClose<T>(v_2, val_x, val_y, val_z, val_w));
        REQUIRE(FuncAllClose<T>(v_3, val_x, val_y, val_z, val_w));
    }

    SECTION("Accessors .x(), .y(), .z(), .w()") {
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto val_w = GenRandomValue(T, 4);

        Vector4 v;
        v.x() = val_x;
        v.y() = val_y;
        v.z() = val_z;
        v.w() = val_w;

        REQUIRE(FuncAllClose<T>(v, val_x, val_y, val_z, val_w));
    }

    SECTION("Accessors [index]") {
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto val_w = GenRandomValue(T, 4);

        Vector4 v;
        v[0] = val_x;
        v[1] = val_y;
        v[2] = val_z;
        v[3] = val_w;
        REQUIRE(FuncAllClose<T>(v, val_x, val_y, val_z, val_w));
    }
}
