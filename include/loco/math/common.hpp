#pragma once

// clang-format off
#if defined(LOCOMATH_FORCE_INLINE)
    #if defined(LOCOMATH_COMPILER_CLANG) || defined(LOCOMATH_COMPILER_GCC)
        #define LM_INLINE inline __attribute__((__always_inline__))
    #elif defined(LOCOMATH_COMPILER_MSVC)
        #define LM_INLINE __forceinline
    #else
        #define LM_INLINE inline
    #endif
#else
    #define LM_INLINE
#endif

#if defined(LOCOMATH_COMPILER_CLANG) || defined(LOCOMATH_COMPILER_GCC)
    #define LM_NEVER_INLINE __attribute__((noinline))
#elif defined(LOCOMATH_COMPILER_MSVC)
    #define LM_NEVER_INLINE __declspec(noinline)
#else
    #define LM_NEVER_INLINE
#endif

// clang-format on
#include <cassert>
#include <cstdint>
#include <type_traits>

namespace loco {
namespace math {

static constexpr double PI = 3.141592653589793;
static constexpr double EPS = 1e-6;

using float32_t = float;
using float64_t = double;
using uint = unsigned int;

template <uint z, uint y, uint x, uint w>
struct ShuffleMask {
    // NOLINTNEXTLINE
    static constexpr uint value = (((z) << 6) | ((y) << 4) | ((x) << 2) | (w));
};

#if defined(LOCOMATH_SSE_ENABLED)
using HAS_SSE = std::true_type;
#else
using HAS_SSE = std::false_type;
#endif

#if defined(LOCOMATH_AVX_ENABLED)
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
/// \tparam V Type of vector related to this comma initializer
///
/// This is a helper class used for operations of the form `v << 1, 2, 3, ...;`,
/// which require to concatenate a comma-initializer after using the `<<`
/// operator. This is based on Eigen's comma-initializer implementation.
///
/// \code
///     Vector3d vec;
///     vec << 1.0, 2.0, 3.0;
/// \endcode
template <typename V>
struct VecCommaInitializer {
    /// Number of scalar dimensions of the vector
    static constexpr uint32_t VECTOR_NDIM = V::VECTOR_NDIM;
    /// Index of the first vector entry on its storage buffer|array
    static constexpr int32_t VECTOR_FIRST_INDEX = 0;
    /// Index of the last vector entry on its storage buffer|array
    static constexpr int32_t VECTOR_LAST_INDEX = VECTOR_NDIM - 1;

    /// Type alias for the float|scalar type in use
    using T = typename V::ElementType;
    /// Type alias for this comma-initializer
    using Type = VecCommaInitializer<V>;
    /// Type alias for the vector type linked to this initializer
    using VectorType = V;

    /// Creates a comma-initializer for the given vector and initial coeff.
    // NOLINTNEXTLINE(runtime/references)
    explicit VecCommaInitializer(VectorType& vec, T coeff0) : m_VectorRef(vec) {
        // Append first coefficient to the vector
        m_VectorRef[m_CurrentBuildIndex++] = coeff0;
    }

    // Follow RAII and the 'Rule of 5' (use defaults though) -------------------

    VecCommaInitializer(const VecCommaInitializer<V>& rhs) = default;

    VecCommaInitializer(VecCommaInitializer<V>&& rhs) noexcept = default;

    auto operator=(const VecCommaInitializer<V>& rhs)
        -> VecCommaInitializer<V>& = default;

    auto operator=(VecCommaInitializer<V>&& rhs) noexcept
        -> VecCommaInitializer<V>& = default;

    /// Release any resources and terminate the initializer's operation
    ~VecCommaInitializer() { _finished(); }

    // -------------------------------------------------------------------------

    /// Appends the given coefficient to the vector managed by this initializer
    auto operator,(T next_coeff) -> Type& {
        assert(m_CurrentBuildIndex <= VECTOR_LAST_INDEX);
        m_VectorRef[m_CurrentBuildIndex++] = next_coeff;
        return *this;
    }

 private:
    /// Terminates the operations of the initializer
    LM_INLINE auto _finished() -> void {
        assert(m_CurrentBuildIndex == (VECTOR_LAST_INDEX + 1));
    }

 private:
    /// Mutable reference to the vector we're currently constructing
    VectorType& m_VectorRef;
    /// Index of the current coefficient being 'built'
    int32_t m_CurrentBuildIndex = VECTOR_FIRST_INDEX;
};

}  // namespace math
}  // namespace loco
