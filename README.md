# TinyMath

A small header-only math library for vectors and matrices

## Build Status

| Build   | Status
| ------- | ------------------------------
| Ubuntu  | [![ci-linux][0]][1]       |
| Windows | [![ci-windows][2]][3]     |
| MacOS   | [![ci-macos][4]][5]       |

## Yet another math library

This library is designed to be a potential replacement to various other great
libraries like `Eigen` and `glm`, but with a narrow focus on 2, 3, and 4
dimensional vectors and matrices.

## Setup

### C++ setup

Clone this package into your `third_party` dependencies:

```bash
# Replace "third_party" with your own dependencies-folder name
git clone https://github.com/wpumacay/tiny_math.git third_party/tiny_math
```

There's a `CMake` target called `loco::math`. Just add the source directory in
your `CMake` workflow, and use the given target as follows:

```CMake
# Add TinyMath as a third-party dependency
add(PATH_TO_TINY_MATH)
# ...
# Link against the exposed loco::math target
target_link_library(MY_LIBRARY PRIVATE loco::math)
```

### Python setup

Use the provided `setup.py` file:

```bash
python setup.py install
```

And import the types from the `lmath` package:

```python
from lmath import Vector3f
```

## Usage

### C++

```c++

#include <vec3_t.h>
#include <mat3_t.h>

int main()
{
    // Create a vec3-float32 and show it on the console
    loco::math::Vector3f vec = { 1.0f, 2.0f, 3.0f };
    std::cout << "vec: " << vec << std::endl;

    // Create a mat3 float32, show its entries and its inverse
    auto mat = loco::math::Matrix3f( 3.0f, 9.0f, 3.0f,
                                     9.0f, 0.0f, 3.0f,
                                     2.0f, 3.0f, 8.0f );

    std::cout << "mat:" << std::endl;
    std::cout << mat << std::endl;
    std::cout << "mat.inverse():" << std::endl;
    std::cout << loco::math::inverse( mat ) << std::endl;

    return 0;
}
```

### Python

```python
import numpy as np
from lmath import Vector3f, Matrix3f

# Create a vec3-float32 and show it on the console
vec = Vector3f(np.array([1.0, 2.0, 3.0], dtype=np.float32))
print(vec)

# Create a mat3 float32, show its entries and its inverse
mat = Matrix3f(np.array([[ 3.0, 9.0, 3.0 ],
                         [ 9.0, 0.0, 3.0 ],
                         [ 2.0, 3.0, 8.0 ]], dtype=np.float32))

print(mat)
print("inverse(): \n\r{}".format(mat.inverse()))
```

---

[0]: <https://github.com/wpumacay/loco_math/actions/workflows/ci-linux.yml/badge.svg> (ci-linux-badge)
[1]: <https://github.com/wpumacay/loco_math/actions/workflows/ci-linux.yml> (ci-linux-status)
[2]: <https://github.com/wpumacay/loco_math/actions/workflows/ci-windows.yml/badge.svg> (ci-windows-badge)
[3]: <https://github.com/wpumacay/loco_math/actions/workflows/ci-windows.yml> (ci-windows-status)
[4]: <https://github.com/wpumacay/loco_math/actions/workflows/ci-macos.yml/badge.svg> (ci-macos-badge)
[5]: <https://github.com/wpumacay/loco_math/actions/workflows/ci-macos.yml> (ci-macos-status)
