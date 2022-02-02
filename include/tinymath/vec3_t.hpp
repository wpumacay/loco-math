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

// Forward-declare comma-initializer for vector3-types
template <typename Scalar_T>
class Vec3CommaInitializer;

/// \class Vector3
///
/// \brief Class representation of a vector in 3d-space
///
/// \tparam Scalar_T Type of scalar value used for this 3d-vector (float|double)
///
/// This is a class that represents a 3d-vector with entries x, y, z of some
/// scalar floating-point type. Its storage is a buffer of the given scalar
/// type, and it's aligned accordingly in order to use the aligned versions of
/// some SIMD instructions (when using either SSE or AVX intrinsics).
template <typename Scalar_T>
class Vector3 {
 public:
    /// Number of scalars used in the storage of the vector
    constexpr static uint32_t BUFFER_SIZE = 4;
    /// Number of scalar dimensions of the vector
    constexpr static uint32_t VECTOR_NDIM = 3;

    /// Typename of the vector
    using Type = Vector3<Scalar_T>;
    /// Typename of the scalar used for the vector (float32, float64, etc.)
    using ElementType = Scalar_T;
    /// Typename of the internal storage used for the vector
    using BufferType = std::array<Scalar_T, BUFFER_SIZE>;

    /// Constructs a zero-initialized vector
    Vector3() = default;

    /// Constructs a vector of the form (x, x, x)
    explicit Vector3(Scalar_T x) {
        m_Elements[0] = x;
        m_Elements[1] = x;
        m_Elements[2] = x;
        m_Elements[3] = 0;
    }

    /// Constructs a vector of the form (x, y, y)
    explicit Vector3(Scalar_T x, Scalar_T y) {
        m_Elements[0] = x;
        m_Elements[1] = y;
        m_Elements[2] = y;
        m_Elements[3] = 0;
    }

    /// Constructs a vector of the form (x, y, z)
    explicit Vector3(Scalar_T x, Scalar_T y, Scalar_T z) {
        m_Elements[0] = x;
        m_Elements[1] = y;
        m_Elements[2] = z;
        m_Elements[3] = 0;
    }

    /// COnstructs a vector from an initializer list of the form {x, y, z}
    Vector3(const std::initializer_list<Scalar_T>& values) {
        // Complain in case we don't receive exactly 3 values
        assert(values.size() == Vector3<Scalar_T>::VECTOR_NDIM);
        // Just copy the whole data from the initializer list
        std::copy(values.begin(), values.end(), m_Elements.data());
    }

    /// Returns a mutable reference to the x-component of the vector
    auto x() -> Scalar_T& { return m_Elements[0]; }

    /// Returns a mutable reference to the y-component of the vector
    auto y() -> Scalar_T& { return m_Elements[1]; }

    /// Returns a mutable reference to the z-component of the vector
    auto z() -> Scalar_T& { return m_Elements[2]; }

    /// Returns an unmutable reference to the x-component of the vector
    auto x() const -> const Scalar_T& { return m_Elements[0]; }

    /// Returns an unmutable reference to the y-component of the vector
    auto y() const -> const Scalar_T& { return m_Elements[1]; }

    /// Returns an unmutable reference to the z-component of the vector
    auto z() const -> const Scalar_T& { return m_Elements[2]; }

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

    /// Returns a comma-initializer to construct the vector via its coefficients
    auto operator<<(Scalar_T coeff) -> Vec3CommaInitializer<Scalar_T> {
        return Vec3CommaInitializer<Scalar_T>(*this, coeff);
    }

    /// Returns a printable string-representation of the vector
    auto toString() const -> std::string {
        std::stringstream str_result;
        if (std::is_same<ElementType, float>()) {
            str_result << "Vector3f(" << x() << ", " << y() << ", " << z()
                       << ")";
        } else if (std::is_same<ElementType, double>()) {
            str_result << "Vector3d(" << x() << ", " << y() << ", " << z()
                       << ")";
        } else {
            str_result << "Vector3X(" << x() << ", " << y() << ", " << z()
                       << ")";
        }
        return str_result.str();
    }

    /// Returns the number of dimensions of the vector (Vector3 <-> 3 scalars)
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
    /// Storage of the vector's scalars (we pad by 1 due to SIMD-alignment)
    alignas(sizeof(Scalar_T) * BUFFER_SIZE) BufferType m_Elements = {0, 0, 0,
                                                                     0};
};

/// \class Vec3CommaInitializer
///
/// \brief Helper class used during comma-initialization of vec3-types
///
/// \tparam Scalar_T Type of scalar used for the 3d vector being constructed
///
/// This is a helper class used for operations of the form `v << 1, 2, 3;`,
/// which require to concatenate a comma-initializer after using the `<<`
/// operator. This is based on Eigen's comma-initializer implementation.
///
/// \code
///     Vector3d vec;
///     vec << 1.0, 2.0, 3.0;
/// \endcode
template <typename Scalar_T>
class Vec3CommaInitializer {
 public:
    /// Number of scalar dimensions of the vector
    constexpr static uint32_t VECTOR_NDIM = 3;
    /// Index of the first vector entry
    constexpr static int32_t VECTOR_FIRST_INDEX = 0;
    /// Index of the last vector entry
    constexpr static int32_t VECTOR_LAST_INDEX = VECTOR_NDIM - 1;

    /// Type of this comma-initializer
    using Type = Vec3CommaInitializer<Scalar_T>;
    /// Vector type currently in use
    using VectorType = Vector3<Scalar_T>;

    /// Constructs a comma-initializer for the given vector and initial coeff.
    // NOLINTNEXTLINE(runtime/references)
    explicit Vec3CommaInitializer(VectorType& vec, Scalar_T coeff0)
        : m_VectorRef(vec) {
        // Append first coefficient to the vector
        m_VectorRef[0] = coeff0;
        ++m_CurrentBuildIndex;
    }

    /// Constructs a comma-initializer by copying from another one
    Vec3CommaInitializer(const Vec3CommaInitializer<Scalar_T>& other) = default;

    /// Copies the contents of a given comma-initializer
    auto operator=(const Vec3CommaInitializer<Scalar_T>& rhs)
        -> Vec3CommaInitializer<Scalar_T>& = default;

    /// Constructs a comma-initializer by moving the ownership of another one
    Vec3CommaInitializer(Vec3CommaInitializer<Scalar_T>&& other) noexcept =
        default;

    /// Moves the contents of a given comma-initializer
    auto operator=(Vec3CommaInitializer<Scalar_T>&& rhs) noexcept
        -> Vec3CommaInitializer<Scalar_T>& = default;

    /// Destroys and terminates the operations of the initializer
    ~Vec3CommaInitializer() { _finished(); }

    /// Appends the given coefficient to the initializer for building the vec3
    auto operator,(Scalar_T next_coeff) -> Type& {
        assert(m_CurrentBuildIndex <= VECTOR_LAST_INDEX);
        m_VectorRef[m_CurrentBuildIndex++] = next_coeff;
        return *this;
    }

 private:
    /// Terminates the operations of the initializer
    TM_INLINE auto _finished() -> void {
        assert(m_CurrentBuildIndex == (VECTOR_LAST_INDEX + 1));
    }

 private:
    /// Mutable reference to the vector we're currently constructing
    VectorType& m_VectorRef;
    /// Index of the current coefficient being built
    int32_t m_CurrentBuildIndex = VECTOR_FIRST_INDEX;
};

/// \brief Prints the given 3d vector to the given output stream
///
/// \tparam T Type of scalar used by the 3d vector operand
///
/// \param[in,out] output_stream The output stream to write the vector to
/// \param[in] src The vector we want to print to the output stream
/// \returns A reference to the modified output stream (to concatenate calls)
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
auto operator<<(std::ostream& output_stream, const Vector3<T>& src)
    -> std::ostream& {
    output_stream << "(" << src.x() << ", " << src.y() << ", " << src.z()
                  << ")";
    return output_stream;
}

/// \brief Reads a 3d vector from the given input stream
///
/// \tparam T Type of scalar used by the 3d vector operand
///
/// \param[in,out] input_stream The input stream from which to read the vector
/// \param[out] dst The vector in which to place the read values
/// \returns A reference to the modified input stream (to concatenate calls)
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
auto operator>>(std::istream& input_stream, Vector3<T>& dst) -> std::istream& {
    // Based on ignition-math implementation https://bit.ly/3iqAVgS
    T x{};
    T y{};
    T z{};

    input_stream.setf(std::ios_base::skipws);
    input_stream >> x >> y >> z;
    if (!input_stream.fail()) {
        dst.x() = x;
        dst.y() = y;
        dst.z() = z;
    }

    return input_stream;
}

}  // namespace math
}  // namespace tiny
