#!/usr/bin/env python

import argparse
import os
import shutil
import subprocess

DOCKERFILE_FMT = """\
FROM {base}
"""

PROG = """\
{py_bin}/pip wheel --index https://test.pypi.org/simple --no-build-isolation \
    --wheel-dir /work math3d=={version} && \
auditwheel repair --wheel-dir /dist /work/*.whl
"""


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--version",
        help="The version to be built",
        type=str,
        default="0.6.0",
    )
    args = parser.parse_args()

    img = "math3d-build"
    base = "quay.io/pypa/manylinux2010_x86_64"
    dockerfile = DOCKERFILE_FMT.format(base=base).encode()

    cmd = ("docker", "build", "-t", img, "-")
    subprocess.run(cmd, input=dockerfile, check=True)

    shutil.rmtree("dist", ignore_errors=True)
    os.makedirs("dist", exist_ok=True)

    for py_bin in (
        "/opt/python/cp37-cp37m/bin",
        "/opt/python/cp38-cp38/bin",
        "/opt/python/cp39-cp39/bin",
        "/opt/python/cp310-cp310/bin",
    ):
        prog = PROG.format(py_bin=py_bin, version=args.version)
        # fmt: off
        if subprocess.call(
            (
                "docker", "run", "-v", f"{os.path.abspath('dist')}:/dist:rw",
                "--rm", "-it", img, "bash", "-euxc", prog,
            )
        ):
            # fmt: on
            return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
