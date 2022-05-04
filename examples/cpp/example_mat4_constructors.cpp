#include <iomanip>
#include <iostream>
#include <loco/math/all.hpp>
#include <type_traits>

template <typename T>
auto run_example_mat4() -> void {
    using Mat4 = loco::math::Matrix4<T>;
    using Vec4 = typename Mat4::ColumnType;

    // Checking size and alignment
    if (std::is_same<T, float>()) {
        std::cout << "Matrix4-float32 type:\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Matrix4-float64 type:\n";
    }

    std::cout << "sizeof(Mat4): " << sizeof(Mat4) << "\n";
    std::cout << "alignof(Mat4): " << alignof(Mat4) << "\n";

    // Default constructor: initializes to zero-matrix
    Mat4 mat_a;

    // clang-format off
    // First constructor: initializes matrix entries given scalar values
    Mat4 mat_b(1.0,  2.0,  3.0,  4.0,
               5.0,  6.0,  7.0,  8.0,
               9.0,  10.0, 11.0, 12.0,
               13.0, 14.0, 15.0, 16.0);
    // clang-format on

    // Second constructor: initialize as diagonal matrix given diagonal values
    Mat4 mat_c(1.0, 6.0, 11.0, 16.0);

    // Third constructor: initialize matrix from columns (vec4s)
    Vec4 col0(1.0, 5.0, 9.0, 13.0);
    Vec4 col1(2.0, 6.0, 10.0, 14.0);
    Vec4 col2(3.0, 7.0, 11.0, 15.0);
    Vec4 col3(4.0, 8.0, 12.0, 16.0);
    Mat4 mat_d(col0, col1, col2, col3);

    // clang-format off
    // Construct from comma-initializer
    Mat4 mat_e;
    mat_e << 1.0,  2.0,  3.0,  4.0,
             5.0,  6.0,  7.0,  8.0,
             9.0,  10.0, 11.0, 12.0,
             13.0, 14.0, 15.0, 16.0;
    // clang-format on

    // Show the matrices :)
    std::cout << "matrix-a\n";
    std::cout << mat_a.toString() << "\n";
    std::cout << "--------------\n";

    std::cout << "matrix-b\n";
    std::cout << mat_b.toString() << "\n";
    std::cout << "--------------\n";

    std::cout << "matrix-c\n";
    std::cout << mat_c.toString() << "\n";
    std::cout << "--------------\n";

    std::cout << "matrix-d\n";
    std::cout << mat_d.toString() << "\n";
    std::cout << "--------------\n";

    std::cout << "matrix-e\n";
    std::cout << mat_e.toString() << "\n";
    std::cout << "--------------\n";

    std::cout << "**********************************************************\n";
}

auto main() -> int {
    constexpr int32_t PRINT_PRECISION = 7;
    std::cout << std::setprecision(PRINT_PRECISION);

    run_example_mat4<loco::math::float32_t>();
    run_example_mat4<loco::math::float64_t>();

    return 0;
}
