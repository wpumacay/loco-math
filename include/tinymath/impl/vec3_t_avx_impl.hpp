#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <tinymath/vec3_t.hpp>

namespace tiny {
namespace math {
namespace avx {

// ***************************************************************************//
//    Declarations for double-precision floating point numbers (float64_t)    //
// ***************************************************************************//
using Vec3d = Vector3<float64_t>;
using Array3d = Vec3d::BufferType;

// NOLINTNEXTLINE(runtime/references)
auto kernel_add_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_sub_v3d(Array3d& dst, const Array3d& lhs, const Array3d& rhs)
    -> void;

// NOLINTNEXTLINE(runtime/references)
auto kernel_scale_v3d(Array3d& dst, float64_t scale, const Array3d& vec)
    -> void;

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
