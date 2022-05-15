#!/bin/bash
mkdir -p build
cd build || exit
cmake -S ../ -B . # If you want to build in release mode add -DCMAKE_BUILD_TYPE=Release flag
if [ -z "$MAKEFLAGS" ]; then
  export MAKEFLAGS=-j$(nproc)
fi
make && make Shaders
./MiniminiMotorways
cd ..
