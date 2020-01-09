# tiny_math

A basic math library for vectors and matrices (just for 2,3, and 4 dimensions)

## Installation

### C++

Use the provided `CMakeLists.txt` file:

```
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4 && make install
```

### Python

Use the provided `setup.py` file:

```bash
python setup.py install
```

## Usage

### C++

```c++

#include <vector_t.h>

int main()
{
    // Create a vec3-float32 and show it on the console
    auto vec = tinymath::Vector3f( { 1.0f, 2.0f, 3.0f } );
    std::cout << "vec: " << tinymath::toString( vec ) << std::endl;

    return 0;
}

```

### Python

```python
import tinymath as tm

# Create a vec3-float32 and show it on the console
vec = tm.Vector3f( [1.0, 2.0, 3.0] )
print( 'vec: {}'.format( vec ) )
```