#pragma once

namespace tiny {
namespace math {

template <typename Scalar_T>
constexpr Scalar_T PI = static_cast<Scalar_T>(3.141592653589793);

template <typename Scalar_T>
constexpr Scalar_T EPS = static_cast<Scalar_T>(1e-9);

using float32_t = float;
using float64_t = double;

}  // namespace math
}  // namespace tiny
