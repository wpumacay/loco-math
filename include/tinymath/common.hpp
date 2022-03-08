#pragma once

// clang-format off
#if defined(TINYMATH_FORCE_INLINE)
    #if defined(TINYMATH_COMPILER_CLANG) || defined(TINYMATH_COMPILER_GCC)
        #define TM_INLINE inline __attribute__((__always_inline__))
    #elif defined(TINYMATH_COMPILER_MSVC)
        #define TM_INLINE __forceinline
    #else
        #define TM_INLINE inline
    #endif
#else
    #define TM_INLINE
#endif

#if defined(TINYMATH_COMPILER_CLANG) || defined(TINYMATH_COMPILER_GCC)
    #define TM_NEVER_INLINE __attribute__((noinline))
#elif defined(TINYMATH_COMPILER_MSVC)
    #define TM_NEVER_INLINE __declspec(noinline)
#else
    #define TM_NEVER_INLINE
#endif

// clang-format on
#include <cstdint>
#include <type_traits>

namespace tiny {
namespace math {

template <typename Scalar_T>
constexpr Scalar_T PI = static_cast<Scalar_T>(3.141592653589793);

template <typename Scalar_T>
constexpr Scalar_T EPS = static_cast<Scalar_T>(1e-6);

using float32_t = float;
using float64_t = double;
using uint = unsigned int;

template <uint z, uint y, uint x, uint w>
struct ShuffleMask {
    // NOLINTNEXTLINE
    static constexpr uint value = (((z) << 6) | ((y) << 4) | ((x) << 2) | (w));
};

#if defined(TINYMATH_SSE_ENABLED)
using HAS_SSE = std::true_type;
#else
using HAS_SSE = std::false_type;
#endif

#if defined(TINYMATH_AVX_ENABLED)
using HAS_AVX = std::true_type;
#else
using HAS_AVX = std::false_type;
#endif

// clang-format off
template <typename Tp> struct IsFloat32 : public std::false_type {};
template <> struct IsFloat32<float32_t> : public std::true_type {};

template <typename Tp> struct IsFloat64 : public std::false_type {};
template <> struct IsFloat64<float64_t> : public std::true_type {};

template <typename Tp>
struct IsScalar : public std::integral_constant<bool,
                IsFloat32<Tp>::value || IsFloat64<Tp>::value> {};

template <typename Tp>
struct CpuNoSIMD : public std::integral_constant<bool,
                IsScalar<Tp>::value && !HAS_SSE::value && !HAS_AVX::value> {};

template <typename Tp>
struct CpuHasSIMD : public std::integral_constant<bool,
                IsScalar<Tp>::value && (HAS_SSE::value || HAS_AVX::value)> {};

template <typename Tp>
struct CpuHasSSE : public std::integral_constant<bool,
                IsScalar<Tp>::value && HAS_SSE::value> {};

template <typename Tp>
struct CpuHasAVX : public std::integral_constant<bool,
                IsScalar<Tp>::value && HAS_AVX::value> {};

// clang-format on

/// \class VecCommaInitializer
///
/// \brief Helper class used during comma-initialization of vec-types
///
/// \tparam Scalar_T Type of scalar used for the vector being constructed
///
/// This is a helper class used for operations of the form `v << 1, 2, 3, ...;`,
/// which require to concatenate a comma-initializer after using the `<<`
/// operator. This is based on Eigen's comma-initializer implementation.
///
/// \code
///     Vector3d vec;
///     vec << 1.0, 2.0, 3.0;
/// \endcode
template <typename T, uint32_t N>
struct VecCommaInitializer {
    /// Number of scalar dimensions of the vector
    static constexpr uint32_t VECTOR_NDIM = N;
    /// Index of the first vector entry on its storage buffer|array
    static constexpr int32_t VECTOR_FIRST_INDEX = 0;
    /// Index of the last vector entry on its storage buffer|array
    static constexpr int32_t VECTOR_LAST_INDEX = VECTOR_NDIM - 1;
};

}  // namespace math
}  // namespace tiny
