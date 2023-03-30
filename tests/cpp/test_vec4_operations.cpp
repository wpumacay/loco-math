#include <catch2/catch.hpp>
#include <math/vec4_t.hpp>

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

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
constexpr auto FuncCompareEqual(T xa, T ya, T za, T xb, T yb, T zb, T wa, T wb,
                                T eps) -> bool {
    return FuncClose<T>(xa, xb, eps) && FuncClose<T>(ya, yb, eps) &&
           FuncClose<T>(za, zb, eps) && FuncClose<T>(wa, wb, eps);
}

template <typename T>
auto FuncAllClose(const math::Vector4<T>& vec, T x, T y, T z, T w) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);
    return FuncClose<T>(vec.x(), x, EPSILON) &&
           FuncClose<T>(vec.y(), y, EPSILON) &&
           FuncClose<T>(vec.z(), z, EPSILON) &&
           FuncClose<T>(vec.w(), w, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector4 class (vec4_t) core Operations", "[vec4_t][ops]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Vector4 = math::Vector4<T>;

    constexpr T EPSILON = static_cast<T>(math::EPS);

    SECTION("Vector comparison ==, !=") {
        Vector4 v_1(1.0, 2.0, 3.0, 4.0);                        // NOLINT
        Vector4 v_2(1.0, 2.0, 3.0, 4.0);                        // NOLINT
        Vector4 v_3(static_cast<T>(1.1), static_cast<T>(2.1),   // NOLINT
                    static_cast<T>(3.1), static_cast<T>(4.1));  // NOLINT

        REQUIRE(v_1 == v_2);
        REQUIRE(v_2 != v_3);
        REQUIRE(v_3 != v_1);

        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);
        auto val_w_a = GenRandomValue(T, 2);

        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);
        auto val_w_b = GenRandomValue(T, 2);

        Vector4 v_a(val_x_a, val_y_a, val_z_a, val_w_a);
        Vector4 v_b(val_x_b, val_y_b, val_z_b, val_w_b);

        auto equal_a_b_lib = (v_a == v_b);
        auto equal_a_b_man =
            FuncCompareEqual<T>(val_x_a, val_y_a, val_z_a, val_x_b, val_y_b,
                                val_z_b, val_w_a, val_w_b, EPSILON);

        auto diff_a_b_lib = (v_a != v_b);
        auto diff_a_b_man = !equal_a_b_man;

        REQUIRE(equal_a_b_lib == equal_a_b_man);
        REQUIRE(diff_a_b_lib == diff_a_b_man);
    }

    SECTION("Vector addition") {
        auto val_x_a = GenRandomValue(T, 4);
        auto val_y_a = GenRandomValue(T, 4);
        auto val_z_a = GenRandomValue(T, 4);
        auto val_w_a = GenRandomValue(T, 4);

        auto val_x_b = GenRandomValue(T, 4);
        auto val_y_b = GenRandomValue(T, 4);
        auto val_z_b = GenRandomValue(T, 4);
        auto val_w_b = GenRandomValue(T, 4);

        Vector4 v_a(val_x_a, val_y_a, val_z_a, val_w_a);
        Vector4 v_b(val_x_b, val_y_b, val_z_b, val_w_b);
        auto v_result = v_a + v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a + val_x_b,
                                val_y_a + val_y_b,
                                val_z_a + val_z_b,
                                val_w_a + val_w_b));
        // clang-format on
    }

    SECTION("Vector substraction") {
        auto val_x_a = GenRandomValue(T, 4);
        auto val_y_a = GenRandomValue(T, 4);
        auto val_z_a = GenRandomValue(T, 4);
        auto val_w_a = GenRandomValue(T, 4);

        auto val_x_b = GenRandomValue(T, 4);
        auto val_y_b = GenRandomValue(T, 4);
        auto val_z_b = GenRandomValue(T, 4);
        auto val_w_b = GenRandomValue(T, 4);

        Vector4 v_a(val_x_a, val_y_a, val_z_a, val_w_a);
        Vector4 v_b(val_x_b, val_y_b, val_z_b, val_w_b);
        auto v_result = v_a - v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a - val_x_b,
                                val_y_a - val_y_b,
                                val_z_a - val_z_b,
                                val_w_a - val_w_b));
        // clang-format on
    }

    SECTION("Vector element-wise product") {
        auto val_x_a = GenRandomValue(T, 4);
        auto val_y_a = GenRandomValue(T, 4);
        auto val_z_a = GenRandomValue(T, 4);
        auto val_w_a = GenRandomValue(T, 4);

        auto val_x_b = GenRandomValue(T, 4);
        auto val_y_b = GenRandomValue(T, 4);
        auto val_z_b = GenRandomValue(T, 4);
        auto val_w_b = GenRandomValue(T, 4);

        Vector4 v_a(val_x_a, val_y_a, val_z_a, val_w_a);
        Vector4 v_b(val_x_b, val_y_b, val_z_b, val_w_b);
        auto v_result = v_a * v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a * val_x_b,
                                val_y_a * val_y_b,
                                val_z_a * val_z_b,
                                val_w_a * val_w_b));
        // clang-format on
    }

    SECTION("Vector scale (by single scalar)") {
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto val_w = GenRandomValue(T, 4);
        auto scale = GenRandomValue(T, 4);

        Vector4 v(val_x, val_y, val_z, val_w);
        auto v_1 = static_cast<double>(scale) * v;
        auto v_2 = v * static_cast<double>(scale);

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_1,
                                val_x * scale,
                                val_y * scale,
                                val_z * scale,
                                val_w * scale));
        REQUIRE(FuncAllClose<T>(v_2,
                                val_x * scale,
                                val_y * scale,
                                val_z * scale,
                                val_w * scale));
        // clang-format on
    }

    SECTION("Vector length") {
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto val_w = GenRandomValue(T, 4);
        Vector4 v(val_x, val_y, val_z, val_w);

        auto length = std::sqrt(val_x * val_x + val_y * val_y + val_z * val_z +
                                val_w * val_w);
        auto v_length = math::norm(v);

        // TODO(wilbert): should check with small generated values as well. Most
        // of the values returned by the generator are quite large (their
        // squares)

        if (math::IsFloat32<T>::value) {
            // Use larger delta, as we're losing precision quickly on f32
            REQUIRE(FuncClose<T>(v_length, length, static_cast<T>(1e-3)));
        } else {
            REQUIRE(FuncClose<T>(v_length, length, EPSILON));
        }
    }

    SECTION("Vector normalization (in place)") {
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto val_w = GenRandomValue(T, 4);
        Vector4 v(val_x, val_y, val_z, val_w);
        math::normalize_in_place(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y + val_z * val_z +
                              val_w * val_w);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;
        auto val_wnorm = val_w / norm;

        auto v_norm = math::norm(v);

        REQUIRE(FuncClose<T>(v_norm, 1.0, EPSILON));
        REQUIRE(FuncAllClose<T>(v, val_xnorm, val_ynorm, val_znorm, val_wnorm));
    }

    SECTION("Vector normalization (out-of place)") {
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto val_w = GenRandomValue(T, 4);
        Vector4 v(val_x, val_y, val_z, val_w);
        auto vn = math::normalize(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y + val_z * val_z +
                              val_w * val_w);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;
        auto val_wnorm = val_w / norm;

        auto vn_norm = math::norm(vn);

        REQUIRE(FuncClose<T>(vn_norm, 1.0, EPSILON));
        REQUIRE(
            FuncAllClose<T>(vn, val_xnorm, val_ynorm, val_znorm, val_wnorm));
    }

    SECTION("Vector dot-product") {
        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);
        auto val_w_a = GenRandomValue(T, 2);

        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);
        auto val_w_b = GenRandomValue(T, 2);

        Vector4 v_a(val_x_a, val_y_a, val_z_a, val_w_a);
        Vector4 v_b(val_x_b, val_y_b, val_z_b, val_w_b);

        auto dot = val_x_a * val_x_b + val_y_a * val_y_b + val_z_a * val_z_b +
                   val_w_a * val_w_b;
        auto v_dot = math::dot(v_a, v_b);

        if (math::IsFloat32<T>::value) {
            // TODO(wilbert): If scalar version is more precise, then we might
            // have an issue with SIMD instructions not returning the correct
            // value

            // Use larger delta, as we're losing precision quickly on f32
            REQUIRE(FuncClose<T>(v_dot, dot, static_cast<T>(1e-1)));
        } else {
            REQUIRE(FuncClose<T>(v_dot, dot, EPSILON));
        }
    }

    SECTION("Vector additive inverse") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        auto val_z = GenRandomValue(T, 10);
        auto val_w = GenRandomValue(T, 10);
        Vector4 v(val_x, val_y, val_z, val_w);
        auto inv_v = -v;

        REQUIRE(FuncAllClose<T>(inv_v, -val_x, -val_y, -val_z, -val_w));
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif
