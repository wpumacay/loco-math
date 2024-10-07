#include <pybind11/pybind11.h>

#include <math/mat3_t.hpp>

namespace py = pybind11;

namespace math {

auto bindings_mat3_functions(py::module m) -> void {
    m.def("transpose",
          static_cast<Matrix3<float32_t> (*)(const Matrix3<float32_t>&)>(
              ::math::transpose<float32_t>));
    m.def("transpose",
          static_cast<Matrix3<float64_t> (*)(const Matrix3<float64_t>&)>(
              ::math::transpose<float64_t>));

    m.def("transpose_", static_cast<void (*)(Matrix3<float32_t>&)>(
                            ::math::transposeInPlace<float32_t>));
    m.def("transpose_", static_cast<void (*)(Matrix3<float64_t>&)>(
                            ::math::transposeInPlace<float64_t>));

    m.def("trace", static_cast<float32_t (*)(const Matrix3<float32_t>&)>(
                       ::math::trace<float32_t>));
    m.def("trace", static_cast<float64_t (*)(const Matrix3<float64_t>&)>(
                       ::math::trace<float64_t>));

    m.def("determinant", static_cast<float32_t (*)(const Matrix3<float32_t>&)>(
                             ::math::determinant<float32_t>));
    m.def("determinant", static_cast<float64_t (*)(const Matrix3<float64_t>&)>(
                             ::math::determinant<float64_t>));

    m.def("inverse",
          static_cast<Matrix3<float32_t> (*)(const Matrix3<float32_t>&)>(
              ::math::inverse<float32_t>));
    m.def("inverse",
          static_cast<Matrix3<float64_t> (*)(const Matrix3<float64_t>&)>(
              ::math::inverse<float64_t>));
}

}  // namespace math
