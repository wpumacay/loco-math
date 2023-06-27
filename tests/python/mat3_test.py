import pytest

import numpy as np
import math3d as m3d

from typing import Type, Union, cast, Tuple

Matrix3Cls = Type[Union[m3d.Matrix3f, m3d.Matrix3d]]
Vector3Cls = Type[Union[m3d.Vector3f, m3d.Vector3d]]

Matrix3 = Union[m3d.Matrix3f, m3d.Matrix3d]
Vector3 = Union[m3d.Vector3f, m3d.Vector3d]

# Make sure our generators are seeded with the answer to the universe :D
np.random.seed(42)
# Number of times we will sample a random matrix for mat3 operator checks
NUM_SAMPLES = 10


def mat3_all_close(mat: Matrix3, mat_np: np.ndarray, epsilon: float = 1e-5) -> bool:
    return np.allclose(cast(np.ndarray, mat), mat_np, atol=epsilon)


def vec3_all_close(vec: Vector3, vec_np: np.ndarray, epsilon: float = 1e-5) -> bool:
    return np.allclose(cast(np.ndarray, vec), vec_np, atol=epsilon)


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
                [[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]],
                dtype=FloatType,
            )
        )
        assert mat3_all_close(mat, np.arange(1, 10).reshape(3, 3).astype(FloatType))


@pytest.mark.parametrize(
    "Mat3, Vec3, FloatType",
    [
        (m3d.Matrix3f, m3d.Vector3f, np.float32),
        (m3d.Matrix3d, m3d.Vector3d, np.float64),
    ],
)
def test_mat3_accessors(Mat3, Vec3, FloatType) -> None:
    mat = Mat3(
        np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]], dtype=FloatType)
    )

    # __getitem__ by using a single entry should return the requested column
    col0, col1, col2 = mat[0], mat[1], mat[2]
    assert type(col0) == Vec3 and type(col1) == Vec3 and type(col2) == Vec3
    assert vec3_all_close(col0, np.array([1.0, 4.0, 7.0], dtype=FloatType))
    assert vec3_all_close(col1, np.array([2.0, 5.0, 8.0], dtype=FloatType))
    assert vec3_all_close(col2, np.array([3.0, 6.0, 9.0], dtype=FloatType))

    # __getitem__ by using a tuple
    assert mat[0, 0] == 1.0 and mat[0, 1] == 2.0 and mat[0, 2] == 3.0
    assert mat[1, 0] == 4.0 and mat[1, 1] == 5.0 and mat[1, 2] == 6.0
    assert mat[2, 0] == 7.0 and mat[2, 1] == 8.0 and mat[2, 2] == 9.0

    # __getitem__ by using a slice
    # TODO(wilbert): implement __getitem__ to retrieve a view of the vector


@pytest.mark.parametrize(
    "Mat3, Vec3, FloatType",
    [
        (m3d.Matrix3f, m3d.Vector3f, np.float32),
        (m3d.Matrix3d, m3d.Vector3d, np.float64),
    ],
)
class TestMat3Operators:
    def test_comparison_operator(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        mat_a = Mat3(np.arange(1, 10).reshape(3, 3).astype(FloatType))
        mat_b = Mat3(np.arange(1, 10).reshape(3, 3).astype(FloatType))

        # Checking comparison operator (__eq__)
        assert mat_a == mat_b

        # Update the matrices so they don't match
        mat_a[0, 0], mat_b[0, 0] = 1.1, 2.1

        # Checking neg. comparison  operator (__neq__)
        assert mat_a != mat_b

    def test_matrix_addition(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        # Testing against some hardcoded matrices
        np_a = np.array(
            [[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]], dtype=FloatType
        )
        np_b = np.array(
            [[2.0, 3.0, 5.0], [7.0, 11.0, 13.0], [17.0, 19.0, 23.0]], dtype=FloatType
        )
        np_c = np_a + np_b

        mat_a, mat_b = Mat3(np_a), Mat3(np_b)
        mat_c = mat_a + mat_b
        assert mat3_all_close(mat_c, np_c)

        # Testing against randomly sampled matrices
        for i in range(NUM_SAMPLES):
            np_a = np.random.randn(3, 3).astype(FloatType)
            np_b = np.random.randn(3, 3).astype(FloatType)
            np_c = np_a + np_b

            mat_a, mat_b = Mat3(np_a), Mat3(np_b)
            mat_c = mat_a + mat_b
            assert mat3_all_close(mat_c, np_c)

    def test_matrix_substraction(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        ...

    def test_matrix_scalar_product(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        ...

    def test_matrix_vector_product(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        ...

    def test_matrix_matrix_product(
        self, Mat3: Matrix3Cls, Vec3: Vector3Cls, FloatType: type
    ) -> None:
        ...
