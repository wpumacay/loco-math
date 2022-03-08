#pragma once

// clang-format off
#include <ios>
#include <array>
#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <type_traits>

#include <tinymath/common.hpp>
// clang-format on

namespace tiny {
namespace math {

/// \class Vector2
///
/// \brief Class representation of a vector in 2d-space
///
/// \tparam Scalar_T Type of scalar value used for this 2d-vector (float|double)
///
/// This is a class that represents a 2d-vector with entries x, y of some
/// scalar floating-point type. Its storage is a buffer of the given scalar
/// type, and it's aligned accordingly in order to use the aligned versions of
/// some SIMD instructions (when using either SSE or AVX intrinsics).
template <typename Scalar_T>
struct Vector2 {
    /// Number of scalars used in the storage of the vector
    static constexpr uint32_t BUFFER_SIZE = 2;
    /// Number of scalar dimensions of the vector
    static constexpr uint32_t VECTOR_NDIM = 3;

    /// Type alias of the vector
    using Type = Vector2<Scalar_T>;
    /// Type alias of the scalar used for this vector (float32|64)
    using ElementType = Scalar_T;
    /// Type alias of the internal storage used for the vector (i.e. std::array)
    using BufferType = std::array<Scalar_T, BUFFER_SIZE>;

    /// Constructs a zero-initialized vector
    Vector2() = default;

    /// Constructs a vector of the form (x, x)
    explicit Vector2(Scalar_T x) {
        m_Elements[0] = x;
        m_Elements[1] = x;
    }

    /// Constructs a vector of the form (x, y)
    explicit Vector2(Scalar_T x, Scalar_T y) {
        m_Elements[0] = x;
        m_Elements[1] = y;
    }

    /// Constructs a vector from an initializer list of the form {x, y}
    Vector2(const std::initializer_list<Scalar_T>& values) {
        assert(values.size() == Vector2<Scalar_T>::VECTOR_NDIM);
        std::copy(values.begin(), values.end(), m_Elements.data());
    }

 private:
    /// Storage of the vector's scalars
    alignas(sizeof(Scalar_T) * BUFFER_SIZE) BufferType m_Elements = {0, 0};
};

}  // namespace math
}  // namespace tiny
