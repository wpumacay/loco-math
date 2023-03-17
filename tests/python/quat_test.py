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
    ...


@pytest.mark.parametrize(
    "Quat,FloatType", [(m3d.Quaternionf, np.float32), (m3d.Quaterniond, np.float64)]
)
class TestQuatOperators:
    ...


@pytest.mark.parametrize(
    "Quat, FloatType", [(m3d.Quaternionf, np.float32), (m3d.Quaterniond, np.float64)]
)
class TestQuatMethods:
    ...
