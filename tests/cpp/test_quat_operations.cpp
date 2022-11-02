#include <catch2/catch.hpp>
#include <loco/math/quat_t_impl.hpp>

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

// clang-format off
template <typename T>
constexpr auto FuncCompareEqual(T wa, T xa, T ya, T za,
                                T wb, T xb, T yb, T zb,
                                T eps) -> bool {
    return FuncClose<T>(wa, wb, eps) && FuncClose<T>(ya, yb, eps) &&
           FuncClose<T>(za, zb, eps) && FuncClose<T>(xa, xb, eps);
}
// clang-format on

template <typename T>
auto FuncAllClose(const loco::math::Quaternion<T>& quat, T w, T x, T y, T z)
    -> bool {
    constexpr T EPSILON = static_cast<T>(loco::math::EPS);
    return FuncClose<T>(quat.w(), w, EPSILON) &&
           FuncClose<T>(quat.x(), x, EPSILON) &&
           FuncClose<T>(quat.y(), y, EPSILON) &&
           FuncClose<T>(quat.z(), z, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Quaternion class (quat_t) core Operations", "[quat_t][ops]",
                   loco::math::float32_t, loco::math::float64_t) {
    using T = TestType;
    using Quaternion = loco::math::Quaternion<T>;

    constexpr T EPSILON = static_cast<T>(loco::math::EPS);

    SECTION("Quaternion comparison ==, !=") {
        // Checking a fixed test case ******************************************
        Quaternion q_1(4.0, 1.0, 2.0, 3.0);
        Quaternion q_2(4.0, 1.0, 2.0, 3.0);
        Quaternion q_3(static_cast<T>(4.1), static_cast<T>(1.1),
                       static_cast<T>(2.1), static_cast<T>(3.1));

        REQUIRE(q_1 == q_2);
        REQUIRE(q_2 != q_3);
        REQUIRE(q_3 != q_1);

        // Checking randomized test cases **************************************
        auto val_w_a = GenRandomValue(T, 2);
        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);

        auto val_w_b = GenRandomValue(T, 2);
        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);

        Quaternion q_a(val_w_a, val_x_a, val_y_a, val_z_a);
        Quaternion q_b(val_w_b, val_x_b, val_y_b, val_z_b);

        auto equal_a_b_lib = (q_a == q_b);
        // clang-format off
        auto equal_a_b_man =
            FuncCompareEqual<T>(val_w_a, val_x_a, val_y_a, val_z_a,
                                val_w_b, val_x_b, val_y_b, val_z_b,
                                EPSILON);
        // clang-format on

        auto diff_a_b_lib = (q_a != q_b);
        auto diff_a_b_man = !equal_a_b_man;

        REQUIRE(equal_a_b_lib == equal_a_b_man);
        REQUIRE(diff_a_b_lib == diff_a_b_man);
    }

    SECTION("Quaternion addition") {
        auto val_w_a = GenRandomValue(T, 2);
        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);

        auto val_w_b = GenRandomValue(T, 2);
        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);

        Quaternion q_a(val_w_a, val_x_a, val_y_a, val_z_a);
        Quaternion q_b(val_w_b, val_x_b, val_y_b, val_z_b);
        auto q_sum = q_a + q_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(q_sum,
                                val_w_a + val_w_b,
                                val_x_a + val_x_b,
                                val_y_a + val_y_b,
                                val_z_a + val_z_b));
        // clang-format on
    }

    SECTION("Quaternion substraction") {
        auto val_w_a = GenRandomValue(T, 2);
        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);

        auto val_w_b = GenRandomValue(T, 2);
        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);

        Quaternion q_a(val_w_a, val_x_a, val_y_a, val_z_a);
        Quaternion q_b(val_w_b, val_x_b, val_y_b, val_z_b);
        auto q_sum = q_a - q_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(q_sum,
                                val_w_a - val_w_b,
                                val_x_a - val_x_b,
                                val_y_a - val_y_b,
                                val_z_a - val_z_b));
        // clang-format on
    }

    SECTION("Quaternion scale (by single scalar)") {
        auto val_w = GenRandomValue(T, 4);
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto scale = GenRandomValue(T, 4);

        Quaternion q(val_w, val_x, val_y, val_z);
        auto q_1 = static_cast<double>(scale) * q;
        auto q_2 = q * static_cast<double>(scale);

        // clang-format off
        REQUIRE(FuncAllClose<T>(q_1,
                                val_w * scale,
                                val_x * scale,
                                val_y * scale,
                                val_z * scale));
        REQUIRE(FuncAllClose<T>(q_2,
                                val_w * scale,
                                val_x * scale,
                                val_y * scale,
                                val_z * scale));
        // clang-format on
    }

    SECTION("Quaternion length") {
        auto val_w = GenRandomValue(T, 4);
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        Quaternion q(val_w, val_x, val_y, val_z);

        auto length = std::sqrt(val_w * val_w + val_x * val_x + val_y * val_y +
                                val_z * val_z);
        auto q_length = loco::math::norm(q);

        // TODO(wilbert): should check with small generated values as well. Most
        // of the values returned by the generator are quite large (their
        // squares)

        if (loco::math::IsFloat32<T>::value) {
            // Use larger delta, as we're losing precision quickly on f32
            REQUIRE(FuncClose<T>(q_length, length, static_cast<T>(1e-3)));
        } else {
            REQUIRE(FuncClose<T>(q_length, length, EPSILON));
        }
    }

    SECTION("Quaternion normalization (in place)") {
        auto val_w = GenRandomValue(T, 4);
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        Quaternion q(val_w, val_x, val_y, val_z);
        loco::math::normalize_in_place(q);

        auto norm = std::sqrt(val_w * val_w + val_x * val_x + val_y * val_y +
                              val_z * val_z);
        auto val_wnorm = val_w / norm;
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;

        auto q_norm = loco::math::norm(q);

        REQUIRE(FuncClose<T>(q_norm, 1.0, EPSILON));
        REQUIRE(FuncAllClose<T>(q, val_wnorm, val_xnorm, val_ynorm, val_znorm));
    }

    SECTION("Vector normalization (out-of place)") {
        auto val_w = GenRandomValue(T, 4);
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        Quaternion q(val_w, val_x, val_y, val_z);
        auto qn = loco::math::normalize(q);

        auto norm = std::sqrt(val_w * val_w + val_x * val_x + val_y * val_y +
                              val_z * val_z);
        auto val_wnorm = val_w / norm;
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;

        auto qn_norm = loco::math::norm(qn);

        REQUIRE(FuncClose<T>(qn_norm, 1.0, EPSILON));
        REQUIRE(
            FuncAllClose<T>(qn, val_wnorm, val_xnorm, val_ynorm, val_znorm));
    }
}
