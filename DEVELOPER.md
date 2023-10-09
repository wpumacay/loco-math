# Some gotchas and things to keep in mind while developing

## Installing from TestPyPI and PyPI

Currently, we're testing from-source installation using TestPyPI [here][0].
Unfortunately, there are some issues while installing from source, related to
build dependencies not being found for some versions (specially setuptools).
This happens if we use the following command:

```shell
# This command fails with an error on the build dependencies
pip install -i https://test.pypi.org/simple/ math3d
```

To fix this issue when installing from source, use the `--no-build-isolation`
option instead:

```shell
pip install --no-build-isolation -i https://test.pypi.org/simple/ math3d
```

## Building manylinux wheels using docker

There's a helper script at `bin/build_manylinux_wheels`, which we can use to
build manylinux wheels for our library. Just make sure that a source `tar.gz`
has been uploaded for the desired version. The script will use this as base
for building the wheels.

```shell
python bin/build_manylinux_wheels.py --version 0.6.0
```

The generated wheels will be located at the `dist` directory. Just use twine
to upload them to the registry (for now, TestPyPI).

[0]: <https://test.pypi.org/project/math3d/>
