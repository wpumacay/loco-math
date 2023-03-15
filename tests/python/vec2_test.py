import pytest

import numpy as np
import math3d as m3d

from typing import Type, Union

Vector2Cls = Type[Union[m3d.Vector2f, m3d.Vector2d]]


@pytest.mark.parametrize("Class", [(m3d.Vector2f), (m3d.Vector2d)])
def test_vec2_attrs(Class: Vector2Cls):
    # Make sure we have exposed both x and y as properties
    assert (hasattr(Class, "x")) and (hasattr(Class, "y"))


@pytest.mark.parametrize("Class", [(m3d.Vector2f), (m3d.Vector2d)])
class TestVec2Constructors:
    def test_default_constructor(self, Class: Vector2Cls):
        # Default constructor initializes to (0.0, 0.0)
        vec = Class()
        assert (vec.x == 0.0) and (vec.y == 0.0)

    def test_single_arg_constructor(self, Class: Vector2Cls):
        # Single scalar argument x_val initializes to (x_val, x_val)
        vec = Class(1.0)
        assert (vec.x == 1.0) and (vec.y == 1.0)

    def test_full_args_constructor(self, Class: Vector2Cls):
        # Two scalar arguments x_val, y_val initializes to (x_val, y_val)
        vec = Class(1.0, 2.0)
        assert (vec.x == 1.0) and (vec.y == 2.0)


@pytest.mark.parametrize(
    "Class,FloatType", [(m3d.Vector2f, np.float32), (m3d.Vector2d, np.float64)]
)
def test_numpy_array_constructor_f32(Class: Vector2Cls, FloatType):
    # From a numpy array (requires same dtype)
    vec_np = np.array([19.0, 23.0])
    vec = Class(vec_np.astype(FloatType))
    assert (vec.x == 19.0) and (vec.y == 23.0)

    vec = Class(vec_np.reshape(1, 2).astype(FloatType))
    assert (vec.x == 19.0) and (vec.y == 23.0)

    vec = Class(vec_np.reshape(2, 1).astype(FloatType))
    assert (vec.x == 19.0) and (vec.y == 23.0)


@pytest.mark.parametrize("Class", [(m3d.Vector2f), (m3d.Vector2d)])
def test_vec2_accessors(Class: Vector2Cls):
    # Can get both x, y as properties
    vec = Class(3.0, 7.0)
    assert (vec.x == 3.0) and (vec.y == 7.0)
    # Can get elements using __getitem__ as well
    assert (vec[0] == 3.0) and (vec[1] == 7.0)
    # Can also update the entries using either of the two accessors
    vec.x, vec.y = 1.0, 2.0
    assert (vec.x == 1.0) and (vec.y == 2.0)


@pytest.mark.parametrize("Class", [(m3d.Vector2f), (m3d.Vector2d)])
class TestVec2Operators:
    def test_comparison_operator(self, Class: Vector2Cls):
        vec_a = Class(1.0, 2.0)
        vec_b = Class(1.0, 2.0)
        # Comparison __eq__ internally calls == operator, which uses an epsilon
        assert vec_a == vec_b

        vec_b.x, vec_b.y = 1.1, 2.1
        # Comparison __neq__ internally calls != operator, which uses an epsilon
        assert vec_a != vec_b

    def test_vector_addition(self, Class: Vector2Cls):
        vec_a = Class(3.0, 7.0)
        vec_b = Class(4.0, 5.0)
        vec_sum = vec_a + vec_b
        assert (vec_sum.x == 7.0) and (vec_sum.y == 12.0)

    def test_vector_substraction(self, Class: Vector2Cls):
        vec_a = Class(3.0, 7.0)
        vec_b = Class(4.0, 5.0)
        vec_diff = vec_a - vec_b
        assert (vec_diff.x == -1.0) and (vec_diff.y == 2.0)

    def test_vector_scalar_product(self, Class):
        vec = Class(4.0, 8.0)
        scale = 3.5
        vec_scaled = vec * scale
        assert (vec_scaled.x == 14.0) and (vec_scaled.y == 28.0)
        vec_scaled = scale * vec
        assert (vec_scaled.x == 14.0) and (vec_scaled.y == 28.0)


@pytest.mark.parametrize(
    "Class,FloatType", [(m3d.Vector2f, np.float32), (m3d.Vector2d, np.float64)]
)
class TestVec2Methods:
    def test_length(self, Class: Vector2Cls, FloatType) -> None:
        vec = Class(3.0, 4.0)
        assert (vec.norm() == 5.0) and (vec.squareNorm() == 25.0)

    def test_normalize_in_place(self, Class: Vector2Cls, FloatType) -> None:
        vec = Class(3.0, 4.0)
        vec.normalize_()
        assert np.abs(vec.x - 0.6) < 1e-5 and np.abs(vec.y - 0.8) < 1e-5

    def test_normalize(self, Class: Vector2Cls, FloatType) -> None:
        vec = Class(3.0, 4.0)
        vec_n = vec.normalize()
        assert np.abs(vec_n.x - 0.6) < 1e-5 and np.abs(vec_n.y - 0.8) < 1e-5

    def test_dot_product(self, Class: Vector2Cls, FloatType) -> None:
        vec_a = Class(3.0, 5.0)
        vec_b = Class(7.0, 11.0)
        assert vec_a.dot(vec_b) == 76.0
