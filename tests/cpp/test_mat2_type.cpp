#include <catch2/catch.hpp>
#include <math/mat2_t.hpp>

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

constexpr double RANGE_MIN = -10.0;
constexpr double RANGE_MAX = 10.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
auto FuncAllClose(const math::Matrix2<T>& mat, T x00, T x01, T x10, T x11)
    -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);
    return FuncClose(mat(0, 0), x00, EPSILON) &&
           FuncClose(mat(0, 1), x01, EPSILON) &&
           FuncClose(mat(1, 0), x10, EPSILON) &&
           FuncClose(mat(1, 1), x11, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Matrix4 class (mat2_t) constructors", "[mat2_t][template]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Matrix2 = math::Matrix2<T>;
    using Vector2 = math::Vector2<T>;

    // Checking all exposed constructors
    SECTION("Default constructor") {
        Matrix2 mat;
        REQUIRE(FuncAllClose<T>(mat, 0.0, 0.0, 0.0, 0.0));
    }
    SECTION("From all matrix entries") {
        auto x00 = GenRandomValue(T, 8);
        auto x01 = GenRandomValue(T, 8);
        auto x10 = GenRandomValue(T, 8);
        auto x11 = GenRandomValue(T, 8);

        Matrix2 mat(x00, x01, x10, x11);
        REQUIRE(FuncAllClose<T>(mat, x00, x01, x10, x11));
    }
    SECTION("From diagonal entries") {
        auto x00 = GenRandomValue(T, 8);
        auto x11 = GenRandomValue(T, 8);

        Matrix2 mat(x00, x11);
        REQUIRE(FuncAllClose<T>(mat, x00, 0.0, 0.0, x11));
    }
    SECTION("From column vectors") {
        auto x00 = GenRandomValue(T, 8);
        auto x01 = GenRandomValue(T, 8);
        auto x10 = GenRandomValue(T, 8);
        auto x11 = GenRandomValue(T, 8);
        Vector2 col0(x00, x10);
        Vector2 col1(x01, x11);

        Matrix2 mat(col0, col1);
        REQUIRE(FuncAllClose<T>(mat, x00, x01, x10, x11));
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif
