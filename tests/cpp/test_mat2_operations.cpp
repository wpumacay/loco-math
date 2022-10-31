#include <catch2/catch.hpp>
#include <loco/math/mat2_t_impl.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#endif

static constexpr double RANGE_MIN = -10.0;
static constexpr double RANGE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
auto FuncAllClose(const loco::math::Matrix2<T>& mat, T x00, T x01, T x10, T x11)
    -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    return FuncClose(mat(0, 0), x00, EPSILON) &&
           FuncClose(mat(0, 1), x01, EPSILON) &&
           FuncClose(mat(1, 0), x10, EPSILON) &&
           FuncClose(mat(1, 1), x11, EPSILON);
}

template <typename T>
auto FuncAllClose(const loco::math::Vector2<T>& vec, T x, T y) -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    return FuncClose(vec.x(), x, EPSILON) && FuncClose(vec.y(), y, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix2 class (mat2_t) core operations", "[mat2_t][ops]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Matrix2 = loco::math::Matrix2<T>;
    using Vector2 = loco::math::Vector2<T>;
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);

    SECTION("Matrix comparison ==, !=") {
        Matrix2 m_1(1.0, 0.0, 0.0, 2.0);
        Matrix2 m_2(1.0, 2.0);
        Matrix2 m_3(static_cast<T>(1.1), static_cast<T>(2.1));

        REQUIRE(m_1 == m_2);
        REQUIRE(m_2 != m_3);
        REQUIRE(m_3 != m_1);
    }

    // Generate first random matrix (2^4 cases possible values)
    auto x00 = GenRandomValue(T, 2);
    auto x01 = GenRandomValue(T, 2);
    auto x10 = GenRandomValue(T, 2);
    auto x11 = GenRandomValue(T, 2);

    Matrix2 m_a(x00, x01, x10, x11);

    // Generate second random matrix (2^4 cases possible values)
    auto y00 = GenRandomValue(T, 2);
    auto y01 = GenRandomValue(T, 2);
    auto y10 = GenRandomValue(T, 2);
    auto y11 = GenRandomValue(T, 2);

    Matrix2 m_b(y00, y01, y10, y11);

    SECTION("Matrix addition") {
        auto mat_sum = m_a + m_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_sum,
                        x00 + y00, x01 + y01,
                        x10 + y10, x11 + y11));
        // clang-format on
    }
    SECTION("Matrix substraction") {
        auto mat_sub = m_a - m_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_sub,
                        x00 - y00, x01 - y01,
                        x10 - y10, x11 - y11));
        // clang-format on
    }
    SECTION("Matrix-Scalar product") {
        auto scale_1 = GenRandomValue(T, 4);
        auto scale_2 = GenRandomValue(T, 4);

        auto mat_scaled_1 = static_cast<double>(scale_1) * m_a;
        auto mat_scaled_2 = m_b * static_cast<double>(scale_2);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_scaled_1,
                        x00 * scale_1, x01 * scale_1,
                        x10 * scale_1, x11 * scale_1));

        REQUIRE(FuncAllClose<T>(mat_scaled_2,
                        y00 * scale_2, y01 * scale_2,
                        y10 * scale_2, y11 * scale_2));
        // clang-format on
    }
    SECTION("Matrix-Matrix product") {
        // Fixed test-case
        Matrix2 m_1(-6.0, 6.0, -8.0, -1.0);
        Matrix2 m_2(6.0, 4.0, 2.0, 1.0);

        auto mat_mul = m_1 * m_2;
        REQUIRE(FuncAllClose<T>(mat_mul, -24.0, -18.0, -50.0, -33.0));

        // Test-cases using the random matrices
        auto mat_mul_ab = m_a * m_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_mul_ab,
                        x00 * y00 + x01 * y10, x00 * y01 + x01 * y11,
                        x10 * y00 + x11 * y10, x10 * y01 + x11 * y11));
        // clang-format on
    }

    SECTION("Matrix-Vector product") {
        // Fixed test-case
        Matrix2 mat(9.0, 8.0, 6.0, -4.0);
        Vector2 vec(6.0, 7.0);
        auto mat_vec_mul_1 = mat * vec;
        REQUIRE(FuncAllClose<T>(mat_vec_mul_1, 110.0, 8.0));

        // Test-cases using the random matrices
        auto v0 = GenRandomValue(T, 4);
        auto v1 = GenRandomValue(T, 4);
        Vector2 v_a(v0, v1);
        auto mat_vec_mul_2 = m_a * v_a;

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_vec_mul_2,
                        x00 * v0 + x01 * v1,
                        x10 * v0 + x11 * v1));
        // clang-format on
    }

    SECTION("Element-wise matrix product") {
        auto mat_ewise = loco::math::hadamard(m_a, m_b);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_ewise,
                        x00 * y00, x01 * y01,
                        x10 * y10, x11 * y11));
        // clang-format on
    }

    SECTION("Matrix transposition") {
        // clang-format off
        REQUIRE(FuncAllClose<T>(loco::math::transpose(m_a),
                        x00, x10,
                        x01, x11));
        REQUIRE(FuncAllClose<T>(loco::math::transpose(m_b),
                        y00, y10,
                        y01, y11));
        // clang-format on
    }

    SECTION("Matrix trace") {
        auto calc_trace_1 = loco::math::trace(m_a);
        auto calc_trace_2 = loco::math::trace(m_b);
        auto expected_trace_1 = x00 + x11;
        auto expected_trace_2 = y00 + y11;

        REQUIRE(FuncClose<T>(calc_trace_1, expected_trace_1, EPSILON));
        REQUIRE(FuncClose<T>(calc_trace_2, expected_trace_2, EPSILON));
    }

    SECTION("Matrix determinant") {
        auto mat = Matrix2(5.0, 5.0, 4.0, 8.0);
        auto calc_det = loco::math::determinant(mat);
        auto expected_det = static_cast<T>(20.0);

        REQUIRE(FuncClose<T>(calc_det, expected_det, EPSILON));
    }

    SECTION("Matrix inverse") {
        auto mat = Matrix2(5.0, 5.0, 4.0, 8.0);
        auto inv_mat = loco::math::inverse(mat);
        // clang-format off
        REQUIRE(FuncAllClose<T>(inv_mat,
                        0.4, -0.25,   // NOLINT
                        -0.2, 0.25)); // NOLINT
        // clang-format on
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
