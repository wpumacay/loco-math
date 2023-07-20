#include <catch2/catch.hpp>
#include <math/vec2_t.hpp>
#include <math/vec3_t.hpp>
#include <math/vec4_t.hpp>
#include <math/mat3_t.hpp>
#include <math/quat_t.hpp>
#include <math/mat4_t.hpp>

// NOLINTNEXTLINE
#define gen_random_value(T, range_min, range_max, Nsamples)   \
    GENERATE(take(Nsamples, random(static_cast<T>(range_min), \
                                   static_cast<T>(range_max))))

namespace math {

template <typename T>
constexpr auto func_value_close(T a, T b, T eps) -> bool {
    return ((a - b) < eps) && ((a - b) > -eps);
}

template <typename T>
constexpr auto func_all_close(const ::math::Vector2<T>& vec, T x, T y, T eps)
    -> bool {
    return func_value_close(vec.x(), x, eps) &&
           func_value_close(vec.y(), y, eps);
}

template <typename T>
constexpr auto func_all_close(const ::math::Vector3<T>& vec, T x, T y, T z,
                              T eps) -> bool {
    return func_value_close(vec.x(), x, eps) &&
           func_value_close(vec.y(), y, eps) &&
           func_value_close(vec.z(), z, eps);
}

}  // namespace math
