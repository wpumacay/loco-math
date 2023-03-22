#include <catch2/catch.hpp>
#include <math/mat4_t.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4305)
#endif

static constexpr double RANGE_MIN = -10.0;
static constexpr double RANGE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomValue(T, N) \
    GENERATE(take(           \
        N, random(static_cast<T>(RANGE_MIN), static_cast<T>(RANGE_MAX))));

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

// clang-format off
template <typename T>
auto FuncAllClose(const math::Matrix4<T>& mat,
                  T x00, T x01, T x02, T x03,
                  T x10, T x11, T x12, T x13,
                  T x20, T x21, T x22, T x23,
                  T x30, T x31, T x32, T x33) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);

    return FuncClose<T>(mat(0, 0), x00, EPSILON) &&
           FuncClose<T>(mat(0, 1), x01, EPSILON) &&
           FuncClose<T>(mat(0, 2), x02, EPSILON) &&
           FuncClose<T>(mat(0, 3), x03, EPSILON) &&
           FuncClose<T>(mat(1, 0), x10, EPSILON) &&
           FuncClose<T>(mat(1, 1), x11, EPSILON) &&
           FuncClose<T>(mat(1, 2), x12, EPSILON) &&
           FuncClose<T>(mat(1, 3), x13, EPSILON) &&
           FuncClose<T>(mat(2, 0), x20, EPSILON) &&
           FuncClose<T>(mat(2, 1), x21, EPSILON) &&
           FuncClose<T>(mat(2, 2), x22, EPSILON) &&
           FuncClose<T>(mat(2, 3), x23, EPSILON) &&
           FuncClose<T>(mat(3, 0), x30, EPSILON) &&
           FuncClose<T>(mat(3, 1), x31, EPSILON) &&
           FuncClose<T>(mat(3, 2), x32, EPSILON) &&
           FuncClose<T>(mat(3, 3), x33, EPSILON);
}
// clang-format on

template <typename T>
auto FuncAllClose(const math::Vector4<T>& vec, T x0, T x1, T x2, T x3) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);
    return FuncClose<T>(vec[0], x0, EPSILON) &&
           FuncClose<T>(vec[1], x1, EPSILON) &&
           FuncClose<T>(vec[2], x2, EPSILON) &&
           FuncClose<T>(vec[3], x3, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix4 class (mat4_t) core operations", "[mat4_t][ops]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Matrix4 = math::Matrix4<T>;
    using Vector4 = math::Vector4<T>;

    constexpr T EPSILON = static_cast<T>(math::EPS);

    SECTION("Matrix comparison ==, !=") {
        // clang-format off
        Matrix4 m_1(1.0, 0.0, 0.0, 0.0,
                    0.0, 2.0, 0.0, 0.0,
                    0.0, 0.0, 3.0, 0.0,
                    0.0, 0.0, 0.0, 4.0);
        Matrix4 m_2(1.0, 2.0, 3.0, 4.0);
        Matrix4 m_3(static_cast<T>(1.1),
                    static_cast<T>(2.1),
                    static_cast<T>(3.1),
                    static_cast<T>(4.1));
        // clang-format on
        REQUIRE(m_1 == m_2);
        REQUIRE(m_2 != m_3);
        REQUIRE(m_3 != m_1);
    }

    // Generate first random matrix (2^4 cases possible values)
    auto x00 = GenRandomValue(T, 2);
    auto x01 = GenRandomValue(T, 1);
    auto x02 = GenRandomValue(T, 1);
    auto x03 = GenRandomValue(T, 1);

    auto x10 = GenRandomValue(T, 1);
    auto x11 = GenRandomValue(T, 2);
    auto x12 = GenRandomValue(T, 1);
    auto x13 = GenRandomValue(T, 1);

    auto x20 = GenRandomValue(T, 1);
    auto x21 = GenRandomValue(T, 1);
    auto x22 = GenRandomValue(T, 2);
    auto x23 = GenRandomValue(T, 1);

    auto x30 = GenRandomValue(T, 1);
    auto x31 = GenRandomValue(T, 1);
    auto x32 = GenRandomValue(T, 1);
    auto x33 = GenRandomValue(T, 2);

    // clang-format off
    Matrix4 m_a(x00, x01, x02, x03,
                x10, x11, x12, x13,
                x20, x21, x22, x23,
                x30, x31, x32, x33);
    // clang-format on

    // Generate second random matrix (2^8 cases possible values)
    auto y00 = GenRandomValue(T, 2);
    auto y10 = GenRandomValue(T, 1);
    auto y01 = GenRandomValue(T, 1);
    auto y11 = GenRandomValue(T, 1);

    auto y02 = GenRandomValue(T, 1);
    auto y12 = GenRandomValue(T, 2);
    auto y03 = GenRandomValue(T, 1);
    auto y13 = GenRandomValue(T, 1);

    auto y20 = GenRandomValue(T, 1);
    auto y30 = GenRandomValue(T, 1);
    auto y21 = GenRandomValue(T, 2);
    auto y31 = GenRandomValue(T, 1);

    auto y22 = GenRandomValue(T, 1);
    auto y32 = GenRandomValue(T, 1);
    auto y23 = GenRandomValue(T, 1);
    auto y33 = GenRandomValue(T, 2);

    // clang-format off
    Matrix4 m_b(y00, y01, y02, y03,
                y10, y11, y12, y13,
                y20, y21, y22, y23,
                y30, y31, y32, y33);
    // clang-format on

    SECTION("Matrix addition") {
        auto mat_sum = m_a + m_b;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_sum,
            x00 + y00, x01 + y01, x02 + y02, x03 + y03,
            x10 + y10, x11 + y11, x12 + y12, x13 + y13,
            x20 + y20, x21 + y21, x22 + y22, x23 + y23,
            x30 + y30, x31 + y31, x32 + y32, x33 + y33));
        // clang-format on
    }
    SECTION("Matrix substraction") {
        auto mat_sub = m_a - m_b;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_sub,
            x00 - y00, x01 - y01, x02 - y02, x03 - y03,
            x10 - y10, x11 - y11, x12 - y12, x13 - y13,
            x20 - y20, x21 - y21, x22 - y22, x23 - y23,
            x30 - y30, x31 - y31, x32 - y32, x33 - y33));
        // clang-format on
    }
    SECTION("Matrix-Scalar product") {
        auto scale_1 = GenRandomValue(T, 1);
        auto scale_2 = GenRandomValue(T, 1);

        auto mat_scaled_1 = static_cast<double>(scale_1) * m_a;
        auto mat_scaled_2 = m_b * static_cast<double>(scale_2);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_scaled_1,
            x00 * scale_1, x01 * scale_1, x02 * scale_1, x03 * scale_1,
            x10 * scale_1, x11 * scale_1, x12 * scale_1, x13 * scale_1,
            x20 * scale_1, x21 * scale_1, x22 * scale_1, x23 * scale_1,
            x30 * scale_1, x31 * scale_1, x32 * scale_1, x33 * scale_1));
        // clang-format on

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_scaled_2,
            y00 * scale_2, y01 * scale_2, y02 * scale_2, y03 * scale_2,
            y10 * scale_2, y11 * scale_2, y12 * scale_2, y13 * scale_2,
            y20 * scale_2, y21 * scale_2, y22 * scale_2, y23 * scale_2,
            y30 * scale_2, y31 * scale_2, y32 * scale_2, y33 * scale_2));
        // clang-format on
    }
    SECTION("Matrix-Matrix product") {
        // clang-format off
        // Fixed test-case
        Matrix4 m_1(-10.0, -6.0, -6.0,  2.0,
                    -8.0,  -6.0, -6.0, -5.0,
                     7.0, -10.0,  5.0,  7.0,
                    -2.0,  -9.0, -8.0,  6.0);

        Matrix4 m_2(7.0,  7.0, -6.0,  3.0,
                   -7.0,  1.0,  8.0,  5.0,
                    7.0, -2.0,  0.0, -4.0,
                   -9.0,  2.0,  5.0, -3.0);

        auto mat_mul = m_1 * m_2;
        REQUIRE(FuncAllClose<T>(mat_mul,
            -88.0, -60.0,  22.0, -42.0,
            -11.0, -60.0, -25.0, -15.0,
             91.0,  43.0, -87.0, -70.0,
            -61.0,   5.0, -30.0, -37.0));
        // clang-format on

        // Test-cases using the random matrices
        auto mat_mul_ab = m_a * m_b;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_mul_ab,
            // First row
            x00 * y00 + x01 * y10 + x02 * y20 + x03 * y30,
            x00 * y01 + x01 * y11 + x02 * y21 + x03 * y31,
            x00 * y02 + x01 * y12 + x02 * y22 + x03 * y32,
            x00 * y03 + x01 * y13 + x02 * y23 + x03 * y33,
            // Second row
            x10 * y00 + x11 * y10 + x12 * y20 + x13 * y30,
            x10 * y01 + x11 * y11 + x12 * y21 + x13 * y31,
            x10 * y02 + x11 * y12 + x12 * y22 + x13 * y32,
            x10 * y03 + x11 * y13 + x12 * y23 + x13 * y33,
            // Third row
            x20 * y00 + x21 * y10 + x22 * y20 + x23 * y30,
            x20 * y01 + x21 * y11 + x22 * y21 + x23 * y31,
            x20 * y02 + x21 * y12 + x22 * y22 + x23 * y32,
            x20 * y03 + x21 * y13 + x22 * y23 + x23 * y33,
            // Fourth row
            x30 * y00 + x31 * y10 + x32 * y20 + x33 * y30,
            x30 * y01 + x31 * y11 + x32 * y21 + x33 * y31,
            x30 * y02 + x31 * y12 + x32 * y22 + x33 * y32,
            x30 * y03 + x31 * y13 + x32 * y23 + x33 * y33));
        // clang-format on
        // @todo(wilbert): test with poorly conditioned matrices
    }

    SECTION("Matrix-Vector product") {
        // Fixed test-case
        // clang-format off
        Matrix4 mat(9.0, 5.0,  9.0,  8.0,
                   -9.0, 1.0, -6.0,  8.0,
                  -10.0, 1.0,  3.0,  6.0,
                   -8.0, 2.0, -2.0, -2.0);
        Vector4 vec(6.0, 7.0, -7.0, 5.0);
        // clang-format on
        auto mat_vec_mul_1 = mat * vec;
        REQUIRE(FuncAllClose<T>(mat_vec_mul_1, 66.0, 35.0, -44.0, -30.0));

        // Test-cases using the random matrices (reuse some random numbers)
        auto v0 = GenRandomValue(T, 2);
        auto v1 = GenRandomValue(T, 2);
        auto v2 = GenRandomValue(T, 2);
        auto v3 = GenRandomValue(T, 2);
        Vector4 v_a(v0, v1, v2, v3);
        auto mat_vec_mul_2 = m_a * v_a;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_vec_mul_2,
             x00 * v0 + x01 * v1 + x02 * v2 + x03 * v3,
             x10 * v0 + x11 * v1 + x12 * v2 + x13 * v3,
             x20 * v0 + x21 * v1 + x22 * v2 + x23 * v3,
             x30 * v0 + x31 * v1 + x32 * v2 + x33 * v3));
        // clang-format on
    }

    SECTION("Element-wise matrix product") {
        auto mat_elmwise = math::hadamard(m_a, m_b);
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_elmwise,
            x00 * y00, x01 * y01, x02 * y02, x03 * y03,
            x10 * y10, x11 * y11, x12 * y12, x13 * y13,
            x20 * y20, x21 * y21, x22 * y22, x23 * y23,
            x30 * y30, x31 * y31, x32 * y32, x33 * y33));
        // clang-format on
    }

    SECTION("Matrix transposition") {
        // clang-format off
        // NOLINTNEXTLINE
        REQUIRE(FuncAllClose<T>(math::transpose(m_a),
            x00, x10, x20, x30,
            x01, x11, x21, x31,
            x02, x12, x22, x32,
            x03, x13, x23, x33));
        // NOLINTNEXTLINE
        REQUIRE(FuncAllClose<T>(math::transpose(m_b),
            y00, y10, y20, y30,
            y01, y11, y21, y31,
            y02, y12, y22, y32,
            y03, y13, y23, y33));
        // clang-format on
    }

    SECTION("Matrix trace") {
        auto calc_trace_1 = math::trace(m_a);
        auto calc_trace_2 = math::trace(m_b);
        auto expected_trace_1 = x00 + x11 + x22 + x33;
        auto expected_trace_2 = y00 + y11 + y22 + y33;

        REQUIRE(FuncClose<T>(calc_trace_1, expected_trace_1, EPSILON));
        REQUIRE(FuncClose<T>(calc_trace_2, expected_trace_2, EPSILON));
    }

    SECTION("Matrix determinant") {
        // clang-format off
        auto mat = Matrix4(1.0, 1.0, 6.0, 7.0,
                           0.0, 8.0, 9.0, 7.0,
                           2.0, 7.0, 8.0, 9.0,
                           6.0, 3.0, 4.0, 0.0);
        // clang-format on
        auto calc_det = math::determinant(mat);
        auto expected_det = static_cast<T>(885);
        REQUIRE(FuncClose<T>(calc_det, expected_det, EPSILON));
    }

    SECTION("Matrix inverse") {
        // clang-format off
        auto mat = Matrix4(1.0, 1.0, 6.0, 7.0,
                           0.0, 8.0, 9.0, 7.0,
                           2.0, 7.0, 8.0, 9.0,
                           6.0, 3.0, 4.0, 0.0);
        // clang-format on
        auto inv_mat = math::inverse(mat);
        // clang-format off
        REQUIRE(FuncAllClose<T>(inv_mat,
            -0.019209, -0.174011,  0.150282,   0.119774,
            -0.232768, 0.0090395,  0.174011,  -0.019209,
              0.20339,  0.254237, -0.355932,  0.0847458,
           0.00451977,  -0.19435,  0.258757, -0.0870056));
        // clang-format on
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif
