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

#include <loco/math/common.hpp>
// clang-format on

namespace loco {
namespace math {

/// \class Vector2
///
/// \brief Class representation of a vector in 2d-space
///
/// \tparam Scalar_T Type of scalar value used for this 2d-vector (float|double)
///
/// This is a class that represents a 2d-vector with entries x, y of some
/// scalar floating-point type. Its storage is a buffer of the given scalar
/// type; however, it's not aligned for SIMD load/store instructions (tradeoff
/// between adding padding/size and usage of aligned load/store). So, SIMD
/// kernels are build using unaligned load/store operations (unlike friends like
/// vec3 and vec4 types)
template <typename Scalar_T>
struct Vector2 {
    /// Number of scalars used in the storage of the vector
    static constexpr uint32_t BUFFER_SIZE = 2;
    /// Number of scalar dimensions of the vector
    static constexpr uint32_t VECTOR_NDIM = 2;

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

    /// Returns a mutable reference to the x-component of the vector
    auto x() -> Scalar_T& { return m_Elements[0]; }

    /// Returns a mutable reference to the y-component of the vector
    auto y() -> Scalar_T& { return m_Elements[1]; }

    /// Returns an unmutable reference to the x-component of the vector
    auto x() const -> const Scalar_T& { return m_Elements[0]; }

    /// Returns an unmutable reference to the y-component of the vector
    auto y() const -> const Scalar_T& { return m_Elements[1]; }

    /// Returns a mutable reference to the underlying storage of the vector
    auto elements() -> BufferType& { return m_Elements; }

    /// Returns an unmutable reference to the underlying storage of the vector
    auto elements() const -> const BufferType& { return m_Elements; }

    /// Returns a pointer to the data of the underlying storage in use
    auto data() -> Scalar_T* { return m_Elements.data(); }

    /// Reeturns a const-pointer to the data of the underlying storage in use
    auto data() const -> const Scalar_T* { return m_Elements.data(); }

    /// Returns a mutable reference to the requested entry of the vector
    auto operator[](uint32_t index) -> Scalar_T& { return m_Elements[index]; }

    /// Returns an unmutable reference to the requested entry of the vector
    auto operator[](uint32_t index) const -> const Scalar_T& {
        return m_Elements[index];
    }

    /// Returns a comma-initializer to construct the vector via its coefficients
    auto operator<<(Scalar_T coeff) -> VecCommaInitializer<Type> {
        return VecCommaInitializer<Type>(*this, coeff);
    }

    /// Returns a printable string-representation of the vector
    auto toString() const -> std::string {
        std::stringstream str_result;
        if (std::is_same<ElementType, float>()) {
            str_result << "Vector2f(" << x() << ", " << y() << ")";
        } else if (std::is_same<ElementType, double>()) {
            str_result << "Vector2d(" << x() << ", " << y() << ")";
        } else {
            str_result << "Vector2X(" << x() << ", " << y() << ")";
        }
        return str_result.str();
    }

    /// Returns the number of dimensions of the vector (Vector2 <-> 2 scalars)
    constexpr auto ndim() const -> uint32_t { return VECTOR_NDIM; }

    /// Returns the number of scalars used by the storage of the vector
    constexpr auto buffer_size() const -> uint32_t { return BUFFER_SIZE; }

    /// Returns the size (in bytes) of the vector
    static constexpr auto num_bytes_size() -> uint32_t { return sizeof(Type); }

    /// Returns the alignment (in bytes) of the vector
    static constexpr auto num_bytes_alignment() -> uint32_t {
        return alignof(Type);
    }

 private:
    /// Storage of the vector's scalars
    alignas(sizeof(Scalar_T) * BUFFER_SIZE) BufferType m_Elements = {0, 0};
};

/// \brief Prints the given vector to the given output stream
///
/// \tparam T Type of scalar used by the vector operand
///
/// \param[in,out] output_stream The output stream to write the vector to
/// \param[in] src The vector we want to print to the output stream
/// \returns A reference to the modified output stream (to concatenate calls)
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
auto operator<<(std::ostream& output_stream, const Vector2<T>& src)
    -> std::ostream& {
    output_stream << "(" << src.x() << ", " << src.y() << ")";
    return output_stream;
}

/// \brief Reads a vector from the given input stream
///
/// \tparam T Type of scalar used by the vector operand
///
/// \param[in,out] input_stream The input stream from which to read the vector
/// \param[out] dst The vector in which to place the read values
/// \returns A reference to the modified input stream (to concatenate calls)
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
auto operator>>(std::istream& input_stream, Vector2<T>& dst) -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3iqAVgS
    T x{};
    T y{};

    input_stream.setf(std::ios_base::skipws);
    input_stream >> x >> y;
    if (!input_stream.fail()) {
        dst.x() = x;
        dst.y() = y;
    }

    return input_stream;
}

}  // namespace math
}  // namespace loco
