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

}  // namespace math
}  // namespace tiny
