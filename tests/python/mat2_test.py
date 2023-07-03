import pytest

import numpy as np
import math3d as m3d

from typing import Type, Union, cast, Tuple

Matrix2Cls = Type[Union[m3d.Matrix2f, m3d.Matrix2d]]
Vector2Cls = Type[Union[m3d.Vector2f, m3d.Vector2d]]

Matrix2 = Union[m3d.Matrix2f, m3d.Matrix2d]
Vector2 = Union[m3d.Vector2f, m3d.Vector2d]

# Make sure our generators are seeded with the answer to the universe :D
np.random.seed(42)
# Number of times we will sample a random matrix for mat2 operator checks
NUM_RANDOM_SAMPLES = 10
# The delta used for tolerance (due to floating point precision mismatches)
EPSILON = 1e-5


def mat2_all_close(mat: Matrix2, mat_np: np.ndarray, epsilon: float = EPSILON) -> bool:
    return np.allclose(cast(np.ndarray, mat), mat_np, atol=epsilon)


def vec2_all_close(vec: Vector2, vec_np: np.ndarray, epsilon: float = EPSILON) -> bool:
    return np.allclose(cast(np.ndarray, vec), vec_np, atol=epsilon)


@pytest.mark.parametrize(
    "Mat2, Vec2, FloatType",
    [
        (m3d.Matrix2f, m3d.Vector2f, np.float32),
        (m3d.Matrix2d, m3d.Vector2d, np.float64),
    ],
)
class TestMat2Constructors:
    def test_default_constructor(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        mat = Mat2()
        expected_np = np.zeros((2, 2), dtype=FloatType)
        assert mat2_all_close(mat, expected_np)

    def test_diagonal_constructor(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        mat = Mat2(1.0, 2.0)
        expected_np = np.diag([1.0, 2.0]).astype(FloatType)
        assert mat2_all_close(mat, expected_np)

    def test_all_entries_constructor(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat2(1.0, 2.0,
                   3.0, 4.0)
        expected_np = np.array([[1.0, 2.0],
                                [3.0, 4.0]], dtype=FloatType)
        # fmt: on
        assert mat2_all_close(mat, expected_np)

    def test_columns_constructor(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        col_0 = Vec2(1.0, 3.0)
        col_1 = Vec2(2.0, 4.0)
        mat = Mat2(col_0, col_1)
        # fmt: off
        expected_np = np.array([[1.0, 2.0],
                                [3.0, 4.0]], dtype=FloatType)
        # fmt: on
        assert mat2_all_close(mat, expected_np)

    def test_numpy_array_constructor(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat2(np.array([[1.0, 2.0],
                             [3.0, 4.0]], dtype=FloatType))
        expected_np = np.array([[1.0, 2.0],
                                [3.0, 4.0]], dtype=FloatType)
        # fmt: on
        assert mat2_all_close(mat, expected_np)
