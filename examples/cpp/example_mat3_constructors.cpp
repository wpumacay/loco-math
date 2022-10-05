#include <iomanip>
#include <iostream>
#include <loco/math/mat3_t.hpp>
#include <type_traits>

template <typename T>
auto run_example_mat2() -> void {
    using Mat3 = loco::math::Matrix3<T>;
    using Vec3 = typename Mat3::ColumnType;

    // Checking size and alignment
    if (std::is_same<T, float>()) {
        std::cout << "Matrix3-float32 type:\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Matrix3-float64 type:\n";
    }

    std::cout << "sizeof(Mat3): " << sizeof(Mat3) << '\n';
    std::cout << "alignof(Mat3): " << alignof(Mat3) << '\n';

    // Default constructor: initializes to zero-matrix
    Mat3 mat_a;

    // clang-format off
    // First constructor: initializes matrix entries given scalar values
    Mat3 mat_b(1.0, 2.0, 3.0,
               4.0, 5.0, 6.0,
               7.0, 8.0, 9.0);
    // clang-format on

    // Second constructor: initialize as diagonal matrix given diagonal values
    Mat3 mat_c(1.0, 2.0, 3.0);

    // Third constructor: initialize matrix from columns (vec4s)
    Vec3 col0(1.0, 2.0, 3.0);
    Vec3 col1(2.0, 3.0, 4.0);
    Vec3 col2(3.0, 4.0, 5.0);
    Mat3 mat_d(col0, col1, col2);

    // Construct from comma-initializer
    Mat3 mat_e;
    mat_e << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;

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
