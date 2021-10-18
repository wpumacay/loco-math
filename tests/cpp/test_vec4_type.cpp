#include <catch2/catch.hpp>
#include <cmath>
#include <tinymath/tinymath.hpp>

/*
 * @todo(wilbert): replace GENERATE of fixed values with random values + seed
 */

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector4 class (vec4_t) core API", "[vec4_t][template]",
                   tiny::math::float32_t, tiny::math::float64_t) {
    using T = TestType;
    using Vector4 = tiny::math::Vector4<T>;

    constexpr TestType EPSILON = tiny::math::EPS<T>;

    SECTION("Constructor Vector4()") {
        Vector4 v;

        REQUIRE(std::abs(v.x() - static_cast<T>(0.0)) < EPSILON);
        REQUIRE(std::abs(v.y() - static_cast<T>(0.0)) < EPSILON);
        REQUIRE(std::abs(v.z() - static_cast<T>(0.0)) < EPSILON);
        REQUIRE(std::abs(v.w() - static_cast<T>(0.0)) < EPSILON);
    }

    SECTION("Constructor Vector4(T x)") {
        auto val = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT

        Vector4 v(val);

        REQUIRE(std::abs(v.x() - val) < EPSILON);
        REQUIRE(std::abs(v.y() - val) < EPSILON);
        REQUIRE(std::abs(v.z() - val) < EPSILON);
        REQUIRE(std::abs(v.w() - val) < EPSILON);
    }

    SECTION("Constructor Vector4(T x, T y)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT

        Vector4 v(val_x, val_y);

        REQUIRE(std::abs(v.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v.y() - val_y) < EPSILON);
        REQUIRE(std::abs(v.z() - val_y) < EPSILON);
        REQUIRE(std::abs(v.w() - val_y) < EPSILON);
    }

    SECTION("Constructor Vector4(T x, T y, T z)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);  // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);  // NOLINT
        auto val_z = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);  // NOLINT

        Vector4 v(val_x, val_y, val_z);

        REQUIRE(std::abs(v.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v.y() - val_y) < EPSILON);
        REQUIRE(std::abs(v.z() - val_z) < EPSILON);
        REQUIRE(std::abs(v.w() - val_z) < EPSILON);
    }

    SECTION("Constructor Vector4(T x, T y, T z, T w)") {
        auto val_x = GENERATE(as<T>{}, 1.0, 2.0, 3.0, 4.0);   // NOLINT
        auto val_y = GENERATE(as<T>{}, 2.0, 4.0, 6.0, 8.0);   // NOLINT
        auto val_z = GENERATE(as<T>{}, 3.0, 5.0, 7.0, 9.0);   // NOLINT
        auto val_w = GENERATE(as<T>{}, 4.0, 6.0, 8.0, 10.0);  // NOLINT

        Vector4 v(val_x, val_y, val_z, val_w);

        REQUIRE(std::abs(v.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v.y() - val_y) < EPSILON);
        REQUIRE(std::abs(v.z() - val_z) < EPSILON);
        REQUIRE(std::abs(v.w() - val_w) < EPSILON);
    }
}
