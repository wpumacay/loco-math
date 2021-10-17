#include <iomanip>
#include <iostream>
#include <tinymath/tinymath.hpp>
#include <type_traits>

template <typename T>
auto printVector(const tiny::math::Vector3<T>& vec) -> void {
    std::cout << "Vector3(";
    std::cout << vec.x() << ", ";
    std::cout << vec.y() << ", ";
    std::cout << vec.z() << ")";
    std::cout << "\n";
}

auto main() -> int {
    constexpr int32_t PRINT_PRECISION = 7;
    std::cout << std::setprecision(PRINT_PRECISION);

    {
        using Vector3f = tiny::math::Vector3<tiny::math::float32_t>;

        Vector3f vec_a;
        Vector3f vec_b(1.0F);
        Vector3f vec_c(1.0F, 2.0F);        // NOLINT
        Vector3f vec_d(1.0F, 2.0F, 3.0F);  // NOLINT

        std::cout << "Using vec3-float32 operator<<"
                  << "\n";
        std::cout << vec_a << "\n";
        std::cout << vec_b << "\n";
        std::cout << vec_c << "\n";
        std::cout << vec_d << "\n";

        std::cout << "Using vec3-float32 toString()"
                  << "\n";
        std::cout << vec_a.toString() << "\n";
        std::cout << vec_b.toString() << "\n";
        std::cout << vec_c.toString() << "\n";
        std::cout << vec_d.toString() << "\n";

        static_assert(std::is_same<Vector3f::ElementType, float>::value,
                      "float32_t should be the same as vanilla 'float'");
    }

    {
        using Vector3d = tiny::math::Vector3<tiny::math::float64_t>;

        Vector3d vec_a;
        Vector3d vec_b(1.0);
        Vector3d vec_c(1.0, 2.0);       // NOLINT
        Vector3d vec_d(1.0, 2.0, 3.0);  // NOLINT

        std::cout << "Using vec3-float64 operator<<"
                  << "\n";
        std::cout << vec_a << "\n";
        std::cout << vec_b << "\n";
        std::cout << vec_c << "\n";
        std::cout << vec_d << "\n";

        std::cout << "Using vec3-float64 toString()"
                  << "\n";
        std::cout << vec_a.toString() << "\n";
        std::cout << vec_b.toString() << "\n";
        std::cout << vec_c.toString() << "\n";
        std::cout << vec_d.toString() << "\n";

        static_assert(std::is_same<Vector3d::ElementType, double>::value,
                      "float32_t should be the same as vanilla 'float'");
    }

    return 0;
}
