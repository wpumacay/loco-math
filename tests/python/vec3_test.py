import pytest

import numpy as np
import math3d as m3d


@pytest.mark.parametrize("VectorCls", [(m3d.Vector3f), (m3d.Vector3d)])
def test_vec3_attrs(VectorCls):
    # Make sure we have exposed x, y, and z as properties
    assert (
        (hasattr(VectorCls, "x"))
        and (hasattr(VectorCls, "y"))
        and (hasattr(VectorCls, "z"))
    )


@pytest.mark.parametrize("VectorCls", [(m3d.Vector3f), (m3d.Vector3d)])
class TestVec3Constructors:
    def test_default_constructor(self, VectorCls):
        # Default constructor initializes to (0.0, 0.0, 0.0)
        vec = VectorCls()
        assert (vec.x == 0.0) and (vec.y == 0.0) and (vec.z == 0.0)

    def test_single_arg_constructor(self, VectorCls):
        # Single scalar argument x initializes to (x, x, x)
        vec = VectorCls(1.0)
        assert (vec.x == 1.0) and (vec.y == 1.0) and (vec.z == 1.0)

    def test_double_args_constructor(self, VectorCls):
        # Two scalar arguments x, y initializes to (x, y, y)
        vec = VectorCls(1.0, 2.0)
        assert (vec.x == 1.0) and (vec.y == 2.0) and (vec.z == 2.0)

    def test_full_args_constructor(self, VectorCls):
        # Three scalar arguments x, y, z, initializes to (v, y, z)
        vec = VectorCls(1.0, 2.0, 3.0)
        assert (vec.x == 1.0) and (vec.y == 2.0) and (vec.z == 3.0)


@pytest.mark.parametrize(
    "VectorCls,FloatType", [(m3d.Vector3f, np.float32), (m3d.Vector3d, np.float64)]
)
def test_numpy_array_constructor(VectorCls, FloatType):
    # From a numpy array (requires same dtype)
    vec_np = np.array([19.0, 23.0, 29.0])
    vec = VectorCls(vec_np.astype(FloatType))
    assert (vec.x == 19.0) and (vec.y == 23.0) and (vec.z == 29.0)

    vec = VectorCls(vec_np.reshape(1, 3).astype(FloatType))
    assert (vec.x == 19.0) and (vec.y == 23.0) and (vec.z == 29.0)

    vec = VectorCls(vec_np.reshape(3, 1).astype(FloatType))
    assert (vec.x == 19.0) and (vec.y == 23.0) and (vec.z == 29.0)


@pytest.mark.parametrize("VectorCls", [(m3d.Vector3f), (m3d.Vector3d)])
def test_vec3_accessors(VectorCls):
    # Can get both x, y as properties
    vec = VectorCls(3.0, 7.0, 11.0)
    assert (vec.x == 3.0) and (vec.y == 7.0) and (vec.z == 11.0)
    # Can get elements using __getitem__ as well
    assert (vec[0] == 3.0) and (vec[1] == 7.0) and (vec[2] == 11.0)
    # Can also update the entries using either of the two accessors
    vec.x, vec.y, vec.z = 1.0, 2.0, 3.0
    assert (vec.x == 1.0) and (vec.y == 2.0) and (vec.z == 3.0)


@pytest.mark.parametrize("VectorCls", [(m3d.Vector3f), (m3d.Vector3d)])
class TestVec3Operators:
    def test_comparison_operator(self, VectorCls):
        vec_a = VectorCls(1.0, 2.0, 3.0)
        vec_b = VectorCls(1.0, 2.0, 3.0)
        # Comparison __eq__ internally calls == operator, which uses an epsilon
        assert vec_a == vec_b

        vec_b.x, vec_b.y, vec_b.z = 1.1, 2.1, 3.1
        # Comparison __neq__ internally calls != operator, which uses an epsilon
        assert vec_a != vec_b

    def test_vector_addition(self, VectorCls):
        vec_a = VectorCls(3.0, 7.0, 11.0)
        vec_b = VectorCls(4.0, 5.0, 6.0)
        vec_sum = vec_a + vec_b
        assert (vec_sum.x == 7.0) and (vec_sum.y == 12.0) and (vec_sum.z == 17.0)

    def test_vector_substraction(self, VectorCls):
        vec_a = VectorCls(3.0, 7.0, 11.0)
        vec_b = VectorCls(4.0, 5.0, 6.0)
        vec_diff = vec_a - vec_b
        assert (vec_diff.x == -1.0) and (vec_diff.y == 2.0) and (vec_diff.z == 5.0)

    def test_vector_elementwise_product(self, VectorCls):
        vec_a = VectorCls(3.0, 7.0, 11.0)
        vec_b = VectorCls(4.0, 5.0, 6.0)
        vec_elm_mul = vec_a * vec_b
        assert (
            (vec_elm_mul.x == 12.0)
            and (vec_elm_mul.y == 35.0)
            and (vec_elm_mul.z == 66.0)
        )

    def test_vector_scalar_product(self, VectorCls):
        vec = VectorCls(4.0, 8.0, 12.0)
        scale = 3.5
        vec_scaled = vec * scale
        assert (
            (vec_scaled.x == 14.0) and (vec_scaled.y == 28.0) and (vec_scaled.z == 42.0)
        )
        vec_scaled = scale * vec
        assert (
            (vec_scaled.x == 14.0) and (vec_scaled.y == 28.0) and (vec_scaled.z == 42.0)
        )
