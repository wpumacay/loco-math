#include <catch2/catch.hpp>
#include <cmath>
#include <tinymath/vec4_t.hpp>

/*
 * @todo(wilbert): replace GENERATE of fixed values with random values + seed
 * @todo(wilbert): add IF-THEN sections to use == and != operators instead
 */

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector4 class (vec4_t) core Operations", "[vec4_t][ops]",
                   tiny::math::float32_t, tiny::math::float64_t) {
    using T = TestType;
    using Vector4 = tiny::math::Vector4<T>;

    constexpr TestType EPSILON = tiny::math::EPS<T>;

    SECTION("Vector addition") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);   // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);   // NOLINT
        auto val_z_a = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);   // NOLINT
        auto val_w_a = GENERATE(as<T>{}, 4.0, 6.0, 8.0, 10.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);   // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);   // NOLINT
        auto val_z_b = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);   // NOLINT
        auto val_w_b = GENERATE(as<T>{}, 4.0, 6.0, 8.0, 10.0);  // NOLINT

        Vector4 v_a(val_x_a, val_y_a, val_z_a, val_w_a);
        Vector4 v_b(val_x_b, val_y_b, val_z_b, val_w_b);
        auto v_result = v_a + v_b;

        REQUIRE(std::abs(v_result.x() - (val_x_a + val_x_b)) < EPSILON);
        REQUIRE(std::abs(v_result.y() - (val_y_a + val_y_b)) < EPSILON);
        REQUIRE(std::abs(v_result.z() - (val_z_a + val_z_b)) < EPSILON);
        REQUIRE(std::abs(v_result.w() - (val_w_a + val_w_b)) < EPSILON);
    }

    SECTION("Vector substraction") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);   // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);   // NOLINT
        auto val_z_a = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);   // NOLINT
        auto val_w_a = GENERATE(as<T>{}, 4.0, 6.0, 8.0, 10.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);   // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);   // NOLINT
        auto val_z_b = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);   // NOLINT
        auto val_w_b = GENERATE(as<T>{}, 4.0, 6.0, 8.0, 10.0);  // NOLINT

        Vector4 v_a(val_x_a, val_y_a, val_z_a, val_w_a);
        Vector4 v_b(val_x_b, val_y_b, val_z_b, val_w_b);
        auto v_result = v_a - v_b;

        REQUIRE(std::abs(v_result.x() - (val_x_a - val_x_b)) < EPSILON);
        REQUIRE(std::abs(v_result.y() - (val_y_a - val_y_b)) < EPSILON);
        REQUIRE(std::abs(v_result.z() - (val_z_a - val_z_b)) < EPSILON);
        REQUIRE(std::abs(v_result.w() - (val_w_a - val_w_b)) < EPSILON);
    }

    SECTION("Vector scale (by single scalar)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);     // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);     // NOLINT
        auto val_z = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);     // NOLINT
        auto val_w = GENERATE(as<T>{}, 4.0, 6.0, 8.0, 10.0);    // NOLINT
        auto scale = GENERATE(as<T>{}, 0.25, 0.50, 0.75, 1.0);  // NOLINT

        Vector4 v(val_x, val_y, val_z, val_w);
        auto v_1 = scale * v;
        auto v_2 = v * scale;

        REQUIRE(std::abs(v_1.x() - (val_x * scale)) < EPSILON);
        REQUIRE(std::abs(v_1.y() - (val_y * scale)) < EPSILON);
        REQUIRE(std::abs(v_1.z() - (val_z * scale)) < EPSILON);
        REQUIRE(std::abs(v_1.w() - (val_w * scale)) < EPSILON);

        REQUIRE(std::abs(v_2.x() - (val_x * scale)) < EPSILON);
        REQUIRE(std::abs(v_2.y() - (val_y * scale)) < EPSILON);
        REQUIRE(std::abs(v_2.z() - (val_z * scale)) < EPSILON);
        REQUIRE(std::abs(v_2.w() - (val_w * scale)) < EPSILON);
    }

    SECTION("Vector dot-product") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);   // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);   // NOLINT
        auto val_z_a = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);   // NOLINT
        auto val_w_a = GENERATE(as<T>{}, 4.0, 6.0, 8.0, 10.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);   // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);   // NOLINT
        auto val_z_b = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);   // NOLINT
        auto val_w_b = GENERATE(as<T>{}, 4.0, 6.0, 8.0, 10.0);  // NOLINT

        Vector4 v_a(val_x_a, val_y_a, val_z_a, val_w_a);
        Vector4 v_b(val_x_b, val_y_b, val_z_b, val_w_b);

        auto dot = val_x_a * val_x_b + val_y_a * val_y_b + val_z_a * val_z_b +
                   val_w_a * val_w_b;
        auto v_dot = v_a.dot(v_b);

        REQUIRE(std::abs(v_dot - dot) < EPSILON);
    }
}
