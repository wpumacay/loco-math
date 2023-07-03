import pytest

import numpy as np
import math3d as m3d

from typing import Type, Union, cast, Tuple

Matrix4Cls = Type[Union[m3d.Matrix4f, m3d.Matrix4d]]
Vector4Cls = Type[Union[m3d.Vector4f, m3d.Vector4d]]

Matrix4 = Union[m3d.Matrix4f, m3d.Matrix4d]
Vector4 = Union[m3d.Vector4f, m3d.Vector4d]

# Make sure our generators are seeded with the answer to the universe :D
np.random.seed(42)
# Number of times we will sample a random matrix for mat4 operator checks
NUM_RANDOM_SAMPLES = 10
# The delta used for tolerance (due to floating point precision mismatches)
EPSILON = 1e-5


def mat4_all_close(mat: Matrix4, mat_np: np.ndarray, epsilon: float = EPSILON) -> bool:
    return np.allclose(cast(np.ndarray, mat), mat_np, atol=epsilon)


def vec2_all_close(vec: Vector4, vec_np: np.ndarray, epsilon: float = EPSILON) -> bool:
    return np.allclose(cast(np.ndarray, vec), vec_np, atol=epsilon)


@pytest.mark.parametrize(
    "Mat4, Vec4, FloatType",
    [
        (m3d.Matrix4f, m3d.Vector4f, np.float32),
        (m3d.Matrix4d, m3d.Vector4d, np.float64),
    ],
)
class TestMat4Constructors:
    def test_default_constructor(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        mat = Mat4()
        expected_np = np.zeros((4, 4), dtype=FloatType)
        assert mat4_all_close(mat, expected_np)

    def test_diagonal_constructor(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        mat = Mat4(1.0, 2.0, 3.0, 4.0)
        expected_np = np.diag([1.0, 2.0, 3.0, 4.0]).astype(FloatType)
        assert mat4_all_close(mat, expected_np)

    def test_all_entries_constructor(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat4( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                   13.0, 14.0, 15.0, 16.0)
        expected_np = np.array([[ 1.0,  2.0,  3.0,  4.0],
                                [ 5.0,  6.0,  7.0,  8.0],
                                [ 9.0, 10.0, 11.0, 12.0],
                                [13.0, 14.0, 15.0, 16.0]], dtype=FloatType)
        # fmt: on
        assert mat4_all_close(mat, expected_np)

    def test_columns_constructor(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        col_0 = Vec4(1.0, 5.0, 9.0, 13.0)
        col_1 = Vec4(2.0, 6.0, 10.0, 14.0)
        col_2 = Vec4(3.0, 7.0, 11.0, 15.0)
        col_3 = Vec4(4.0, 8.0, 12.0, 16.0)
        mat = Mat4(col_0, col_1, col_2, col_3)
        # fmt: off
        expected_np = np.array([[ 1.0,  2.0,  3.0,  4.0],
                                [ 5.0,  6.0,  7.0,  8.0],
                                [ 9.0, 10.0, 11.0, 12.0],
                                [13.0, 14.0, 15.0, 16.0]], dtype=FloatType)
        # fmt: on
        assert mat4_all_close(mat, expected_np)

    def test_numpy_array_constructor(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat4(np.array([[ 1.0,  2.0,  3.0,  4.0],
                             [ 5.0,  6.0,  7.0,  8.0],
                             [ 9.0, 10.0, 11.0, 12.0],
                             [13.0, 14.0, 15.0, 16.0]], dtype=FloatType))
        expected_np = np.array([[ 1.0,  2.0,  3.0,  4.0],
                                [ 5.0,  6.0,  7.0,  8.0],
                                [ 9.0, 10.0, 11.0, 12.0],
                                [13.0, 14.0, 15.0, 16.0]], dtype=FloatType)
        # fmt: on
        assert mat4_all_close(mat, expected_np)
