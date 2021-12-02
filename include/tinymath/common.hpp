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
    #define TM_INLINE inline
#endif
// clang-format on

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

}  // namespace math
}  // namespace tiny
