FROM ubuntu:20.04

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

RUN :\
    && groupadd -g 1000 randuser \
    && useradd -d /home/randuser -s /bin/bash -m randuser -u 1000 -g 1000

USER randuser

ENV CMAKE_GENERATOR="Ninja"
ENV CMAKE_BUILD_PARALLEL_LEVEL=20

WORKDIR /home/randuser/math3d
