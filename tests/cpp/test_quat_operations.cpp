#include <catch2/catch.hpp>
#include <math/quat_t.hpp>

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
auto FuncAllClose(const math::Quaternion<T>& quat, T w, T x, T y, T z) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);
    return FuncClose<T>(quat.w(), w, EPSILON) &&
           FuncClose<T>(quat.x(), x, EPSILON) &&
           FuncClose<T>(quat.y(), y, EPSILON) &&
           FuncClose<T>(quat.z(), z, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Quaternion class (quat_t) core Operations", "[quat_t][ops]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Quat = math::Quaternion<T>;
    using Vec3 = ::math::Vector3<T>;

    constexpr T EPSILON = static_cast<T>(math::EPS);

    SECTION("Quaternion comparison ==, !=") {
        // Checking a fixed test case ******************************************
        Quat q_1(4.0, 1.0, 2.0, 3.0);
        Quat q_2(4.0, 1.0, 2.0, 3.0);
        Quat q_3(static_cast<T>(4.1), static_cast<T>(1.1), static_cast<T>(2.1),
                 static_cast<T>(3.1));

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

        Quat q_a(val_w_a, val_x_a, val_y_a, val_z_a);
        Quat q_b(val_w_b, val_x_b, val_y_b, val_z_b);

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

        Quat q_a(val_w_a, val_x_a, val_y_a, val_z_a);
        Quat q_b(val_w_b, val_x_b, val_y_b, val_z_b);
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

        Quat q_a(val_w_a, val_x_a, val_y_a, val_z_a);
        Quat q_b(val_w_b, val_x_b, val_y_b, val_z_b);
        auto q_sum = q_a - q_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(q_sum,
                                val_w_a - val_w_b,
                                val_x_a - val_x_b,
                                val_y_a - val_y_b,
                                val_z_a - val_z_b));
        // clang-format on
    }

    SECTION("Quaternion product") {
        auto a_w = GenRandomValue(T, 2);
        auto a_x = GenRandomValue(T, 2);
        auto a_y = GenRandomValue(T, 2);
        auto a_z = GenRandomValue(T, 2);

        auto b_w = GenRandomValue(T, 2);
        auto b_x = GenRandomValue(T, 2);
        auto b_y = GenRandomValue(T, 2);
        auto b_z = GenRandomValue(T, 2);

        Quat q_a(a_w, a_x, a_y, a_z);
        Quat q_b(b_w, b_x, b_y, b_z);
        auto q_prod = q_a * q_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(q_prod,
            a_w * b_w - a_x * b_x - a_y * b_y - a_z * b_z,
            a_w * b_x + b_w * a_x + a_y * b_z - b_y * a_z,
            a_w * b_y + b_w * a_y + a_z * b_x - b_z * a_x,
            a_w * b_z + b_w * a_z + a_x * b_y - b_x * a_y));
        // clang-format on
    }

    SECTION("Quaternion scale (by single scalar)") {
        auto val_w = GenRandomValue(T, 4);
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        auto scale = GenRandomValue(T, 4);

        Quat q(val_w, val_x, val_y, val_z);
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
        Quat q(val_w, val_x, val_y, val_z);

        auto length = std::sqrt(val_w * val_w + val_x * val_x + val_y * val_y +
                                val_z * val_z);
        auto q_length = math::norm(q);

        // TODO(wilbert): should check with small generated values as well. Most
        // of the values returned by the generator are quite large (their
        // squares)

        if (math::IsFloat32<T>::value) {
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
        Quat q(val_w, val_x, val_y, val_z);
        math::normalize_in_place(q);

        auto norm = std::sqrt(val_w * val_w + val_x * val_x + val_y * val_y +
                              val_z * val_z);
        auto val_wnorm = val_w / norm;
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;

        auto q_norm = math::norm(q);

        REQUIRE(FuncClose<T>(q_norm, 1.0, EPSILON));
        REQUIRE(FuncAllClose<T>(q, val_wnorm, val_xnorm, val_ynorm, val_znorm));
    }

    SECTION("Quaternion normalization (out-of place)") {
        auto val_w = GenRandomValue(T, 4);
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        Quat q(val_w, val_x, val_y, val_z);
        auto qn = math::normalize(q);

        auto norm = std::sqrt(val_w * val_w + val_x * val_x + val_y * val_y +
                              val_z * val_z);
        auto val_wnorm = val_w / norm;
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;

        auto qn_norm = math::norm(qn);

        REQUIRE(FuncClose<T>(qn_norm, 1.0, EPSILON));
        REQUIRE(
            FuncAllClose<T>(qn, val_wnorm, val_xnorm, val_ynorm, val_znorm));
    }

    SECTION("Quaternion conjugate") {
        auto val_w = GenRandomValue(T, 4);
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        Quat q(val_w, val_x, val_y, val_z);

        auto q_conj = math::conjugate<T>(q);
        REQUIRE(FuncAllClose<T>(q_conj, val_w, -val_x, -val_y, -val_z));
    }

    SECTION("Quaternion inverse") {
        auto val_w = GenRandomValue(T, 4);
        auto val_x = GenRandomValue(T, 4);
        auto val_y = GenRandomValue(T, 4);
        auto val_z = GenRandomValue(T, 4);
        Quat q(val_w, val_x, val_y, val_z);

        auto length_sq =
            val_w * val_w + val_x * val_x + val_y * val_y + val_z * val_z;
        auto qinv_w = val_w / length_sq;
        auto qinv_x = -val_x / length_sq;
        auto qinv_y = -val_y / length_sq;
        auto qinv_z = -val_z / length_sq;

        auto q_inv = math::inverse<T>(q);
        REQUIRE(FuncAllClose<T>(q_inv, qinv_w, qinv_x, qinv_y, qinv_z));
    }

    SECTION("Quaternion as rotations") {
        // Check the rotation of the basis vectors around each of the three axes
        Vec3 vec_i(1.0, 0.0, 0.0);
        Vec3 vec_j(0.0, 1.0, 0.0);
        Vec3 vec_k(0.0, 0.0, 1.0);

        auto q_x = Quat::RotationX(static_cast<T>(::math::PI / 2.0));
        auto q_y = Quat::RotationY(static_cast<T>(::math::PI / 2.0));
        auto q_z = Quat::RotationZ(static_cast<T>(::math::PI / 2.0));

        REQUIRE(vec_j == ::math::rotate<T>(q_z, vec_i));
        REQUIRE(vec_k == ::math::rotate<T>(q_x, vec_j));
        REQUIRE(vec_i == ::math::rotate<T>(q_y, vec_k));
    }
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif
