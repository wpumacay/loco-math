#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <initializer_list>

namespace tinymath
{

    typedef float tf32;
    typedef double tf64;
    typedef tf32 tfloat;

    template< typename Scalar_T >
    Scalar_T clamp( Scalar_T x, Scalar_T xMin, Scalar_T xMax );

}

#include "../src/common_impl.hpp"