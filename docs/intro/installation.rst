############
Installation
############

.. toctree::
   :caption: Contents
   :maxdepth: 1

C++
###

Math3d is a header-only library. You can just include the files you need
directly. However, if you have a CMake workflow already setup, you can use
the ``math::math`` target, like this:

Get the source code (e.g. git clone the repo).

.. code-block:: bash

    # Clone the repo (e.g. send it to dependencies folder)
    git clone git@github.com:wpumacay/math3d deps/math3d

Add the project to your ``CMake`` workflow.

.. code-block:: cmake

    # Add the math3d project
    add_subdirectory(deps/math3d)

    # Link to math::math target
    target_link_libraries(my_target INTEFACE math::math)

Below is a minimal example that takes the cross product of two 3d vectors:

.. code-block:: c++

    #include <iostream>
    #include <math/vec3_t.hpp>

    using Vec3 = ::math::Vector3<float>;

    auto main() -> int {

        Vec3 vec_a = {1.0F, 1.0F, 1.0F};
        Vec3 vec_b = {1.0F, 2.0F, 3.0F};

        std::cout << "vec-a: " << vec_a << std::endl;
        std::cout << "vec-b: " << vec_b << std::endl;

        // Compute the cross product using a helper function
        auto vec_c = ::math::cross(vec_a, vec_b);

        std::cout << "cross(a, b): " << vec_c << std::endl;

        // Or, compute it using the Vector3::cross method
        auto vec_d = vec_a.cross(vec_b);

        std::cout << "a.cross(b): " << vec_d << std::endl;

        return 0;
    }


Python
######

Math3d is ``pip`` installable from source (not available in PyPI yet), so you
can grab the source and use pip to install as follows:

.. code-block:: bash

    # Get the source code (e.g. git clone the repo)
    git clone git@github.com:wpumacay/math3d && cd math3d

    # Create a virtual environment (or use your own env.)
    virtualenv venv && . venv/bin/activate

    # Install it using pip
    pip install -v .

Below is a minimal example similar to the one shown above:

.. code-block:: python

    import math3d as m3d

    if __name__ == "__main__":
        vec_a = m3d.Vector3f(1.0, 1.0, 1.0)
        vec_b = m3d.Vector3f(1.0, 2.0, 3.0)

        print(f"vec-a: {vec_a}")
        print(f"vec-b: {vec_b}")

        vec_c = vec_a.cross(vec_b)

        print(f"a.cross(b): {vec_c}")
