#include <catch2/catch.hpp>
#include <cmath>
#include <tinymath/vec3_t.hpp>

/*
 * @todo(wilbert): replace GENERATE of fixed values with random values + seed
 */

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector3 class (vec3_t) core Operations", "[vec3_t][ops]",
                   tiny::math::float32_t, tiny::math::float64_t) {
    using T = TestType;
    using Vector3 = tiny::math::Vector3<T>;

    constexpr TestType EPSILON = tiny::math::EPS<T>;

    SECTION("Vector addition") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_a = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_b = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);
        auto v_result = v_a + v_b;

        REQUIRE(std::abs(v_result.x() - (val_x_a + val_x_b)) < EPSILON);
        REQUIRE(std::abs(v_result.y() - (val_y_a + val_y_b)) < EPSILON);
        REQUIRE(std::abs(v_result.z() - (val_z_a + val_z_b)) < EPSILON);
    }

    SECTION("Vector substraction") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_a = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_b = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);
        auto v_result = v_a - v_b;

        REQUIRE(std::abs(v_result.x() - (val_x_a - val_x_b)) < EPSILON);
        REQUIRE(std::abs(v_result.y() - (val_y_a - val_y_b)) < EPSILON);
        REQUIRE(std::abs(v_result.z() - (val_z_a - val_z_b)) < EPSILON);
    }

    SECTION("Vector scale (by single scalar)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);     // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);     // NOLINT
        auto val_z = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);     // NOLINT
        auto scale = GENERATE(as<T>{}, 0.25, 0.50, 0.75, 1.0);  // NOLINT

        Vector3 v(val_x, val_y, val_z);
        auto v_1 = scale * v;
        auto v_2 = v * scale;

        REQUIRE(std::abs(v_1.x() - (val_x * scale)) < EPSILON);
        REQUIRE(std::abs(v_1.y() - (val_y * scale)) < EPSILON);
        REQUIRE(std::abs(v_1.z() - (val_z * scale)) < EPSILON);

        REQUIRE(std::abs(v_2.x() - (val_x * scale)) < EPSILON);
        REQUIRE(std::abs(v_2.y() - (val_y * scale)) < EPSILON);
        REQUIRE(std::abs(v_2.z() - (val_z * scale)) < EPSILON);
    }
}
