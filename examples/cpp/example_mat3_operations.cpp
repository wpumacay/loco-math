#include <math/mat3_t.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

template <typename T,
          typename = typename std::enable_if<math::IsScalar<T>::value>::type>
LM_NEVER_INLINE auto run_operations_mat3() -> void {
    using Mat3 = math::Matrix3<T>;
    using Vec3 = math::Vector3<T>;

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
    Mat3 mat_hadamard = math::hadamard(mat_a, mat_b);
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

    // clang-format off
    // Just a random non-singular matrix
    Mat3 mat_c(6.0, 5.0, 9.0,
               0.0, 2.0, 0.0,
               5.0, 3.0, 6.0);
    // clang-format on

    auto mat_transpose = math::transpose(mat_c);
    auto mat_trace = math::trace(mat_c);
    auto mat_determinant = math::determinant(mat_c);
    auto mat_inverse = math::inverse(mat_c);

    std::cout << "c.T: " << '\n' << mat_transpose.toString() << '\n';
    std::cout << "tr(c): " << mat_trace << '\n';
    std::cout << "det(c): " << mat_determinant << '\n';
    std::cout << "inv(c): " << '\n' << mat_inverse.toString() << '\n';
}

auto main() -> int {
    run_operations_mat3<float>();
    run_operations_mat3<double>();
    return 0;
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
