#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <tinymath/common.hpp>

namespace tiny {
namespace math {

/// \class Vector4
///
/// \brief Class representation of a vector in 4d-space
///
/// \tparam Scalar_T Type of scalar value used for this 4d-vector (float|double)
///
/// This is a class that represents a 4d-vector with entries x, y, z, w of some
/// scalar floating-point type. Its storage is a buffer of the given scalar
/// type, and it's aligned accordingly in order to use the aligned versions of
/// some SIMD instructions (when using either SSE or AVX intrinsics).
template <typename Scalar_T>
class Vector4 {
 public:
    /// Number of scalars used in the storage of the vector
    constexpr static uint32_t BUFFER_SIZE = 4;
    /// Number of scalar dimensions of the vector
    constexpr static uint32_t VECTOR_NDIM = 4;

    /// Typename of the vector
    using Type = Vector4<Scalar_T>;
    /// Typename of the scalar used for the vector (float32, float64, etc.)
    using ElementType = Scalar_T;
    /// Typename of the internal storage used for the vector
    using BufferType = std::array<Scalar_T, BUFFER_SIZE>;

    /// Constructs a zero-initialized vector
    Vector4() = default;

    /// Constructs a vector of the form (x, x, x, x)
    explicit Vector4(Scalar_T x);

    /// Constructs a vector of the form (x, y, y, y)
    explicit Vector4(Scalar_T x, Scalar_T y);

    /// Constructs a vector of the form (x, y, z, z)
    explicit Vector4(Scalar_T x, Scalar_T y, Scalar_T z);

    /// Constructs a vector of the form (x, y, z, w)
    explicit Vector4(Scalar_T x, Scalar_T y, Scalar_T z, Scalar_T w);

    // @todo(wilbert): RAII break (rule of 5)

    /// Returns a mutable reference to the x-component of the vector
    constexpr auto x() -> Scalar_T& { return m_Elements[0]; }

    /// Returns a mutable reference to the y-component of the vector
    constexpr auto y() -> Scalar_T& { return m_Elements[1]; }

    /// Returns a mutable reference to the z-component of the vector
    constexpr auto z() -> Scalar_T& { return m_Elements[2]; }

    /// Returns a mutable reference to the w-component of the vector
    constexpr auto w() -> Scalar_T& { return m_Elements[3]; }

    /// Returns an unmutable reference to the x-component of the vector
    constexpr auto x() const -> const Scalar_T& { return m_Elements[0]; }

    /// Returns an unmutable reference to the y-component of the vector
    constexpr auto y() const -> const Scalar_T& { return m_Elements[1]; }

    /// Returns an unmutable reference to the z-component of the vector
    constexpr auto z() const -> const Scalar_T& { return m_Elements[2]; }

    /// Returns an unmutable reference to the w-component of the vector
    constexpr auto w() const -> const Scalar_T& { return m_Elements[3]; }

    /// Returns a mutable reference to the underlying storage of the vector
    auto elements() -> BufferType& { return m_Elements; }

    /// Returns an unmutable reference to the underlying storage of the vector
    auto elements() const -> const BufferType& { return m_Elements; }

    /// Returns a mutable reference to the requested entry of the vector
    auto operator[](uint32_t index) -> Scalar_T& { return m_Elements[index]; }

    /// Returns an unmutable reference to the requested entry of the vector
    auto operator[](uint32_t index) const -> const Scalar_T& {
        return m_Elements[index];
    }

    /// Returns the dot-product of this vector with the given vector argument
    TM_INLINE auto dot(const Vector4<Scalar_T>& other) const -> Scalar_T;

    /// Returns a printable string-representation of the vector
    auto toString() const -> std::string;

    /// Returns the number of dimensions of the vector (Vector4 <-> 4 scalars)
    constexpr auto ndim() const -> uint32_t { return VECTOR_NDIM; }

    /// Returns the number of scalars used by the storage of the vector
    constexpr auto buffer_size() const -> uint32_t { return BUFFER_SIZE; }

    /// Returns the size (in bytes) of the vector
    constexpr auto num_bytes_size() const -> uint32_t { return sizeof(Type); }

    /// Returns the alignment (in bytes) of the vector
    constexpr auto num_bytes_alignment() const -> uint32_t {
        return alignof(Type);
    }

 private:
    /// Storage of the vector's scalars
    alignas(sizeof(Scalar_T) * BUFFER_SIZE) BufferType m_Elements = {0, 0, 0,
                                                                     0};
};

/// \brief Returns the vector-sum of two 4d vector operands
///
/// \tparam Scalar_T Type of scalar value used for the 4d-vector operands
///
/// This operator implements an element-wise sum of two Vector4 operands given
/// as input arguments. The internal operator selects the appropriate "kernel"
/// (just a function) to which to call, depending on whether or not the library
/// was compiled using SIMD support (i.e. SSE and AVX function intrinsics will
/// be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the vector-sum
/// \param[in] rhs Right-hand-side operand of the vector-sum
template <typename Scalar_T>
auto operator+(const Vector4<Scalar_T>& lhs, const Vector4<Scalar_T>& rhs)
    -> Vector4<Scalar_T>;

/// \brief Returns the vector-difference of two 4d vector operands
///
/// \tparam Scalar_T Type of scalar value used for the 4d-vector operands
///
/// This operator implements an element-wise difference of two Vector4 operands
/// given as input arguments. The internal operator selects the appropriate
/// "kernel" (just a function) to which to call, depending on whether or not the
/// library was compiled using SIMD support (i.e. SSE and AVX function
/// intrinsics will be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the vector-sum
/// \param[in] rhs Right-hand-side operand of the vector-sum
template <typename Scalar_T>
auto operator-(const Vector4<Scalar_T>& lhs, const Vector4<Scalar_T>& rhs)
    -> Vector4<Scalar_T>;

/// \brief Returns the scalar-vector product of a scalar and 4d vector operands
///
/// \tparam Scalar_T Type of scalar used by both scalar and vector operands
///
/// This operator implements the scalar-vector product of two operands (a scalar
/// and a vector in that order) given as input arguments. The internal operator
/// selects the appropriate "kernel" (just a function) to which to call,
/// depending on whether or not the library was compiled using SIMD support
/// (i.e. SSE and AVX function intrinsics will be used to handle the operation).
///
/// \param[in] scale Scalar value by which to scale the second operand
/// \param[in] vec Vector in 4d-space which we want to scale
template <typename Scalar_T>
auto operator*(Scalar_T scale, const Vector4<Scalar_T>& vec)
    -> Vector4<Scalar_T>;

/// \brief Returns the vector-scalar product of a 4d vector and scalar operands
///
/// \tparam Scalar_T Type of scalar used by both vector and scalar operands
///
/// This operator implements the vector-scalar product of two operands (a vector
/// and a scalar in that order) given as input arguments. The internal operator
/// selects the appropriate "kernel" (just a function) to which to call,
/// depending on whether or not the library was compiled using SIMD support
/// (i.e. SSE and AVX function intrinsics will be used to handle the operation).
///
/// \param[in] vec Vector in 4d-space which we want to scale
/// \param[in] scale Scalar value by which to scale the first operand
template <typename Scalar_T>
auto operator*(const Vector4<Scalar_T>& vec, Scalar_T scale)
    -> Vector4<Scalar_T>;

/// \brief Returns the element-wise product of two 4d vector operands
///
/// \tparam Scalar_T Type of scalar value used by the 4d-vector operands
///
/// This operator implements an element-wise product (Hadamard-Schur product) of
/// two Vector4 operands given as input arguments. The internal operator selects
/// the appropriate "kernel" (just a function) to which to call, depending on
/// whether or not the library was compiled using SIMD support (i.e. SSE and AVX
/// function intrinsics will be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the element-wise product
/// \param[in] rhs Right-hand-side operand of the element-wise product
template <typename Scalar_T>
auto operator*(const Vector4<Scalar_T>& lhs, const Vector4<Scalar_T>& rhs)
    -> Vector4<Scalar_T>;

/// \brief Checks if two given vectors are "equal" (within epsilon margin)
///
/// \tparam Scalar_T Type of scalar value used by the 4d-vector operands
///
/// This operator implements an "np.allclose"-like operation (numpy's allclose
/// function), checking if the corresponding (x,y,z) entries of both operands
/// are within a certain margin "epsilon" (pre-defined constant). There was an
/// "equal"-like SIMD instruction that implements floating point comparisons,
/// however, we're not using it as single-precision floating point operations
/// and transformation functions within the library might result in compounding
/// errors that the user might want to test a small margin of error tuned
/// appropriately (specially for single-precision floating point types)
///
/// \param[in] lhs Left-hand-side operand of the comparison
/// \param[in] rhs Right-hand-side operand of the comparison
/// \returns true if the given vectors are within a pre-defined epsilon margin
template <typename Scalar_T>
auto operator==(const Vector4<Scalar_T>& lhs, const Vector4<Scalar_T>& rhs)
    -> bool;

/// \brief Checks if two given vectors are not "equal" (within epsilon margin)
///
/// \tparam Scalar_T Type of scalar value used by the 4d-vector operands
///
/// \param[in] lhs Left-hand-side operand of the comparison
/// \param[in] rhs Right-hand-side operand of the comparison
/// \returns true if the given vectors are not within a pre-defined margin
template <typename Scalar_T>
auto operator!=(const Vector4<Scalar_T>& lhs, const Vector4<Scalar_T>& rhs)
    -> bool;

/// \brief Prints the given 4d vector to the given output stream
///
/// \tparam Scalar_T Type of scalar used by the 4d vector operand
///
/// \param[in,out] output_stream The output stream to write the vector to
/// \param[in] src The vector we want to print to the output stream
/// \returns A reference to the modified output stream (to concatenate calls)
template <typename Scalar_T>
auto operator<<(std::ostream& output_stream, const Vector4<Scalar_T>& src)
    -> std::ostream&;

/// \brief Reads a 4d vector from the given input stream
///
/// \tparam Scalar_T Type of scalar used by the 4d vector operand
///
/// \param[in,out] input_stream The input stream from which to read the vector
/// \param[out] dst The vector in which to place the read values
/// \returns A reference to the modified input stream (to concatenate calls)
template <typename Scalar_T>
auto operator>>(std::istream& input_stream, Vector4<Scalar_T>& dst)
    -> std::istream&;

}  // namespace math
}  // namespace tiny
