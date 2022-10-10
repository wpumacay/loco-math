#pragma once

#if defined(LOCOMATH_AVX_ENABLED)

#include <immintrin.h>

#include <loco/math/mat3_t.hpp>

/**
 * SSE instruction sets required for each kernel:
 *
 * - kernel_add_mat4                : AVX
 * - kernel_sub_mat4                : AVX
 * - kernel_scale_mat4              : AVX
 * - kernel_hadamard_mat4           : AVX
 *   kernel_matmul_mat4             : AVX
 *   kernel_matmul_vec_mat4         : AVX
 *
 * Notes:
 * 0. Matrix order:
 *    Our matrices' internal storage layout is column-major order
 *
 * 1. For AVX-float32:
 *    The columns of the matrix can each one be stored in an xmm register (4xf32
 *    fits into 128bit xmm reg.). Or we could use fit more into a ymm register
 *    (up to 8 floats, which is exactly 2 columns)
 *
 * 2. For AVX-float64:
 *    We can only store full columns into the ymm registers
 */

namespace loco {
namespace math {
namespace avx {

template <typename T>
using Mat3Buffer = typename Matrix3<T>::BufferType;

template <typename T>
using Vec3Buffer = typename Vector3<T>::BufferType;

template <typename T>
using SFINAE_MAT3_F32_AVX_GUARD =
    typename std::enable_if<CpuHasAVX<T>::value && IsFloat32<T>::value>::type*;

template <typename T>
using SFINAE_MAT3_F64_AVX_GUARD =
    typename std::enable_if<CpuHasAVX<T>::value && IsFloat64<T>::value>::type*;

// ***************************************************************************//
//                    Dispatch AVX-kernel for matrix addition                 //
// ***************************************************************************//

template <typename T, SFINAE_MAT3_F32_AVX_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    // Will use avx instructions (ymm-regs) for the first group of 2 columns,
    // and then sse instructions (xmm-regs) for the remaining column :)
    auto ymm_lhs_cols_01 =
        _mm256_load_ps(static_cast<const float*>(lhs[0].data()));
    auto ymm_rhs_cols_01 =
        _mm256_load_ps(static_cast<const float*>(rhs[0].data()));
    auto ymm_sum_cols_01 = _mm256_add_ps(ymm_lhs_cols_01, ymm_rhs_cols_01);

    auto xmm_lhs_col_2 = _mm_load_ps(static_cast<const float*>(lhs[2].data()));
    auto xmm_rhs_col_2 = _mm_load_ps(static_cast<const float*>(rhs[2].data()));
    auto xmm_sum_col_2 = _mm_add_ps(xmm_lhs_col_2, xmm_rhs_col_2);

    _mm256_store_ps(static_cast<float*>(dst[0].data()), ymm_sum_cols_01);
    _mm_store_ps(static_cast<float*>(dst[2].data()), xmm_sum_col_2);
}

template <typename T, SFINAE_MAT3_F64_AVX_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    // A single column fits into a ymm register ((3+1)xf64 <> 256-bit reg.)
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto ymm_lhs_col_j =
            _mm256_load_pd(static_cast<const double*>(lhs[j].data()));
        auto ymm_rhs_col_j =
            _mm256_load_pd(static_cast<const double*>(rhs[j].data()));
        auto ymm_sum_cols_j = _mm256_add_pd(ymm_lhs_col_j, ymm_rhs_col_j);
        _mm256_store_pd(static_cast<double*>(dst[j].data()), ymm_sum_cols_j);
    }
}

// ***************************************************************************//
//                 Dispatch AVX-kernel for matrix substraction                //
// ***************************************************************************//

template <typename T, SFINAE_MAT3_F32_AVX_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    // Proceed the same way we used the addition kernel
    auto ymm_lhs_cols_01 =
        _mm256_load_ps(static_cast<const float*>(lhs[0].data()));
    auto ymm_rhs_cols_01 =
        _mm256_load_ps(static_cast<const float*>(rhs[0].data()));
    auto ymm_sum_cols_01 = _mm256_sub_ps(ymm_lhs_cols_01, ymm_rhs_cols_01);

    auto xmm_lhs_col_2 = _mm_load_ps(static_cast<const float*>(lhs[2].data()));
    auto xmm_rhs_col_2 = _mm_load_ps(static_cast<const float*>(rhs[2].data()));
    auto xmm_sum_col_2 = _mm_sub_ps(xmm_lhs_col_2, xmm_rhs_col_2);

    _mm256_store_ps(static_cast<float*>(dst[0].data()), ymm_sum_cols_01);
    _mm_store_ps(static_cast<float*>(dst[2].data()), xmm_sum_col_2);
}

template <typename T, SFINAE_MAT3_F64_AVX_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto ymm_lhs_col_j =
            _mm256_load_pd(static_cast<const double*>(lhs[j].data()));
        auto ymm_rhs_col_j =
            _mm256_load_pd(static_cast<const double*>(rhs[j].data()));
        auto ymm_sum_cols_j = _mm256_sub_pd(ymm_lhs_col_j, ymm_rhs_col_j);
        _mm256_store_pd(static_cast<double*>(dst[j].data()), ymm_sum_cols_j);
    }
}

}  // namespace avx
}  // namespace math
}  // namespace loco

#endif  // LOCOMATH_AVX_ENABLED
