#include <iomanip>
#include <iostream>

#include <math/vec2_t.hpp>

template <typename T>
auto run_example_vec2() -> void {
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

    // Using some of the constructors available for 3d-vector types
    Vec2 vec_a;
    Vec2 vec_b(1.0);
    Vec2 vec_c(1.0, 2.0);
    Vec2 vec_e = {2.0, 4.0};
    Vec2 vec_f;
    // cppcheck-suppress constStatement
    vec_f << 1.0, 2.0;

    // Send the sample vectors to the standard output stream
    std::cout << "Vector2()" << '\n';
    std::cout << vec_a << "\n";
    std::cout << "Vector2(x)" << '\n';
    std::cout << vec_b << "\n";
    std::cout << "Vector2(x, y)" << '\n';
    std::cout << vec_c << "\n";
    std::cout << "Vector2 vec = {x, y}" << '\n';
    std::cout << vec_e << "\n";
    std::cout << "Vector2 vec; vec << x, y;" << '\n';
    std::cout << vec_f << "\n";

    std::cout << "**********************************************************\n";
}

auto main() -> int {
    constexpr int32_t PRINT_PRECISION = 7;
    std::cout << std::setprecision(PRINT_PRECISION);

    run_example_vec2<float>();
    run_example_vec2<double>();

    return 0;
}
