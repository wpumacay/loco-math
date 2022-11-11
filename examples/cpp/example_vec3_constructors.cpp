#include <iomanip>
#include <iostream>

#include <math/vec3_t.hpp>

template <typename T>
auto run_example_vec3() -> void {
    using Vec3 = math::Vector3<T>;

    // Just note which scalar type we're using
    if (std::is_same<T, float>()) {
        std::cout << "Checking out Vector3<float> types *****************\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Checking out Vector3<double> types ****************\n";
    } else {
        std::cout << "Uhmmm, neither float nor double used as scalar type D:\n";
        return;
    }

    // Using some of the constructors available for 3d-vector types
    Vec3 vec_a;
    Vec3 vec_b(1.0);
    Vec3 vec_c(1.0, 2.0);
    Vec3 vec_d(1.0, 2.0, 3.0);
    Vec3 vec_e = {2.0, 4.0, 6.0};
    Vec3 vec_f;
    // cppcheck-suppress constStatement
    vec_f << 1.0, 2.0, 3.0;

    // Send the sample vectors to the standard output stream
    std::cout << "Vector3()" << '\n';
    std::cout << vec_a << "\n";
    std::cout << "Vector3(x)" << '\n';
    std::cout << vec_b << "\n";
    std::cout << "Vector3(x, y)" << '\n';
    std::cout << vec_c << "\n";
    std::cout << "Vector3(x, y, z)" << '\n';
    std::cout << vec_d << "\n";
    std::cout << "Vector3 vec = {x, y, z}" << '\n';
    std::cout << vec_e << "\n";
    std::cout << "Vector3 vec; vec << x, y, z;" << '\n';
    std::cout << vec_f << "\n";

    std::cout << "**********************************************************\n";
}

auto main() -> int {
    constexpr int32_t PRINT_PRECISION = 7;
    std::cout << std::setprecision(PRINT_PRECISION);

    run_example_vec3<float>();
    run_example_vec3<double>();

    return 0;
}
