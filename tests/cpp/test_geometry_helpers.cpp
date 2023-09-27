#include <catch2/catch.hpp>
#include <math/utils/geometry_helpers.hpp>

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
#pragma warning(disable : 4244)
#endif

TEMPLATE_TEST_CASE("Utilities [Geometric-Helpers]", "[geometric][funcs]",
                   ::math::float32_t, ::math::float64_t) {
    using T = TestType;
    using Vec3 = ::math::Vector3<T>;
    using Line = ::math::Line<T>;

    const Vec3 ZERO = {0.0, 0.0, 0.0};

    SECTION("Line default constructor") {
        Line line;

        REQUIRE(line.start == ZERO);
        REQUIRE(line.end == ZERO);
    }

    SECTION("Line constructor from points") {
        Line line({1.0, 1.0, 1.0}, {2.0, 3.0, 4.0});

        REQUIRE(line.start == Vec3(1.0, 1.0, 1.0));
        REQUIRE(line.end == Vec3(2.0, 3.0, 4.0));
    }

    SECTION("Line constructor from initializer list") {
        Line line = {{1.0, 1.0, 1.0}, {2.0, 3.0, 4.0}};

        REQUIRE(line.start == Vec3(1.0, 1.0, 1.0));
        REQUIRE(line.end == Vec3(2.0, 3.0, 4.0));
    }

    SECTION("Line distanceTo point func") {
        // Line = x-axis, points = {(1, 0, 0), (0, 1, 0), (0, 0, 1)}
        {
            Line line = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};
            Vec3 p_a = {1.0, 0.0, 0.0};
            Vec3 p_b = {0.0, 1.0, 0.0};
            Vec3 p_c = {0.0, 0.0, 1.0};

            REQUIRE(std::abs(line.distanceTo(p_a) - 0.0) < 1e-5);
            REQUIRE(std::abs(line.distanceTo(p_b) - 1.0) < 1e-5);
            REQUIRE(std::abs(line.distanceTo(p_c) - 1.0) < 1e-5);
        }
    }
}
