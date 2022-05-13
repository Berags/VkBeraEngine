#!/bin/bash
mkdir -p build
cd build || exit
cmake -S ../ -B .
if [ -z "$MAKEFLAGS" ]; then
  export MAKEFLAGS=-j$(nproc)
fi
make && make Shaders
./MiniminiMotorways
cd ..
