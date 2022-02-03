#include <catch2/catch.hpp>
#include <cmath>
#include <tinymath/tinymath.hpp>

template <typename T>
constexpr T RANGE_MIN = -10.0;
template <typename T>
constexpr T RANGE_MAX = 10.0;

template <typename T, int N>
auto GenRandom() -> T {
    return GENERATE(take(N, random(RANGE_MIN<T>, RANGE_MAX<T>)));
}

// clang-format off
template <typename T>
auto FuncAllClose(const tiny::math::Matrix4<T>& mat,
                  T x00, T x01, T x02, T x03,
                  T x10, T x11, T x12, T x13,
                  T x20, T x21, T x22, T x23,
                  T x30, T x31, T x32, T x33) -> void {
    const auto& cols = mat.elements();

    REQUIRE(std::abs(cols[0][0] - x00) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[0][1] - x10) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[0][2] - x20) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[0][3] - x30) < tiny::math::EPS<T>);

    REQUIRE(std::abs(cols[1][0] - x01) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[1][1] - x11) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[1][2] - x21) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[1][3] - x31) < tiny::math::EPS<T>);

    REQUIRE(std::abs(cols[2][0] - x02) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[2][1] - x12) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[2][2] - x22) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[2][3] - x32) < tiny::math::EPS<T>);

    REQUIRE(std::abs(cols[3][0] - x03) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[3][1] - x13) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[3][2] - x23) < tiny::math::EPS<T>);
    REQUIRE(std::abs(cols[3][3] - x33) < tiny::math::EPS<T>);
}
// clang-format on

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix4 class (mat4_t) core operations", "[mat4_t][ops]",
                   tiny::math::float32_t, tiny::math::float64_t) {
    using T = TestType;
    using Matrix4 = tiny::math::Matrix4<T>;
    using Vector4 = tiny::math::Vector4<T>;

    // clang-format off
    // Generate first random matrix (2^8 cases possible values)
    auto x00 = GenRandom<T, 2>(); auto x10 = GenRandom<T, 1>();
    auto x01 = GenRandom<T, 2>(); auto x11 = GenRandom<T, 1>();
    auto x02 = GenRandom<T, 2>(); auto x12 = GenRandom<T, 1>();
    auto x03 = GenRandom<T, 2>(); auto x13 = GenRandom<T, 1>();

    auto x20 = GenRandom<T, 1>(); auto x30 = GenRandom<T, 2>();
    auto x21 = GenRandom<T, 1>(); auto x31 = GenRandom<T, 2>();
    auto x22 = GenRandom<T, 1>(); auto x32 = GenRandom<T, 2>();
    auto x23 = GenRandom<T, 1>(); auto x33 = GenRandom<T, 2>();

    Matrix4 m_a(x00, x01, x02, x03,
                x10, x11, x12, x13,
                x20, x21, x22, x23,
                x30, x31, x32, x33);

    // Generate second random matrix (2^8 cases possible values)
    auto y00 = GenRandom<T, 2>(); auto y10 = GenRandom<T, 1>();
    auto y01 = GenRandom<T, 2>(); auto y11 = GenRandom<T, 1>();
    auto y02 = GenRandom<T, 2>(); auto y12 = GenRandom<T, 1>();
    auto y03 = GenRandom<T, 2>(); auto y13 = GenRandom<T, 1>();

    auto y20 = GenRandom<T, 1>(); auto y30 = GenRandom<T, 2>();
    auto y21 = GenRandom<T, 1>(); auto y31 = GenRandom<T, 2>();
    auto y22 = GenRandom<T, 1>(); auto y32 = GenRandom<T, 2>();
    auto y23 = GenRandom<T, 1>(); auto y33 = GenRandom<T, 2>();

    Matrix4 m_b(y00, y01, y02, y03,
                y10, y11, y12, y13,
                y20, y21, y22, y23,
                y30, y31, y32, y33);
    // clang-format on

    SECTION("Matrix comparison ==, !=") {
        // clang-format off
        Matrix4 m_1(1.0, 0.0, 0.0, 0.0,
                    0.0, 2.0, 0.0, 0.0,
                    0.0, 0.0, 3.0, 0.0,
                    0.0, 0.0, 0.0, 4.0);
        Matrix4 m_2(1.0, 2.0, 3.0, 4.0);
        Matrix4 m_3(1.1, 2.1, 3.1, 4.1);
        // clang-format on
        REQUIRE(m_1 == m_2);
        REQUIRE(m_2 != m_3);
        REQUIRE(m_3 != m_1);
    }
    SECTION("Matrix addition") {
        auto mat_sum = m_a + m_b;
        // clang-format off
        FuncAllClose<T>(mat_sum,
            x00 + y00, x01 + y01, x02 + y02, x03 + y03,
            x10 + y10, x11 + y11, x12 + y12, x13 + y13,
            x20 + y20, x21 + y21, x22 + y22, x23 + y23,
            x30 + y30, x31 + y31, x32 + y32, x33 + y33);
        // clang-format on
    }
    SECTION("Matrix substraction") {
        auto mat_sub = m_a - m_b;
        // clang-format off
        FuncAllClose<T>(mat_sub,
            x00 - y00, x01 - y01, x02 - y02, x03 - y03,
            x10 - y10, x11 - y11, x12 - y12, x13 - y13,
            x20 - y20, x21 - y21, x22 - y22, x23 - y23,
            x30 - y30, x31 - y31, x32 - y32, x33 - y33);
        // clang-format on
    }
    SECTION("Matrix-Scalar product") {
        auto scale_1 = GenRandom<T, 1>();
        auto scale_2 = GenRandom<T, 1>();

        auto mat_scaled_1 = scale_1 * m_a;
        auto mat_scaled_2 = m_b * scale_2;

        // clang-format off
        FuncAllClose<T>(mat_scaled_1,
            x00 * scale_1, x01 * scale_1, x02 * scale_1, x03 * scale_1,
            x10 * scale_1, x11 * scale_1, x12 * scale_1, x13 * scale_1,
            x20 * scale_1, x21 * scale_1, x22 * scale_1, x23 * scale_1,
            x30 * scale_1, x31 * scale_1, x32 * scale_1, x33 * scale_1);
        // clang-format on

        // clang-format off
        FuncAllClose<T>(mat_scaled_2,
            y00 * scale_2, y01 * scale_2, y02 * scale_2, y03 * scale_2,
            y10 * scale_2, y11 * scale_2, y12 * scale_2, y13 * scale_2,
            y20 * scale_2, y21 * scale_2, y22 * scale_2, y23 * scale_2,
            y30 * scale_2, y31 * scale_2, y32 * scale_2, y33 * scale_2);
        // clang-format on
    }
}
