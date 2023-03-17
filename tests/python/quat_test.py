import pytest

import numpy as np
import math3d as m3d

from typing import Type, Union

QuaternionCls = Type[Union[m3d.Quaternionf, m3d.Quaterniond]]


@pytest.mark.parametrize("Quat", [(m3d.Quaternionf), (m3d.Quaterniond)])
def test_quat_attrs(Quat: QuaternionCls) -> None:
    assert (
        hasattr(Quat, "w")
        and hasattr(Quat, "x")
        and hasattr(Quat, "y")
        and hasattr(Quat, "z")
    )


@pytest.mark.parametrize(
    "Quat,FloatType", [(m3d.Quaternionf, np.float32), (m3d.Quaterniond, np.float64)]
)
class TestQuatConstructors:
    def test_default_constructor(self, Quat: QuaternionCls, FloatType: type) -> None:
        q = Quat()
        assert q.w == 1.0 and q.x == 0.0 and q.y == 0.0 and q.z == 0.0

    def test_single_scalar_arg_constructor(
        self, Quat: QuaternionCls, FloatType: type
    ) -> None:
        q = Quat(2.0)
        assert q.w == 2.0 and q.x == 0.0 and q.y == 0.0 and q.z == 0.0

    def test_four_scalars_args_constructor(
        self, Quat: QuaternionCls, FloatType: type
    ) -> None:
        q = Quat(2.0, 3.0, 5.0, 7.0)
        assert q.w == 2.0 and q.x == 3.0 and q.y == 5.0 and q.z == 7.0

    def test_numpy_array_constructor(
        self, Quat: QuaternionCls, FloatType: type
    ) -> None:
        arr_np = np.array([11.0, 13.0, 17.0, 19.0])
        q = Quat(arr_np.astype(FloatType))
        assert q.w == 11.0 and q.x == 13.0 and q.y == 17.0 and q.z == 19.0

        q = Quat(arr_np.reshape(1, 4).astype(FloatType))
        assert q.w == 11.0 and q.x == 13.0 and q.y == 17.0 and q.z == 19.0

        q = Quat(arr_np.reshape(4, 1).astype(FloatType))
        assert q.w == 11.0 and q.x == 13.0 and q.y == 17.0 and q.z == 19.0

        q = Quat([11.0, 13.0, 17.0, 19.0])
        assert q.w == 11.0 and q.x == 13.0 and q.y == 17.0 and q.z == 19.0


@pytest.mark.parametrize("Quat", [(m3d.Quaternionf), (m3d.Quaterniond)])
def test_quat_accessors(Quat: QuaternionCls) -> None:
    q = Quat(3.0, 5.0, 7.0, 11.0)
    assert q.w == 3.0 and q.x == 5.0 and q.y == 7.0 and q.z == 11.0
    assert q[0] == 3.0 and q[1] == 5.0 and q[2] == 7.0 and q[3] == 11.0

    q[0], q.z = 13.0, 17.0
    assert q.w == 13.0 and q[3] == 17.0


@pytest.mark.parametrize(
    "Quat,FloatType", [(m3d.Quaternionf, np.float32), (m3d.Quaterniond, np.float64)]
)
class TestQuatOperators:
    def test_comparison_operator(self, Quat: QuaternionCls, FloatType: type) -> None:
        q1 = Quat(1.0, 2.0, 3.0, 4.0)
        q2 = Quat(1.0, 2.0, 3.0, 4.0)
        assert q1 == q2

        q1.w, q2.w = 11.0, 13.0
        assert q1 != q2

    def test_quat_addition(self, Quat: QuaternionCls, FloatType: type) -> None:
        q1 = Quat(1.0, 2.0, 4.0, 8.0)
        q2 = Quat(1.0, 3.0, 9.0, 27.0)
        q_sum = q1 + q2
        assert q_sum.w == 2.0 and q_sum.x == 5.0 and q_sum.y == 13.0 and q_sum.z == 35.0

    def test_quat_substraction(self, Quat: QuaternionCls, FloatType: type) -> None:
        q1 = Quat(1.0, 2.0, 4.0, 8.0)
        q2 = Quat(1.0, 3.0, 9.0, 27.0)
        q_sum = q1 - q2
        assert (
            q_sum.w == 0.0 and q_sum.x == -1.0 and q_sum.y == -5.0 and q_sum.z == -19.0
        )

    def test_quat_scalar_product(self, Quat: QuaternionCls, FloatType: type) -> None:
        q, scale = Quat(1.0, 2.0, 3.0, 4.0), 2.5
        q_scaled = q * scale
        assert (
            q_scaled.w == 2.5
            and q_scaled.x == 5.0
            and q_scaled.y == 7.5
            and q_scaled.z == 10.0
        )
        q_scaled = scale * q
        assert (
            q_scaled.w == 2.5
            and q_scaled.x == 5.0
            and q_scaled.y == 7.5
            and q_scaled.z == 10.0
        )

    def test_quat_multiplication(self, Quat: QuaternionCls, FloatType: type) -> None:
        i = Quat(0.0, 1.0, 0.0, 0.0)
        j = Quat(0.0, 0.0, 1.0, 0.0)
        k = Quat(0.0, 0.0, 0.0, 1.0)
        assert i * j == k and j * k == i and k * i == j

        q1 = Quat(1.0, 2.0, 3.0, 4.0)
        q2 = Quat(1.0, 3.0, 5.0, 7.0)
        q_mul = q1 * q2
        assert (
            q_mul.w == -48.0 and q_mul.x == 6.0 and q_mul.y == 6.0 and q_mul.z == 12.0
        )


@pytest.mark.parametrize(
    "Quat, FloatType", [(m3d.Quaternionf, np.float32), (m3d.Quaterniond, np.float64)]
)
class TestQuatMethods:
    ...
