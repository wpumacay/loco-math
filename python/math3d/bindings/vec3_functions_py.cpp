#include <pybind11/pybind11.h>

#include <math/vec3_t.hpp>

#include <conversions_py.hpp>

namespace py = pybind11;

namespace math {

auto bindings_vec3_functions(py::module m) -> void {
    m.def("dot", static_cast<float32_t (*)(const Vector3<float32_t>&,
                                           const Vector3<float32_t>&)>(
                     ::math::dot<float32_t>));
    m.def("dot", static_cast<float64_t (*)(const Vector3<float64_t>&,
                                           const Vector3<float64_t>&)>(
                     ::math::dot<float64_t>));

    m.def("cross", static_cast<Vector3<float32_t> (*)(
                       const Vector3<float32_t>&, const Vector3<float32_t>&)>(
                       ::math::cross<float32_t>));

    m.def("cross", static_cast<Vector3<float64_t> (*)(
                       const Vector3<float64_t>&, const Vector3<float64_t>&)>(
                       ::math::cross<float64_t>));

    m.def("squareNorm", static_cast<float32_t (*)(const Vector3<float32_t>&)>(
                            ::math::squareNorm<float32_t>));
    m.def("squareNorm", static_cast<float64_t (*)(const Vector3<float64_t>&)>(
                            ::math::squareNorm<float64_t>));

    m.def("norm", static_cast<float32_t (*)(const Vector3<float32_t>&)>(
                      ::math::norm<float32_t>));
    m.def("norm", static_cast<float64_t (*)(const Vector3<float64_t>&)>(
                      ::math::norm<float64_t>));

    m.def("normalize",
          static_cast<Vector3<float32_t> (*)(const Vector3<float32_t>&)>(
              ::math::normalize<float32_t>));
    m.def("normalize",
          static_cast<Vector3<float64_t> (*)(const Vector3<float64_t>&)>(
              ::math::normalize<float64_t>));

    m.def("normalize_", static_cast<void (*)(Vector3<float32_t>&)>(
                            ::math::normalize_in_place<float32_t>));
    m.def("normalize_", static_cast<void (*)(Vector3<float64_t>&)>(
                            ::math::normalize_in_place<float64_t>));

    m.def("lerp",
          static_cast<Vector3<float32_t> (*)(
              const Vector3<float32_t>&, const Vector3<float32_t>&, float32_t)>(
              ::math::lerp<float32_t>));
    m.def("lerp",
          static_cast<Vector3<float64_t> (*)(
              const Vector3<float64_t>&, const Vector3<float64_t>&, float64_t)>(
              ::math::lerp<float64_t>));
}

}  // namespace math
