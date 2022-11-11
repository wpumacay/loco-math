#include <math/vec4_t.hpp>

template <typename T, typename = typename std::enable_if<
                          loco::math::IsScalar<T>::value>::type>
LM_NEVER_INLINE auto run_operations_vec4() -> void {
    using Vec4 = loco::math::Vector4<T>;

    // Preamble (show the type we're currently working with)
    if (std::is_same<T, float>()) {
        std::cout << "Vector2-float32 type:\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Vector2-float64 type:\n";
    }

    Vec4 vec_a(1.0, 2.0, 3.0, 4.0);
    Vec4 vec_b(3.0, 5.0, 7.0, 9.0);

    Vec4 vec_sum = vec_a + vec_b;
    Vec4 vec_diff = vec_a - vec_b;
    Vec4 vec_scale_1 = 2.5 * vec_a;
    Vec4 vec_scale_2 = vec_b * 0.25;
    Vec4 vec_mul = vec_a * vec_b;

    std::cout << "a: " << '\n' << vec_a.toString() << '\n';
    std::cout << "b: " << '\n' << vec_b.toString() << '\n';
    std::cout << "a + b: " << '\n' << vec_sum.toString() << '\n';
    std::cout << "a - b: " << '\n' << vec_diff.toString() << '\n';
    std::cout << "2.5 * a: " << '\n' << vec_scale_1.toString() << '\n';
    std::cout << "b * 0.25: " << '\n' << vec_scale_2.toString() << '\n';
    std::cout << "a . b: " << '\n' << loco::math::dot(vec_a, vec_b) << '\n';
    std::cout << "b . a: " << '\n' << loco::math::dot(vec_b, vec_a) << '\n';
    std::cout << "|a|: " << '\n' << loco::math::norm(vec_a) << '\n';
    std::cout << "|a|^2: " << '\n' << loco::math::squareNorm(vec_a) << '\n';
    std::cout << "|b|: " << '\n' << loco::math::norm(vec_b) << '\n';
    std::cout << "|b|^2: " << '\n' << loco::math::squareNorm(vec_b) << '\n';
    std::cout << "a * b: " << '\n' << vec_mul.toString() << '\n';
    std::cout << "a == b: " << '\n'
              << ((vec_a == vec_b) ? "True" : "False") << '\n';
    std::cout << "a != b: " << '\n'
              << ((vec_a != vec_b) ? "True" : "False") << '\n';
}

auto main() -> int {
    run_operations_vec4<float>();
    run_operations_vec4<double>();
    return 0;
}
