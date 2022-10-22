#include <cmath>
#include <catch2/catch.hpp>
#include <loco/math/mat2_t_impl.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#endif

static constexpr double ANGLE_MIN = -loco::math::PI;
static constexpr double ANGLE_MAX = loco::math::PI;

// NOLINTNEXTLINE
#define GenRandomAngle(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(ANGLE_MIN), \
                                   static_cast<Type>(ANGLE_MAX))))

static constexpr double SCALE_MIN = -10.0;
static constexpr double SCALE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomScale(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(SCALE_MIN), \
                                   static_cast<Type>(SCALE_MAX))))

// clang-format off
template <typename T>
auto CheckAllClose(const loco::math::Matrix2<T>& mat,
                T x00, T x01,
                T x10, T x11)
    -> void {
    REQUIRE(std::abs(mat(0, 0) - x00) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(0, 1) - x01) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(1, 0) - x10) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(1, 1) - x11) < static_cast<T>(loco::math::EPS));
}
// clang-format on

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix2 class (mat2_t) factory functions",
                   "[mat2_t][funcs]", loco::math::float32_t,
                   loco::math::float64_t) {
    using T = TestType;
    using Matrix2 = loco::math::Matrix2<T>;
    using Vector2 = loco::math::Vector2<T>;

    SECTION("Rotation matrix") {
        constexpr int NUM_SAMPLES = 100;
        auto angle = GenRandomAngle(T, NUM_SAMPLES);
        auto rot_mat = Matrix2::Rotation(angle);

        // clang-format off
        CheckAllClose<T>(rot_mat,
            std::cos(angle), -std::sin(angle),
            std::sin(angle), std::cos(angle));
        // clang-format on
    }

    SECTION("Scale matrix - from scalars") {
        constexpr int NUM_SAMPLES = 100;
        auto scale_x = GenRandomScale(T, NUM_SAMPLES);
        auto scale_y = GenRandomScale(T, NUM_SAMPLES);
        auto scale_mat = Matrix2::Scale(scale_x, scale_y);

        // clang-format off
        CheckAllClose<T>(scale_mat,
            scale_x, 0.0,
            0.0, scale_y);
        // clang-format on
    }

    SECTION("Scale matrix - from vec2") {
        constexpr int NUM_SAMPLES = 100;
        auto scale = Vector2(GenRandomScale(T, NUM_SAMPLES),
                             GenRandomScale(T, NUM_SAMPLES));
        auto scale_mat = Matrix2::Scale(scale);

        // clang-format off
        CheckAllClose<T>(scale_mat,
            scale.x(), 0.0,
            0.0, scale.y());
        // clang-format on
    }
}
