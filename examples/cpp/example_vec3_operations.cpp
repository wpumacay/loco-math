#include <iostream>
#include <loco/math/all.hpp>

template <typename T>
auto printVector(const loco::math::Vector3<T>& vec) -> void {
    std::cout << "Vector3(";
    std::cout << vec.x() << ", ";
    std::cout << vec.y() << ", ";
    std::cout << vec.z() << ")";
    std::cout << "\n";
}

auto main() -> int {
    {
        using Vector3f = loco::math::Vector3<loco::math::float32_t>;
        Vector3f vec_a(1.0F, 2.0F, 3.0F);  // NOLINT
        Vector3f vec_b(2.0F, 4.0F, 6.0F);  // NOLINT

        auto vec_c = vec_a + vec_b;
        auto vec_d = vec_a - vec_b;
        printVector(vec_c);
        printVector(vec_d);

        std::cout << "dot-vec3f(a,b): " << loco::math::dot(vec_a, vec_b)
                  << "\n";
        std::cout << "len^2-vec3f(a): " << loco::math::squareNorm(vec_a)
                  << "\n";
        std::cout << "len^2-vec3f(b): " << loco::math::squareNorm(vec_b)
                  << "\n";
        std::cout << "len-vec3f(a): " << loco::math::norm(vec_a) << "\n";
        std::cout << "len-vec3f(b): " << loco::math::norm(vec_b) << "\n";
    }

    {
        using Vector3d = loco::math::Vector3<loco::math::float64_t>;
        Vector3d vec_a(1.0, 2.0, 3.0);  // NOLINT
        Vector3d vec_b(2.0, 4.0, 6.0);  // NOLINT

        auto vec_c = vec_a + vec_b;
        auto vec_d = vec_a - vec_b;
        printVector(vec_c);
        printVector(vec_d);

        std::cout << "dot-vec3d(a,b): " << loco::math::dot(vec_a, vec_b)
                  << "\n";
        std::cout << "len^2-vec3d(a): " << loco::math::squareNorm(vec_a)
                  << "\n";
        std::cout << "len^2-vec3d(b): " << loco::math::squareNorm(vec_b)
                  << "\n";
        std::cout << "len-vec3d(a): " << loco::math::norm(vec_a) << "\n";
        std::cout << "len-vec3d(b): " << loco::math::norm(vec_b) << "\n";
    }

    return 0;
}
