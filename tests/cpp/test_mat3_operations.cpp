#include <catch2/catch.hpp>
#include <loco/math/mat3_t_impl.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4305)
#endif

static constexpr double RANGE_MIN = -10.0;
static constexpr double RANGE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))));

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

template <typename T>
auto FuncAllClose(const loco::math::Vector3<T>& vec, T x0, T x1, T x2) -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);

    return FuncClose<T>(vec[0], x0, EPSILON) &&
           FuncClose<T>(vec[1], x1, EPSILON) &&
           FuncClose<T>(vec[2], x2, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix3 class (mat3_t) core operations", "[mat3_t][ops]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Matrix3 = loco::math::Matrix3<T>;
    using Vector3 = loco::math::Vector3<T>;

    constexpr T EPSILON = static_cast<T>(loco::math::EPS);

    SECTION("Matrix comparison ==, !=") {
        // clang-format off
        Matrix3 m_1(1.0, 0.0, 0.0,
                    0.0, 2.0, 0.0,
                    0.0, 0.0, 3.0);
        Matrix3 m_2(1.0, 2.0, 3.0);
        Matrix3 m_3(static_cast<T>(1.1),
                    static_cast<T>(2.1),
                    static_cast<T>(3.1));
        // clang-format on
        REQUIRE(m_1 == m_2);
        REQUIRE(m_2 != m_3);
        REQUIRE(m_3 != m_1);
    }

    // Generate first random matrix (2^8 cases possible values)
    auto x00 = GenRandomValue(T, 2);
    auto x01 = GenRandomValue(T, 2);
    auto x02 = GenRandomValue(T, 2);

    auto x10 = GenRandomValue(T, 2);
    auto x11 = GenRandomValue(T, 2);
    auto x12 = GenRandomValue(T, 2);

    auto x20 = GenRandomValue(T, 2);
    auto x21 = GenRandomValue(T, 2);
    auto x22 = GenRandomValue(T, 1);

    // clang-format off
    Matrix3 m_a(x00, x01, x02,
                x10, x11, x12,
                x20, x21, x22);
    // clang-format on

    // Generate second random matrix (2^8 cases possible values)
    auto y00 = GenRandomValue(T, 2);
    auto y01 = GenRandomValue(T, 2);
    auto y02 = GenRandomValue(T, 2);

    auto y10 = GenRandomValue(T, 2);
    auto y11 = GenRandomValue(T, 2);
    auto y12 = GenRandomValue(T, 2);

    auto y20 = GenRandomValue(T, 2);
    auto y21 = GenRandomValue(T, 2);
    auto y22 = GenRandomValue(T, 1);

    // clang-format off
    Matrix3 m_b(y00, y01, y02,
                y10, y11, y12,
                y20, y21, y22);
    // clang-format on

    SECTION("Matrix addition") {
        auto mat_sum = m_a + m_b;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_sum,
                x00 + y00, x01 + y01, x02 + y02,
                x10 + y10, x11 + y11, x12 + y12,
                x20 + y20, x21 + y21, x22 + y22));
        // clang-format on
    }
    SECTION("Matrix substraction") {
        auto mat_sub = m_a - m_b;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_sub,
                x00 - y00, x01 - y01, x02 - y02,
                x10 - y10, x11 - y11, x12 - y12,
                x20 - y20, x21 - y21, x22 - y22));
        // clang-format on
    }
    SECTION("Matrix-Scalar product") {
        auto scale_1 = GenRandomValue(T, 1);
        auto scale_2 = GenRandomValue(T, 1);

        auto mat_scaled_1 = static_cast<double>(scale_1) * m_a;
        auto mat_scaled_2 = m_b * static_cast<double>(scale_2);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_scaled_1,
                x00 * scale_1, x01 * scale_1, x02 * scale_1,
                x10 * scale_1, x11 * scale_1, x12 * scale_1,
                x20 * scale_1, x21 * scale_1, x22 * scale_1));
        // clang-format on

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_scaled_2,
                y00 * scale_2, y01 * scale_2, y02 * scale_2,
                y10 * scale_2, y11 * scale_2, y12 * scale_2,
                y20 * scale_2, y21 * scale_2, y22 * scale_2));
        // clang-format on
    }
    SECTION("Matrix-Matrix product") {
        // clang-format off
        // Fixed test-case
        Matrix3 m_1(-10.0, -10.0, -2.0,
                     -8.0,  -8.0,  1.0,
                      5.0,  -7.0, -3.0);

        Matrix3 m_2(-1.0, -1.0,  8.0,
                     6.0,  6.0,  0.0,
                    -8.0,  2.0, -9.0);

        auto mat_mul = m_1 * m_2;
        REQUIRE(FuncAllClose<T>(mat_mul,
                -34.0, -54.0, -62.0,
                -48.0, -38.0, -73.0,
                -23.0, -53.0,  67.0));
        // clang-format on

        // Test-cases using the random matrices
        auto mat_mul_ab = m_a * m_b;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_mul_ab,
                // First row
                x00 * y00 + x01 * y10 + x02 * y20,
                x00 * y01 + x01 * y11 + x02 * y21,
                x00 * y02 + x01 * y12 + x02 * y22,
                // Second row
                x10 * y00 + x11 * y10 + x12 * y20,
                x10 * y01 + x11 * y11 + x12 * y21,
                x10 * y02 + x11 * y12 + x12 * y22,
                // Third row
                x20 * y00 + x21 * y10 + x22 * y20,
                x20 * y01 + x21 * y11 + x22 * y21,
                x20 * y02 + x21 * y12 + x22 * y22));
        // clang-format on
        // @todo(wilbert): test with poorly conditioned matrices
    }

    SECTION("Matrix-Vector product") {
        // Fixed test-case
        // clang-format off
               Matrix3 mat(1.0, -4.0, 1.0,
                          -6.0, -7.0, 9.0,
                          -4.0,  6.0, 0.0);
               Vector3 vec(2.0, 7.0, 6.0);
        // clang-format on
        auto mat_vec_mul_1 = mat * vec;
        REQUIRE(FuncAllClose<T>(mat_vec_mul_1, -20.0, -7.0, 34.0));
        // Test-cases using the random matrices (reuse some randomnumbers)
        auto v0 = GenRandomValue(T, 2);
        auto v1 = GenRandomValue(T, 2);
        auto v2 = GenRandomValue(T, 2);
        Vector3 v_a(v0, v1, v2);
        auto mat_vec_mul_2 = m_a * v_a;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_vec_mul_2,
                x00 * v0 + x01 * v1 + x02 * v2,
                x10 * v0 + x11 * v1 + x12 * v2,
                x20 * v0 + x21 * v1 + x22 * v2));
        // clang-format on
    }

    SECTION("Element-wise matrix product") {
        auto mat_elmwise = loco::math::hadamard(m_a, m_b);
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_elmwise,
                x00 * y00, x01 * y01, x02 * y02,
                x10 * y10, x11 * y11, x12 * y12,
                x20 * y20, x21 * y21, x22 * y22));
        // clang-format on
    }

    SECTION("Matrix transposition") {
        // clang-format off
        // NOLINTNEXTLINE
        FuncAllClose<T>(loco::math::transpose(m_a),
            x00, x10, x20,
            x01, x11, x21,
            x02, x12, x22);
        // NOLINTNEXTLINE
        FuncAllClose<T>(loco::math::transpose(m_b),
            y00, y10, y20,
            y01, y11, y21,
            y02, y12, y22);
        // clang-format on
    }

    SECTION("Matrix trace") {
        auto calc_trace_1 = loco::math::trace(m_a);
        auto calc_trace_2 = loco::math::trace(m_b);
        auto expected_trace_1 = x00 + x11 + x22;
        auto expected_trace_2 = y00 + y11 + y22;

        REQUIRE(FuncClose<T>(calc_trace_1, expected_trace_1, EPSILON));
        REQUIRE(FuncClose<T>(calc_trace_2, expected_trace_2, EPSILON));
    }

    SECTION("Matrix determinant") {
        // clang-format off
        auto mat = Matrix3(6.0, 5.0, 9.0,
                           0.0, 2.0, 0.0,
                           5.0, 3.0, 6.0);
        // clang-format on
        auto calc_det = loco::math::determinant(mat);
        auto expected_det = static_cast<T>(-18.0);
        REQUIRE(FuncClose<T>(calc_det, expected_det, EPSILON));
    }

    SECTION("Matrix inverse") {
        // clang-format off
        auto mat = Matrix3(6.0, 5.0, 9.0,
                           0.0, 2.0, 0.0,
                           5.0, 3.0, 6.0);
        // clang-format on
        auto inv_mat = loco::math::inverse(mat);
        // clang-format off
        REQUIRE(FuncAllClose<T>(inv_mat,
            -0.666667,  0.166667,       1.0,
                  0.0,       0.5,       0.0,
             0.555556, -0.388889, -0.666667));
        // clang-format on
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif
