
#include <common.h>

namespace tinymath
{

    template< typename Scalar_T >
    Scalar_T clamp( Scalar_T x, Scalar_T xMin, Scalar_T xMax )
    {
        return ( ( x < xMin ) ? xMin : ( ( x > xMax ) ? xMax : x ) );
    }

}