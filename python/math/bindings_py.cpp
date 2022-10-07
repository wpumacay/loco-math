#include <string>

#include <pybind11/pybind11.h>

#include <vec2_py.hpp>
#include <vec3_py.hpp>
#include <vec4_py.hpp>
#include <mat2_py.hpp>
#include <mat3_py.hpp>
#include <mat4_py.hpp>

namespace py = pybind11;

// NOLINTNEXTLINE
PYBIND11_MODULE(_math, m) {
    loco::math::bindings_vector2<loco::math::float32_t>(m, "Vector2f");
    loco::math::bindings_vector2<loco::math::float64_t>(m, "Vector2d");
    loco::math::bindings_vector3<loco::math::float32_t>(m, "Vector3f");
    loco::math::bindings_vector3<loco::math::float64_t>(m, "Vector3d");
    loco::math::bindings_vector4<loco::math::float32_t>(m, "Vector4f");
    loco::math::bindings_vector4<loco::math::float64_t>(m, "Vector4d");
    loco::math::bindings_matrix2<loco::math::float32_t>(m, "Matrix2f");
    loco::math::bindings_matrix2<loco::math::float64_t>(m, "Matrix2d");
    loco::math::bindings_matrix3<loco::math::float32_t>(m, "Matrix3f");
    loco::math::bindings_matrix3<loco::math::float64_t>(m, "Matrix3d");
    loco::math::bindings_matrix4<loco::math::float32_t>(m, "Matrix4f");
    loco::math::bindings_matrix4<loco::math::float64_t>(m, "Matrix4d");
}
