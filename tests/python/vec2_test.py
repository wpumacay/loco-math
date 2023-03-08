import numpy as np
import math3d as m3d

def test_vec2_attrs():
    # Make sure we have exposed both x and y as properties
    assert (hasattr(m3d.Vector2f, 'x')) and (hasattr(m3d.Vector2f, 'y'))

class TestVec2Constructors:
    def test_default_constructor(self):
        # Default constructor initializes to (0.0, 0.0)
        vec = m3d.Vector2f()
        assert (vec.x == 0.0) and (vec.y == 0.0)

    def test_single_arg_constructor(self):
        # Single scalar argument x_val initializes to (x_val, x_val)
        vec = m3d.Vector2f(1.0)
        assert (vec.x == 1.0) and (vec.y == 1.0)

    def test_full_args_constructor(self):
        # Two scalar arguments x_val, y_val initializes to (x_val, y_val)
        vec = m3d.Vector2f(1.0, 2.0)
        assert (vec.x == 1.0) and (vec.y == 2.0)

    def test_numpy_array_constructor(self):
        # From a numpy array (requires same dtype)
        vec = m3d.Vector2f(np.array([11., 23.], dtype=np.float32))
        assert (vec.x == 11.0) and (vec.y == 23.0)

def test_vec2_accessors():
    # Can get both x, y as properties
    vec = m3d.Vector2f(3.0, 7.0)
    assert (vec.x == 3.0) and (vec.y == 7.0)
    # Can get elements using __getitem__ as well
    assert (vec[0] == 3.0) and (vec[1] == 7.0)

class TestVec2Operators:
    def test_comparison_operator(self):
        pass

    def test_vector_addition(self):
        pass

    def test_vector_substraction(self):
        pass

    def test_vector_elementwise_product(self):
        pass

    def test_vector_scalar_product(self):
        pass
