#include <pybind11/pybind11.h>

#include <loco/math/all.hpp>
#include <string>

namespace py = pybind11;

// @todo(wilbert): might need to avoid using extern, and instead add all the
// binding-generation functions as parametrized templated functions

namespace loco {
namespace math {

// @todo(wilbert): check if should actually pass by reference, or should pass
// by const-reference instead

// Disable linting for the following extern declarations, as we're using the
// pattern of pass by reference used by some pybind11 examples

// NOLINTNEXTLINE(runtime/references)
extern void bindings_vector3(py::module& m, const std::string& className);
// NOLINTNEXTLINE(runtime/references)
extern void bindings_vector4(py::module& m, const std::string& className);

}  // namespace math
}  // namespace loco

// NOLINTNEXTLINE @todo(wilbert): check how other projects handle this part
// PYBIND11_MODULE(math, m) {
//     // loco::math::bindings_vector3<float32_t>(m, "Vector3f");
//     // loco::math::bindings_vector3<float64_t>(m, "Vector3d");
//
//     // loco::math::bindings_vector4<float32_t>(m, "Vector4f");
//     // loco::math::bindings_vector4<float64_t>(m, "Vector4d");
// }
