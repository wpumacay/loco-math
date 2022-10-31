#include <catch2/catch.hpp>
#include <loco/math/mat3_t.hpp>

constexpr double RANGE_MIN = -100.0;
constexpr double RANGE_MAX = 100.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

// clang-format off
template <typename T>
auto FuncAllClose(const loco::math::Matrix3<T>& mat,
                  T x00, T x01, T x02,
                  T x10, T x11, T x12,
                  T x20, T x21, T x22) -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);

    return FuncClose<T>(mat(0, 0), x00, EPSILON) &&
           FuncClose<T>(mat(0, 1), x01, EPSILON) &&
           FuncClose<T>(mat(0, 2), x02, EPSILON) &&
           FuncClose<T>(mat(1, 0), x10, EPSILON) &&
           FuncClose<T>(mat(1, 1), x11, EPSILON) &&
           FuncClose<T>(mat(1, 2), x12, EPSILON) &&
           FuncClose<T>(mat(2, 0), x20, EPSILON) &&
           FuncClose<T>(mat(2, 1), x21, EPSILON) &&
           FuncClose<T>(mat(2, 2), x22, EPSILON);
}
// clang-format on

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix3 class (mat3_t) constructors", "[mat3_t][template]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Matrix3 = loco::math::Matrix3<T>;
    using Vector3 = loco::math::Vector3<T>;

    // Checking all exposed constructors
    SECTION("Default constructor") {
        Matrix3 mat;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0));
        // clang-format on
    }
    SECTION("From all matrix entries") {
        // clang-format off
        Matrix3 mat(1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0);

        REQUIRE(FuncAllClose<T>(mat,
                1.0, 2.0, 3.0,
                4.0, 5.0, 6.0,
                7.0, 8.0, 9.0));
        // clang-format on
    }
    SECTION("From diagonal entries") {
        auto x00 = GenRandomValue(T, 8);
        auto x11 = GenRandomValue(T, 8);
        auto x22 = GenRandomValue(T, 8);

        Matrix3 mat(x00, x11, x22);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                x00, 0.0, 0.0,
                0.0, x11, 0.0,
                0.0, 0.0, x22));
        // clang-format on
    }
    SECTION("From column vectors") {
        auto x00 = GenRandomValue(T, 8);
        auto x11 = GenRandomValue(T, 8);
        auto x22 = GenRandomValue(T, 8);

        Vector3 col0 = {x00, 2.0, 3.0};
        Vector3 col1 = {4.0, x11, 6.0};
        Vector3 col2 = {7.0, 8.0, x22};

        Matrix3 mat(col0, col1, col2);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                x00, 4.0, 7.0,
                2.0, x11, 8.0,
                3.0, 6.0, x22));
        // clang-format on
    }
}
