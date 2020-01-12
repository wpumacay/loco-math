
#include <bindings_common.h>

namespace tinymath
{

    void bindings_common( py::module& m )
    {
        m.def( "clamp", &tinymath::clamp );
        m.def( "rad2degrees", &tinymath::rad2degrees );
        m.def( "deg2radians", &tinymath::deg2radians );
        m.attr( "pi" ) = TINYMATH_PI;
    }

}