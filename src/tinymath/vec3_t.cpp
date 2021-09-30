#include <tinymath/impl/vec3_t_scalar_impl.hpp>

#if defined(TINYMATH_SSE_ENABLED)
#include <tinymath/impl/vec3_t_sse_impl.hpp>
#endif

#if defined(TINYMATH_AVX_ENABLED)
#include <tinymath/impl/vec3_t_avx_impl.hpp>
#endif

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {

template <>
TINYMATH_INLINE_EXPR auto operator+(const Vector3<float32_t>& lhs,
                                    const Vector3<float32_t>& rhs)
    -> Vector3<float32_t> {
    Vector3<float32_t> result;
#if defined(TINYMATH_SSE_ENABLED)
    // SSE allows SIMD addition of 4-float packed vectors, so we use it here
    sse::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases (AVX registers require 8-floats)
    scalar::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
TINYMATH_INLINE_EXPR auto operator-(const Vector3<float32_t>& lhs,
                                    const Vector3<float32_t>& rhs)
    -> Vector3<float32_t> {
    Vector3<float32_t> result;
#if defined(TINYMATH_SSE_ENABLED)
    // SSE allows SIMD substraction of 4-float packed vectors, so we use it here
    sse::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases (AVX registers require 8-floats)
    scalar::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
TINYMATH_INLINE_EXPR auto operator+(const Vector3<float64_t>& lhs,
                                    const Vector3<float64_t>& rhs)
    -> Vector3<float64_t> {
    Vector3<float64_t> result;
#if defined(TINYMATH_AVX_ENABLED)
    // AVX allows SIMD addition of 4-double packed vectors, so we use it
    avx::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases, SSE register width is not enough
    scalar::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
TINYMATH_INLINE_EXPR auto operator-(const Vector3<float64_t>& lhs,
                                    const Vector3<float64_t>& rhs)
    -> Vector3<float64_t> {
    Vector3<float64_t> result;
#if defined(TINYMATH_AVX_ENABLED)
    // AVX allows SIMD substraction of 4-double packed vectors, so we use it
    avx::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#else
    // Use scalar version for all other cases, SSE register width is not enough
    scalar::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

}  // namespace math
}  // namespace tiny
