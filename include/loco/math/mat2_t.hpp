#pragma once

#include <iomanip>
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

#include <loco/math/vec2_t.hpp>

namespace loco {
namespace math {

template <typename T>
using SFINAE_MAT2_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

/// \class Matrix2
///
/// \brief Class representation of a 2 by 2 matrix of real-valued entries
///
/// \tparam Scalar_T Type of scalar value used for the entries of the matrix
///
/// This is a class that represents 2x2 matrices with real-valued entries. The
/// internal data is stored as the columns of the matrix using 2d vectors of the
/// same scalar type. The resulting storage is column major and aligned in a way
/// that allows the use of aligned versions of some SIMD instructions (when
/// using either SSE or AVX instrinsics).
template <typename Scalar_T, SFINAE_MAT2_GUARD<Scalar_T> = nullptr>
class Matrix2 {
 public:
    /// Number of scalars used for the storage of this matrix
    static constexpr uint32_t BUFFER_SIZE = 4;
    /// Number of dimensions of the matrix (square 2x2 matrix)
    static constexpr uint32_t MATRIX_SIZE = 2;
    /// Number of dimensions of this matrix (as in numpy.ndarray.ndim)
    static constexpr uint32_t MATRIX_NDIM = 2;

    /// Typename of the matrix
    using Type = Matrix2<Scalar_T>;
    /// Typename of the scalar used for the matrix entries (float, double, etc.)
    using ElementType = Scalar_T;
    /// Typename of the internal storage used by the matrix
    using BufferType = std::array<Vector2<Scalar_T>, MATRIX_SIZE>;
    /// Typename of the columns of the matrix
    using ColumnType = Vector2<Scalar_T>;

    /// Creates a zero-initialized matrix
    Matrix2() = default;

    /// Creates a matrix using the given scalars for its entries
    explicit Matrix2(Scalar_T x00, Scalar_T x01, Scalar_T x10, Scalar_T x11) {
        m_Elements[0][0] = x00;
        m_Elements[1][0] = x01;

        m_Elements[0][1] = x10;
        m_Elements[1][1] = x11;
    }

    explicit Matrix2(Scalar_T x00, Scalar_T x11) {
        m_Elements[0][0] = x00;
        m_Elements[1][1] = x11;
    }

    explicit Matrix2(const ColumnType& col0, const ColumnType& col1) {
        m_Elements[0] = col0;
        m_Elements[1] = col1;
    }

    /// Returns a mutable reference to the underlying storage of the matrix
    auto elements() -> BufferType& { return m_Elements; }

    /// Returns an unmutable reference to the underlying storage of the matrix
    auto elements() const -> const BufferType& { return m_Elements; }

    /// Returns a pointer to the data of the underlying storage in use
    auto data() -> Scalar_T* { return m_Elements[0].data(); }

    /// Reeturns a const-pointer to the data of the underlying storage in use
    auto data() const -> const Scalar_T* { return m_Elements[0].data(); }

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
    auto operator<<(Scalar_T coeff) -> MatCommaInitializer<Type> {
        return MatCommaInitializer<Type>(*this, coeff);
    }

    /// Returns a printable string-representation of the matrix
    auto toString() const -> std::string {
        const auto& data_elms = m_Elements;
        std::stringstream sstr_result;

        sstr_result << "( " << data_elms[0][0] << ", " << data_elms[1][0]
                    << '\n';
        sstr_result << "  " << data_elms[0][1] << ", " << data_elms[1][1]
                    << ')';

        return sstr_result.str();
    }

    /// Returns the number of rows
    static constexpr auto rows() -> uint32_t { return MATRIX_SIZE; }

    /// Returns the number of columns
    static constexpr auto cols() -> uint32_t { return MATRIX_SIZE; }

    /// Returns the number of elements in the matrix
    static constexpr auto size() -> uint32_t {
        return MATRIX_SIZE * MATRIX_SIZE;
    }

    /// Returns the dimnension of the matrix
    static constexpr auto ndim() -> uint32_t { return MATRIX_SIZE; }

    /// Returns the number of scalars used by the storage of the matrix
    static constexpr auto buffer_size() -> uint32_t { return BUFFER_SIZE; }

    /// Returns the size (in bytes) of the matrix
    static constexpr auto num_bytes_size() -> uint32_t { return sizeof(Type); }

    /// Returns the alignment (in bytes) of the matrix
    static constexpr auto num_bytes_alignment() -> uint32_t {
        return alignof(Type);
    }

    /// Returns a 4x4 identity matrix of the current scalar type
    static auto Identity() -> Type {
        return Matrix2<Scalar_T>(1.0, 0.0, 0.0, 1.0);
    }

    /// Returns a 4x4 zero matrix of the current scalar type
    static auto Zeros() -> Type { return Matrix2<Scalar_T>(); }

 private:
    /// The buffer where all data is stored (as an array of 2 column
    /// vectors)
    alignas(sizeof(Scalar_T) * BUFFER_SIZE) BufferType m_Elements;
};

}  // namespace math
}  // namespace loco
