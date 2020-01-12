#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <initializer_list>

#define TINYMATH_PI 3.141592653589793f

namespace tinymath
{

    typedef float tf32;
    typedef double tf64;
    typedef tf32 tfloat;

    tfloat clamp( tfloat x, tfloat xMin, tfloat xMax );
    tfloat rad2degrees( tfloat rads );
    tfloat deg2radians( tfloat degs );

}
