#include <iostream>
#include <tinymath/vec3_t.hpp>

template <typename T>
auto printVector(const tiny::math::Vector3<T>& vec) -> void {
    std::cout << "Vector3(";
    std::cout << vec.x() << ", ";
    std::cout << vec.y() << ", ";
    std::cout << vec.z() << ")";
    std::cout << "\n";
}

auto main() -> int {
    {
        using Vector3f = tiny::math::Vector3<tiny::math::float32_t>;
        Vector3f vec_a(1.0F, 2.0F, 3.0F);  // NOLINT
        Vector3f vec_b(2.0F, 4.0F, 6.0F);  // NOLINT

        auto vec_c = vec_a + vec_b;
        auto vec_d = vec_a - vec_b;
        printVector(vec_c);
        printVector(vec_d);
    }

    {
        using Vector3d = tiny::math::Vector3<tiny::math::float64_t>;
        Vector3d vec_a(1.0, 2.0, 3.0);  // NOLINT
        Vector3d vec_b(2.0, 4.0, 6.0);  // NOLINT

        auto vec_c = vec_a + vec_b;
        auto vec_d = vec_a - vec_b;
        printVector(vec_c);
        printVector(vec_d);
    }

    return 0;
}
