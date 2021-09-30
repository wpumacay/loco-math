#pragma once

#include <array>
#include <cstdint>
#include <tinymath/common.hpp>

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

    TINYMATH_INLINE_EXPR auto x() -> Scalar_T& { return m_Elements[0]; }

    TINYMATH_INLINE_EXPR auto y() -> Scalar_T& { return m_Elements[1]; }

    TINYMATH_INLINE_EXPR auto z() -> Scalar_T& { return m_Elements[2]; }

    TINYMATH_INLINE_EXPR auto x() const -> const Scalar_T& {
        return m_Elements[0];
    }

    TINYMATH_INLINE_EXPR auto y() const -> const Scalar_T& {
        return m_Elements[1];
    }

    TINYMATH_INLINE_EXPR auto z() const -> const Scalar_T& {
        return m_Elements[2];
    }

    TINYMATH_INLINE_EXPR auto elements() -> BufferType& { return m_Elements; }

    TINYMATH_INLINE_EXPR auto elements() const -> const BufferType& {
        return m_Elements;
    }

    TINYMATH_INLINE_EXPR auto operator[](uint32_t index) -> Scalar_T& {
        return &m_Elements[index];
    }

    TINYMATH_INLINE_EXPR auto operator[](uint32_t index) const
        -> const Scalar_T& {
        return &m_Elements[index];
    }

    constexpr auto ndim() const -> uint32_t { return VECTOR_NDIM; }

    constexpr auto buffer_size() const -> uint32_t { return BUFFER_SIZE; }

 private:
    // @todo(wilbert): add union trick to handle xmm and ymm registers on SIMD

    BufferType m_Elements = {0, 0, 0, 1};
};

template <typename Scalar_T>
TINYMATH_INLINE_EXPR auto operator+(const Vector3<Scalar_T>& lhs,
                                    const Vector3<Scalar_T>& rhs)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
TINYMATH_INLINE_EXPR auto operator-(const Vector3<Scalar_T>& lhs,
                                    const Vector3<Scalar_T>& rhs)
    -> Vector3<Scalar_T>;

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

}  // namespace math
}  // namespace tiny
