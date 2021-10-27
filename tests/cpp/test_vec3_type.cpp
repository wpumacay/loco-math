#include <catch2/catch.hpp>
#include <cmath>
#include <tinymath/tinymath.hpp>
#include <type_traits>

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector3 class (vec3_t) constructors", "[vec3_t][template]",
                   tiny::math::float32_t, tiny::math::float64_t) {
    using T = TestType;
    using Vector3 = tiny::math::Vector3<T>;

    // Checking size and alignment (we pad by 1 scalar to keep the alignment)
    constexpr int EXPECTED_SIZE = 4 * sizeof(T);
    constexpr int EXPECTED_ALIGNMENT = 4 * sizeof(T);
    static_assert(std::is_floating_point<T>(), "");
    static_assert(EXPECTED_SIZE == Vector3::num_bytes_size(), "");
    static_assert(EXPECTED_ALIGNMENT == Vector3::num_bytes_alignment(), "");

    constexpr T EPSILON = tiny::math::EPS<T>;
    constexpr int32_t NUM_SAMPLES = 10;
    constexpr T RAND_RANGE_MIN = static_cast<T>(-10.0);
    constexpr T RAND_RANGE_MAX = static_cast<T>(10.0);

    SECTION("Default constructor") {
        Vector3 v;

        REQUIRE(std::abs(v.x() - static_cast<T>(0.0)) < EPSILON);
        REQUIRE(std::abs(v.y() - static_cast<T>(0.0)) < EPSILON);
        REQUIRE(std::abs(v.z() - static_cast<T>(0.0)) < EPSILON);
    }

    SECTION("From single scalar argument") {
        auto val_x =
            GENERATE(take(NUM_SAMPLES, random(RAND_RANGE_MIN, RAND_RANGE_MAX)));

        Vector3 v(val_x);

        REQUIRE(std::abs(v.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v.y() - val_x) < EPSILON);
        REQUIRE(std::abs(v.z() - val_x) < EPSILON);
    }

    SECTION("From two scalar arguments") {
        auto val_x =
            GENERATE(take(NUM_SAMPLES, random(RAND_RANGE_MIN, RAND_RANGE_MAX)));
        auto val_y =
            GENERATE(take(NUM_SAMPLES, random(RAND_RANGE_MIN, RAND_RANGE_MAX)));

        Vector3 v(val_x, val_y);

        REQUIRE(std::abs(v.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v.y() - val_y) < EPSILON);
        REQUIRE(std::abs(v.z() - val_y) < EPSILON);
    }

    SECTION("From three scalar arguments or from initializer_list") {
        auto val_x =
            GENERATE(take(NUM_SAMPLES, random(RAND_RANGE_MIN, RAND_RANGE_MAX)));
        auto val_y =
            GENERATE(take(NUM_SAMPLES, random(RAND_RANGE_MIN, RAND_RANGE_MAX)));
        auto val_z =
            GENERATE(take(NUM_SAMPLES, random(RAND_RANGE_MIN, RAND_RANGE_MAX)));

        Vector3 v_1(val_x, val_y, val_z);
        Vector3 v_2 = {val_x, val_y, val_z};

        REQUIRE(std::abs(v_1.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v_1.y() - val_y) < EPSILON);
        REQUIRE(std::abs(v_1.z() - val_z) < EPSILON);

        REQUIRE(std::abs(v_2.x() - val_x) < EPSILON);
        REQUIRE(std::abs(v_2.y() - val_y) < EPSILON);
        REQUIRE(std::abs(v_2.z() - val_z) < EPSILON);
    }
}
