#include <string>

#include <pybind11/pybind11.h>

#include <loco/math/vec2_t_impl.hpp>
#include <loco/math/vec3_t_impl.hpp>
#include <loco/math/vec4_t_impl.hpp>
#include <loco/math/mat4_t_impl.hpp>

namespace py = pybind11;

// @todo(wilbert): might need to avoid using extern, and instead add all the
// binding-generation functions as parametrized templated functions

namespace loco {
namespace math {

// NOLINTNEXTLINE
extern void bindings_vector3(py::module& m, const std::string& className);
// NOLINTNEXTLINE
extern void bindings_vector4(py::module& m, const std::string& className);

}  // namespace math
}  // namespace loco

// NOLINTNEXTLINE
PYBIND11_MODULE(_math, m) {
    // loco::math::bindings_vector3<float32_t>(m, "Vector3f");
    // loco::math::bindings_vector3<float64_t>(m, "Vector3d");
    // loco::math::bindings_vector4<float32_t>(m, "Vector4f");
    // loco::math::bindings_vector4<float64_t>(m, "Vector4d");
}
