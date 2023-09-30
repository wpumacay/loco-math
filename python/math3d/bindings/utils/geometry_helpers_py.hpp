#pragma once

#include <memory>
#include <utility>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <math/utils/geometry_helpers.hpp>

#include "../conversions_py.hpp"

namespace py = pybind11;

namespace math {

template <typename T>
using SFINAE_LINE_BINDINGS = typename std::enable_if<IsScalar<T>::value>::type*;

template <typename T, SFINAE_LINE_BINDINGS<T> = nullptr>
// NOLINTNEXTLINE
auto bindings_utils_line(py::module& m, const char* class_name) -> void {
    using Line = ::math::Line<T>;
    using Vec3 = ::math::Vector3<T>;
    py::class_<Line>(m, class_name)
        .def(py::init<>())
        .def(py::init<Vec3, Vec3>())
        .def(py::init([](const py::array_t<T>& np_start,
                         const py::array_t<T>& np_end) -> Line {
            return Line(nparray_to_vec3<T>(np_start),
                        nparray_to_vec3<T>(np_end));
        }))
        .def_readwrite("start", &Line::start)
        .def_readwrite("end", &Line::end)
        .def("distanceTo",
             [](const Line& self, const Vec3& point) -> T {
                 return self.distanceTo(point);
             })
        .def("distanceTo",
             [](const Line& self, const py::array_t<T>& np_point) -> T {
                 return self.distanceTo(nparray_to_vec3<T>(np_point));
             })
        .def("__repr__", [](const Line& self) -> py::str {
            return py::str(self.toString());
        });
}

}  // namespace math
