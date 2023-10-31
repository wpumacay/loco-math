#!/usr/bin/env python

# Script adapted from Anthony Sottile's onigurumacffi repo:
# https://github.com/asottile/onigurumacffi/blob/main/bin/build-manylinux-wheels

import argparse
import os
import subprocess


DOCKERFILE_FMT = """\
FROM {baseImage}

RUN :\
    && apt-get update -q \
    && export DEBIAN_FRONTEND=nointeractive \
    && apt-get install -y --no-install-recommends \
         build-essential git cmake ninja-build clang \
         python3 python3-dev python3-virtualenv \
    && apt-get autoclean -y \
    && apt-get autoremove -y \
    && apt-get clean \
    && rm -r /var/lib/apt/lists/* \
    && :

RUN git config --global http.sslVerify false

ENV CMAKE_GENERATOR={generator}
ENV CMAKE_BUILD_PARALLEL_LEVEL={jobs}

WORKDIR /src

COPY . .
"""

PROG = """\
export CC={CC} && export CXX={CXX} && \
cmake -B build && cmake --build build && \
cd build/tests/cpp && ctest && cd /src && \
virtualenv venv && . venv/bin/activate && \
pip install pytest numpy && pip install -v . && pytest tests/python
"""

COMPILER_OPTIONS = {
    "ubuntu:18.04": [
        {"CC": "gcc", "CXX": "g++"},
        {"CC": "clang", "CXX": "clang++"},
    ],
    "ubuntu:20.04": [
        {"CC": "gcc", "CXX": "g++"},
        {"CC": "clang", "CXX": "clang++"},
    ],
    "ubuntu:22.04": [
        {"CC": "gcc", "CXX": "g++"},
        {"CC": "clang", "CXX": "clang++"},
    ],
}


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--generator",
        help="The type of generator to be used, either Ninja or Unix Makefiles",
        type=str,
        default="'Unix Makefiles'",
    )
    parser.add_argument(
        "--jobs",
        help="The number of parallel jobs to run for the build",
        type=int,
        default=20,
    )
    parser.add_argument(
        "--baseImage",
        help="The base image to be used, e.g. ubuntu:20.04",
        type=str,
        default="ubuntu:22.04",
    )
    args = parser.parse_args()

    img = f"math3d-build-{args.baseImage}"
    dockerfile = DOCKERFILE_FMT.format(
        baseImage=args.baseImage,
        generator=args.generator,
        jobs=args.jobs,
    )

    cmd = ("docker", "build", "-t", img, "-")
    subprocess.run(cmd, input=dockerfile.encode(), check=True)

    compiler_opts = COMPILER_OPTIONS[args.baseImage]
    for comp_opt in compiler_opts:
        prog = PROG.format(
            CC=comp_opt["CC"],
            CXX=comp_opt["CXX"],
        )

        # fmt: off
        if subprocess.call(
            (
                "docker", "run", "--rm", "-it", img, "bash", "-euxc", prog,
            )
        ):
            # fmt: on
            return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
