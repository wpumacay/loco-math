#include <catch2/catch.hpp>
#include <math/vec2_t.hpp>

#include "./common_math_helpers.hpp"
#include "./common_math_generators.hpp"

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Lerp function for vec2_t", "[vec2_t][lerp]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Vector2 = ::math::Vector2<T>;

    constexpr T EPSILON = static_cast<T>(1e-6);

    SECTION("Basic cases") {
        Vector2 v_0(0.0, 0.0);
        Vector2 v_1(1.0, 0.0);
        Vector2 v_2(0.0, 1.0);
        Vector2 v_3(1.0, 1.0);

        auto v_a = ::math::lerp<T>(v_0, v_1, 0.5);
        auto v_b = ::math::lerp<T>(v_0, v_2, 0.5);
        auto v_c = ::math::lerp<T>(v_0, v_3, 0.5);

        REQUIRE(::math::func_all_close<T>(v_a, 0.5, 0.0, EPSILON));
        REQUIRE(::math::func_all_close<T>(v_b, 0.0, 0.5, EPSILON));
        REQUIRE(::math::func_all_close<T>(v_c, 0.5, 0.5, EPSILON));
    }

    SECTION("Edge case - alpha = 0") {
        Vector2 v_0(1.0, 2.0);
        Vector2 v_1(3.0, 4.0);

        auto v_a = ::math::lerp<T>(v_0, v_1, 0.0);
        REQUIRE(::math::func_all_close<T>(v_a, 1.0, 2.0, EPSILON));

        auto v_b = ::math::lerp<T>(v_1, v_0, 0.0);
        REQUIRE(::math::func_all_close<T>(v_b, 3.0, 4.0, EPSILON));
    }

    SECTION("Edge case - alpha = 1") {
        Vector2 v_0(1.0, 2.0);
        Vector2 v_1(3.0, 4.0);

        auto v_a = ::math::lerp<T>(v_0, v_1, 1.0);
        REQUIRE(::math::func_all_close<T>(v_a, 3.0, 4.0, EPSILON));

        auto v_b = ::math::lerp<T>(v_1, v_0, 1.0);
        REQUIRE(::math::func_all_close<T>(v_b, 1.0, 2.0, EPSILON));
    }

    SECTION("Edge case - alpha outside of [0, 1]") {
        Vector2 v_0(0.0, 0.0);
        Vector2 v_1(1.0, 2.0);

        auto v_a = ::math::lerp<T>(v_0, v_1, -0.5);
        REQUIRE(::math::func_all_close<T>(v_a, -0.5, -1.0, EPSILON));

        auto v_b = ::math::lerp<T>(v_0, v_1, 1.5);
        REQUIRE(::math::func_all_close<T>(v_b, 1.5, 3.0, EPSILON));
    }
}
