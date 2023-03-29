import pytest

import numpy as np
import math3d as m3d

from typing import Type, Union, cast

Vec3Cls = Type[Union[m3d.Vector3f, m3d.Vector3d]]
QuatCls = Type[Union[m3d.Quaternionf, m3d.Quaterniond]]
Mat3Cls = Type[Union[m3d.Matrix3f, m3d.Matrix3d]]
Pose3dCls = Type[Union[m3d.Pose3d_f, m3d.Pose3d_d]]

np.random.seed(0)


@pytest.mark.parametrize("Class", [(m3d.Pose3d_f), (m3d.Pose3d_d)])
def test_pose3d_attrs(Class: Pose3dCls) -> None:
    # Make sure we have exposed 'position' and 'orientation' properties
    assert hasattr(Class, "position") and hasattr(Class, "orientation")


@pytest.mark.parametrize(
    "Class,Type", [(m3d.Pose3d_f, np.float32), (m3d.Pose3d_d, np.float64)]
)
def test_default_constructor(Class: Pose3dCls, Type: type) -> None:
    pose = Class()
    # Default position is set to the world origin
    assert np.allclose(
        cast(np.ndarray, pose.position),
        np.array([0.0, 0.0, 0.0], dtype=Type),
    )
    # Default orientation is set to the (w=1, x=0, y=0, z=0)
    assert np.allclose(
        cast(np.ndarray, pose.orientation),
        np.array([1.0, 0.0, 0.0, 0.0], dtype=Type),
    )


@pytest.mark.parametrize(
    "Pose,Vec3,Quat,Type",
    [
        (m3d.Pose3d_f, m3d.Vector3f, m3d.Quaternionf, np.float32),
        (m3d.Pose3d_d, m3d.Vector3d, m3d.Quaterniond, np.float64),
    ],
)
def test_pos_quat_constructor(
    Pose: Pose3dCls, Vec3: Vec3Cls, Quat: QuatCls, Type: type
) -> None:
    position = Vec3(np.random.randn(1, 3).astype(Type))
    quat_orientation = Quat(np.random.randn(1, 4).astype(Type))
    pose = Pose(position, quat_orientation)
    # Position should be copied directly to the pose object
    assert np.allclose(cast(np.ndarray, pose.position), cast(np.ndarray, position))
    # Orientation is normalized to ensure it represents a rotation
    assert np.abs(pose.orientation.length() - 1.0) < 1e-5


@pytest.mark.parametrize(
    "Pose,Vec3,Mat3,Quat,Type",
    [
        (m3d.Pose3d_f, m3d.Vector3f, m3d.Matrix3f, m3d.Quaternionf, np.float32),
        (m3d.Pose3d_d, m3d.Vector3d, m3d.Matrix3d, m3d.Quaterniond, np.float64),
    ],
)
def test_pos_mat3_constructor(
    Pose: Pose3dCls, Vec3: Vec3Cls, Mat3: Mat3Cls, Quat: QuatCls, Type: type
) -> None:
    position = Vec3(np.random.randn(1, 3).astype(Type))
    # NOTE(wilbert): if using [-pi, pi], we might get neg. quaternions, which
    # in the end result in the same orientation, but won't check using allclose
    angle = np.pi * (np.random.random() - 0.5)

    rotmat = Mat3.RotationX(angle)
    pose = Pose(position, rotmat)
    assert np.allclose(cast(np.ndarray, pose.position), cast(np.ndarray, position))
    assert np.allclose(
        cast(np.ndarray, pose.orientation),
        cast(np.ndarray, Quat.RotationX(angle)),
        atol=1e-5,
    )
    assert np.abs(pose.orientation.length() - 1.0) < 1e-5

    rotmat = Mat3.RotationY(angle)
    pose = Pose(position, rotmat)
    assert np.allclose(cast(np.ndarray, pose.position), cast(np.ndarray, position))
    assert np.allclose(
        cast(np.ndarray, pose.orientation),
        cast(np.ndarray, Quat.RotationY(angle)),
        atol=1e-5,
    )
    assert np.abs(pose.orientation.length() - 1.0) < 1e-5

    rotmat = Mat3.RotationZ(angle)
    pose = Pose(position, rotmat)
    assert np.allclose(cast(np.ndarray, pose.position), cast(np.ndarray, position))
    assert np.allclose(
        cast(np.ndarray, pose.orientation),
        cast(np.ndarray, Quat.RotationZ(angle)),
        atol=1e-5,
    )
    assert np.abs(pose.orientation.length() - 1.0) < 1e-5
