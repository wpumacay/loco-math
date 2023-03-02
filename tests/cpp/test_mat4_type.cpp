#include <catch2/catch.hpp>
#include <math/mat4_t.hpp>

constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))));

// NOLINTNEXTLINE
#define GenRandomInRange(Type, Nsamples, range_min, range_max)   \
    GENERATE(take(Nsamples, random(static_cast<Type>(range_min), \
                                   static_cast<Type>(range_max))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

// clang-format off
template <typename T>
auto FuncAllClose(const math::Matrix4<T>& mat,
                  T x00, T x01, T x02, T x03,
                  T x10, T x11, T x12, T x13,
                  T x20, T x21, T x22, T x23,
                  T x30, T x31, T x32, T x33) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);

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
TEMPLATE_TEST_CASE("Matrix4 class (mat4_t) constructors", "[mat4_t][template]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Vec3 = math::Vector3<T>;
    using Vec4 = math::Vector4<T>;
    using Euler = math::Euler<T>;
    using Quat = math::Quaternion<T>;
    using Mat3 = math::Matrix3<T>;
    using Mat4 = math::Matrix4<T>;

    // Checking all exposed constructors
    SECTION("Default constructor") {
        Mat4 mat;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0));
        // clang-format on
    }
    SECTION("From all matrix entries") {
        // clang-format off
        Mat4 mat(1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0,  10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);

        REQUIRE(FuncAllClose<T>(mat,
                1.0,  2.0,  3.0,  4.0,
                5.0,  6.0,  7.0,  8.0,
                9.0,  10.0, 11.0, 12.0,
                13.0, 14.0, 15.0, 16.0));
        // clang-format on
    }
    SECTION("From diagonal entries") {
        auto x00 = GenRandomValue(T, 4);
        auto x11 = GenRandomValue(T, 4);
        auto x22 = GenRandomValue(T, 4);
        auto x33 = GenRandomValue(T, 4);
        Mat4 mat(x00, x11, x22, x33);
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                x00, 0.0, 0.0, 0.0,
                0.0, x11, 0.0, 0.0,
                0.0, 0.0, x22, 0.0,
                0.0, 0.0, 0.0, x33));
        // clang-format on
    }
    SECTION("From column vectors") {
        auto x00 = GenRandomValue(T, 4);
        auto x11 = GenRandomValue(T, 4);
        auto x22 = GenRandomValue(T, 4);
        auto x33 = GenRandomValue(T, 4);

        Vec4 col0 = {x00, 2.0, 3.0, 4.0};
        Vec4 col1 = {5.0, x11, 7.0, 8.0};
        Vec4 col2 = {9.0, 10.0, x22, 12.0};
        Vec4 col3 = {13.0, 14.0, 15.0, x33};

        Mat4 mat(col0, col1, col2, col3);
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                x00, 5.0, 9.0,  13.0,
                2.0, x11, 10.0, 14.0,
                3.0, 7.0, x22,  15.0,
                4.0, 8.0, 12.0, x33));
        // clang-format on
    }
    SECTION("From position and orientation") {
        auto pos_x = GenRandomValue(T, 2);
        auto pos_y = GenRandomValue(T, 2);
        auto pos_z = GenRandomValue(T, 2);
        Vec3 position(pos_x, pos_y, pos_z);

        SECTION("Orientation given as a rotation matrix") {
            auto angle = GenRandomInRange(T, 2, -math::PI, math::PI);
            auto cos_t = std::cos(angle);
            auto sin_t = std::sin(angle);
            auto orientation = Mat3::RotationX(angle);

            Mat4 tf(position, orientation);
            // clang-format off
            REQUIRE(FuncAllClose<T>(tf,
                    1.0,  0.0 ,   0.0  , pos_x,
                    0.0, cos_t, -sin_t , pos_y,
                    0.0, sin_t,  cos_t , pos_z,
                    0.0,  0.0 ,   0.0  , 1.0));
            // clang-format on
        }
        SECTION("Orientation given as a quaternion") {
            auto angle = GenRandomInRange(T, 2, -math::PI, math::PI);
            auto cos_t = std::cos(angle);
            auto sin_t = std::sin(angle);
            auto orientation = Quat::RotationY(angle);

            Mat4 tf(position, orientation);
            // clang-format off
            REQUIRE(FuncAllClose<T>(tf,
                     cos_t , 0.0 , sin_t , pos_x,
                      0.0  , 1.0 ,  0.0  , pos_y,
                    -sin_t , 0.0 , cos_t , pos_z,
                      0.0  , 0.0 ,  0.0  , 1.0));
            // clang-format on
        }
        SECTION("Orientation given as euler angles") {
            auto angle = GenRandomInRange(T, 2, -math::PI, math::PI);
            auto cos_t = std::cos(angle);
            auto sin_t = std::sin(angle);
            auto orientation = Euler(0.0, 0.0, angle);

            Mat4 tf(position, orientation);
            // clang-format off
            REQUIRE(FuncAllClose<T>(tf,
                    cos_t, -sin_t , 0.0 , pos_x,
                    sin_t,  cos_t , 0.0 , pos_y,
                     0.0 ,   0.0  , 1.0 , pos_z,
                     0.0 ,   0.0  , 0.0 , 1.0));
            // clang-format on
        }
    }
}
