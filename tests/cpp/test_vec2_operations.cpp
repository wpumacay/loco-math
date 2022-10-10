#include <catch2/catch.hpp>

#include <loco/math/vec2_t_impl.hpp>

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
constexpr auto FuncCompareEqual(T xa, T ya, T xb, T yb, T eps) -> bool {
    return FuncClose<T>(xa, xb, eps) && FuncClose<T>(ya, yb, eps);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector2 class (vec2_t) core Operations", "[vec2_t][ops]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Vector2 = loco::math::Vector2<T>;

    constexpr T EPSILON = static_cast<T>(loco::math::EPS);

    SECTION("Vector comparison ==, !=") {
        Vector2 v_1(static_cast<T>(1.0), static_cast<T>(2.0));  // NOLINT
        Vector2 v_2(static_cast<T>(1.0), static_cast<T>(2.0));  // NOLINT
        Vector2 v_3(static_cast<T>(1.1), static_cast<T>(2.1));  // NOLINT

        REQUIRE(v_1 == v_2);
        REQUIRE(v_2 != v_3);
        REQUIRE(v_3 != v_1);

        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 0.5, 0.25);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 1.0, 1.25);  // NOLINT

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
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 0.5, 0.25);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 1.0, 1.25);  // NOLINT

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);
        auto v_result = v_a + v_b;

        REQUIRE(std::abs(v_result.x() - (val_x_a + val_x_b)) < EPSILON);
        REQUIRE(std::abs(v_result.y() - (val_y_a + val_y_b)) < EPSILON);
    }

    SECTION("Vector substraction") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 0.5, 0.25);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 1.0, 1.25);  // NOLINT

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);
        auto v_result = v_a - v_b;

        REQUIRE(std::abs(v_result.x() - (val_x_a - val_x_b)) < EPSILON);
        REQUIRE(std::abs(v_result.y() - (val_y_a - val_y_b)) < EPSILON);
    }

    SECTION("Vector element-wise product") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 0.5, 0.25);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 1.0, 1.25);  // NOLINT

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);
        auto v_result = v_a * v_b;

        REQUIRE(std::abs(v_result.x() - (val_x_a * val_x_b)) < EPSILON);
        REQUIRE(std::abs(v_result.y() - (val_y_a * val_y_b)) < EPSILON);
    }

    SECTION("Vector scale (by single scalar)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);     // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);     // NOLINT
        auto scale = GENERATE(as<T>{}, 0.25, 0.50, 0.75, 1.0);  // NOLINT

        Vector2 v(val_x, val_y);
        auto v_1 = static_cast<double>(scale) * v;
        auto v_2 = v * static_cast<double>(scale);

        REQUIRE(std::abs(v_1.x() - (val_x * scale)) < EPSILON);
        REQUIRE(std::abs(v_1.y() - (val_y * scale)) < EPSILON);

        REQUIRE(std::abs(v_2.x() - (val_x * scale)) < EPSILON);
        REQUIRE(std::abs(v_2.y() - (val_y * scale)) < EPSILON);
    }

    SECTION("Vector length") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        Vector2 v(val_x, val_y);

        auto length_square = val_x * val_x + val_y * val_y;
        auto length = std::sqrt(length_square);

        auto v_length_square = loco::math::squareNorm(v);
        auto v_length = loco::math::norm(v);

        REQUIRE(std::abs(v_length_square - length_square) < EPSILON);
        REQUIRE(std::abs(v_length - length) < EPSILON);
    }

    SECTION("Vector normalization (in place)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        Vector2 v(val_x, val_y);
        loco::math::normalize_in_place(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;

        auto v_norm = loco::math::norm(v);

        REQUIRE(std::abs(v_norm - static_cast<T>(1.0)) < EPSILON);
        REQUIRE(std::abs(v.x() - val_xnorm) < EPSILON);
        REQUIRE(std::abs(v.y() - val_ynorm) < EPSILON);
    }

    SECTION("Vector normalization (out-of place)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        Vector2 v(val_x, val_y);
        auto vn = loco::math::normalize(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;

        auto vn_norm = loco::math::norm(vn);

        REQUIRE(std::abs(vn_norm - static_cast<T>(1.0)) < EPSILON);
        REQUIRE(std::abs(vn.x() - val_xnorm) < EPSILON);
        REQUIRE(std::abs(vn.y() - val_ynorm) < EPSILON);
    }

    SECTION("Vector dot-product") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT

        Vector2 v_a(val_x_a, val_y_a);
        Vector2 v_b(val_x_b, val_y_b);

        auto dot = val_x_a * val_x_b + val_y_a * val_y_b;
        auto v_dot = loco::math::dot(v_a, v_b);

        REQUIRE(std::abs(v_dot - dot) < EPSILON);
    }
}
