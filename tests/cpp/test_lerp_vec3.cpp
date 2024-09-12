#include <catch2/catch.hpp>
#include <math/vec3_t.hpp>

#include "./common_math_helpers.hpp"
#include "./common_math_generators.hpp"

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Lerp function for vec3_t", "[vec3_t][lerp]",
                   ::math::float32_t, ::math::float64_t) {
    using T = TestType;
    using Vector3 = ::math::Vector3<T>;

    constexpr T EPSILON = static_cast<T>(1e-6);

    SECTION("Basic cases") {
        Vector3 v_0(0.0, 0.0, 0.0);
        Vector3 v_1(1.0, 0.0, 0.0);
        Vector3 v_2(0.0, 1.0, 0.0);
        Vector3 v_3(0.0, 0.0, 1.0);
        Vector3 v_4(1.0, 1.0, 1.0);

        auto v_a = ::math::lerp<T>(v_0, v_1, 0.5);
        auto v_b = ::math::lerp<T>(v_0, v_2, 0.5);
        auto v_c = ::math::lerp<T>(v_0, v_3, 0.5);
        auto v_d = ::math::lerp<T>(v_0, v_4, 0.5);

        REQUIRE(::math::func_all_close<T>(v_a, 0.5, 0.0, 0.0, EPSILON));
        REQUIRE(::math::func_all_close<T>(v_b, 0.0, 0.5, 0.0, EPSILON));
        REQUIRE(::math::func_all_close<T>(v_c, 0.0, 0.0, 0.5, EPSILON));
        REQUIRE(::math::func_all_close<T>(v_d, 0.5, 0.5, 0.5, EPSILON));
    }

    SECTION("Edge case - alpha = 0") {
        Vector3 v_0(1.0, 2.0, 3.0);
        Vector3 v_1(4.0, 5.0, 6.0);

        auto v_a = ::math::lerp<T>(v_0, v_1, 0.0);
        REQUIRE(::math::func_all_close<T>(v_a, 1.0, 2.0, 3.0, EPSILON));

        auto v_b = ::math::lerp<T>(v_1, v_0, 0.0);
        REQUIRE(::math::func_all_close<T>(v_b, 4.0, 5.0, 6.0, EPSILON));
    }

    SECTION("Edge case - alpha = 1") {
        Vector3 v_0(1.0, 2.0, 3.0);
        Vector3 v_1(4.0, 5.0, 6.0);

        auto v_a = ::math::lerp<T>(v_0, v_1, 1.0);
        REQUIRE(::math::func_all_close<T>(v_a, 4.0, 5.0, 6.0, EPSILON));

        auto v_b = ::math::lerp<T>(v_1, v_0, 1.0);
        REQUIRE(::math::func_all_close<T>(v_b, 1.0, 2.0, 3.0, EPSILON));
    }

    SECTION("Edge case - alpha outside of [0, 1]") {
        Vector3 v_0(0.0, 0.0, 0.0);
        Vector3 v_1(1.0, 2.0, 3.0);

        auto v_a = ::math::lerp<T>(v_0, v_1, -0.5);
        REQUIRE(::math::func_all_close<T>(v_a, -0.5, -1.0, -1.5, EPSILON));

        auto v_b = ::math::lerp<T>(v_0, v_1, 1.5);
        REQUIRE(::math::func_all_close<T>(v_b, 1.5, 3.0, 4.5, EPSILON));
    }
}
