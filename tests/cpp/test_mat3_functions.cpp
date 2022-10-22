#include <cmath>
#include <catch2/catch.hpp>
#include <loco/math/mat3_t_impl.hpp>

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
auto CheckAllClose(const loco::math::Matrix3<T>& mat,
                T x00, T x01, T x02,
                T x10, T x11, T x12,
                T x20, T x21, T x22)
    -> void {
    REQUIRE(std::abs(mat(0, 0) - x00) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(0, 1) - x01) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(0, 2) - x02) < static_cast<T>(loco::math::EPS));

    REQUIRE(std::abs(mat(1, 0) - x10) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(1, 1) - x11) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(1, 2) - x12) < static_cast<T>(loco::math::EPS));

    REQUIRE(std::abs(mat(2, 0) - x20) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(2, 1) - x21) < static_cast<T>(loco::math::EPS));
    REQUIRE(std::abs(mat(2, 2) - x22) < static_cast<T>(loco::math::EPS));
}
// clang-format on

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix3 class (mat3_t) factory functions",
                   "[mat3_t][funcs]", loco::math::float32_t,
                   loco::math::float64_t) {
    using T = TestType;
    using Matrix3 = loco::math::Matrix3<T>;
    using Vector3 = loco::math::Vector3<T>;

    SECTION("Rotation matrix - X") {
        constexpr int NUM_SAMPLES = 100;
        auto angle = GenRandomAngle(T, NUM_SAMPLES);
        auto rot_mat = Matrix3::RotationX(angle);

        // clang-format off
        CheckAllClose<T>(rot_mat,
            1.0,        0.0     ,       0.0       ,
            0.0, std::cos(angle), -std::sin(angle),
            0.0, std::sin(angle),  std::cos(angle));
        // clang-format on
    }

    SECTION("Rotation matrix - Y") {
        constexpr int NUM_SAMPLES = 100;
        auto angle = GenRandomAngle(T, NUM_SAMPLES);
        auto rot_mat = Matrix3::RotationY(angle);

        // clang-format off
        CheckAllClose<T>(rot_mat,
            std::cos(angle), 0.0, std::sin(angle),
                  0.0      , 1.0,       0.0      ,
           -std::sin(angle), 0.0, std::cos(angle));
        // clang-format on
    }

    SECTION("Rotation matrix - Z") {
        constexpr int NUM_SAMPLES = 100;
        auto angle = GenRandomAngle(T, NUM_SAMPLES);
        auto rot_mat = Matrix3::RotationZ(angle);

        // clang-format off
        CheckAllClose<T>(rot_mat,
            std::cos(angle), -std::sin(angle), 0.0,
            std::sin(angle),  std::cos(angle), 0.0,
                 0.0       ,        0.0      , 1.0);
        // clang-format on
    }

    SECTION("Scale matrix - from scalars") {
        constexpr int NUM_SAMPLES = 100;
        auto scale_x = GenRandomScale(T, NUM_SAMPLES);
        auto scale_y = GenRandomScale(T, NUM_SAMPLES);
        auto scale_z = GenRandomScale(T, NUM_SAMPLES);
        auto scale_mat = Matrix3::Scale(scale_x, scale_y, scale_z);

        // clang-format off
        CheckAllClose<T>(scale_mat,
            scale_x,   0.0  ,   0.0  ,
                0.0, scale_y,   0.0  ,
                0.0,   0.0  , scale_z);
        // clang-format on
    }

    SECTION("Scale matrix - from vec3") {
        constexpr int NUM_SAMPLES = 100;
        auto scale = Vector3(GenRandomScale(T, NUM_SAMPLES),
                             GenRandomScale(T, NUM_SAMPLES),
                             GenRandomScale(T, NUM_SAMPLES));
        auto scale_mat = Matrix3::Scale(scale);

        // clang-format off
        CheckAllClose<T>(scale_mat,
            scale.x(),   0.0  ,   0.0  ,
                0.0, scale.y(),   0.0  ,
                0.0,   0.0  , scale.z());
        // clang-format on
    }
}
