#include <loco/math/mat2_t_impl.hpp>
#include <type_traits>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

template <typename T, typename = typename std::enable_if<
                          loco::math::IsScalar<T>::value>::type>
LM_NEVER_INLINE auto run_operations_mat2() -> void {
    using Mat2 = loco::math::Matrix2<T>;
    using Vec2 = loco::math::Vector2<T>;

    // Preamble (show the type we're currently working with)
    if (std::is_same<T, float>()) {
        std::cout << "Matrix2-float32 type:\n";
    } else if (std::is_same<T, double>()) {
        std::cout << "Matrix2-float64 type:\n";
    }

    // clang-format off
    Mat2 mat_a(1.0,  2.0,  3.0,  4.0);

    Mat2 mat_b(2.0,  4.0,  6.0,  8.0);

    Vec2 vec(1.0, 2.0);
    // clang-format on

    Mat2 mat_sum = mat_a + mat_b;
    Mat2 mat_diff = mat_a - mat_b;
    Mat2 mat_scale_1 = 2.5 * mat_a;
    Mat2 mat_scale_2 = mat_b * 0.25;
    Mat2 mat_matmul = mat_a * mat_b;
    Mat2 mat_hadamard = loco::math::hadamard(mat_a, mat_b);
    Vec2 vec_matvecmul = mat_a * vec;

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
    Mat2 mat_c(5.0, 5.0,
               4.0, 8.0);
    // clang-format on

    auto mat_transpose = loco::math::transpose(mat_c);
    auto mat_trace = loco::math::trace(mat_c);
    auto mat_determinant = loco::math::determinant(mat_c);
    auto mat_inverse = loco::math::inverse(mat_c);

    std::cout << "c.T: " << '\n' << mat_transpose.toString() << '\n';
    std::cout << "tr(c): " << mat_trace << '\n';
    std::cout << "det(c): " << mat_determinant << '\n';
    std::cout << "inv(c): " << '\n' << mat_inverse.toString() << '\n';
}

auto main() -> int {
    run_operations_mat2<float>();
    run_operations_mat2<double>();
    return 0;
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#endif
