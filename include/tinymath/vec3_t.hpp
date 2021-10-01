#pragma once

#include <array>
#include <cstdint>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <tinymath/common.hpp>
#include <type_traits>

namespace tiny {
namespace math {

template <typename Scalar_T>
class Vector3 {
 public:
    constexpr static uint32_t BUFFER_SIZE = 4;
    constexpr static uint32_t VECTOR_NDIM = 3;

    using ElementType = Scalar_T;
    using BufferType = std::array<Scalar_T, BUFFER_SIZE>;

    Vector3() = default;

    explicit Vector3(Scalar_T x);

    explicit Vector3(Scalar_T x, Scalar_T y);

    explicit Vector3(Scalar_T x, Scalar_T y, Scalar_T z);

    auto x() -> Scalar_T& { return m_Elements[0]; }

    auto y() -> Scalar_T& { return m_Elements[1]; }

    auto z() -> Scalar_T& { return m_Elements[2]; }

    auto x() const -> const Scalar_T& { return m_Elements[0]; }

    auto y() const -> const Scalar_T& { return m_Elements[1]; }

    auto z() const -> const Scalar_T& { return m_Elements[2]; }

    auto elements() -> BufferType& { return m_Elements; }

    auto elements() const -> const BufferType& { return m_Elements; }

    auto operator[](uint32_t index) -> Scalar_T& { return m_Elements[index]; }

    auto operator[](uint32_t index) const -> const Scalar_T& {
        return m_Elements[index];
    }

    auto toString() const -> std::string;

    constexpr auto ndim() const -> uint32_t { return VECTOR_NDIM; }

    constexpr auto buffer_size() const -> uint32_t { return BUFFER_SIZE; }

 private:
    // @todo(wilbert): add union trick to handle xmm and ymm registers on
    // SIMD

    BufferType m_Elements = {0, 0, 0, 1};
};

template <typename Scalar_T>
auto operator+(const Vector3<Scalar_T>& lhs, const Vector3<Scalar_T>& rhs)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
auto operator-(const Vector3<Scalar_T>& lhs, const Vector3<Scalar_T>& rhs)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
auto operator<<(std::ostream& stdout, const Vector3<Scalar_T>& src)
    -> std::ostream& {
    stdout << "(" << src.x() << ", " << src.y() << ", " << src.z() << ")";
    return stdout;
}

template <typename Scalar_T>
auto operator>>(std::istream& stdin, Vector3<Scalar_T>& dst) -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3iqAVgS
    Scalar_T x{};
    Scalar_T y{};
    Scalar_T z{};

    stdin.setf(std::ios_base::skipws);
    stdin >> x >> y >> z;
    if (!stdin.fail()) {
        dst.x() = x;
        dst.y() = y;
        dst.z() = z;
    }

    return stdin;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x) {
    m_Elements[0] = x;
    m_Elements[1] = x;
    m_Elements[2] = x;
    m_Elements[3] = 1;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x, Scalar_T y) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = y;
    m_Elements[3] = 1;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x, Scalar_T y, Scalar_T z) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = z;
    m_Elements[3] = 1;
}

template <typename Scalar_T>
auto Vector3<Scalar_T>::toString() const -> std::string {
    std::stringstream str_result;
    if (std::is_same<ElementType, float>()) {
        str_result << "Vector3f(" << x() << ", " << y() << ", " << z() << ")";
    } else if (std::is_same<ElementType, double>()) {
        str_result << "Vector3d(" << x() << ", " << y() << ", " << z() << ")";
    } else {
        str_result << "Vector3X(" << x() << ", " << y() << ", " << z() << ")";
    }
    return str_result.str();
}

}  // namespace math
}  // namespace tiny
