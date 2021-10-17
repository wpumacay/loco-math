#include <catch2/catch.hpp>
#include <cmath>
#include <tinymath/tinymath.hpp>

/*
 * @todo(wilbert): replace GENERATE of fixed values with random values + seed
 */

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector3 class (vec3_t) core API", "[vec3_t][template]",
                   tiny::math::float32_t, tiny::math::float64_t) {
    using T = TestType;
    using Vector3 = tiny::math::Vector3<T>;

    constexpr TestType EPSILON = tiny::math::EPS<T>;

    SECTION("Constructor Vector3()") {
        Vector3 v;

        REQUIRE(std::abs(v.x() - static_cast<T>(0.0)) < EPSILON);
        REQUIRE(std::abs(v.y() - static_cast<T>(0.0)) < EPSILON);
        REQUIRE(std::abs(v.z() - static_cast<T>(0.0)) < EPSILON);
    }

    SECTION("Constructor Vector3(T x)") {
        auto val = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT

        Vector3 v(val);

        REQUIRE(std::abs(v.x() - val) < EPSILON);
        REQUIRE(std::abs(v.y() - val) < EPSILON);
        REQUIRE(std::abs(v.z() - val) < EPSILON);
    }

    SECTION("Constructor Vector3(T x, T y)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT

        Vector3 v(val_x, val_y);

        REQUIRE(std::abs(v.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v.y() - val_y) < EPSILON);
        REQUIRE(std::abs(v.z() - val_y) < EPSILON);
    }

    SECTION("Constructor Vector3(T x, T y, T z)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        Vector3 v(val_x, val_y, val_z);

        REQUIRE(std::abs(v.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v.y() - val_y) < EPSILON);
        REQUIRE(std::abs(v.z() - val_z) < EPSILON);
    }
}
