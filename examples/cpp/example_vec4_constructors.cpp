#include <iomanip>
#include <iostream>
#include <loco/math/all.hpp>
#include <type_traits>

template <typename T>
auto run_example_vec4() -> void {
    using Vec4 = loco::math::Vector4<T>;

    // Checking size and alignment (we pad by 1 scalar to keep the alignment)
    constexpr int EXPECTED_SIZE = 4 * sizeof(T);
    constexpr int EXPECTED_ALIGNMENT = 4 * sizeof(T);
    static_assert(EXPECTED_SIZE == Vec4::num_bytes_size(),
                  "Wrong number of bytes in internal storage");
    static_assert(EXPECTED_ALIGNMENT == Vec4::num_bytes_alignment(),
                  "Wrong alignment of internal storage");

    // Just note which scalar type we're using
    if (std::is_same<T, float>()) {
        std::cout << "Checking out Vector4<float> types *****************\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Checking out Vector4<double> types ****************\n";
    } else {
        std::cout << "Uhmmm, neither float nor double used as scalar type D:\n";
        return;
    }

    // Using some of the constructors available for 4d-vector types
    Vec4 vec_a;
    Vec4 vec_b(1.0);
    Vec4 vec_c(1.0, 2.0);
    Vec4 vec_d(1.0, 2.0, 3.0);
    Vec4 vec_e(1.0, 2.0, 3.0, 4.0);
    Vec4 vec_f = {2.0, 4.0, 6.0, 8.0};
    Vec4 vec_g;
    // cppcheck-suppress constStatement
    vec_g << 1.0, 2.0, 3.0, 4.0;

    // Send the sample vectors to the standard output stream
    std::cout << "Vector4()" << '\n';
    std::cout << vec_a << "\n";
    std::cout << "Vector4(x)" << '\n';
    std::cout << vec_b << "\n";
    std::cout << "Vector4(x, y)" << '\n';
    std::cout << vec_c << "\n";
    std::cout << "Vector4(x, y, z)" << '\n';
    std::cout << vec_d << "\n";
    std::cout << "Vector4(x, y, z, w)" << '\n';
    std::cout << vec_e << "\n";
    std::cout << "Vector4 vec = {x, y, z, w}" << '\n';
    std::cout << vec_f << "\n";
    std::cout << "Vector4 vec; vec << x, y, z, w;" << '\n';
    std::cout << vec_g << "\n";

    std::cout << "**********************************************************\n";
}

auto main() -> int {
    constexpr int32_t PRINT_PRECISION = 7;
    std::cout << std::setprecision(PRINT_PRECISION);

    run_example_vec4<float>();
    run_example_vec4<double>();

    return 0;
}
