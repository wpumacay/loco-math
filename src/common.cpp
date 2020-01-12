
#include <common.h>

namespace tinymath
{

    tfloat clamp( tfloat x, tfloat xMin, tfloat xMax )
    {
        return ( ( x < xMin ) ? xMin : ( ( x > xMax ) ? xMax : x ) );
    }

    tfloat rad2degrees( tfloat rads )
    {
        return 180.0 * ( rads / TINYMATH_PI );
    }

    tfloat deg2radians( tfloat degs )
    {
        return TINYMATH_PI * ( degs / 180.0 );
    }

}