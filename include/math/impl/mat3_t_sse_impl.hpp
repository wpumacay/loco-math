#pragma once

#if defined(MATH_SSE_ENABLED)

#include <emmintrin.h>
#include <smmintrin.h>
#include <xmmintrin.h>

#include <math/mat3_t_decl.hpp>

/**
 * SSE instruction sets required for each kernel:
 *
 * - kernel_add_mat4                : SSE|SSE2
 * - kernel_sub_mat4                : SSE|SSE2
 * - kernel_scale_mat4              : SSE|SSE2
 * - kernel_hadamard_mat4           : SSE|SSE2
 *   kernel_matmul_mat4             : SSE|SSE2|FMA?(if available)
 *   kernel_matmul_vec_mat4         : SSE|SSE2|FMA?(if available)
 *
 * Notes:
 * 0. Matrix order:
 *    Our matrices' internal storage layout is column-major order
 *
 * 1. For SSE-float32:
 *    The columns of the matrix can each one be stored in an xmm register (
 *    (3+1)xf32 fits into a 128bit xmm reg.)
 *
 * 2. For SSE-float64:
 *    We can only store half of a column of the matrices into an xmm register,
 *    so we have to use both lo-hi halves in 2 separate xmm registers for an op
 *
 * 3. The kernels for mat3 should be similar to the ones for mat4 (as we're
 *    using 1float for padding), but different in the sense that these should be
 *    truncated (we're missing one column, so we have to handle evth manually)
 */

namespace math {
namespace sse {

template <typename T>
using Mat3Buffer = typename Matrix3<T>::BufferType;

template <typename T>
using Vec3Buffer = typename Vector3<T>::BufferType;

template <typename T>
using SFINAE_MAT3_SSE_F32_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat32<T>::value>::type*;

template <typename T>
using SFINAE_MAT3_SSE_F64_GUARD =
    typename std::enable_if<CpuHasSSE<T>::value && IsFloat64<T>::value>::type*;

// ***************************************************************************//
//                   Dispatch SSE-kernel for matrix addition                  //
// ***************************************************************************//

template <typename T, SFINAE_MAT3_SSE_F32_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    // vec3 (4 floats, as it uses padding) fits into an xmm register. The
    // padding float is set to zero during instantiation
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_lhs_col_j =
            _mm_loadu_ps(static_cast<const float*>(lhs[j].data()));
        auto xmm_rhs_col_j =
            _mm_loadu_ps(static_cast<const float*>(rhs[j].data()));
        auto xmm_sum_col_j = _mm_add_ps(xmm_lhs_col_j, xmm_rhs_col_j);

        _mm_storeu_ps(static_cast<float*>(dst[j].data()), xmm_sum_col_j);
    }
}

template <typename T, SFINAE_MAT3_SSE_F64_GUARD<T> = nullptr>
LM_INLINE auto kernel_add_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    // [c0, c1, c2, c3] -> column-major order (in storage), each with (3+1)xf32
    // So, we can send only half of each column to an xmm register
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_lhs_col_j_lo =
            _mm_loadu_pd(static_cast<const double*>(lhs[j].data()));
        auto xmm_lhs_col_j_hi =
            _mm_loadu_pd(static_cast<const double*>(lhs[j].data() + 2));

        auto xmm_rhs_col_j_lo =
            _mm_loadu_pd(static_cast<const double*>(rhs[j].data()));
        auto xmm_rhs_col_j_hi =
            _mm_loadu_pd(static_cast<const double*>(rhs[j].data() + 2));

        auto xmm_add_col_j_lo = _mm_add_pd(xmm_lhs_col_j_lo, xmm_rhs_col_j_lo);
        auto xmm_add_col_j_hi = _mm_add_pd(xmm_lhs_col_j_hi, xmm_rhs_col_j_hi);

        _mm_storeu_pd(static_cast<double*>(dst[j].data()), xmm_add_col_j_lo);
        _mm_storeu_pd(static_cast<double*>(dst[j].data() + 2),
                      xmm_add_col_j_hi);
    }
}

// ***************************************************************************//
//                 Dispatch SSE-kernel for matrix substraction                //
// ***************************************************************************//

template <typename T, SFINAE_MAT3_SSE_F32_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_lhs_col_j =
            _mm_loadu_ps(static_cast<const float*>(lhs[j].data()));
        auto xmm_rhs_col_j =
            _mm_loadu_ps(static_cast<const float*>(rhs[j].data()));
        auto xmm_sub_col_j = _mm_sub_ps(xmm_lhs_col_j, xmm_rhs_col_j);

        _mm_storeu_ps(static_cast<float*>(dst[j].data()), xmm_sub_col_j);
    }
}

template <typename T, SFINAE_MAT3_SSE_F64_GUARD<T> = nullptr>
LM_INLINE auto kernel_sub_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                               const Mat3Buffer<T>& rhs) -> void {
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_lhs_col_j_lo =
            _mm_loadu_pd(static_cast<const double*>(lhs[j].data()));
        auto xmm_lhs_col_j_hi =
            _mm_loadu_pd(static_cast<const double*>(lhs[j].data() + 2));

        auto xmm_rhs_col_j_lo =
            _mm_loadu_pd(static_cast<const double*>(rhs[j].data()));
        auto xmm_rhs_col_j_hi =
            _mm_loadu_pd(static_cast<const double*>(rhs[j].data() + 2));

        auto xmm_sub_col_j_lo = _mm_sub_pd(xmm_lhs_col_j_lo, xmm_rhs_col_j_lo);
        auto xmm_sub_col_j_hi = _mm_sub_pd(xmm_lhs_col_j_hi, xmm_rhs_col_j_hi);

        _mm_storeu_pd(static_cast<double*>(dst[j].data()), xmm_sub_col_j_lo);
        _mm_storeu_pd(static_cast<double*>(dst[j].data() + 2),
                      xmm_sub_col_j_hi);
    }
}

// ***************************************************************************//
//                Dispatch SSE-kernel for matrix-scalar product               //
// ***************************************************************************//

template <typename T, SFINAE_MAT3_SSE_F32_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_mat3(Mat3Buffer<T>& dst, T scale,
                                 const Mat3Buffer<T>& src) -> void {
    auto xmm_scale = _mm_set1_ps(scale);
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_col_j = _mm_loadu_ps(static_cast<const float*>(src[j].data()));
        auto xmm_col_scaled_j = _mm_mul_ps(xmm_scale, xmm_col_j);
        _mm_storeu_ps(static_cast<float*>(dst[j].data()), xmm_col_scaled_j);
    }
}

template <typename T, SFINAE_MAT3_SSE_F64_GUARD<T> = nullptr>
LM_INLINE auto kernel_scale_mat3(Mat3Buffer<T>& dst, T scale,
                                 const Mat3Buffer<T>& src) -> void {
    auto xmm_scale = _mm_set1_pd(scale);
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_col_j_lo =
            _mm_loadu_pd(static_cast<const double*>(src[j].data()));
        auto xmm_col_j_hi =
            _mm_loadu_pd(static_cast<const double*>(src[j].data() + 2));
        auto xmm_col_scaled_j_lo = _mm_mul_pd(xmm_scale, xmm_col_j_lo);
        auto xmm_col_scaled_j_hi = _mm_mul_pd(xmm_scale, xmm_col_j_hi);
        _mm_storeu_pd(static_cast<double*>(dst[j].data()), xmm_col_scaled_j_lo);
        _mm_storeu_pd(static_cast<double*>(dst[j].data() + 2),
                      xmm_col_scaled_j_hi);
    }
}

// ***************************************************************************//
//                Dispatch SSE-kernel for matrix-matrix product               //
// ***************************************************************************//

template <typename T, SFINAE_MAT3_SSE_F32_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                                  const Mat3Buffer<T>& rhs) -> void {
    // Use the "linear combination view" of the matrix-vector product, and apply
    // it along all column vectors of the right-hand side
    for (uint32_t k = 0; k < Matrix3<T>::MATRIX_SIZE; ++k) {
        // Compute each resulting column, as in the  "matmul_vec" kernel
        auto xmm_result_col_k = _mm_setzero_ps();
        for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
            //                              k=4            [      |     ]
            // A * v = (lhs * rhs)[:,k] = SUM   rhs[j,k] * |  lhs[:,j]  ]
            //                              k=0            [      |     ]
            auto xmm_scalar_rhs_jk = _mm_set1_ps(rhs[k][j]);
            auto xmm_lhs_col_j =
                _mm_loadu_ps(static_cast<const float*>(lhs[j].data()));
            auto xmm_lhs_col_scaled_j =
                _mm_mul_ps(xmm_scalar_rhs_jk, xmm_lhs_col_j);
            xmm_result_col_k =
                _mm_add_ps(xmm_result_col_k, xmm_lhs_col_scaled_j);
        }
        _mm_storeu_ps(static_cast<float*>(dst[k].data()), xmm_result_col_k);
    }
}

template <typename T, SFINAE_MAT3_SSE_F64_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_mat3(Mat3Buffer<T>& dst, const Mat3Buffer<T>& lhs,
                                  const Mat3Buffer<T>& rhs) -> void {
    // Use the same approach as the f32 version, but use lo-hi halves xmm regs.
    for (uint32_t k = 0; k < Matrix3<T>::MATRIX_SIZE; ++k) {
        auto xmm_result_col_k_lo = _mm_setzero_pd();
        auto xmm_result_col_k_hi = _mm_setzero_pd();
        for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
            auto xmm_scalar_rhs_jk = _mm_set1_pd(rhs[k][j]);
            auto xmm_lhs_col_j_lo =
                _mm_loadu_pd(static_cast<const double*>(lhs[j].data()));
            auto xmm_lhs_col_j_hi =
                _mm_loadu_pd(static_cast<const double*>(lhs[j].data() + 2));
            auto xmm_lhs_col_scaled_j_lo =
                _mm_mul_pd(xmm_scalar_rhs_jk, xmm_lhs_col_j_lo);
            auto xmm_lhs_col_scaled_j_hi =
                _mm_mul_pd(xmm_scalar_rhs_jk, xmm_lhs_col_j_hi);
            xmm_result_col_k_lo =
                _mm_add_pd(xmm_result_col_k_lo, xmm_lhs_col_scaled_j_lo);
            xmm_result_col_k_hi =
                _mm_add_pd(xmm_result_col_k_hi, xmm_lhs_col_scaled_j_hi);
        }
        _mm_storeu_pd(static_cast<double*>(dst[k].data()), xmm_result_col_k_lo);
        _mm_storeu_pd(static_cast<double*>(dst[k].data() + 2),
                      xmm_result_col_k_hi);
    }
}

// ***************************************************************************//
//                Dispatch SSE-kernel for matrix-vector product               //
// ***************************************************************************//

template <typename T, SFINAE_MAT3_SSE_F32_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_vec_mat3(Vec3Buffer<T>& dst,
                                      const Mat3Buffer<T>& mat,
                                      const Vec3Buffer<T>& vec) -> void {
    // Use the "linear combination view" of the matrix-vector product
    //         [ |  |  |  |  ]
    // A * v = | a0 a1 a2 a3 | * [v0,v1,v2,v3]^T
    //         [ |  |  |  |  ]
    //
    //             [ |]       [ |]        [ |]        [ |]
    // A * v = v0 *|a0]+ v1 * |a1] + v2 * |a2] + v3 * |a3]
    //             [ |]       [ |]        [ |]        [ |]
    //
    // Each column A[:,j] contains 4xf32 of data, so it fits in a single xmm reg
    // Notice that we're considering the padding, which makes vec3 a vec4 kinda
    auto xmm_result = _mm_setzero_ps();
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_vec_scalar_j = _mm_set1_ps(vec[j]);
        auto xmm_mat_col_j =
            _mm_loadu_ps(static_cast<const float*>(mat[j].data()));
        auto xmm_mat_col_scaled_j = _mm_mul_ps(xmm_vec_scalar_j, xmm_mat_col_j);
        xmm_result = _mm_add_ps(xmm_result, xmm_mat_col_scaled_j);
    }
    _mm_storeu_ps(static_cast<float*>(dst.data()), xmm_result);
}

template <typename T, SFINAE_MAT3_SSE_F64_GUARD<T> = nullptr>
LM_INLINE auto kernel_matmul_vec_mat3(Vec3Buffer<T>& dst,
                                      const Mat3Buffer<T>& mat,
                                      const Vec3Buffer<T>& vec) -> void {
    // Use the "linear combination view" of the matrix-vector product
    //         [ |  |  |  |  ]
    // A * v = | a0 a1 a2 a3 | * [v0,v1,v2,v3]^T
    //         [ |  |  |  |  ]
    //
    //             [ |]       [ |]        [ |]        [ |]
    // A * v = v0 *|a0]+ v1 * |a1] + v2 * |a2] + v3 * |a3]
    //             [ |]       [ |]        [ |]        [ |]
    //
    // Each column A[:,j] contains 4xf64 of data, so we have to split again into
    // lo-hi sections of 2xf64 each that fit into the xmm registers
    auto xmm_result_lo = _mm_setzero_pd();
    auto xmm_result_hi = _mm_setzero_pd();
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_vec_scalar_j = _mm_set1_pd(vec[j]);
        auto xmm_mat_col_j_lo =
            _mm_loadu_pd(static_cast<const double*>(mat[j].data()));
        auto xmm_mat_col_j_hi =
            _mm_loadu_pd(static_cast<const double*>(mat[j].data() + 2));
        auto xmm_mat_col_j_scaled_lo =
            _mm_mul_pd(xmm_vec_scalar_j, xmm_mat_col_j_lo);
        auto xmm_mat_col_j_scaled_hi =
            _mm_mul_pd(xmm_vec_scalar_j, xmm_mat_col_j_hi);

        xmm_result_lo = _mm_add_pd(xmm_result_lo, xmm_mat_col_j_scaled_lo);
        xmm_result_hi = _mm_add_pd(xmm_result_hi, xmm_mat_col_j_scaled_hi);
    }
    _mm_storeu_pd(static_cast<double*>(dst.data()), xmm_result_lo);
    _mm_storeu_pd(static_cast<double*>(dst.data() + 2), xmm_result_hi);
}

// ***************************************************************************//
//             Dispatch SSE-kernel for matrix element-wise product            //
// ***************************************************************************//

template <typename T, SFINAE_MAT3_SSE_F32_GUARD<T> = nullptr>
LM_INLINE auto kernel_hadamard_mat3(Mat3Buffer<T>& dst,
                                    const Mat3Buffer<T>& lhs,
                                    const Mat3Buffer<T>& rhs) -> void {
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_lhs_col_j =
            _mm_loadu_ps(static_cast<const float*>(lhs[j].data()));
        auto xmm_rhs_col_j =
            _mm_loadu_ps(static_cast<const float*>(rhs[j].data()));
        auto xmm_prod_col_j = _mm_mul_ps(xmm_lhs_col_j, xmm_rhs_col_j);

        _mm_storeu_ps(static_cast<float*>(dst[j].data()), xmm_prod_col_j);
    }
}

template <typename T, SFINAE_MAT3_SSE_F64_GUARD<T> = nullptr>
LM_INLINE auto kernel_hadamard_mat3(Mat3Buffer<T>& dst,
                                    const Mat3Buffer<T>& lhs,
                                    const Mat3Buffer<T>& rhs) -> void {
    for (uint32_t j = 0; j < Matrix3<T>::MATRIX_SIZE; ++j) {
        auto xmm_lhs_col_j_lo =
            _mm_loadu_pd(static_cast<const double*>(lhs[j].data()));
        auto xmm_lhs_col_j_hi =
            _mm_loadu_pd(static_cast<const double*>(lhs[j].data() + 2));

        auto xmm_rhs_col_j_lo =
            _mm_loadu_pd(static_cast<const double*>(rhs[j].data()));
        auto xmm_rhs_col_j_hi =
            _mm_loadu_pd(static_cast<const double*>(rhs[j].data() + 2));

        auto xmm_prod_col_j_lo = _mm_mul_pd(xmm_lhs_col_j_lo, xmm_rhs_col_j_lo);
        auto xmm_prod_col_j_hi = _mm_mul_pd(xmm_lhs_col_j_hi, xmm_rhs_col_j_hi);

        _mm_storeu_pd(static_cast<double*>(dst[j].data()), xmm_prod_col_j_lo);
        _mm_storeu_pd(static_cast<double*>(dst[j].data() + 2),
                      xmm_prod_col_j_hi);
    }
}

}  // namespace sse
}  // namespace math

#endif  // MATH_SSE_ENABLED
