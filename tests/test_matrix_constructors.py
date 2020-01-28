#!/usr/bin/env python

import pytest
import tinymath as tm
import numpy as np

def test_defaultConstructor() :
    tm_mat3 = tm.Matrix3f()
    np_mat3 = np.identity( 3 ).astype( np.float32 )
    print( tm_mat3 )
    print( np_mat3 )
    assert np.allclose( tm_mat3, np_mat3 ), 'test_defaultConstructor() >>> mat3 default constructor does not return identity'

    tm_mat4 = tm.Matrix4f()
    np_mat4 = np.identity( 4 ).astype( np.float32 )
    assert np.allclose( tm_mat4, np_mat4 ), 'test_defaultConstructor() >>> mat4 default constructor does not return identity'

def test_fromBufferConstructorSameSize() :
    np_mat3_1 = np.arange( 3 * 3 ).reshape( 3, 3 ).astype( np.float32 )
    tm_mat3_1 = tm.Matrix3f( np_mat3_1 )
    assert np.allclose( tm_mat3_1, np_mat3_1 ), 'test_fromBufferConstructor >>> mat3 from-buffer does not return same matrix as ndarray'

    tm_mat3_2 = tm.Matrix3f( tm_mat3_1 )
    assert np.allclose( tm_mat3_2, tm_mat3_1 ), 'test_fromBufferConstructor >>> mat3 from-buffer does not return same matrix as Matrix3f'

    np_mat4_1 = np.arange( 4 * 4 ).reshape( 4, 4 ).astype( np.float32 )
    tm_mat4_1 = tm.Matrix4f( np_mat4_1 )
    assert np.allclose( tm_mat4_1, np_mat4_1 ), 'test_fromBufferConstructor >>> mat4 from-buffer does not return same matrix as ndarray'

    tm_mat4_2 = tm.Matrix4f( tm_mat4_1 )
    assert np.allclose( tm_mat4_2, tm_mat4_1 ), 'test_fromBufferConstructor >>> mat4 from-buffer does not return same matrix as Matrix4f'

def test_fromBufferConstructorBiggerSize() :
    np_mat_1 = np.arange( 5 * 7 ).reshape( 5, 7 ).astype( np.float32 )
    tm_mat3_1 = tm.Matrix3f( np_mat_1 ) # test with row-major data
    tm_mat4_1 = tm.Matrix4f( np_mat_1 ) # test with row-major data
    assert np.allclose( tm_mat3_1, np_mat_1[:3,:3] ), 'test_fromBufferConstructorBiggerSize >>> mat3 from-buffer does not return expected sub-matrix for top-left portion (from ndarray)'
    assert np.allclose( tm_mat4_1, np_mat_1[:4,:4] ), 'test_fromBufferConstructorBiggerSize >>> mat4 from-buffer does not return expected sub-matrix for top-left portion (from ndarray)'

    tm_mat3_2 = tm.Matrix3f( tm_mat4_1 ) # test with column-major data
    assert np.allclose( tm_mat3_2, tm_mat3_1 ), 'test_fromBufferConstructorBiggerSize >>> mat3 from-buffer does not return expected sub-matrix for top-left portion (from Matrix4f)'

def test_fromBufferConstructorMatAndVec() :
    np_mat4_1 = np.zeros( ( 4, 4 ) )
    np_mat4_1[:3,:3] = np.arange( 9 ).reshape( 3, 3 )
    np_mat4_1[:,3] = np.array( [ 100., 200., 300., 1. ] )
    tm_mat4_1 = tm.Matrix4f( np_mat4_1[:3,:3], np_mat4_1[:3,3] ) # test with row-major data
    assert np.allclose( np_mat4_1, tm_mat4_1 ), 'test_fromBufferConstructorMatAndVec >>> mat4 from-buffer (mat,vec) does not return expected matrix'

    tm_mat3_1 = tm.Matrix3f( tm_mat4_1 )
    tm_mat4_2 = tm.Matrix4f( tm_mat3_1, [100., 200., 300.] ) # test with column-major data
    assert np.allclose( tm_mat4_2, tm_mat4_1 ), 'test_fromBufferConstructorMatAndVec >>> mat4 from-buffer (mat,vec) does not return expected matrix (from Matrix3f)'