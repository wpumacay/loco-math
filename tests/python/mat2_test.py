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


@pytest.mark.parametrize(
    "Mat2, Vec2, FloatType",
    [
        (m3d.Matrix2f, m3d.Vector2f, np.float32),
        (m3d.Matrix2d, m3d.Vector2d, np.float64),
    ],
)
class TestMat2Accessors:
    def test_get_column(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat2(1.0, 2.0,
                   3.0, 4.0)
        # fmt: on

        # __getitem__ by using a single entry should return the requested column
        col0, col1 = mat[0], mat[1]
        assert type(col0) == Vec2 and type(col1) == Vec2
        assert vec2_all_close(col0, np.array([1.0, 3.0], dtype=FloatType))
        assert vec2_all_close(col1, np.array([2.0, 4.0], dtype=FloatType))

    def test_get_entry(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat2(1.0, 2.0,
                   3.0, 4.0)
        # fmt: on

        # __getitem__ by using a tuple to get matrix entries
        assert mat[0, 0] == 1.0 and mat[0, 1] == 2.0
        assert mat[1, 0] == 3.0 and mat[1, 1] == 4.0

    def test_get_view(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # __getitem__ by using a slice of the matrix (view)
        # TODO(wilbert): impl. __getitem__ to retrieve a slice-view of the vector
        ...

    def test_set_column(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat2(1.0, 2.0,
                   3.0, 4.0)

        # __setitem__ by passing a column vector and column index
        mat[0] = np.array([1.1, 3.1], dtype=FloatType)
        mat[1] = np.array([2.1, 4.1], dtype=FloatType)
        expected_np = np.array([[1.1, 2.1],
                                [3.1, 4.1]], dtype=FloatType)
        # fmt: on
        assert mat2_all_close(mat, expected_np)

    def test_set_entry(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat2(1.0, 2.0,
                   3.0, 4.0)

        # __setitem__ by passing a single float and a tuple as index
        mat[0, 0], mat[0, 1] = 1.1, 2.1
        mat[1, 0], mat[1, 1] = 3.1, 4.1

        expected_np = np.array([[1.1, 2.1],
                                [3.1, 4.1]], dtype=FloatType)
        # fmt: on
        assert mat2_all_close(mat, expected_np)


@pytest.mark.parametrize(
    "Mat2, Vec2, FloatType",
    [
        (m3d.Matrix2f, m3d.Vector2f, np.float32),
        (m3d.Matrix2d, m3d.Vector2d, np.float64),
    ],
)
class TestMat2Operators:
    def test_comparison_operator(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat_a = Mat2(1.0, 2.0,
                     3.0, 4.0)
        mat_b = Mat2(1.0, 2.0,
                     3.0, 4.0)
        # fmt: on

        # Checking comparison operator (__eq__)
        assert mat_a == mat_b

        # Update the matrices so they don't match
        mat_a[0, 0], mat_b[0, 0] = 1.1, 2.1

        # Checking neg. comparison  operator (__neq__)
        assert mat_a != mat_b

    def test_matrix_addition(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # Testing against some hard-coded matrices
        # fmt: off
        mat_a = Mat2(1.0, 2.0,
                     3.0, 4.0)
        mat_b = Mat2(2.0, 3.0,
                     5.0, 7.0)
        mat_c = mat_a + mat_b
        expected_c = Mat2(3.0, 5.0,
                          8.0, 11.0)
        # fmt: on
        assert type(mat_c) is Mat2
        assert mat_c == expected_c

        # Testing against some randomly sampled matrices
        for _ in range(NUM_RANDOM_SAMPLES):
            np_a = np.random.randn(2, 2).astype(FloatType)
            np_b = np.random.randn(2, 2).astype(FloatType)
            np_c = np_a + np_b

            mat_a, mat_b = Mat2(np_a), Mat2(np_b)
            mat_c = mat_a + mat_b
            # Check that we're doing what numpy does for addition
            assert mat2_all_close(mat_c, np_c)

    def test_matrix_substraction(
        self, Mat2: Matrix2Cls, Vec2: Vector2Cls, FloatType: type
    ) -> None:
        # Testing against some hard-coded matrices
        # fmt: off
        mat_a = Mat2(1.0, 2.0,
                     3.0, 4.0)
        mat_b = Mat2(2.0, 3.0,
                     5.0, 7.0)
        mat_c = mat_a - mat_b
        expected_c = Mat2(-1.0, -1.0,
                          -2.0, -3.0)
        # fmt: on
        assert type(mat_c) is Mat2
        assert mat_c == expected_c

        # Testing against some randomly sampled matrices
        for _ in range(NUM_RANDOM_SAMPLES):
            np_a = np.random.randn(2, 2).astype(FloatType)
            np_b = np.random.randn(2, 2).astype(FloatType)
            np_c = np_a - np_b

            mat_a, mat_b = Mat2(np_a), Mat2(np_b)
            mat_c = mat_a - mat_b
            # Check that we're doing what numpy does for addition
            assert mat2_all_close(mat_c, np_c)
