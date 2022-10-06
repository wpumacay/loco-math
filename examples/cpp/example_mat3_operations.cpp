#include <loco/math/mat3_t_impl.hpp>
#include <type_traits>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

template <typename T, typename = typename std::enable_if<
                          loco::math::IsScalar<T>::value>::type>
auto run_operations_mat4() -> void {
    using Mat3 = loco::math::Matrix3<T>;
    using Vec3 = loco::math::Vector3<T>;

    // Preamble (show the type we're currently working with)
    if (std::is_same<T, float>()) {
        std::cout << "Matrix3-float32 type:\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Matrix3-float64 type:\n";
    }

    // clang-format off
    Mat3 mat_a(1.0, 2.0, 3.0,
               4.0, 5.0, 6.0,
               7.0, 8.0, 9.0);

    Mat3 mat_b(2.0, 4.0, 6.0,
               8.0, 10.0, 12.0,
               14.0, 16.0, 18.0);

    Vec3 vec(1.0, 2.0, 3.0);
    // clang-format on

    Mat3 mat_sum = mat_a + mat_b;
    Mat3 mat_diff = mat_a - mat_b;
    Mat3 mat_scale_1 = 2.5 * mat_a;
    Mat3 mat_scale_2 = mat_b * 0.25;
    Mat3 mat_matmul = mat_a * mat_b;
    Mat3 mat_hadamard = loco::math::hadamard(mat_a, mat_b);
    Vec3 vec_matvecmul = mat_a * vec;

    std::cout << "a: " << '\n' << mat_a.toString() << '\n';
    std::cout << "b: " << '\n' << mat_b.toString() << '\n';
    std::cout << "a + b: " << '\n' << mat_sum.toString() << '\n';
    std::cout << "a - b: " << '\n' << mat_diff.toString() << '\n';
    std::cout << "2.5 * a: " << '\n' << mat_scale_1.toString() << '\n';
    std::cout << "b * 0.25: " << '\n' << mat_scale_2.toString() << '\n';
    std::cout << "a * b: " << '\n' << mat_matmul.toString() << '\n';
    std::cout << "a . b: " << '\n' << mat_hadamard.toString() << '\n';
    std::cout << "a * v: " << '\n' << vec_matvecmul.toString() << '\n';
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

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
