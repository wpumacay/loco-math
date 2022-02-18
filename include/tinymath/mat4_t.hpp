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
#include <utility>
#include <algorithm>
#include <type_traits>

#include <tinymath/vec4_t.hpp>
// clang-format on

namespace tiny {
namespace math {

// Forward declare comma-initializer for matrix4-types
template <typename Scalar_T>
class Mat4CommaInitializer;

/// \class Matrix4
///
/// \brief Class representation of a 4 by 4 matrix of real-valued entries
///
/// \tparam Scalar_T Type of scalar value used for the entries of the matrix
///
/// This is a class that represents 4x4 matrices with real-valued entries. The
/// internal data is stored as the columns of the matrix using 4d vectors of the
/// same scalar type. The resulting storage is column major and aligned in a way
/// that allows the use of aligned versions of some SIMD instructions (when
/// using either SSE or AVX instrinsics).
template <typename Scalar_T>
class Matrix4 {
 public:
    /// Number of scalars used in the storage of the matrix
    constexpr static uint32_t BUFFER_SIZE = 16;
    /// Number of dimensions of the matrix (square 4x4 matrix)
    constexpr static uint32_t MATRIX_NDIM = 4;

    /// Typename of the matrix
    using Type = Matrix4<Scalar_T>;
    /// Typename of the scalar used for the matrix entries (float, double, etc.)
    using ElementType = Scalar_T;
    /// Typename of the internal storage used by the matrix
    using BufferType = std::array<Vector4<Scalar_T>, MATRIX_NDIM>;
    /// Typename of the columns of the matrix
    using ColumnType = Vector4<Scalar_T>;

    /// Creates a zero-initialized matrix
    Matrix4() = default;

    /// Creates a matrix using the given scalars for its entries
    explicit Matrix4(Scalar_T x00, Scalar_T x01, Scalar_T x02, Scalar_T x03,
                     Scalar_T x10, Scalar_T x11, Scalar_T x12, Scalar_T x13,
                     Scalar_T x20, Scalar_T x21, Scalar_T x22, Scalar_T x23,
                     Scalar_T x30, Scalar_T x31, Scalar_T x32, Scalar_T x33) {
        // Row-0
        m_Elements[0][0] = x00;
        m_Elements[1][0] = x01;
        m_Elements[2][0] = x02;
        m_Elements[3][0] = x03;

        // Row-1
        m_Elements[0][1] = x10;
        m_Elements[1][1] = x11;
        m_Elements[2][1] = x12;
        m_Elements[3][1] = x13;

        // Row-2
        m_Elements[0][2] = x20;
        m_Elements[1][2] = x21;
        m_Elements[2][2] = x22;
        m_Elements[3][2] = x23;

        // Row-3
        m_Elements[0][3] = x30;
        m_Elements[1][3] = x31;
        m_Elements[2][3] = x32;
        m_Elements[3][3] = x33;
    }

    /// Creates a diagonal matrix using the given diagonal elements
    explicit Matrix4(Scalar_T d0, Scalar_T d1, Scalar_T d2, Scalar_T d3) {
        m_Elements[0][0] = d0;
        m_Elements[1][1] = d1;
        m_Elements[2][2] = d2;
        m_Elements[3][3] = d3;
    }

    /// Creates a matrix using the given columns
    explicit Matrix4(const ColumnType& col0, const ColumnType& col1,
                     const ColumnType& col2, const ColumnType& col3) {
        m_Elements[0] = col0;
        m_Elements[1] = col1;
        m_Elements[2] = col2;
        m_Elements[3] = col3;
    }

    /// Returns a mutable reference to the underlying storage of the matrix
    auto elements() -> BufferType& { return m_Elements; }

    /// Returns an unmutable reference to the underlying storage of the matrix
    auto elements() const -> const BufferType& { return m_Elements; }

    /// Gets a mutable reference to the column requested by the given index
    auto operator[](uint32_t col_index) -> ColumnType& {
        return m_Elements[col_index];
    }

    /// Gets an unmutable reference to the column requested by the given index
    auto operator[](uint32_t col_index) const -> const ColumnType& {
        return m_Elements[col_index];
    }

    /// Gets a mutable reference to the requested matrix entry
    auto operator()(uint32_t row_index, uint32_t col_index) -> Scalar_T& {
        return m_Elements[col_index][row_index];
    }

    /// Gets an unmutable reference to the requested matrix entry
    auto operator()(uint32_t row_index, uint32_t col_index) const
        -> const Scalar_T& {
        return m_Elements[col_index][row_index];
    }

    /// Returns a comma-initializer to construct the matrix via its coefficients
    auto operator<<(Scalar_T coeff) -> Mat4CommaInitializer<Scalar_T> {
        return Mat4CommaInitializer<Scalar_T>(*this, coeff);
    }

    /// Returns a printable string-representation of the matrix
    auto toString() const -> std::string {
        auto& data = m_Elements;
        std::stringstream sstr_result;

        sstr_result << "( " << data[0][0] << ", " << data[1][0] << ", "
                    << data[2][0] << ", " << data[3][0] << "\n";
        sstr_result << "  " << data[0][1] << ", " << data[1][1] << ", "
                    << data[2][1] << ", " << data[3][1] << "\n";
        sstr_result << "  " << data[0][2] << ", " << data[1][2] << ", "
                    << data[2][2] << ", " << data[3][2] << "\n";
        sstr_result << "  " << data[0][3] << ", " << data[1][3] << ", "
                    << data[2][3] << ", " << data[3][3] << " )";

        return sstr_result.str();
    }

    /// Returns the number of rows
    constexpr auto rows() const -> uint32_t { return MATRIX_NDIM; }

    /// Returns the number of columns
    constexpr auto cols() const -> uint32_t { return MATRIX_NDIM; }

    /// Returns the number of elements in the matrix
    constexpr auto size() const -> uint32_t {
        return MATRIX_NDIM * MATRIX_NDIM;
    }

    /// Returns the dimnension of the matrix
    constexpr auto ndim() const -> uint32_t { return MATRIX_NDIM; }

    /// Returns the number of scalars used by the storage of the matrix
    constexpr auto buffer_size() const -> uint32_t { return BUFFER_SIZE; }

    /// Returns the size (in bytes) of the matrix
    static constexpr auto num_bytes_size() -> uint32_t { return sizeof(Type); }

    /// Returns the alignment (in bytes) of the matrix
    static constexpr auto num_bytes_alignment() -> uint32_t {
        return alignof(Type);
    }

    /// Returns a 4x4 identity matrix of the current scalar type
    static auto Identity() -> Type {
        // clang-format off
        return Matrix4<Scalar_T>(1.0, 0.0, 0.0, 0.0,
                                 0.0, 1.0, 0.0, 0.0,
                                 0.0, 0.0, 1.0, 0.0,
                                 0.0, 0.0, 0.0, 1.0);
        // clang-format on
    }

    /// Returns a 4x4 zero matrix of the current scalar type
    static auto Zeros() -> Type { return Matrix4<Scalar_T>(); }

 private:
    /// The buffer where all data lies (as an array of 4 column vectors)
    alignas(sizeof(Scalar_T) * BUFFER_SIZE) BufferType m_Elements;
};

/// \class Mat4CommaInitializer
///
/// \brief Helper class used during comma-initialization of mat4-types
///
/// \tparam Scalar_T Type of scalar used for the 4d matrices being constructed
///
/// This is a helper class used for operations of the form `v << 1.0, 2.0,...;`,
/// which require to concatenate a comma-initializer after using the `<<`
/// operator. This is based on Eigen's comma-initializer implementation.
///
/// \code
///     Matrix4d mat;
///     mat << 1.0,  2.0,  3.0,  4.0,
///            5.0,  6.0,  7.0,  8.0,
///            9.0,  10.0, 11.0, 12.0,
///            13.0, 14.0, 15.0, 16.0;
/// \endcode
template <typename Scalar_T>
class Mat4CommaInitializer {
 public:
    /// Number of scalar dimensions of the vector
    constexpr static uint32_t MATRIX_NDIM = Matrix4<Scalar_T>::MATRIX_NDIM;
    /// Index of the first vector entry
    constexpr static int32_t MATRIX_FIRST_INDEX = 0;
    /// Index of the last vector entry
    constexpr static int32_t MATRIX_LAST_INDEX = MATRIX_NDIM * MATRIX_NDIM - 1;

    /// Type of this comma-initializer
    using Type = Mat4CommaInitializer<Scalar_T>;
    /// Matrix type currently in use
    using MatrixType = Matrix4<Scalar_T>;

    /// Constructs a comma-initializer for the given vector and initial coeff.
    // NOLINTNEXTLINE(runtime/references)
    explicit Mat4CommaInitializer(MatrixType& vec, Scalar_T coeff0)
        : m_MatrixRef(vec) {
        // Append first entry of the matrix
        m_MatrixRef[0][0] = coeff0;
        ++m_CurrentBuildIndex;
    }

    /// Constructs a comma-initializer by copying from another one
    Mat4CommaInitializer(const Mat4CommaInitializer<Scalar_T>& other) = default;

    /// Copies the contents of a given comma-initializer
    auto operator=(const Mat4CommaInitializer<Scalar_T>& rhs)
        -> Mat4CommaInitializer<Scalar_T>& = default;

    /// Constructs a comma-initializer by moving the ownership of another one
    Mat4CommaInitializer(Mat4CommaInitializer<Scalar_T>&& other) noexcept =
        default;

    /// Moves the contents of a given comma-initializer
    auto operator=(Mat4CommaInitializer<Scalar_T>&& rhs) noexcept
        -> Mat4CommaInitializer<Scalar_T>& = default;

    /// Destroys and terminates the operations of the initializer
    ~Mat4CommaInitializer() { _finished(); }

    /// Appends the given coefficient to the initializer for building the vec3
    auto operator,(Scalar_T next_coeff) -> Type& {
        assert(m_CurrentBuildIndex <= MATRIX_LAST_INDEX);
        // Get the indices of the current (col, row) we're dealing with (notice
        // that the current index grows in row-major order, unlike our layout)
        const int row_index = m_CurrentBuildIndex / MATRIX_NDIM;  // NOLINT
        const int col_index = m_CurrentBuildIndex % MATRIX_NDIM;  // NOLINT
        m_MatrixRef[col_index][row_index] = next_coeff;
        ++m_CurrentBuildIndex;
        return *this;
    }

 private:
    /// Terminates the operations of the initializer and returns the built vec3
    TM_INLINE auto _finished() -> void {
        assert(m_CurrentBuildIndex == (MATRIX_LAST_INDEX + 1));
    }

 private:
    /// Mutable reference to the matrix we're currently constructing
    MatrixType& m_MatrixRef;
    /// Index of the current coefficient being built
    int32_t m_CurrentBuildIndex = MATRIX_FIRST_INDEX;
};

template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
auto operator<<(std::ostream& output_stream, const Matrix4<T>& src)
    -> std::ostream& {
    // @todo(wilbert): complet this part of the implementation
    return output_stream;
}

template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
auto operator>>(std::istream& input_stream, Matrix4<T>& dst) -> std::istream& {
    // @todo(wilbert): complet this part of the implementation
    return input_stream;
}

}  // namespace math
}  // namespace tiny
