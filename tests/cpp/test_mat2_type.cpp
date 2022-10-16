#include <catch2/catch.hpp>
#include <cmath>
#include <loco/math/mat2_t.hpp>
#include <type_traits>

constexpr int N_SAMPLES = 4;
constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

template <typename T>
auto FuncAllClose(const loco::math::Matrix2<T>& mat, T x00, T x01, T x10, T x11)
    -> void {
    REQUIRE(std::abs(mat(0, 0) - x00) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(0, 1) - x01) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(1, 0) - x10) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(1, 1) - x11) < static_cast<T>(loco::math::EPS));
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix4 class (mat2_t) constructors", "[mat2_t][template]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Matrix2 = loco::math::Matrix2<T>;
    using Vector2 = loco::math::Vector2<T>;

    // Checking all exposed constructors
    SECTION("Default constructor") {
        Matrix2 mat;
        FuncAllClose<T>(mat, 0.0, 0.0, 0.0, 0.0);
    }
    SECTION("From all matrix entries") {
        auto x00 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x01 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x10 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x11 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        Matrix2 mat(x00, x01, x10, x11);
        FuncAllClose<T>(mat, x00, x01, x10, x11);
    }
    SECTION("From diagonal entries") {
        auto x00 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x11 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        Matrix2 mat(x00, x11);
        FuncAllClose<T>(mat, x00, 0.0, 0.0, x11);
    }
    SECTION("From column vectors") {
        auto x00 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x01 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x10 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x11 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        Vector2 col0(x00, x10);
        Vector2 col1(x01, x11);

        Matrix2 mat(col0, col1);
        FuncAllClose<T>(mat, x00, x01, x10, x11);
    }
}
