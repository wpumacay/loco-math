#include <catch2/catch.hpp>
#include <math/vec2_t.hpp>

constexpr double RANGE_MIN = -1000.0;
constexpr double RANGE_MAX = 1000.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

// NOLINTNEXTLINE
#define GenRandomScaleValue(Type, Nsamples, Scale_min, Scale_max) \
    GENERATE(take(Nsamples, random(static_cast<Type>(Scale_min),  \
                                   static_cast<Type>(Scale_max))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
constexpr auto FuncCompareEqual(T xa, T ya, T xb, T yb, T eps) -> bool {
    return FuncClose<T>(xa, xb, eps) && FuncClose<T>(ya, yb, eps);
}

template <typename T>
auto FuncAllClose(const math::Vector2<T>& vec, T x, T y) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);
    return FuncClose<T>(vec.x(), x, EPSILON) &&
           FuncClose<T>(vec.y(), y, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector2 class (vec2_t) core Operations", "[vec2_t][ops]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Vector2 = math::Vector2<T>;

    constexpr T EPSILON = static_cast<T>(math::EPS);

    SECTION("Vector comparison ==, !=") {
        Vector2 v_1(static_cast<T>(1.0), static_cast<T>(2.0));  // NOLINT
        Vector2 v_2(static_cast<T>(1.0), static_cast<T>(2.0));  // NOLINT
        Vector2 v_3(static_cast<T>(1.1), static_cast<T>(2.1));  // NOLINT

        REQUIRE(v_1 == v_2);
        REQUIRE(v_2 != v_3);
        REQUIRE(v_3 != v_1);

        auto val_x_a = GenRandomValue(T, 4);
        auto val_y_a = GenRandomValue(T, 4);

        auto val_x_b = GenRandomValue(T, 4);
        auto val_y_b = GenRandomValue(T, 4);

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);

        auto equal_a_b_lib = (v_a == v_b);
        auto equal_a_b_man =
            FuncCompareEqual<T>(val_x_a, val_y_a, val_x_b, val_y_b, EPSILON);

        auto diff_a_b_lib = (v_a != v_b);
        auto diff_a_b_man = !equal_a_b_man;

        REQUIRE(equal_a_b_lib == equal_a_b_man);
        REQUIRE(diff_a_b_lib == diff_a_b_man);
    }

    SECTION("Vector addition") {
        auto val_x_a = GenRandomValue(T, 4);
        auto val_y_a = GenRandomValue(T, 4);

        auto val_x_b = GenRandomValue(T, 4);
        auto val_y_b = GenRandomValue(T, 4);

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);
        auto v_result = v_a + v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a + val_x_b,
                                val_y_a + val_y_b));
        // clang-format on
    }

    SECTION("Vector substraction") {
        auto val_x_a = GenRandomValue(T, 4);
        auto val_y_a = GenRandomValue(T, 4);

        auto val_x_b = GenRandomValue(T, 4);
        auto val_y_b = GenRandomValue(T, 4);

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);
        auto v_result = v_a - v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a - val_x_b,
                                val_y_a - val_y_b));
        // clang-format on
    }

    SECTION("Vector element-wise product") {
        auto val_x_a = GenRandomValue(T, 4);
        auto val_y_a = GenRandomValue(T, 4);

        auto val_x_b = GenRandomValue(T, 4);
        auto val_y_b = GenRandomValue(T, 4);

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);
        auto v_result = v_a * v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a * val_x_b,
                                val_y_a * val_y_b));
        // clang-format on
    }

    SECTION("Vector scale (by single scalar)") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        auto scale = GenRandomScaleValue(T, 10, -10.0, 10.0);

        Vector2 v(val_x, val_y);
        auto v_1 = static_cast<double>(scale) * v;
        auto v_2 = v * static_cast<double>(scale);

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_1,
                                val_x * scale,
                                val_y * scale));
        REQUIRE(FuncAllClose<T>(v_2,
                                val_x * scale,
                                val_y * scale));
        // clang-format on
    }

    SECTION("Vector length") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        Vector2 v(val_x, val_y);

        auto length_square = val_x * val_x + val_y * val_y;
        auto length = std::sqrt(length_square);

        auto v_length_square = math::squareNorm(v);
        auto v_length = math::norm(v);

        REQUIRE(FuncClose(v_length_square, length_square, EPSILON));
        REQUIRE(FuncClose(v_length, length, EPSILON));
    }

    SECTION("Vector normalization (in place)") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        Vector2 v(val_x, val_y);
        math::normalize_in_place(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;

        auto v_norm = math::norm(v);

        REQUIRE(FuncClose<T>(v_norm, 1.0, EPSILON));
        REQUIRE(FuncAllClose<T>(v, val_xnorm, val_ynorm));
    }

    SECTION("Vector normalization (out-of place)") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        Vector2 v(val_x, val_y);
        auto vn = math::normalize(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;

        auto vn_norm = math::norm(vn);

        REQUIRE(FuncClose<T>(vn_norm, 1.0, EPSILON));
        REQUIRE(FuncAllClose<T>(vn, val_xnorm, val_ynorm));
    }

    SECTION("Vector dot-product") {
        auto val_x_a = GenRandomValue(T, 4);
        auto val_y_a = GenRandomValue(T, 4);

        auto val_x_b = GenRandomValue(T, 4);
        auto val_y_b = GenRandomValue(T, 4);

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);

        auto dot = val_x_a * val_x_b + val_y_a * val_y_b;
        auto v_dot = math::dot(v_a, v_b);

        REQUIRE(FuncClose<T>(v_dot, dot, EPSILON));
    }

    SECTION("Vector additive inverse") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        Vector2 v(val_x, val_y);
        auto inv_v = -v;

        REQUIRE(FuncAllClose<T>(inv_v, -val_x, -val_y));
    }
}
