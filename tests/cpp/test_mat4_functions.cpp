#include <catch2/catch.hpp>
#include <math/mat4_t.hpp>

static constexpr auto ANGLE_MIN = -loco::math::PI;
static constexpr auto ANGLE_MAX = loco::math::PI;

// NOLINTNEXTLINE
#define GenRandomAngle(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(ANGLE_MIN), \
                                   static_cast<Type>(ANGLE_MAX))))

static constexpr auto SCALE_MIN = -10.0;
static constexpr auto SCALE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomScale(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(SCALE_MIN), \
                                   static_cast<Type>(SCALE_MAX))))

static constexpr auto RANGE_MIN = -100.0;
static constexpr auto RANGE_MAX = 100.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

// clang-format off
template <typename T>
auto FuncAllClose(const loco::math::Matrix4<T>& mat,
                  T x00, T x01, T x02, T x03,
                  T x10, T x11, T x12, T x13,
                  T x20, T x21, T x22, T x23,
                  T x30, T x31, T x32, T x33) -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);

    return FuncClose<T>(mat(0, 0), x00, EPSILON) &&
           FuncClose<T>(mat(0, 1), x01, EPSILON) &&
           FuncClose<T>(mat(0, 2), x02, EPSILON) &&
           FuncClose<T>(mat(0, 3), x03, EPSILON) &&
           FuncClose<T>(mat(1, 0), x10, EPSILON) &&
           FuncClose<T>(mat(1, 1), x11, EPSILON) &&
           FuncClose<T>(mat(1, 2), x12, EPSILON) &&
           FuncClose<T>(mat(1, 3), x13, EPSILON) &&
           FuncClose<T>(mat(2, 0), x20, EPSILON) &&
           FuncClose<T>(mat(2, 1), x21, EPSILON) &&
           FuncClose<T>(mat(2, 2), x22, EPSILON) &&
           FuncClose<T>(mat(2, 3), x23, EPSILON) &&
           FuncClose<T>(mat(3, 0), x30, EPSILON) &&
           FuncClose<T>(mat(3, 1), x31, EPSILON) &&
           FuncClose<T>(mat(3, 2), x32, EPSILON) &&
           FuncClose<T>(mat(3, 3), x33, EPSILON);
}
// clang-format on

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix4 class (mat4_t) factory functions",
                   "[mat4_t][funcs]", loco::math::float32_t,
                   loco::math::float64_t) {
    using T = TestType;
    using Matrix4 = loco::math::Matrix4<T>;
    using Vector3 = loco::math::Vector3<T>;

    SECTION("Rotation matrix -X") {
        auto angle = GenRandomAngle(T, 100);
        auto rot_mat = Matrix4::RotationX(angle);

        // clang-format off
        REQUIRE(FuncAllClose<T>(rot_mat,
                1.0,        0.0     ,        0.0      , 0.0,
                0.0, std::cos(angle), -std::sin(angle), 0.0,
                0.0, std::sin(angle),  std::cos(angle), 0.0,
                0.0,        0.0     ,        0.0      , 1.0));

        // clang-format on
    }

    SECTION("Rotation matrix - Y") {
        auto angle = GenRandomAngle(T, 100);
        auto rot_mat = Matrix4::RotationY(angle);

        // clang-format off
        REQUIRE(FuncAllClose<T>(rot_mat,
                std::cos(angle), 0.0, std::sin(angle), 0.0,
                      0.0      , 1.0,       0.0      , 0.0,
               -std::sin(angle), 0.0, std::cos(angle), 0.0,
                      0.0      , 0.0,       0.0      , 1.0));
        // clang-format on
    }

    SECTION("Rotation matrix - Z") {
        auto angle = GenRandomAngle(T, 100);
        auto rot_mat = Matrix4::RotationZ(angle);

        // clang-format off
        REQUIRE(FuncAllClose<T>(rot_mat,
            std::cos(angle), -std::sin(angle), 0.0, 0.0,
            std::sin(angle),  std::cos(angle), 0.0, 0.0,
                 0.0       ,        0.0      , 1.0, 0.0,
                 0.0       ,        0.0      , 0.0, 1.0));
        // clang-format on
    }

    SECTION("Scale matrix - from scalars") {
        auto scale_x = GenRandomScale(T, 10);
        auto scale_y = GenRandomScale(T, 10);
        auto scale_z = GenRandomScale(T, 10);
        auto scale_mat = Matrix4::Scale(scale_x, scale_y, scale_z);

        // clang-format off
        REQUIRE(FuncAllClose<T>(scale_mat,
                scale_x,     0.0,     0.0, 0.0,
                    0.0, scale_y,     0.0, 0.0,
                    0.0,     0.0, scale_z, 0.0,
                    0.0,     0.0,     0.0, 1.0));
        // clang-format on
    }

    SECTION("Scale matrix - from vec3") {
        auto scale = Vector3(GenRandomScale(T, 10), GenRandomScale(T, 10),
                             GenRandomScale(T, 10));
        auto scale_mat = Matrix4::Scale(scale);

        // clang-format off
        REQUIRE(FuncAllClose<T>(scale_mat,
                scale.x(),       0.0,       0.0, 0.0,
                      0.0, scale.y(),       0.0, 0.0,
                      0.0,       0.0, scale.z(), 0.0,
                      0.0,       0.0,       0.0, 1.0));
        // clang-format on
    }

    SECTION("Translation matrix - from vec3") {
        auto position = Vector3(GenRandomValue(T, 10), GenRandomValue(T, 10),
                                GenRandomValue(T, 10));
        auto translation_mat = Matrix4::Translation(position);

        // clang-format off
        REQUIRE(FuncAllClose<T>(translation_mat,
                1.0, 0.0, 0.0, position.x(),
                0.0, 1.0, 0.0, position.y(),
                0.0, 0.0, 1.0, position.z(),
                0.0, 0.0, 0.0, 1.0));
        // clang-format on
    }
}
