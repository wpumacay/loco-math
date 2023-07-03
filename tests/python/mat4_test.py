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


@pytest.mark.parametrize(
    "Mat4, Vec4, FloatType",
    [
        (m3d.Matrix4f, m3d.Vector4f, np.float32),
        (m3d.Matrix4d, m3d.Vector4d, np.float64),
    ],
)
class TestMat2Accessors:
    def test_get_column(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat4( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                   13.0, 14.0, 15.0, 16.0)
        # fmt: on

        # __getitem__ by using a single entry should return the requested column
        col0, col1, col2, col3 = mat[0], mat[1], mat[2], mat[3]
        assert (
            type(col0) is Vec4
            and type(col1) is Vec4
            and type(col2) is Vec4
            and type(col3) is Vec4
        )
        assert vec2_all_close(col0, np.array([1.0, 5.0, 9.0, 13.0], dtype=FloatType))
        assert vec2_all_close(col1, np.array([2.0, 6.0, 10.0, 14.0], dtype=FloatType))
        assert vec2_all_close(col2, np.array([3.0, 7.0, 11.0, 15.0], dtype=FloatType))
        assert vec2_all_close(col3, np.array([4.0, 8.0, 12.0, 16.0], dtype=FloatType))

    def test_get_entry(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat4( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                   13.0, 14.0, 15.0, 16.0)
        # fmt: on

        # __getitem__ by using a tuple to get matrix entries
        assert (
            mat[0, 0] == 1.0
            and mat[0, 1] == 2.0
            and mat[0, 2] == 3.0
            and mat[0, 3] == 4.0
        )
        assert (
            mat[1, 0] == 5.0
            and mat[1, 1] == 6.0
            and mat[1, 2] == 7.0
            and mat[1, 3] == 8.0
        )
        assert (
            mat[2, 0] == 9.0
            and mat[2, 1] == 10.0
            and mat[2, 2] == 11.0
            and mat[2, 3] == 12.0
        )
        assert (
            mat[3, 0] == 13.0
            and mat[3, 1] == 14.0
            and mat[3, 2] == 15.0
            and mat[3, 3] == 16.0
        )

    def test_get_view(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        # __getitem__ by using a slice of the matrix (view)
        # TODO(wilbert): impl. __getitem__ to retrieve a slice-view of the vector
        ...

    def test_set_column(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat4( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                   13.0, 14.0, 15.0, 16.0)

        # __setitem__ by passing a column vector and column index
        mat[0] = np.array([1.1, 5.1, 9.1, 13.1], dtype=FloatType)
        mat[1] = np.array([2.1, 6.1, 10.1, 14.1], dtype=FloatType)
        mat[2] = np.array([3.1, 7.1, 11.1, 15.1], dtype=FloatType)
        mat[3] = np.array([4.1, 8.1, 12.1, 16.1], dtype=FloatType)
        expected_np = np.array([[ 1.1,  2.1,  3.1,  4.1],
                                [ 5.1,  6.1,  7.1,  8.1],
                                [ 9.1, 10.1, 11.1, 12.1],
                                [13.1, 14.1, 15.1, 16.1]], dtype=FloatType)
        # fmt: on
        assert mat4_all_close(mat, expected_np)

    def test_set_entry(
        self, Mat4: Matrix4Cls, Vec4: Vector4Cls, FloatType: type
    ) -> None:
        # fmt: off
        mat = Mat4( 1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0,
                   13.0, 14.0, 15.0, 16.0)

        # __setitem__ by passing a single float and a tuple as index
        mat[0, 0], mat[0, 1], mat[0, 2], mat[0, 3] = 1.1, 2.1, 3.1, 4.1
        mat[1, 0], mat[1, 1], mat[1, 2], mat[1, 3] = 5.1, 6.1, 7.1, 8.1
        mat[2, 0], mat[2, 1], mat[2, 2], mat[2, 3] = 9.1, 10.1, 11.1, 12.1
        mat[3, 0], mat[3, 1], mat[3, 2], mat[3, 3] = 13.1, 14.1, 15.1, 16.1

        expected_np = np.array([[ 1.1,  2.1,  3.1,  4.1],
                                [ 5.1,  6.1,  7.1,  8.1],
                                [ 9.1, 10.1, 11.1, 12.1],
                                [13.1, 14.1, 15.1, 16.1]], dtype=FloatType)
        # fmt: on
        assert mat4_all_close(mat, expected_np)
