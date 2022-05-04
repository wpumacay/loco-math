#include <catch2/catch.hpp>
#include <cmath>
#include <loco/math/all.hpp>
#include <type_traits>

constexpr int N_SAMPLES = 10;
constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

template <typename T>
auto FuncAllClose(const loco::math::Vector4<T>& vec, T x, T y, T z, T w)
    -> void {
    constexpr T EPSILON = loco::math::EPS<T>;
    REQUIRE(std::abs(vec.x() - x) < EPSILON);
    REQUIRE(std::abs(vec.y() - y) < EPSILON);
    REQUIRE(std::abs(vec.z() - z) < EPSILON);
    REQUIRE(std::abs(vec.w() - w) < EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector4 class (vec4_t) constructors", "[vec4_t][template]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Vector4 = loco::math::Vector4<T>;

    // Checking size and alignment (we pad by 1 scalar to keep the alignment)
    constexpr int EXPECTED_SIZE = 4 * sizeof(T);
    constexpr int EXPECTED_ALIGNMENT = 4 * sizeof(T);
    static_assert(std::is_floating_point<T>(), "");
    static_assert(EXPECTED_SIZE == Vector4::num_bytes_size(), "");
    static_assert(EXPECTED_ALIGNMENT == Vector4::num_bytes_alignment(), "");

    // Checking the correctness of the constructors

    SECTION("Default constructor") {
        Vector4 v;
        FuncAllClose<T>(v, 0.0, 0.0, 0.0, 0.0);
    }

    SECTION("From single scalar argument") {
        auto val_x =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));

        Vector4 v(val_x);

        FuncAllClose<T>(v, val_x, val_x, val_x, val_x);
    }

    SECTION("From two scalar arguments") {
        auto val_x =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));
        auto val_y =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));

        Vector4 v(val_x, val_y);

        FuncAllClose<T>(v, val_x, val_y, val_y, val_y);
    }

    SECTION("From three scalar arguments") {
        auto val_x =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));
        auto val_y =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));
        auto val_z =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));

        Vector4 v(val_x, val_y, val_z);

        FuncAllClose<T>(v, val_x, val_y, val_z, val_z);
    }

    SECTION(
        "From four scalar arguments, from initializer_list, or using "
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
        auto val_w =
            GENERATE(take(N_SAMPLES, random(static_cast<T>(RANGE_MIN),
                                            static_cast<T>(RANGE_MAX))));

        Vector4 v_1(val_x, val_y, val_z, val_w);
        Vector4 v_2 = {val_x, val_y, val_z, val_w};
        Vector4 v_3;
        v_3 << val_x, val_y, val_z, val_w;

        FuncAllClose<T>(v_1, val_x, val_y, val_z, val_w);
        FuncAllClose<T>(v_2, val_x, val_y, val_z, val_w);
        FuncAllClose<T>(v_3, val_x, val_y, val_z, val_w);
    }
}
