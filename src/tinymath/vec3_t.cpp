/// #include <tinymath/impl/vec3_t_avx_impl.hpp>
#include <tinymath/impl/vec3_t_scalar_impl.hpp>
/// #include <tinymath/impl/vec3_t_sse_impl.hpp>
#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x) {
    m_Elements[0] = x;
    m_Elements[1] = x;
    m_Elements[2] = x;
    m_Elements[3] = 1;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x, Scalar_T y) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = y;
    m_Elements[3] = 1;
}

template <typename Scalar_T>
Vector3<Scalar_T>::Vector3(Scalar_T x, Scalar_T y, Scalar_T z) {
    m_Elements[0] = x;
    m_Elements[1] = y;
    m_Elements[2] = z;
    m_Elements[3] = 1;
}

template <>
TINYMATH_INLINE_EXPR auto operator+(const Vector3<float32_t>& lhs,
                                    const Vector3<float32_t>& rhs)
    -> Vector3<float32_t> {
    Vector3<float32_t> result;
#if defined(TINYMATH_USE_SSE)
    sse::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
TINYMATH_INLINE_EXPR auto operator-(const Vector3<float32_t>& lhs,
                                    const Vector3<float32_t>& rhs)
    -> Vector3<float32_t> {
    Vector3<float32_t> result;
#if defined(TINYMATH_USE_SSE)
    sse::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
TINYMATH_INLINE_EXPR auto operator+(const Vector3<float64_t>& lhs,
                                    const Vector3<float64_t>& rhs)
    -> Vector3<float64_t> {
    Vector3<float64_t> result;
#if defined(TINYMATH_USE_AVX)
    avx::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_add(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

template <>
TINYMATH_INLINE_EXPR auto operator-(const Vector3<float64_t>& lhs,
                                    const Vector3<float64_t>& rhs)
    -> Vector3<float64_t> {
    Vector3<float64_t> result;
#if defined(TINYMATH_USE_AVX)
    avx::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#else
    scalar::kernel_sub(result.elements(), lhs.elements(), rhs.elements());
#endif
    return result;
}

}  // namespace math
}  // namespace tiny
