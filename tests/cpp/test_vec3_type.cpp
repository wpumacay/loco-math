#include <catch2/catch.hpp>
#include <type_traits>
#include <cmath>

#include <loco/math/vec3_t_impl.hpp>

constexpr size_t N_SAMPLES = 10;
constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

template <typename T>
auto FuncAllClose(const loco::math::Vector3<T>& vec, T x, T y, T z) -> void {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    REQUIRE(std::abs(vec.x() - x) < EPSILON);
    REQUIRE(std::abs(vec.y() - y) < EPSILON);
    REQUIRE(std::abs(vec.z() - z) < EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector3 class (vec3_t) constructors", "[vec3_t][template]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Vector3 = loco::math::Vector3<T>;

    // Checking the correctness of the constructors

    SECTION("Default constructor") {
        Vector3 v;
        FuncAllClose<T>(v, 0.0, 0.0, 0.0);
    }

    SECTION("From single scalar argument") {
        auto val_x =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));

        Vector3 v(val_x);
        FuncAllClose(v, val_x, val_x, val_x);
    }

    SECTION("From two scalar arguments") {
        auto val_x =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));
        auto val_y =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));

        Vector3 v(val_x, val_y);
        FuncAllClose(v, val_x, val_y, val_y);
    }

    SECTION(
        "From three scalar arguments, from initializer_list, or using "
        "comma-initializer") {
        auto val_x =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));
        auto val_y =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));
        auto val_z =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));

        Vector3 v_1(val_x, val_y, val_z);
        Vector3 v_2 = {val_x, val_y, val_z};
        Vector3 v_3;
        // cppcheck-suppress constStatement
        v_3 << val_x, val_y, val_z;

        FuncAllClose(v_1, val_x, val_y, val_z);
        FuncAllClose(v_2, val_x, val_y, val_z);
        FuncAllClose(v_3, val_x, val_y, val_z);
    }
}
