#include <catch2/catch.hpp>
#include <cmath>
#include <loco/math/mat3_t.hpp>
#include <type_traits>

constexpr int N_SAMPLES = 4;
constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

// clang-format off
template <typename T>
auto FuncAllClose(const loco::math::Matrix3<T>& mat,
                  T x00, T x01, T x02,
                  T x10, T x11, T x12,
                  T x20, T x21, T x22) -> void {
    const auto& cols = mat.elements();

    REQUIRE(std::abs(cols[0][0] - x00) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[0][1] - x10) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[0][2] - x20) < static_cast<T>(loco::math::EPS));

    REQUIRE(std::abs(cols[1][0] - x01) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[1][1] - x11) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[1][2] - x21) < static_cast<T>(loco::math::EPS));

    REQUIRE(std::abs(cols[2][0] - x02) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[2][1] - x12) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[2][2] - x22) < static_cast<T>(loco::math::EPS));
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
        FuncAllClose<T>(mat,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0);
        // clang-format on
    }
    SECTION("From all matrix entries") {
        // @todo(wilbert): could create custom generator that fills the matrix
        // clang-format off
        Matrix3 mat(1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0);

        FuncAllClose<T>(mat,
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0);
        // clang-format on
    }
    SECTION("From diagonal entries") {
        auto x00 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x11 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x22 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        Matrix3 mat(x00, x11, x22);
        // clang-format off
        FuncAllClose<T>(mat,
            x00, 0.0, 0.0,
            0.0, x11, 0.0,
            0.0, 0.0, x22);
        // clang-format on
    }
    SECTION("From column vectors") {
        auto x00 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x11 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x22 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));

        Vector3 col0 = {x00, 2.0, 3.0};
        Vector3 col1 = {4.0, x11, 6.0};
        Vector3 col2 = {7.0, 8.0, x22};

        Matrix3 mat(col0, col1, col2);
        // clang-format off
        FuncAllClose<T>(mat,
            x00, 4.0, 7.0,
            2.0, x11, 8.0,
            3.0, 6.0, x22);
        // clang-format on
    }
}
