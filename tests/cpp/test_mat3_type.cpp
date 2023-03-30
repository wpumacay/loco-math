#include <catch2/catch.hpp>
#include <math/mat3_t.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#pragma clang diagnostic ignored "-Wdouble-promotion"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4305)
#endif

constexpr double RANGE_MIN = -100.0;
constexpr double RANGE_MAX = 100.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

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
TEMPLATE_TEST_CASE("Matrix3 class (mat3_t) constructors", "[mat3_t][template]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Vec3 = math::Vector3<T>;
    using Euler = math::Euler<T>;
    using Mat3 = math::Matrix3<T>;
    using Mat4 = math::Matrix4<T>;
    using Quat = math::Quaternion<T>;

    // Checking all exposed constructors
    SECTION("Default constructor") {
        Mat3 mat;
        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 0.0, 0.0));
        // clang-format on
    }
    SECTION("From all matrix entries") {
        // clang-format off
        Mat3 mat(1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0);

        REQUIRE(FuncAllClose<T>(mat,
                1.0, 2.0, 3.0,
                4.0, 5.0, 6.0,
                7.0, 8.0, 9.0));
        // clang-format on
    }
    SECTION("From diagonal entries") {
        auto x00 = GenRandomValue(T, 8);
        auto x11 = GenRandomValue(T, 8);
        auto x22 = GenRandomValue(T, 8);

        Mat3 mat(x00, x11, x22);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                x00, 0.0, 0.0,
                0.0, x11, 0.0,
                0.0, 0.0, x22));
        // clang-format on
    }
    SECTION("From column vectors") {
        auto x00 = GenRandomValue(T, 8);
        auto x11 = GenRandomValue(T, 8);
        auto x22 = GenRandomValue(T, 8);

        Vec3 col0 = {x00, 2.0, 3.0};
        Vec3 col1 = {4.0, x11, 6.0};
        Vec3 col2 = {7.0, 8.0, x22};

        Mat3 mat(col0, col1, col2);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
                x00, 4.0, 7.0,
                2.0, x11, 8.0,
                3.0, 6.0, x22));
        // clang-format on
    }
    SECTION("From quaternion") {
        // NOLINTNEXTLINE
        Quat q(1.0F, 0.0F, 0.0F, 0.0F);
        Mat3 mat(q);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat,
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0));
        // clang-format on
    }
    SECTION("From Euler angles") {
        auto theta = GenRandomInRange(T, 10, -::math::PI, ::math::PI);
        auto cos_t = std::cos(theta);
        auto sin_t = std::sin(theta);

        Euler e_x(theta, 0.0, 0.0);
        Euler e_y(0.0, theta, 0.0);
        Euler e_z(0.0, 0.0, theta);
        Mat3 mat_x(e_x);
        Mat3 mat_y(e_y);
        Mat3 mat_z(e_z);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_x,
            1.0,  0.0 ,  0.0 ,
            0.0, cos_t, -sin_t,
            0.0, sin_t, cos_t));

        REQUIRE(FuncAllClose<T>(mat_y,
            cos_t , 0.0,  sin_t ,
             0.0  , 1.0,   0.0  ,
           -sin_t , 0.0,  cos_t));

        REQUIRE(FuncAllClose<T>(mat_z,
            cos_t , -sin_t , 0.0,
            sin_t ,  cos_t , 0.0,
             0.0  ,   0.0  , 1.0));
        // clang-format on
    }
    SECTION("From 4x4 transform matrix") {
        auto theta = GenRandomInRange(T, 10, -::math::PI, ::math::PI);
        auto cos_t = std::cos(theta);
        auto sin_t = std::sin(theta);

        Mat4 tf_x = Mat4::RotationX(theta);
        Mat4 tf_y = Mat4::RotationY(theta);
        Mat4 tf_z = Mat4::RotationZ(theta);
        Mat3 mat_x(tf_x);
        Mat3 mat_y(tf_y);
        Mat3 mat_z(tf_z);

        // clang-format off
        REQUIRE(FuncAllClose<T>(mat_x,
            1.0,  0.0 ,  0.0 ,
            0.0, cos_t, -sin_t,
            0.0, sin_t, cos_t));

        REQUIRE(FuncAllClose<T>(mat_y,
            cos_t , 0.0,  sin_t ,
             0.0  , 1.0,   0.0  ,
           -sin_t , 0.0,  cos_t));

        REQUIRE(FuncAllClose<T>(mat_z,
            cos_t , -sin_t , 0.0,
            sin_t ,  cos_t , 0.0,
             0.0  ,   0.0  , 1.0));
        // clang-format on
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif
