#pragma once

// clang-format off
#include <tinymath/vec3_t.hpp>
#include <tinymath/impl/vec3_t_scalar_impl.hpp>
#include <tinymath/impl/vec3_t_sse_impl.hpp>
#include <tinymath/impl/vec3_t_avx_impl.hpp>
#include <type_traits>
// clang-format on

namespace tiny {
namespace math {

/// \brief Returns the square of the norm-2 of the vector
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto squareNorm(const Vector3<T>& vec) -> T {
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert): call the related AVX implementation
#elif defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_length_square_vec3<T>(vec.elements());
#else
    return scalar::kernel_length_square_vec3<T>(vec.elements());
#endif
}

/// \brief Returns the norm-2 of the vector
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto norm(const Vector3<T>& vec) -> T {
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert): call the related AVX implementation
#elif defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_length_vec3<T>(vec.elements());
#else
    return std::sqrt(scalar::kernel_length_square_vec3<T>(vec.elements()));
#endif
}

/// \brief Returns a normalized version of this vector
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto normalize(const Vector3<T>& vec) -> Vector3<T> {
    Vector3<T> vec_normalized = vec;
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_normalize_in_place_vec3<T>(vec_normalized.elements());
#else
    scalar::kernel_normalize_in_place_vec3<T>(vec_normalized.elements());
#endif
    return vec_normalized;
}

/// \brief Normalizes in-place the given vector
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto normalize_in_place(Vector3<T>& vec) -> void {  // NOLINT
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_normalize_in_place_vec3<T>(vec.elements());
#else
    scalar::kernel_normalize_in_place_vec3<T>(vec.elements());
#endif
}

/// \brief Returns the dot-product of the given two vectors
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto dot(const Vector3<T>& lhs, const Vector3<T>& rhs) -> T {
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_dot_vec3<T>(lhs.elements(), rhs.elements());
#else
    return scalar::kernel_dot_vec3<T>(lhs.elements(), rhs.elements());
#endif
}

/// \brief Returns the cross-product of the given two vectors
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto cross(const Vector3<T>& lhs, const Vector3<T>& rhs)
    -> Vector3<T> {
    Vector3<T> vec_cross;
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_cross_vec3<T>(vec_cross.elements(), lhs.elements(),
                              rhs.elements());
#else
    scalar::kernel_cross_vec3<T>(vec_cross.elements(), lhs.elements(),
                                 rhs.elements());
#endif
    return vec_cross;
}

/// \brief Returns the vector-sum of two 3d vector operands
///
/// \tparam T Type of scalar value used for the 3d-vector operands
///
/// This operator implements an element-wise sum of two Vector3 operands given
/// as input arguments. The internal operator selects the appropriate "kernel"
/// (just a function) to which to call, depending on whether or not the library
/// was compiled using SIMD support (i.e. SSE and AVX function intrinsics will
/// be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the vector-sum
/// \param[in] rhs Right-hand-side operand of the vector-sum
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto operator+(const Vector3<T>& lhs, const Vector3<T>& rhs)
    -> Vector3<T> {
    Vector3<T> vec_result;
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_add_vec3<T>(vec_result.elements(), lhs.elements(),
                            rhs.elements());
#else
    scalar::kernel_add_vec3<T>(vec_result.elements(), lhs.elements(),
                               rhs.elements());
#endif
    return vec_result;
}

/// \brief Returns the vector-difference of two 3d vector operands
///
/// \tparam T Type of scalar value used for the 3d-vector operands
///
/// This operator implements an element-wise difference of two Vector3 operands
/// given as input arguments. The internal operator selects the appropriate
/// "kernel" (just a function) to which to call, depending on whether or not the
/// library was compiled using SIMD support (i.e. SSE and AVX function
/// intrinsics will be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the vector-sum
/// \param[in] rhs Right-hand-side operand of the vector-sum
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto operator-(const Vector3<T>& lhs, const Vector3<T>& rhs)
    -> Vector3<T> {
    Vector3<T> vec_result;
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_sub_vec3<T>(vec_result.elements(), lhs.elements(),
                            rhs.elements());
#else
    scalar::kernel_sub_vec3<T>(vec_result.elements(), lhs.elements(),
                               rhs.elements());
#endif
    return vec_result;
}

/// \brief Returns the scalar-vector product of a scalar and 3d vector operands
///
/// \tparam T Type of scalar used by both scalar and vector operands
///
/// This operator implements the scalar-vector product of two operands (a scalar
/// and a vector in that order) given as input arguments. The internal operator
/// selects the appropriate "kernel" (just a function) to which to call,
/// depending on whether or not the library was compiled using SIMD support
/// (i.e. SSE and AVX function intrinsics will be used to handle the operation).
///
/// \param[in] scale Scalar value by which to scale the second operand
/// \param[in] vec Vector in 3d-space which we want to scale
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto operator*(T scale, const Vector3<T>& vec) -> Vector3<T> {
    Vector3<T> vec_result;
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_vec3<T>(vec_result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_vec3<T>(vec_result.elements(), scale, vec.elements());
#endif
    return vec_result;
}

/// \brief Returns the vector-scalar product of a 3d vector and scalar operands
///
/// \tparam T Type of scalar used by both vector and scalar operands
///
/// This operator implements the vector-scalar product of two operands (a vector
/// and a scalar in that order) given as input arguments. The internal operator
/// selects the appropriate "kernel" (just a function) to which to call,
/// depending on whether or not the library was compiled using SIMD support
/// (i.e. SSE and AVX function intrinsics will be used to handle the operation).
///
/// \param[in] vec Vector in 3d-space which we want to scale
/// \param[in] scale Scalar value by which to scale the first operand
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto operator*(const Vector3<T>& vec, T scale) -> Vector3<T> {
    Vector3<T> vec_result;
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_vec3<T>(vec_result.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_vec3(vec_result.elements(), scale, vec.elements());
#endif
    return vec_result;
}

/// \brief Returns the element-wise product of two 3d vector operands
///
/// \tparam T Type of scalar value used by the 3d-vector operands
///
/// This operator implements an element-wise product (Hadamard-Schur product) of
/// two Vector3 operands given as input arguments. The internal operator selects
/// the appropriate "kernel" (just a function) to which to call, depending on
/// whether or not the library was compiled using SIMD support (i.e. SSE and AVX
/// function intrinsics will be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the element-wise product
/// \param[in] rhs Right-hand-side operand of the element-wise product
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto operator*(const Vector3<T>& lhs, const Vector3<T>& rhs)
    -> Vector3<T> {
    Vector3<T> vec_result;
#if defined(TINYMATH_AVX_ENABLED)
    // @todo(wilbert)
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_hadamard_vec3<T>(vec_result.elements(), lhs.elements(),
                                 rhs.elements());
#else
    scalar::kernel_hadamard_vec3<T>(vec_result.elements(), lhs.elements(),
                                    rhs.elements());
#endif
    return vec_result;
}

/// \brief Checks if two given vectors are "equal" (within epsilon margin)
///
/// \tparam T Type of scalar value used by the 3d-vector operands
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
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto operator==(const Vector3<T>& lhs, const Vector3<T>& rhs)
    -> bool {
    return scalar::kernel_compare_eq_vec3<T>(lhs.elements(), rhs.elements());
}

/// \brief Checks if two given vectors are not "equal" (within epsilon margin)
///
/// \tparam T Type of scalar value used by the 3d-vector operands
///
/// \param[in] lhs Left-hand-side operand of the comparison
/// \param[in] rhs Right-hand-side operand of the comparison
/// \returns true if the given vectors are not within a pre-defined margin
template <typename T,
          typename std::enable_if<IsScalar<T>::value>::type* = nullptr>
TM_INLINE auto operator!=(const Vector3<T>& lhs, const Vector3<T>& rhs)
    -> bool {
    return !scalar::kernel_compare_eq_vec3<T>(lhs.elements(), rhs.elements());
}

}  // namespace math
}  // namespace tiny
