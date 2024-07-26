#include <math/euler_t.hpp>
#include <math/mat3_t.hpp>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-float-conversion"
#pragma clang diagnostic ignored "-Wdouble-promotion"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4305)
#pragma warning(disable : 4244)
#endif

template <typename T,
          typename = typename std::enable_if<math::IsScalar<T>::value>::type>
MATH3D_NEVER_INLINE auto run_conversions_euler() -> void {
    using Mat3 = ::math::Matrix3<T>;
    using Euler = ::math::Euler<T>;

    // Create Rotation matrix from Euler angles
    {
        Euler rot_euler(::math::PI / 3, ::math::PI / 4, ::math::PI / 6,
                        ::math::euler::Order::XYZ,
                        ::math::euler::Convention::INTRINSIC);

        Mat3 rot_mat(rot_euler);

        std::cout << "rot_euler:\n";
        std::cout << rot_euler << "\n";
        std::cout << "rot_mat:\n";
        std::cout << rot_mat << "\n";
    }

    // Create Euler angles from Rotation matrix
    {
        // clang-format off
        Mat3 rot_mat(0.6123724, -0.3535533, 0.7071067,
                     0.7803300, 0.1268264, -0.6123724,
                     0.1268264, 0.9267766, 0.3535533);
        // clang-format on

        Euler rot_euler(rot_mat);

        std::cout << "rot_mat:\n";
        std::cout << rot_mat << "\n";
        std::cout << "rot_euler:\n";
        std::cout << rot_euler << "\n";
    }
}

auto main() -> int {
    std::cout << "Euler conversions for float type -----------------\n";
    run_conversions_euler<float>();
    std::cout << "--------------------------------------------------\n";
    std::cout << "Euler conversions for double type ----------------\n";
    run_conversions_euler<double>();
    std::cout << "--------------------------------------------------\n";
    return 0;
}

#if defined(__clang__)
#pragma clang diagnostic pop  // NOLINT
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif
