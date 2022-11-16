#include <catch2/catch.hpp>
#include <math/vec3_t.hpp>

constexpr double RANGE_MIN = -1000.0;
constexpr double RANGE_MAX = 1000.0;

// NOLINTNEXTLINE
#define GenRandomValue(Type, Nsamples)                           \
    GENERATE(take(Nsamples, random(static_cast<Type>(RANGE_MIN), \
                                   static_cast<Type>(RANGE_MAX))))

// NOLINTNEXTLINE
#define GenRandomScaleValue(Type, Nsamples, Scale_min, Scale_max) \
    GENERATE(take(Nsamples, random(static_cast<Type>(Scale_min),  \
                                   static_cast<Type>(Scale_max))))

template <typename T>
constexpr auto FuncClose(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
constexpr auto FuncCompareEqual(T xa, T ya, T za, T xb, T yb, T zb, T eps)
    -> bool {
    return FuncClose<T>(xa, xb, eps) && FuncClose<T>(ya, yb, eps) &&
           FuncClose<T>(za, zb, eps);
}

template <typename T>
auto FuncAllClose(const math::Vector3<T>& vec, T x, T y, T z) -> bool {
    constexpr T EPSILON = static_cast<T>(math::EPS);
    return FuncClose<T>(vec.x(), x, EPSILON) &&
           FuncClose<T>(vec.y(), y, EPSILON) && FuncClose(vec.z(), z, EPSILON);
}

// NOLINTNEXTLINE
TEMPLATE_TEST_CASE("Vector3 class (vec3_t) core Operations", "[vec3_t][ops]",
                   math::float32_t, math::float64_t) {
    using T = TestType;
    using Vector3 = math::Vector3<T>;

    constexpr T EPSILON = static_cast<T>(math::EPS);

    SECTION("Vector comparison ==, !=") {
        Vector3 v_1(1.0, 2.0, 3.0);  // NOLINT
        Vector3 v_2(1.0, 2.0, 3.0);  // NOLINT
        Vector3 v_3(static_cast<T>(1.1), static_cast<T>(2.1),
                    static_cast<T>(3.1));

        REQUIRE(v_1 == v_2);
        REQUIRE(v_2 != v_3);
        REQUIRE(v_3 != v_1);

        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);

        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);

        auto equal_a_b_lib = (v_a == v_b);
        auto equal_a_b_man = FuncCompareEqual<T>(
            val_x_a, val_y_a, val_z_a, val_x_b, val_y_b, val_z_b, EPSILON);

        auto diff_a_b_lib = (v_a != v_b);
        auto diff_a_b_man = !equal_a_b_man;

        REQUIRE(equal_a_b_lib == equal_a_b_man);
        REQUIRE(diff_a_b_lib == diff_a_b_man);
    }

    SECTION("Vector addition") {
        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);

        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);
        auto v_result = v_a + v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a + val_x_b,
                                val_y_a + val_y_b,
                                val_z_a + val_z_b));
        // clang-format on
    }

    SECTION("Vector substraction") {
        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);

        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);
        auto v_result = v_a - v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a - val_x_b,
                                val_y_a - val_y_b,
                                val_z_a - val_z_b));
        // clang-format on
    }

    SECTION("Vector element-wise product") {
        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);

        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);
        auto v_result = v_a * v_b;

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_result,
                                val_x_a * val_x_b,
                                val_y_a * val_y_b,
                                val_z_a * val_z_b));
        // clang-format on
    }

    SECTION("Vector scale (by single scalar)") {
        auto val_x = GenRandomValue(T, 8);
        auto val_y = GenRandomValue(T, 8);
        auto val_z = GenRandomValue(T, 8);
        auto scale = GenRandomScaleValue(T, 4, -10.0, 10.0);

        Vector3 v(val_x, val_y, val_z);
        auto v_1 = static_cast<double>(scale) * v;
        auto v_2 = v * static_cast<double>(scale);

        // clang-format off
        REQUIRE(FuncAllClose<T>(v_1,
                                val_x * scale,
                                val_y * scale,
                                val_z * scale));
        REQUIRE(FuncAllClose<T>(v_2,
                                val_x * scale,
                                val_y * scale,
                                val_z * scale));
        // clang-format on
    }

    SECTION("Vector length") {
        auto val_x = GenRandomValue(T, 8);
        auto val_y = GenRandomValue(T, 8);
        auto val_z = GenRandomValue(T, 8);
        Vector3 v(val_x, val_y, val_z);

        auto length_square = val_x * val_x + val_y * val_y + val_z * val_z;
        auto length = std::sqrt(length_square);

        auto v_length_square = math::squareNorm(v);
        auto v_length = math::norm(v);

        REQUIRE(FuncClose(v_length_square, length_square, EPSILON));
        REQUIRE(FuncClose(v_length, length, EPSILON));
    }

    SECTION("Vector normalization (in place)") {
        auto val_x = GenRandomValue(T, 8);
        auto val_y = GenRandomValue(T, 8);
        auto val_z = GenRandomValue(T, 8);
        Vector3 v(val_x, val_y, val_z);
        math::normalize_in_place(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y + val_z * val_z);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;

        auto v_norm = math::norm(v);

        REQUIRE(FuncClose<T>(v_norm, 1.0, EPSILON));
        REQUIRE(FuncAllClose<T>(v, val_xnorm, val_ynorm, val_znorm));
    }

    SECTION("Vector normalization (out-of place)") {
        auto val_x = GenRandomValue(T, 8);
        auto val_y = GenRandomValue(T, 8);
        auto val_z = GenRandomValue(T, 8);
        Vector3 v(val_x, val_y, val_z);
        auto vn = math::normalize(v);

        auto norm = std::sqrt(val_x * val_x + val_y * val_y + val_z * val_z);
        auto val_xnorm = val_x / norm;
        auto val_ynorm = val_y / norm;
        auto val_znorm = val_z / norm;

        auto vn_norm = math::norm(vn);

        REQUIRE(FuncClose<T>(vn_norm, static_cast<T>(1.0), EPSILON));
        REQUIRE(FuncAllClose<T>(vn, val_xnorm, val_ynorm, val_znorm));
    }

    SECTION("Vector dot-product") {
        auto val_x_a = GenRandomValue(T, 2);
        auto val_y_a = GenRandomValue(T, 2);
        auto val_z_a = GenRandomValue(T, 2);

        auto val_x_b = GenRandomValue(T, 2);
        auto val_y_b = GenRandomValue(T, 2);
        auto val_z_b = GenRandomValue(T, 2);

        Vector3 v_a(val_x_a, val_y_a, val_z_a);
        Vector3 v_b(val_x_b, val_y_b, val_z_b);

        auto dot = val_x_a * val_x_b + val_y_a * val_y_b + val_z_a * val_z_b;
        auto v_dot = math::dot(v_a, v_b);

        REQUIRE(FuncClose(v_dot, dot, EPSILON));
    }

    SECTION("Vector cross-product") {
        // Checking standard basis vectors: i, j, k
        {
            Vector3 v_i(1.0, 0.0, 0.0);
            Vector3 v_j(0.0, 1.0, 0.0);
            Vector3 v_k(0.0, 0.0, 1.0);

            auto v_ij = math::cross(v_i, v_j);
            auto v_jk = math::cross(v_j, v_k);
            auto v_ki = math::cross(v_k, v_i);

            // i x j = k
            REQUIRE(FuncAllClose<T>(v_ij, 0.0, 0.0, 1.0));

            // j x k = i
            REQUIRE(FuncAllClose<T>(v_jk, 1.0, 0.0, 0.0));

            // k x i = j
            REQUIRE(FuncAllClose<T>(v_ki, 0.0, 1.0, 0.0));
        }

        // Checking a fixed case (a.cross(b) + c)
        {
            Vector3 v_a(1.0, 2.0, 3.0);  // NOLINT
            Vector3 v_b(4.0, 5.0, 6.0);  // NOLINT
            Vector3 v_c(7.0, 8.0, 9.0);  // NOLINT

            auto result = math::cross(v_a, v_b) + v_c;
            REQUIRE(FuncAllClose<T>(result, 4.0, 14.0, 6.0));
        }
    }

    SECTION("Vector additive inverse") {
        auto val_x = GenRandomValue(T, 10);
        auto val_y = GenRandomValue(T, 10);
        auto val_z = GenRandomValue(T, 10);
        Vector3 v(val_x, val_y, val_z);
        auto inv_v = -v;

        REQUIRE(FuncAllClose<T>(inv_v, -val_x, -val_y, -val_z));
    }
}
