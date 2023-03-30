import pytest

import numpy as np
import math3d as m3d

from typing import Type, Union, List, cast

Matrix3Cls = Type[Union[m3d.Matrix3f, m3d.Matrix3d]]
Vector3Cls = Type[Union[m3d.Vector3f, m3d.Vector3d]]

Matrix3 = Union[m3d.Matrix3f, m3d.Matrix3d]
Vector3 = Union[m3d.Vector3f, m3d.Vector3d]


def mat3_all_close(mat: Matrix3, mat_np: np.ndarray, epsilon: float = 1e-5) -> bool:
    return np.allclose(cast(np.ndarray, mat), mat_np, atol=epsilon)


@pytest.mark.parametrize(
    "Mat3, Vec3, FloatType",
    [
        (m3d.Matrix3f, m3d.Vector3f, np.float32),
        (m3d.Matrix3d, m3d.Vector3d, np.float64),
    ],
)
class TestMat3Constructors:
    def test_default_constructor(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        mat = Mat3()
        assert mat3_all_close(mat, np.zeros((3, 3), dtype=FloatType))

    def test_diagonal_constructor(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        mat = Mat3(1.0, 2.0, 3.0)
        assert mat3_all_close(mat, np.diag([1.0, 2.0, 3.0]).astype(FloatType))

    def test_all_entries_constructor(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        mat = Mat3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)
        assert mat3_all_close(mat, np.arange(1, 10).reshape(3, 3).astype(FloatType))

    def test_columns_constructor(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        col_0 = Vec3(1.0, 4.0, 7.0)
        col_1 = Vec3(2.0, 5.0, 8.0)
        col_2 = Vec3(3.0, 6.0, 9.0)
        mat = Mat3(col_0, col_1, col_2)
        assert mat3_all_close(mat, np.arange(1, 10).reshape(3, 3).astype(FloatType))

    def test_numpy_array_constructor(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        mat = Mat3(
            np.array(
                [[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]], dtype=FloatType
            )
        )
        assert mat3_all_close(mat, np.arange(1, 10).reshape(3, 3).astype(FloatType))
