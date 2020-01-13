# tiny_math

A basic math library for vectors and matrices (just for 2,3, and 4 dimensions)

## Yet another math library

This library is intended mainly for test purposes (integration with PyPi, ReadTheDocs, CI, python-bindings, etc.).
However, we currently use it as a replacement to other more complete libraries like [glm](https://glm.g-truc.net/0.9.9/index.html) 
and [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) in some projects that make heavy use of C/C++  and 
also require Python support through bindings.

## Setup

### C++

Clone this package into your `third_party` dependencies:

```bash
# Replace "third_party" with your own dependencies-folder name
git clone https://github.com/wpumacay/tiny_math.git third_party/tiny_math
```

The library is a template-based header-only library, so just include the headers in the `include` 
folder, e.g. in your own `CMakeLists.txt`:

```txt
include_directories( third_party/tiny_math/include )
```

Alternatively, you can use the CMake target `tinymath_cpp_lib` as a dependency in your own target:

```txt
add_library( my_own_awesome_library tinymath_cpp_lib )
```

### Python

Use the provided `setup.py` file:

```bash
python setup.py install
```

Or via PyPi:

```bash
pip install wp-tinymath
```

And import the `tinymath` package in your python files:

```python
import tinymath as tm
```

## Usage

### C++

```c++

#include <vector_t.h>
#include <matrix_t.h>

int main()
{
    // Create a vec3-float32 and show it on the console
    tinymath::Vector3f _vec = { 1.0f, 2.0f, 3.0f };
    std::cout << "vec: " << tinymath::toString( vec ) << std::endl;

    // Create a mat3 float32, show its entries and its inverse
    auto mat = tinymath::Matrix3f( { 3.0f, 9.0f, 3.0f,
                                     9.0f, 0.0f, 3.0f,
                                     2.0f, 3.0f, 8.0f } );

    std::cout << "mat:" << std::endl;
    std::cout << tinymath::toString( mat ) << std::endl;
    std::cout << "mat.inverse():" << std::endl;
    std::cout << tinymath::toString( mat.inverse() ) << std::endl;

    return 0;
}

```

### Python

```python
import tinymath as tm

# Create a vec3-float32 and show it on the console
vec = tm.Vector3f( [1.0, 2.0, 3.0] )
print( 'vec: {}'.format( vec ) )

# Create a mat3 float32, show its entries and its inverse
mat = tm.Matrix3f( [ [ 3.0, 9.0, 3.0 ],
                     [ 9.0, 0.0, 3.0 ],
                     [ 2.0, 3.0, 8.0 ] ] );

print( "mat:" )
print( mat )
print( "mat.inverse():" )
print( mat.inverse() )
```