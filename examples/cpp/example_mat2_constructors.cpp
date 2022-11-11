#include <iomanip>
#include <iostream>

#include <math/mat2_t.hpp>

template <typename T>
auto run_example_mat2() -> void {
    using Mat2 = loco::math::Matrix2<T>;
    using Vec2 = typename Mat2::ColumnType;

    // Checking size and alignment
    if (std::is_same<T, float>()) {
        std::cout << "Matrix4-float32 type:\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Matrix4-float64 type:\n";
    }

    std::cout << "sizeof(Mat2): " << sizeof(Mat2) << '\n';
    std::cout << "alignof(Mat2): " << alignof(Mat2) << '\n';

    // Default constructor: initializes to zero-matrix
    Mat2 mat_a;

    // clang-format off
    // First constructor: initializes matrix entries given scalar values
    Mat2 mat_b(1.0,  2.0,  3.0,  4.0);
    // clang-format on

    // Second constructor: initialize as diagonal matrix given diagonal values
    Mat2 mat_c(1.0, 16.0);

    // Third constructor: initialize matrix from columns (vec4s)
    Vec2 col0(1.0, 5.0);
    Vec2 col1(2.0, 6.0);
    Mat2 mat_d(col0, col1);

    // Construct from comma-initializer
    Mat2 mat_e;
    mat_e << 1.0, 2.0, 3.0, 4.0;

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

    run_example_mat2<loco::math::float32_t>();
    run_example_mat2<loco::math::float64_t>();

    return 0;
}
