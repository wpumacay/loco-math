#include <iomanip>
#include <iostream>
#include <tinymath/vec3_t.hpp>
#include <type_traits>

template <typename T>
auto printVector(const tiny::math::Vector3<T>& vec) -> void {
    constexpr int32_t PRINT_PRECISION = 7;
    std::cout << std::setprecision(PRINT_PRECISION);
    std::cout << "Vector3(";
    std::cout << vec.x() << ", ";
    std::cout << vec.y() << ", ";
    std::cout << vec.z() << ")";
    std::cout << "\n";
}

auto main() -> int {
    {
        using Vector3f = tiny::math::Vector3<tiny::math::float32_t>;

        Vector3f vec_a;
        Vector3f vec_b(1.0F);
        Vector3f vec_c(1.0F, 2.0F);        // NOLINT
        Vector3f vec_d(1.0F, 2.0F, 3.0F);  // NOLINT

        printVector<tiny::math::float32_t>(vec_a);
        printVector<tiny::math::float32_t>(vec_b);
        printVector<tiny::math::float32_t>(vec_c);
        printVector<tiny::math::float32_t>(vec_d);

        static_assert(std::is_same<Vector3f::ElementType, float>::value,
                      "float32_t should be the same as vanilla 'float'");
    }

    {
        using Vector3d = tiny::math::Vector3<tiny::math::float64_t>;
        Vector3d vec_a;
        Vector3d vec_b(1.0);
        Vector3d vec_c(1.0, 2.0);       // NOLINT
        Vector3d vec_d(1.0, 2.0, 3.0);  // NOLINT

        printVector<tiny::math::float64_t>(vec_a);
        printVector<tiny::math::float64_t>(vec_b);
        printVector<tiny::math::float64_t>(vec_c);
        printVector<tiny::math::float64_t>(vec_d);

        static_assert(std::is_same<Vector3d::ElementType, double>::value,
                      "float32_t should be the same as vanilla 'float'");
    }

    return 0;
}
