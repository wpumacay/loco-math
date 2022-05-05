#include <iostream>
#include <loco/math/all.hpp>

template <typename T>
auto printVector(const loco::math::Vector4<T>& vec) -> void {
    std::cout << "Vector4(";
    std::cout << vec.x() << ", ";
    std::cout << vec.y() << ", ";
    std::cout << vec.z() << ", ";
    std::cout << vec.w() << ")";
    std::cout << "\n";
}

auto main() -> int {
    {
        using Vector4f = loco::math::Vector4<loco::math::float32_t>;
        Vector4f vec_a(1.0F, 2.0F, 3.0F, 4.0F);  // NOLINT
        Vector4f vec_b(2.0F, 4.0F, 6.0F, 8.0F);  // NOLINT

        auto vec_c = vec_a + vec_b;
        auto vec_d = vec_a - vec_b;
        printVector(vec_c);
        printVector(vec_d);
    }

    {
        using Vector4d = loco::math::Vector4<loco::math::float64_t>;
        Vector4d vec_a(1.0, 2.0, 3.0, 4.0);  // NOLINT
        Vector4d vec_b(2.0, 4.0, 6.0, 8.0);  // NOLINT

        auto vec_c = vec_a + vec_b;
        auto vec_d = vec_a - vec_b;
        printVector(vec_c);
        printVector(vec_d);
    }

    return 0;
}
