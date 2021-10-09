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

    // @todo(wilbert): implement square_length (PR: #3)
    auto length_square() const -> Scalar_T;

    // @todo(wilbert): implement length (PR: #3)
    auto length() const -> Scalar_T;

    // @todo(wilbert): implement inner product (PR: #3)
    auto dot() const -> Scalar_T;

    // @todo(wilbert): implement cross product (PR: #3)
    auto cross() const -> Vector3<Scalar_T>;

    auto toString() const -> std::string;

    constexpr auto ndim() const -> uint32_t { return VECTOR_NDIM; }

    constexpr auto buffer_size() const -> uint32_t { return BUFFER_SIZE; }

 private:
    // @todo(wilbert): add union trick to handle xmm and ymm registers on SIMD

    BufferType m_Elements = {0, 0, 0, 0};
};

template <typename Scalar_T>
auto operator+(const Vector3<Scalar_T>& lhs, const Vector3<Scalar_T>& rhs)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
auto operator-(const Vector3<Scalar_T>& lhs, const Vector3<Scalar_T>& rhs)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
auto operator*(Scalar_T scale, const Vector3<Scalar_T>& vec)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
auto operator*(const Vector3<Scalar_T>& vec, Scalar_T scale)
    -> Vector3<Scalar_T>;

// @todo(wilbert): implement Hadamard-Schur product (PR: #3)
template <typename Scalar_T>
auto operator*(const Vector3<Scalar_T>& v1, const Vector3<Scalar_T>& v2)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
auto operator<<(std::ostream& output_stream, const Vector3<Scalar_T>& src)
    -> std::ostream& {
    output_stream << "(" << src.x() << ", " << src.y() << ", " << src.z()
                  << ")";
    return output_stream;
}

template <typename Scalar_T>
auto operator>>(std::istream& input_stream, Vector3<Scalar_T>& dst)
    -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3iqAVgS
    Scalar_T x{};
    Scalar_T y{};
    Scalar_T z{};

    input_stream.setf(std::ios_base::skipws);
    input_stream >> x >> y >> z;
    if (!input_stream.fail()) {
        dst.x() = x;
        dst.y() = y;
        dst.z() = z;
    }

    return input_stream;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x) {
    m_Elements[0] = x;
    m_Elements[1] = x;
    m_Elements[2] = x;
    m_Elements[3] = 0;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x, Scalar_T y) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = y;
    m_Elements[3] = 0;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x, Scalar_T y, Scalar_T z) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = z;
    m_Elements[3] = 0;
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
