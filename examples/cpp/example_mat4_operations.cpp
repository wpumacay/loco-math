#include <tinymath/tinymath.hpp>
#include <type_traits>

template <typename T, typename = typename std::enable_if<
                          tiny::math::IsScalar<T>::value>::type>
auto run_operations_mat4() -> void {
    using Mat4 = tiny::math::Matrix4<T>;

    // Preamble (show the type we're currently working with)
    if (std::is_same<T, float>()) {
        std::cout << "Matrix4-float32 type:\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Matrix4-float64 type:\n";
    }

    // clang-format off
    Mat4 mat_a(1.0,  2.0,  3.0,  4.0,
               5.0,  6.0,  7.0,  8.0,
               9.0,  10.0, 11.0, 12.0,
               13.0, 14.0, 15.0, 16.0);

    Mat4 mat_b(2.0,  4.0,  6.0,  8.0,
               10.0, 12.0, 14.0, 16.0,
               18.0, 20.0, 22.0, 24.0,
               26.0, 28.0, 30.0, 32.0);
    // clang-format on

    Mat4 mat_sum = mat_a + mat_b;
    Mat4 mat_diff = mat_a - mat_b;
    Mat4 mat_scale_1 = 2.5 * mat_a;
    Mat4 mat_scale_2 = mat_b * 0.25;
    Mat4 mat_matmul = mat_a * mat_b;
    Mat4 mat_hadamard = tiny::math::hadamard(mat_a, mat_b);

    std::cout << "a: " << '\n' << mat_a.toString() << '\n';
    std::cout << "b: " << '\n' << mat_b.toString() << '\n';
    std::cout << "a + b: " << '\n' << mat_sum.toString() << '\n';
    std::cout << "a - b: " << '\n' << mat_diff.toString() << '\n';
    std::cout << "2.5 * a: " << '\n' << mat_scale_1.toString() << '\n';
    std::cout << "b * 0.25: " << '\n' << mat_scale_2.toString() << '\n';
    std::cout << "a * b: " << '\n' << mat_matmul.toString() << '\n';
    std::cout << "a . b: " << '\n' << mat_hadamard.toString() << '\n';
    std::cout << "a == b: " << '\n'
              << ((mat_a == mat_b) ? "True" : "False") << '\n';
    std::cout << "a != b: " << '\n'
              << ((mat_a != mat_b) ? "True" : "False") << '\n';
}

auto main() -> int {
    run_operations_mat4<float>();
    run_operations_mat4<double>();
    return 0;
}
