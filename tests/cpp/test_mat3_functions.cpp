#include <catch2/catch.hpp>
#include <math/mat3_t.hpp>
#include <math/quat_t.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

static constexpr double ANGLE_MIN = -math::PI;
static constexpr double ANGLE_MAX = math::PI;

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

static constexpr double RANGE_MIN = -1.0;
static constexpr double RANGE_MAX = 1.0;

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
auto FuncAllClose(const math::Matrix3<T>& mat,
                  T x00, T x01, T x02,
                  T x10, T x11, T x12,
                  T x20, T x21, T x22) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);

    return FuncClose<T>(mat(0, 0), x00, EPSILON) &&
           FuncClose<T>(mat(0, 1), x01, EPSILON) &&
           FuncClose<T>(mat(0, 2), x02, EPSILON) &&
           FuncClose<T>(mat(1, 0), x10, EPSILON) &&
           FuncClose<T>(mat(1, 1), x11, EPSILON) &&
           FuncClose<T>(mat(1, 2), x12, EPSILON) &&
           FuncClose<T>(mat(2, 0), x20, EPSILON) &&
           FuncClose<T>(mat(2, 1), x21, EPSILON) &&
           FuncClose<T>(mat(2, 2), x22, EPSILON);
}
// clang-format on

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix3 class (mat3_t) factory functions",
                   "[mat3_t][funcs]", math::float32_t, math::float64_t) {
    using T = TestType;
    using Matrix3 = math::Matrix3<T>;
    using Vector3 = math::Vector3<T>;
    using Quaternion = math::Quaternion<T>;

    SECTION("Rotation matrix - from Quaternion") {
        auto w = GenRandomValue(T, 4);
        auto x = GenRandomValue(T, 4);
        auto y = GenRandomValue(T, 4);
        auto z = GenRandomValue(T, 4);

        auto quat = Quaternion(w, x, y, z);
        auto rot_mat = Matrix3(quat);

        auto length = std::sqrt(w * w + x * x + y * y + z * z);
        w /= length;
        x /= length;
        y /= length;
        z /= length;

        auto xx = x * x;
        auto yy = y * y;
        auto zz = z * z;
        auto xy = x * y;
        auto wz = w * z;
        auto xz = x * z;
        auto wy = w * y;
        auto yz = y * z;
        auto wx = w * x;

        // clang-format off
        REQUIRE(FuncAllClose<T>(rot_mat,
        // NOLINTNEXTLINE
        1.0 - 2.0 * (yy + zz),     2.0 * (xy - wz)   ,    2.0 * (xz + wy)   ,
        // NOLINTNEXTLINE
            2.0 * (xy + wz)  , 1.0 - 2.0 * (xx + zz) ,    2.0 * (yz - wx)   ,
        // NOLINTNEXTLINE
            2.0 * (xz - wy)  ,     2.0 * (yz + wx)   , 1.0 - 2.0 * (xx + yy)));
        // clang-format on
    }

    SECTION("Rotation matrix - X") {
        auto angle = GenRandomAngle(T, 100);
        auto rot_mat = Matrix3::RotationX(angle);

        // clang-format off
        REQUIRE(FuncAllClose<T>(rot_mat,
                1.0,        0.0     ,       0.0       ,
                0.0, std::cos(angle), -std::sin(angle),
                0.0, std::sin(angle),  std::cos(angle)));
        // clang-format on
    }

    SECTION("Rotation matrix - Y") {
        auto angle = GenRandomAngle(T, 100);
        auto rot_mat = Matrix3::RotationY(angle);

        // clang-format off
        REQUIRE(FuncAllClose<T>(rot_mat,
                 std::cos(angle), 0.0, std::sin(angle),
                       0.0      , 1.0,       0.0      ,
                -std::sin(angle), 0.0, std::cos(angle)));
        // clang-format on
    }

    SECTION("Rotation matrix - Z") {
        auto angle = GenRandomAngle(T, 100);
        auto rot_mat = Matrix3::RotationZ(angle);

        // clang-format off
        REQUIRE(FuncAllClose<T>(rot_mat,
                std::cos(angle), -std::sin(angle), 0.0,
                std::sin(angle),  std::cos(angle), 0.0,
                     0.0       ,        0.0      , 1.0));
        // clang-format on
    }

    SECTION("Scale matrix - from scalars") {
        auto scale_x = GenRandomScale(T, 10);
        auto scale_y = GenRandomScale(T, 10);
        auto scale_z = GenRandomScale(T, 10);
        auto scale_mat = Matrix3::Scale(scale_x, scale_y, scale_z);

        // clang-format off
        REQUIRE(FuncAllClose<T>(scale_mat,
                scale_x,   0.0  ,   0.0  ,
                    0.0, scale_y,   0.0  ,
                    0.0,   0.0  , scale_z));
        // clang-format on
    }

    SECTION("Scale matrix - from vec3") {
        auto scale = Vector3(GenRandomScale(T, 10), GenRandomScale(T, 10),
                             GenRandomScale(T, 10));
        auto scale_mat = Matrix3::Scale(scale);

        // clang-format off
        REQUIRE(FuncAllClose<T>(scale_mat,
                scale.x(),   0.0  ,   0.0  ,
                    0.0, scale.y(),   0.0  ,
                    0.0,   0.0  , scale.z()));
        // clang-format on
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
