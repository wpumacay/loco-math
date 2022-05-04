#include <catch2/catch.hpp>
#include <cmath>
#include <loco/math/all.hpp>
#include <type_traits>

constexpr int N_SAMPLES = 4;
constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

// clang-format off
template <typename T>
auto FuncAllClose(const loco::math::Matrix4<T>& mat,
                  T x00, T x01, T x02, T x03,
                  T x10, T x11, T x12, T x13,
                  T x20, T x21, T x22, T x23,
                  T x30, T x31, T x32, T x33) -> void {
    const auto& cols = mat.elements();

    REQUIRE(std::abs(cols[0][0] - x00) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[0][1] - x10) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[0][2] - x20) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[0][3] - x30) < static_cast<T>(loco::math::EPS));

    REQUIRE(std::abs(cols[1][0] - x01) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[1][1] - x11) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[1][2] - x21) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[1][3] - x31) < static_cast<T>(loco::math::EPS));

    REQUIRE(std::abs(cols[2][0] - x02) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[2][1] - x12) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[2][2] - x22) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[2][3] - x32) < static_cast<T>(loco::math::EPS));

    REQUIRE(std::abs(cols[3][0] - x03) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[3][1] - x13) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[3][2] - x23) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(cols[3][3] - x33) < static_cast<T>(loco::math::EPS));
}
// clang-format on

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix4 class (mat4_t) constructors", "[mat4_t][template]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Matrix4 = loco::math::Matrix4<T>;
    using Vector4 = loco::math::Vector4<T>;

    // Checking size and alignment (storage is an array of column vectors)
    constexpr int EXPECTED_SIZE = 16 * sizeof(T);
    constexpr int EXPECTED_ALIGNMENT = 16 * sizeof(T);
    static_assert(Matrix4::num_bytes_size() == EXPECTED_SIZE, "");
    static_assert(Matrix4::num_bytes_alignment() == EXPECTED_ALIGNMENT, "");

    // Checking all exposed constructors
    SECTION("Default constructor") {
        Matrix4 mat;
        // clang-format off
        FuncAllClose<T>(mat,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0);
        // clang-format on
    }
    SECTION("From all matrix entries") {
        // @todo(wilbert): could create custom generator that fills the matrix
        // clang-format off
        Matrix4 mat(1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0,  10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);

        FuncAllClose<T>(mat,
            1.0,  2.0,  3.0,  4.0,
            5.0,  6.0,  7.0,  8.0,
            9.0,  10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0);
        // clang-format on
    }
    SECTION("From diagonal entries") {
        auto x00 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x11 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x22 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x33 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        Matrix4 mat(x00, x11, x22, x33);
        // clang-format off
        FuncAllClose<T>(mat,
            x00, 0.0, 0.0, 0.0,
            0.0, x11, 0.0, 0.0,
            0.0, 0.0, x22, 0.0,
            0.0, 0.0, 0.0, x33);
        // clang-format on
    }
    SECTION("From column vectors") {
        auto x00 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x11 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x22 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));
        auto x33 = GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                                   static_cast<T>(RANGE_MAX))));

        Vector4 col0 = {x00, 2.0, 3.0, 4.0};
        Vector4 col1 = {5.0, x11, 7.0, 8.0};
        Vector4 col2 = {9.0, 10.0, x22, 12.0};
        Vector4 col3 = {13.0, 14.0, 15.0, x33};

        Matrix4 mat(col0, col1, col2, col3);
        // clang-format off
        FuncAllClose<T>(mat,
            x00, 5.0, 9.0,  13.0,
            2.0, x11, 10.0, 14.0,
            3.0, 7.0, x22,  15.0,
            4.0, 8.0, 12.0, x33);
        // clang-format on
    }
}
