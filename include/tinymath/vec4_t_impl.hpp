#pragma once

// clang-format off
#include <tinymath/vec4_t.hpp>
#include <tinymath/impl/vec4_t_scalar_impl.hpp>
#include <tinymath/impl/vec4_t_sse_impl.hpp>
#include <tinymath/impl/vec4_t_avx_impl.hpp>
// clang-format on

namespace tiny {
namespace math {

template <typename T>
using SFINAE_VEC4_GUARD = typename std::enable_if<IsScalar<T>::value>::type*;

/// \brief Returns the dot-product of the given two vectors
template <typename T, SFINAE_VEC4_GUARD<T> = nullptr>
TM_INLINE auto dot(const Vector4<T>& lhs, const Vector4<T>& rhs) -> T {
#if defined(TINYMATH_AVX_ENABLED)
    return avx::kernel_dot_vec4<T>(lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    return sse::kernel_dot_vec4<T>(lhs.elements(), rhs.elements());
#else
    return scalar::kernel_dot_vec4<T>(lhs.elements(), rhs.elements());
#endif
}

/// \brief Returns the vector-sum of two 4d vector operands
///
/// \tparam T Type of scalar value used for the 4d-vector operands
///
/// This operator implements an element-wise sum of two Vector4 operands given
/// as input arguments. The internal operator selects the appropriate "kernel"
/// (just a function) to which to call, depending on whether or not the library
/// was compiled using SIMD support (i.e. SSE and AVX function intrinsics will
/// be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the vector-sum
/// \param[in] rhs Right-hand-side operand of the vector-sum
template <typename T, SFINAE_VEC4_GUARD<T> = nullptr>
TM_INLINE auto operator+(const Vector4<T>& lhs, const Vector4<T>& rhs)
    -> Vector4<T> {
    Vector4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_add_vec4<T>(dst.elements(), rhs.elements(), lhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_add_vec4<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add_vec4<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

/// \brief Returns the vector-difference of two 4d vector operands
///
/// \tparam T Type of scalar value used for the 4d-vector operands
///
/// This operator implements an element-wise difference of two Vector4 operands
/// given as input arguments. The internal operator selects the appropriate
/// "kernel" (just a function) to which to call, depending on whether or not the
/// library was compiled using SIMD support (i.e. SSE and AVX function
/// intrinsics will be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the vector-sum
/// \param[in] rhs Right-hand-side operand of the vector-sum
template <typename T, SFINAE_VEC4_GUARD<T> = nullptr>
TM_INLINE auto operator-(const Vector4<T>& lhs, const Vector4<T>& rhs)
    -> Vector4<T> {
    Vector4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_sub_vec4<T>(dst.elements(), lhs.elements(), rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_sub_vec4<T>(dst.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub_vec4<T>(dst.elements(), lhs.elements(), rhs.elements());
#endif
    return dst;
}

/// \brief Returns the scalar-vector product of a scalar and 4d vector operands
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
/// \param[in] vec Vector in 4d-space which we want to scale
template <typename T, SFINAE_VEC4_GUARD<T> = nullptr>
TM_INLINE auto operator*(T scale, const Vector4<T>& vec) -> Vector4<T> {
    Vector4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_vec4<T>(dst.elements(), scale, vec.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_vec4<T>(dst.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_vec4<T>(dst.elements(), scale, vec.elements());
#endif
    return dst;
}

/// \brief Returns the vector-scalar product of a 4d vector and scalar operands
///
/// \tparam T Type of scalar used by both vector and scalar operands
///
/// This operator implements the vector-scalar product of two operands (a vector
/// and a scalar in that order) given as input arguments. The internal operator
/// selects the appropriate "kernel" (just a function) to which to call,
/// depending on whether or not the library was compiled using SIMD support
/// (i.e. SSE and AVX function intrinsics will be used to handle the operation).
///
/// \param[in] vec Vector in 4d-space which we want to scale
/// \param[in] scale Scalar value by which to scale the first operand
template <typename T, SFINAE_VEC4_GUARD<T> = nullptr>
TM_INLINE auto operator*(const Vector4<T>& vec, T scale) -> Vector4<T> {
    Vector4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_scale_vec4<T>(dst.elements(), scale, vec.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_scale_vec4<T>(dst.elements(), scale, vec.elements());
#else
    scalar::kernel_scale_vec4<T>(dst.elements(), scale, vec.elements());
#endif
    return dst;
}

/// \brief Returns the element-wise product of two 4d vector operands
///
/// \tparam T Type of scalar value used by the 4d-vector operands
///
/// This operator implements an element-wise product (Hadamard-Schur product) of
/// two Vector4 operands given as input arguments. The internal operator selects
/// the appropriate "kernel" (just a function) to which to call, depending on
/// whether or not the library was compiled using SIMD support (i.e. SSE and AVX
/// function intrinsics will be used to handle the operation).
///
/// \param[in] lhs Left-hand-side operand of the element-wise product
/// \param[in] rhs Right-hand-side operand of the element-wise product
template <typename T, SFINAE_VEC4_GUARD<T> = nullptr>
TM_INLINE auto operator*(const Vector4<T>& lhs, const Vector4<T>& rhs)
    -> Vector4<T> {
    Vector4<T> dst;
#if defined(TINYMATH_AVX_ENABLED)
    avx::kernel_hadamard_vec4<T>(dst.elements(), lhs.elements(),
                                 rhs.elements());
#elif defined(TINYMATH_SSE_ENABLED)
    sse::kernel_hadamard_vec4<T>(dst.elements(), lhs.elements(),
                                 rhs.elements());
#else
    scalar::kernel_hadamard_vec4<T>(dst.elements(), lhs.elements(),
                                    rhs.elements());
#endif
    return dst;
};

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
template <typename T, SFINAE_VEC4_GUARD<T> = nullptr>
TM_INLINE auto operator==(const Vector4<T>& lhs, const Vector4<T>& rhs)
    -> bool {
    return scalar::kernel_compare_eq_vec4<T>(lhs.elements(), rhs.elements());
}

/// \brief Checks if two given vectors are not "equal" (within epsilon margin)
///
/// \tparam Scalar_T Type of scalar value used by the 4d-vector operands
///
/// \param[in] lhs Left-hand-side operand of the comparison
/// \param[in] rhs Right-hand-side operand of the comparison
/// \returns true if the given vectors are not within a pre-defined margin
template <typename T, SFINAE_VEC4_GUARD<T> = nullptr>
TM_INLINE auto operator!=(const Vector4<T>& lhs, const Vector4<T>& rhs)
    -> bool {
    return !scalar::kernel_compare_eq_vec4<T>(lhs.elements(), rhs.elements());
}

}  // namespace math
}  // namespace tiny
