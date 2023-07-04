import pytest

import numpy as np
import math3d as m3d

from typing import Type, Union, List

EulerCls = Type[Union[m3d.Euler_f, m3d.Euler_d]]
Vector3Cls = Type[Union[m3d.Vector3f, m3d.Vector3d]]
QuaternionCls = Type[Union[m3d.Quaternionf, m3d.Quaterniond]]
Matrix3Cls = Type[Union[m3d.Matrix3f, m3d.Matrix3d]]
Matrix4Cls = Type[Union[m3d.Matrix4f, m3d.Matrix4d]]

EulerType = Union[m3d.Euler_f, m3d.Euler_d]

# Make sure our generators are seeded with the answer to the universe :D
np.random.seed(42)
# Number of times we will sample a random matrix for mat4 operator checks
NUM_RANDOM_SAMPLES = 10
# The delta used for tolerance (due to floating point precision mismatches)
EPSILON = 1e-5


from pdb import set_trace


def euler_all_close(euler: EulerType, e_list: List[float], tol: float = 1e-5) -> None:
    return (
        np.abs(euler.x - e_list[0]) < tol
        and np.abs(euler.y - e_list[1]) < tol
        and np.abs(euler.z - e_list[2]) < tol
    )


@pytest.mark.parametrize("euler_t", [(m3d.Euler_f), (m3d.Euler_d)])
def test_euler_attribs(euler_t: EulerCls) -> None:
    assert hasattr(euler_t, "x")
    assert hasattr(euler_t, "y")
    assert hasattr(euler_t, "z")
    assert hasattr(euler_t, "order")
    assert hasattr(euler_t, "convention")


@pytest.mark.parametrize("Euler", [(m3d.Euler_f), (m3d.Euler_d)])
def test_default_constructor(Euler: EulerCls) -> None:
    e = Euler()
    assert e.order == m3d.eOrder.XYZ
    assert e.convention == m3d.eConvention.INTRINSIC
    assert euler_all_close(e, [0.0, 0.0, 0.0], EPSILON)


@pytest.mark.parametrize("Euler", [(m3d.Euler_f), (m3d.Euler_d)])
def test_angles_constructor(Euler: EulerCls) -> None:
    e_x, e_y, e_z = np.pi / 2.0, np.pi / 3.0, np.pi / 4.0
    e = Euler(e_x, e_y, e_z)
    assert e.order == m3d.eOrder.XYZ
    assert e.convention == m3d.eConvention.INTRINSIC
    assert euler_all_close(e, [e_x, e_y, e_z], EPSILON)


@pytest.mark.parametrize(
    "Euler, Mat3", [(m3d.Euler_f, m3d.Matrix3f), (m3d.Euler_d, m3d.Matrix3d)]
)
def test_from_rotmat_constructor(Euler: EulerCls, Mat3: Matrix3Cls) -> None:
    rot_x = Mat3.RotationX(np.pi / 3.0)
    rot_y = Mat3.RotationY(np.pi / 4.0)
    rot_z = Mat3.RotationZ(np.pi / 5.0)

    euler_x = Euler(rot_x)
    euler_y = Euler(rot_y)
    euler_z = Euler(rot_z)

    # Be a little more forgiving with the tolerance for these calculations
    CONST_EPS = 1e-4

    assert euler_all_close(euler_x, [np.pi / 3.0, 0.0, 0.0], CONST_EPS)
    assert euler_all_close(euler_y, [0.0, np.pi / 4.0, 0.0], CONST_EPS)
    assert euler_all_close(euler_z, [0.0, 0.0, np.pi / 5.0], CONST_EPS)


@pytest.mark.parametrize(
    "Euler, Mat4", [(m3d.Euler_f, m3d.Matrix4f), (m3d.Euler_d, m3d.Matrix4d)]
)
def test_from_transform_constructor(Euler: EulerCls, Mat4: Matrix4Cls) -> None:
    tf_rot_x = Mat4.RotationX(np.pi / 3.0)
    tf_rot_y = Mat4.RotationY(np.pi / 4.0)
    tf_rot_z = Mat4.RotationZ(np.pi / 5.0)

    euler_x = Euler(tf_rot_x)
    euler_y = Euler(tf_rot_y)
    euler_z = Euler(tf_rot_z)

    # Be a little more forgiving with the tolerance for these calculations
    CONST_EPS = 1e-4

    assert euler_all_close(euler_x, [np.pi / 3.0, 0.0, 0.0], CONST_EPS)
    assert euler_all_close(euler_y, [0.0, np.pi / 4.0, 0.0], CONST_EPS)
    assert euler_all_close(euler_z, [0.0, 0.0, np.pi / 5.0], CONST_EPS)
