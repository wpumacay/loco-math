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
