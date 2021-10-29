
#include <bindings_common.h>

namespace tinymath {

void bindings_common(py::module& m) { m.attr("pi") = TINYMATH_PI; }

}  // namespace tinymath
