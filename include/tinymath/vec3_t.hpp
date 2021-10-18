#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <tinymath/common.hpp>

namespace tiny {
namespace math {

template <typename Scalar_T>
class Vector3 {
 public:
    constexpr static uint32_t BUFFER_SIZE = 4;
    constexpr static uint32_t VECTOR_NDIM = 3;

    using Type = Vector3<Scalar_T>;
    using ElementType = Scalar_T;
    using BufferType = std::array<Scalar_T, BUFFER_SIZE>;

    Vector3() = default;

    explicit Vector3(Scalar_T x);

    explicit Vector3(Scalar_T x, Scalar_T y);

    explicit Vector3(Scalar_T x, Scalar_T y, Scalar_T z);

    // @todo(wilbert): RAII breaks (rule of 5). Add remaining initializers

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

    TM_INLINE auto squaredNorm() const -> Scalar_T;

    TM_INLINE auto norm() const -> Scalar_T;

    TM_INLINE auto normalize() -> void;

    TM_INLINE auto normalized() const -> Vector3<Scalar_T>;

    TM_INLINE auto dot(const Vector3<Scalar_T>& other) const -> Scalar_T;

    TM_INLINE auto cross(const Vector3<Scalar_T>& other) const
        -> Vector3<Scalar_T>;

    auto toString() const -> std::string;

    constexpr auto ndim() const -> uint32_t { return VECTOR_NDIM; }

    constexpr auto buffer_size() const -> uint32_t { return BUFFER_SIZE; }

 private:
    // @todo(wilbert): add union trick to handle xmm and ymm registers on SIMD
    // @todo(wilbert): use alignas(sizeof(T)*BUFFER_SIZE) to fix issue #5

    alignas(sizeof(Scalar_T) * BUFFER_SIZE) BufferType m_Elements = {0, 0, 0,
                                                                     0};
};

template <typename Scalar_T>
TM_INLINE auto operator+(const Vector3<Scalar_T>& lhs,
                         const Vector3<Scalar_T>& rhs) -> Vector3<Scalar_T>;

template <typename Scalar_T>
TM_INLINE auto operator-(const Vector3<Scalar_T>& lhs,
                         const Vector3<Scalar_T>& rhs) -> Vector3<Scalar_T>;

template <typename Scalar_T>
TM_INLINE auto operator*(Scalar_T scale, const Vector3<Scalar_T>& vec)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
TM_INLINE auto operator*(const Vector3<Scalar_T>& vec, Scalar_T scale)
    -> Vector3<Scalar_T>;

template <typename Scalar_T>
TM_INLINE auto operator*(const Vector3<Scalar_T>& lhs,
                         const Vector3<Scalar_T>& rhs) -> Vector3<Scalar_T>;

template <typename Scalar_T>
TM_INLINE auto operator==(const Vector3<Scalar_T>& lhs,
                          const Vector3<Scalar_T>& rhs) -> bool;

template <typename Scalar_T>
TM_INLINE auto operator!=(const Vector3<Scalar_T>& lhs,
                          const Vector3<Scalar_T>& rhs) -> bool;

template <typename Scalar_T>
auto operator<<(std::ostream& output_stream, const Vector3<Scalar_T>& src)
    -> std::ostream&;

template <typename Scalar_T>
auto operator>>(std::istream& input_stream, Vector3<Scalar_T>& dst)
    -> std::istream&;

}  // namespace math
}  // namespace tiny
