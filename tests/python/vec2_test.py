import pytest

import numpy as np
import math3d as m3d


@pytest.mark.parametrize("VectorCls", [(m3d.Vector2f), (m3d.Vector2d)])
def test_vec2_attrs(VectorCls):
    # Make sure we have exposed both x and y as properties
    assert (hasattr(VectorCls, "x")) and (hasattr(VectorCls, "y"))


@pytest.mark.parametrize("VectorCls", [(m3d.Vector2f), (m3d.Vector2d)])
class TestVec2Constructors:
    def test_default_constructor(self, VectorCls):
        # Default constructor initializes to (0.0, 0.0)
        vec = VectorCls()
        assert (vec.x == 0.0) and (vec.y == 0.0)

    def test_single_arg_constructor(self, VectorCls):
        # Single scalar argument x_val initializes to (x_val, x_val)
        vec = VectorCls(1.0)
        assert (vec.x == 1.0) and (vec.y == 1.0)

    def test_full_args_constructor(self, VectorCls):
        # Two scalar arguments x_val, y_val initializes to (x_val, y_val)
        vec = VectorCls(1.0, 2.0)
        assert (vec.x == 1.0) and (vec.y == 2.0)


def test_numpy_array_constructor_f32():
    # From a numpy array (requires same dtype)
    vec = m3d.Vector2f(np.array([11.0, 23.0], dtype=np.float32))
    assert (vec.x == 11.0) and (vec.y == 23.0)


def test_numpy_array_constructor_f64():
    # From a numpy array (requires same dtype)
    vec = m3d.Vector2d(np.array([11.0, 23.0], dtype=np.float64))
    assert (vec.x == 11.0) and (vec.y == 23.0)


@pytest.mark.parametrize("VectorCls", [(m3d.Vector2f), (m3d.Vector2d)])
def test_vec2_accessors(VectorCls):
    # Can get both x, y as properties
    vec = VectorCls(3.0, 7.0)
    assert (vec.x == 3.0) and (vec.y == 7.0)
    # Can get elements using __getitem__ as well
    assert (vec[0] == 3.0) and (vec[1] == 7.0)
    # Can also update the entries using either of the two accessors
    vec.x, vec.y = 1.0, 2.0
    assert (vec.x == 1.0) and (vec.y == 2.0)


@pytest.mark.parametrize("VectorCls", [(m3d.Vector2f), (m3d.Vector2d)])
class TestVec2Operators:
    def test_comparison_operator(self, VectorCls):
        vec_a = VectorCls(1.0, 2.0)
        vec_b = VectorCls(1.0, 2.0)
        # Comparison __eq__ internally calls == operator, which uses an epsilon
        assert vec_a == vec_b

        vec_b.x, vec_b.y = 1.1, 2.1
        # Comparison __neq__ internally calls != operator, which uses an epsilon
        assert vec_a != vec_b

    def test_vector_addition(self, VectorCls):
        vec_a = VectorCls(3.0, 7.0)
        vec_b = VectorCls(4.0, 5.0)
        vec_sum = vec_a + vec_b
        assert (vec_sum.x == 7.0) and (vec_sum.y == 12.0)

    def test_vector_substraction(self, VectorCls):
        vec_a = VectorCls(3.0, 7.0)
        vec_b = VectorCls(4.0, 5.0)
        vec_diff = vec_a - vec_b
        assert (vec_diff.x == -1.0) and (vec_diff.y == 2.0)

    def test_vector_elementwise_product(self, VectorCls):
        vec_a = VectorCls(3.0, 7.0)
        vec_b = VectorCls(4.0, 5.0)
        vec_elm_mul = vec_a * vec_b
        assert (vec_elm_mul.x == 12.0) and (vec_elm_mul.y == 35.0)

    def test_vector_scalar_product(self, VectorCls):
        vec = VectorCls(4.0, 8.0)
        scale = 3.5
        vec_scaled = vec * scale
        assert (vec_scaled.x == 14.0) and (vec_scaled.y == 28.0)
        vec_scaled = scale * vec
        assert (vec_scaled.x == 14.0) and (vec_scaled.y == 28.0)
