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

#include <math/vec3_t_decl.hpp>
#include <math/vec4_t_decl.hpp>

namespace math {

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
    constexpr static uint32_t MATRIX_SIZE = 4;
    /// Number of dimensions of this matrix (as in numpy.ndarray.ndim)
    static constexpr uint32_t MATRIX_NDIM = 2;

    /// Typename of the matrix
    using Type = Matrix4<Scalar_T>;
    /// Typename of the scalar used for the matrix entries (float, double, etc.)
    using ElementType = Scalar_T;
    /// Typename of the internal storage used by the matrix
    using BufferType = std::array<Vector4<Scalar_T>, MATRIX_SIZE>;
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
    explicit Matrix4(Scalar_T x00, Scalar_T x11, Scalar_T x22, Scalar_T x33) {
        m_Elements[0][0] = x00;
        m_Elements[1][1] = x11;
        m_Elements[2][2] = x22;
        m_Elements[3][3] = x33;
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
                    << ", " << data_elms[2][0] << ", " << data_elms[3][0]
                    << "\n";
        sstr_result << "  " << data_elms[0][1] << ", " << data_elms[1][1]
                    << ", " << data_elms[2][1] << ", " << data_elms[3][1]
                    << "\n";
        sstr_result << "  " << data_elms[0][2] << ", " << data_elms[1][2]
                    << ", " << data_elms[2][2] << ", " << data_elms[3][2]
                    << "\n";
        sstr_result << "  " << data_elms[0][3] << ", " << data_elms[1][3]
                    << ", " << data_elms[2][3] << ", " << data_elms[3][3]
                    << " )";

        return sstr_result.str();
    }

    /// Creates a rotation matrix for the given angle around the X-axis
    static auto RotationX(Scalar_T angle) -> Matrix4<Scalar_T>;

    /// Creates a rotation matrix for the given angle around the Y-axis
    static auto RotationY(Scalar_T angle) -> Matrix4<Scalar_T>;

    /// Creates a rotation matrix for the given angle around the Z-axis
    static auto RotationZ(Scalar_T angle) -> Matrix4<Scalar_T>;

    /// Creates a scale matrix for the given separate scale arguments
    static auto Scale(Scalar_T scale_x, Scalar_T scale_y, Scalar_T scale_z)
        -> Matrix4<Scalar_T>;

    /// Creates a scale matrix for the given scale arguments given as a vec3
    static auto Scale(const Vector3<Scalar_T>& scale) -> Matrix4<Scalar_T>;

    /// Creates a translation matrix from the given translation given as a vec3
    static auto Translation(const Vector3<Scalar_T>& position)
        -> Matrix4<Scalar_T>;

    /// Creates a perspective projection matrix from the given configuration
    static auto Perspective(Scalar_T fov, Scalar_T aspect, Scalar_T near,
                            Scalar_T far) -> Matrix4<Scalar_T>;

    /// Creates a perspective projection matrix from the frustum sizes
    static auto Perspective(Scalar_T left, Scalar_T right, Scalar_T top,
                            Scalar_T bottom, Scalar_T near, Scalar_T far)
        -> Matrix4<Scalar_T>;

    /// Creates a orthographic projection matrix from the given configuration
    static auto Ortho(Scalar_T width, Scalar_T height, Scalar_T near,
                      Scalar_T far) -> Matrix4<Scalar_T>;

    /// Returns a 4x4 identity matrix of the current scalar type
    static auto Identity() -> Matrix4<Scalar_T>;

    /// Returns a 4x4 zero matrix of the current scalar type
    static auto Zeros() -> Matrix4<Scalar_T>;

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

 private:
    /// The buffer where all data lies (as an array of 4 column vectors)
    BufferType m_Elements;
};

}  // namespace math
