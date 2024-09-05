#include <iomanip>
#include <iostream>

#include <math/vec2_t.hpp>

template <typename T>
auto run_example_lerp_vec2() -> void {
    using Vec2 = math::Vector2<T>;

    // Just note which scalar type we're using
    if (std::is_same<T, float>()) {
        std::cout << "Checking out Vector2<float> types *****************\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Checking out Vector2<double> types ****************\n";
    } else {
        std::cout << "Uhmmm, neither float nor double used as scalar type D:\n";
        return;
    }

    Vec2 vec_a = {1.0, 0.0};
    Vec2 vec_b = {0.0, 1.0};
    Vec2 vec_c = ::math::lerp<T>(vec_a, vec_b, 0.5);

    std::cout << "vec_a: " << vec_a << std::endl;
    std::cout << "vec_b: " << vec_b << std::endl;
    std::cout << "lerp(vec_a, vec_b, 0.5): " << vec_c << std::endl;

    std::cout << "**********************************************************\n";
}

auto main() -> int {
    run_example_lerp_vec2<float>();
    run_example_lerp_vec2<double>();

    return 0;
}
