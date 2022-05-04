#include <catch2/catch.hpp>
#include <loco/math/all.hpp>

/*
 * @todo(wilbert): replace GENERATE of fixed values with random values + seed
 * @todo(wilbert): add IF-THEN sections to use == and != operators instead
 */

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
constexpr auto FuncCompareEqual(T xa, T ya, T za, T xb, T yb, T zb, T eps)
    -> bool {
    return FuncClose<T>(xa, xb, eps) && FuncClose<T>(ya, yb, eps) &&
           FuncClose<T>(za, zb, eps);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector3 class (vec3_t) core Operations", "[vec3_t][ops]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Vector3 = loco::math::Vector3<T>;

    constexpr T EPSILON = static_cast<T>(loco::math::EPS);

    SECTION("Vector comparison ==, !=") {
        Vector3 v_1(1.0, 2.0, 3.0);  // NOLINT
        Vector3 v_2(1.0, 2.0, 3.0);  // NOLINT
        Vector3 v_3(1.1, 2.1, 3.1);  // NOLINT

        REQUIRE(v_1 == v_2);
        REQUIRE(v_2 != v_3);
        REQUIRE(v_3 != v_1);

        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_a = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_b = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);

        auto equal_a_b_lib = (v_a == v_b);
        auto equal_a_b_man = FuncCompareEqual<T>(
            val_x_a, val_y_a, val_z_a, val_x_b, val_y_b, val_z_b, EPSILON);

        auto diff_a_b_lib = (v_a != v_b);
        auto diff_a_b_man = !equal_a_b_man;

        REQUIRE(equal_a_b_lib == equal_a_b_man);
        REQUIRE(diff_a_b_lib == diff_a_b_man);
    }

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

    SECTION("Vector element-wise product") {
        auto val_x_a = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_a = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_a = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        auto val_x_b = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y_b = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z_b = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);
        auto v_result = v_a * v_b;

        REQUIRE(std::abs(v_result.x() - (val_x_a * val_x_b)) < EPSILON);
        REQUIRE(std::abs(v_result.y() - (val_y_a * val_y_b)) < EPSILON);
        REQUIRE(std::abs(v_result.z() - (val_z_a * val_z_b)) < EPSILON);
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

        auto v_length_square = loco::math::squareNorm(v);
        auto v_length = loco::math::norm(v);

        REQUIRE(std::abs(v_length_square - length_square) < EPSILON);
        REQUIRE(std::abs(v_length - length) < EPSILON);
    }

    SECTION("Vector normalization (in place)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT
        Vector3 v(val_x, val_y, val_z);
        loco::math::normalize_in_place(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y + val_z * val_z);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;

        auto v_norm = loco::math::norm(v);

        REQUIRE(std::abs(v_norm - 1.0) < EPSILON);
        REQUIRE(std::abs(v.x() - val_xnorm) < EPSILON);
        REQUIRE(std::abs(v.y() - val_ynorm) < EPSILON);
        REQUIRE(std::abs(v.z() - val_znorm) < EPSILON);
    }

    SECTION("Vector normalization (out-of place)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT
        Vector3 v(val_x, val_y, val_z);
        auto vn = loco::math::normalize(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y + val_z * val_z);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;

        auto vn_norm = loco::math::norm(vn);

        REQUIRE(std::abs(vn_norm - 1.0) < EPSILON);
        REQUIRE(std::abs(vn.x() - val_xnorm) < EPSILON);
        REQUIRE(std::abs(vn.y() - val_ynorm) < EPSILON);
        REQUIRE(std::abs(vn.z() - val_znorm) < EPSILON);
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
        auto v_dot = loco::math::dot(v_a, v_b);

        REQUIRE(std::abs(v_dot - dot) < EPSILON);
    }

    SECTION("Vector cross-product") {
        // Checking standard basis vectors: i, j, k
        {
            Vector3 v_i(1.0, 0.0, 0.0);
            Vector3 v_j(0.0, 1.0, 0.0);
            Vector3 v_k(0.0, 0.0, 1.0);

            auto v_ij = loco::math::cross(v_i, v_j);
            auto v_jk = loco::math::cross(v_j, v_k);
            auto v_ki = loco::math::cross(v_k, v_i);

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

        // Checking a fixed case (a.cross(b) + c)
        {
            Vector3 v_a(1.0, 2.0, 3.0);  // NOLINT
            Vector3 v_b(4.0, 5.0, 6.0);  // NOLINT
            Vector3 v_c(7.0, 8.0, 9.0);  // NOLINT

            auto result = loco::math::cross(v_a, v_b) + v_c;
            REQUIRE(std::abs(result.x() - 4.0) < EPSILON);   // NOLINT
            REQUIRE(std::abs(result.y() - 14.0) < EPSILON);  // NOLINT
            REQUIRE(std::abs(result.z() - 6.0) < EPSILON);   // NOLINT
        }
    }
}
