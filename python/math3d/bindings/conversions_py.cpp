#include <conversions_py.hpp>

namespace math {

auto bindings_conversions_functions(py::module m) -> void {
    m.def("vec2_to_nparray_f32", ::math::vec2_to_nparray<::math::float32_t>);
    m.def("vec2_to_nparray_f64", ::math::vec2_to_nparray<::math::float64_t>);
    m.def("vec3_to_nparray_f32", ::math::vec3_to_nparray<::math::float32_t>);
    m.def("vec3_to_nparray_f64", ::math::vec3_to_nparray<::math::float64_t>);
    m.def("vec4_to_nparray_f32", ::math::vec4_to_nparray<::math::float32_t>);
    m.def("vec4_to_nparray_f64", ::math::vec4_to_nparray<::math::float64_t>);

    m.def("nparray_to_vec2_f32", ::math::nparray_to_vec2<::math::float32_t>);
    m.def("nparray_to_vec2_f64", ::math::nparray_to_vec2<::math::float64_t>);
    m.def("nparray_to_vec3_f32", ::math::nparray_to_vec3<::math::float32_t>);
    m.def("nparray_to_vec3_f64", ::math::nparray_to_vec3<::math::float64_t>);
    m.def("nparray_to_vec4_f32", ::math::nparray_to_vec4<::math::float32_t>);
    m.def("nparray_to_vec4_f64", ::math::nparray_to_vec4<::math::float64_t>);
}

}  // namespace math
