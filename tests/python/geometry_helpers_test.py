from typing import Type, Union, cast

import numpy as np
import pytest
from numpy.typing import NDArray

import math3d as m3d

LineCls = Type[Union[m3d.Line_f, m3d.Line_d]]
Vector3Cls = Type[Union[m3d.Vector3f, m3d.Vector3d]]

Vector3 = Union[m3d.Vector3f, m3d.Vector3d]

# Make sure our generators are seeded with the answer to the universe :D
np.random.seed(42)
# The delta used for tolerance (due to floating point precision mismatches)
EPSILON = 1e-5


def vec3_all_close(
    vec: Vector3, vec_np: NDArray, epsilon: float = EPSILON
) -> bool:
    return np.allclose(cast(NDArray, vec), vec_np, atol=epsilon)


@pytest.mark.parametrize("Line", [(m3d.Line_f), (m3d.Line_d)])
def test_line_attrs(Line: LineCls) -> None:
    assert hasattr(Line, "start") and hasattr(Line, "end")


@pytest.mark.parametrize(
    "Line, FloatType", [(m3d.Line_f, np.float32), (m3d.Line_d, np.float64)]
)
def test_line_ctor_default(Line: LineCls, FloatType: type) -> None:
    line = Line()

    assert vec3_all_close(line.start, np.zeros((3,)).astype(FloatType))
    assert vec3_all_close(line.end, np.zeros((3,)).astype(FloatType))


@pytest.mark.parametrize(
    "Line, Vec3, FloatType",
    [
        (m3d.Line_f, m3d.Vector3f, np.float32),
        (m3d.Line_d, m3d.Vector3f, np.float64),
    ],
)
def test_line_ctor_vec_args(
    Line: LineCls, Vec3: Vector3Cls, FloatType: type
) -> None:
    v_start = Vec3(1.0, 1.0, 1.0)
    v_end = Vec3(2.0, 3.0, 4.0)
    line = Line(v_start, v_end)

    assert vec3_all_close(
        line.start, np.array([1.0, 1.0, 1.0], dtype=FloatType)
    )
    assert vec3_all_close(line.end, np.array([2.0, 3.0, 4.0], dtype=FloatType))


@pytest.mark.parametrize(
    "Line, FloatType", [(m3d.Line_f, np.float32), (m3d.Line_d, np.float64)]
)
def test_line_ctor_npvec_args(Line: LineCls, FloatType: type) -> None:
    np_start = np.array([1.0, 1.0, 1.0], dtype=FloatType)
    np_end = np.array([2.0, 3.0, 4.0], dtype=FloatType)
    line = Line(np_start, np_end)

    assert vec3_all_close(
        line.start, np.array([1.0, 1.0, 1.0], dtype=FloatType)
    )
    assert vec3_all_close(line.end, np.array([2.0, 3.0, 4.0], dtype=FloatType))


@pytest.mark.parametrize(
    "Line, Vec3", [(m3d.Line_f, m3d.Vector3f), (m3d.Line_d, m3d.Vector3f)]
)
def test_line_distanceTo_method(Line: LineCls, Vec3: Vector3Cls) -> None:
    # Line = x-axis, points = {(1, 0, 0), (0, 1, 0), (0, 0, 1)}
    line = Line([0.0, 0.0, 0.0], [1.0, 0.0, 0.0])
    p_a = Vec3(1.0, 0.0, 0.0)
    p_b = Vec3(0.0, 1.0, 0.0)
    p_c = Vec3(0.0, 0.0, 1.0)

    assert np.abs(line.distanceTo(p_a) - 0.0) < EPSILON
    assert np.abs(line.distanceTo(p_b) - 1.0) < EPSILON
    assert np.abs(line.distanceTo(p_c) - 1.0) < EPSILON


@pytest.mark.parametrize(
    "Line, FloatType", [(m3d.Line_f, np.float32), (m3d.Line_d, np.float64)]
)
def test_line_distanceTo_method_npargs(Line: LineCls, FloatType: type) -> None:
    # Line = x-axis, points = {(1, 0, 0), (0, 1, 0), (0, 0, 1)}
    line = Line([0.0, 0.0, 0.0], [1.0, 0.0, 0.0])
    p_a = np.array([1.0, 0.0, 0.0], dtype=FloatType)
    p_b = np.array([0.0, 1.0, 0.0], dtype=FloatType)
    p_c = np.array([0.0, 0.0, 1.0], dtype=FloatType)

    assert np.abs(line.distanceTo(p_a) - 0.0) < EPSILON
    assert np.abs(line.distanceTo(p_b) - 1.0) < EPSILON
    assert np.abs(line.distanceTo(p_c) - 1.0) < EPSILON
