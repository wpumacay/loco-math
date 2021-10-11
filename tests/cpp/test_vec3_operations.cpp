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

    constexpr T EPSILON = tiny::math::EPS<T>;

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

    SECTION("Vector length") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT
        Vector3 v(val_x, val_y, val_z);

        auto length_square = val_x * val_x + val_y * val_y + val_z * val_z;
        auto length = std::sqrt(length_square);

        auto v_length_square = v.length_square();
        auto v_length = v.length();

        REQUIRE(std::abs(v_length_square - length_square) < EPSILON);
        REQUIRE(std::abs(v_length - length) < EPSILON);
    }

    SECTION("Vector dot-product") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_a = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_b = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);

        auto dot = val_x_a * val_x_b + val_y_a * val_y_b + val_z_a * val_z_b;
        auto v_dot = v_a.dot(v_b);

        REQUIRE(std::abs(v_dot - dot) < EPSILON);
    }

    SECTION("Vector cross-product") {
        // Checking Standard basis vectors: i, j, k
        {
            Vector3 v_i(1.0, 0.0, 0.0);
            Vector3 v_j(0.0, 1.0, 0.0);
            Vector3 v_k(0.0, 0.0, 1.0);

            auto v_ij = v_i.cross(v_j);
            auto v_jk = v_j.cross(v_k);
            auto v_ki = v_k.cross(v_i);

            // i x j = k
            REQUIRE(std::abs(v_ij.x() - 0.0) < EPSILON);
            REQUIRE(std::abs(v_ij.y() - 0.0) < EPSILON);
            REQUIRE(std::abs(v_ij.z() - 1.0) < EPSILON);

            // j x k = i
            REQUIRE(std::abs(v_jk.x() - 1.0) < EPSILON);
            REQUIRE(std::abs(v_jk.y() - 0.0) < EPSILON);
            REQUIRE(std::abs(v_jk.z() - 0.0) < EPSILON);

            // k x i = j
            REQUIRE(std::abs(v_ki.x() - 0.0) < EPSILON);
            REQUIRE(std::abs(v_ki.y() - 1.0) < EPSILON);
            REQUIRE(std::abs(v_ki.z() - 0.0) < EPSILON);
        }
    }
}
