#pragma once

#include <string>
#include <tinymath/vec4_t.hpp>

namespace tiny {
namespace math {

template <typename Scalar_T>
class Matrix4 {
 public:
    constexpr static uint32_t BUFFER_SIZE = 16;
    constexpr static uint32_t MATRIX_NDIM = 4;

    using Type = Matrix4<Scalar_T>;
    using ElementType = Scalar_T;
    using BufferType = std::array<Vector4<Scalar_T>, MATRIX_NDIM>;
    using ColumnType = Vector4<Scalar_T>;

    /// Creates a zero-initialized matrix
    Matrix4() = default;

    /// Creates a matrix using the given scalars for its entries
    explicit Matrix4(Scalar_T x00, Scalar_T x01, Scalar_T x02, Scalar_T x03,
                     Scalar_T x10, Scalar_T x11, Scalar_T x12, Scalar_T x13,
                     Scalar_T x20, Scalar_T x21, Scalar_T x22, Scalar_T x23,
                     Scalar_T x30, Scalar_T x31, Scalar_T x32, Scalar_T x33);

    /// Creates a diagonal matrix using the given diagonal elements
    explicit Matrix4(Scalar_T d0, Scalar_T d1, Scalar_T d2, Scalar_T d3);

    /// Creates a matrix using the given columns
    explicit Matrix4(const ColumnType& col0, const ColumnType& col1,
                     const ColumnType& col2, const ColumnType& col3);

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
    auto operator()(uint32_t col_index, uint32_t row_index) -> Scalar_T& {
        return m_Elements[col_index][row_index];
    }

    /// Gets an unmutable reference to the requested matrix entry
    auto operator()(uint32_t col_index, uint32_t row_index) const -> Scalar_T& {
        return m_Elements[col_index][row_index];
    }

    /// Transposes the matrix in-place
    auto transposeInPlace() -> void;

    /// Returns the transposed version of the matrix
    auto transpose() const -> Matrix4<Scalar_T>;

    /// Returns a printable string-representation of the matrix
    auto toString() const -> std::string;

    /// Returns the dimnension of the matrix
    constexpr auto ndim() const -> uint32_t { return MATRIX_NDIM; }

    /// Returns the number of scalars used by the storage of the matrix
    constexpr auto buffer_size() const -> uint32_t { return BUFFER_SIZE; }

 private:
    /// The buffer (array) where all data lies
    BufferType m_Elements;
};

}  // namespace math
}  // namespace tiny
