#pragma once

#if defined(TINYMATH_AVX_ENABLED)

#include <immintrin.h>

#include <tinymath/mat4_t.hpp>
#include <type_traits>

namespace tiny {
namespace math {
namespace avx {

template <typename T>
using ArrayCols = typename Matrix4<T>::BufferType;

// ***************************************************************************//
//                    Dispatch AVX-kernel for matrix addition                 //
// ***************************************************************************//

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_add_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                               const ArrayCols<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_add_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                               const ArrayCols<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f64 matrices
}

// ***************************************************************************//
//                 Dispatch AVX-kernel for matrix substraction                //
// ***************************************************************************//

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_sub_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                               const ArrayCols<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_sub_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                               const ArrayCols<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f64 matrices
}

// ***************************************************************************//
//                Dispatch AVX-kernel for matrix-scalar product               //
// ***************************************************************************//

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_scale_mat4(ArrayCols<T>& dst, T scale,
                                 const ArrayCols<T>& mat) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_scale_mat4(ArrayCols<T>& dst, T scale,
                                 const ArrayCols<T>& mat) -> void {
    // @todo(wilbert): AVX implementation for mat4-f64 matrices
}

// ***************************************************************************//
//                Dispatch AVX-kernel for matrix-matrix product               //
// ***************************************************************************//

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_matmul_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                                  const ArrayCols<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_matmul_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                                  const ArrayCols<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f64 matrices
}

// ***************************************************************************//
//             Dispatch AVX-kernel for matrix element-wise product            //
// ***************************************************************************//

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat32<T>::value>::type* = nullptr>
TM_INLINE auto kernel_hadamard_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                                    const ArrayCols<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat4-f32 matrices
}

template <typename T,
          typename std::enable_if<CpuHasAVX<T>::value &&
                                  IsFloat64<T>::value>::type* = nullptr>
TM_INLINE auto kernel_hadamard_mat4(ArrayCols<T>& dst, const ArrayCols<T>& lhs,
                                    const ArrayCols<T>& rhs) -> void {
    // @todo(wilbert): AVX implementation for mat64-f64 matrices
}

}  // namespace avx
}  // namespace math
}  // namespace tiny

#endif  // TINYMATH_AVX_ENABLED
