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
class Vector4 {
 public:
    constexpr static uint32_t BUFFER_SIZE = 4;
    constexpr static uint32_t VECTOR_NDIM = 4;

    using ElementType = Scalar_T;
    using BufferType = std::array<Scalar_T, BUFFER_SIZE>;

    Vector4() = default;

    explicit Vector4(Scalar_T x);

    explicit Vector4(Scalar_T x, Scalar_T y);

    explicit Vector4(Scalar_T x, Scalar_T y, Scalar_T z);

    explicit Vector4(Scalar_T x, Scalar_T y, Scalar_T z, Scalar_T w);

    // @todo(wilbert): RAII break (rule of 5)

    auto x() -> Scalar_T& { return m_Elements[0]; }

    auto y() -> Scalar_T& { return m_Elements[1]; }

    auto z() -> Scalar_T& { return m_Elements[2]; }

    auto w() -> Scalar_T& { return m_Elements[3]; }

    auto x() const -> const Scalar_T& { return m_Elements[0]; }

    auto y() const -> const Scalar_T& { return m_Elements[1]; }

    auto z() const -> const Scalar_T& { return m_Elements[2]; }

    auto w() const -> const Scalar_T& { return m_Elements[3]; }

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

    BufferType m_Elements = {0, 0, 0, 0};
};

template <typename Scalar_T>
auto operator+(const Vector4<Scalar_T>& lhs, const Vector4<Scalar_T>& rhs)
    -> Vector4<Scalar_T>;

template <typename Scalar_T>
auto operator-(const Vector4<Scalar_T>& lhs, const Vector4<Scalar_T>& rhs)
    -> Vector4<Scalar_T>;

template <typename Scalar_T>
auto operator*(Scalar_T scale, const Vector4<Scalar_T>& vec)
    -> Vector4<Scalar_T>;

template <typename Scalar_T>
auto operator*(const Vector4<Scalar_T>& vec, Scalar_T scale)
    -> Vector4<Scalar_T>;

// @todo(wilbert): implement Hadamard-Schur product (PR: #3)
template <typename Scalar_T>
auto operator*(const Vector4<Scalar_T>& v1, const Vector4<Scalar_T>& v2)
    -> Vector4<Scalar_T>;

template <typename Scalar_T>
auto operator<<(std::ostream& output_stream, const Vector4<Scalar_T>& src)
    -> std::ostream& {
    output_stream << "(" << src.x() << ", " << src.y() << ", " << src.z()
                  << ", " << src.w() << ")";
    return output_stream;
}

template <typename Scalar_T>
auto operator>>(std::istream& input_stream, Vector4<Scalar_T>& dst)
    -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3iqAVgS
    Scalar_T x{};
    Scalar_T y{};
    Scalar_T z{};
    Scalar_T w{};

    input_stream.setf(std::ios_base::skipws);
    input_stream >> x >> y >> z >> w;
    if (!input_stream.fail()) {
        dst.x() = x;
        dst.y() = y;
        dst.z() = z;
        dst.w() = w;
    }

    return input_stream;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(Scalar_T x) {
    m_Elements[0] = x;
    m_Elements[1] = x;
    m_Elements[2] = x;
    m_Elements[3] = x;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(Scalar_T x, Scalar_T y) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = y;
    m_Elements[3] = y;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(Scalar_T x, Scalar_T y, Scalar_T z) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = z;
    m_Elements[3] = z;
}

template <typename Scalar_T>
Vector4<Scalar_T>::Vector4(Scalar_T x, Scalar_T y, Scalar_T z, Scalar_T w) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = z;
    m_Elements[3] = w;
}

template <typename Scalar_T>
auto Vector4<Scalar_T>::toString() const -> std::string {
    std::stringstream str_result;
    if (std::is_same<ElementType, float>()) {
        str_result << "Vector4f(" << x() << ", " << y() << ", " << z() << ", "
                   << w() << ")";
    } else if (std::is_same<ElementType, double>()) {
        str_result << "Vector4d(" << x() << ", " << y() << ", " << z() << ", "
                   << w() << ")";
    } else {
        str_result << "Vector4X(" << x() << ", " << y() << ", " << z() << ", "
                   << w() << ")";
    }
    return str_result.str();
}

}  // namespace math
}  // namespace tiny
