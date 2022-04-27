#!/bin/bash
mkdir -p build
cd build || exit
cmake -S ../ -B .
make && make Shaders && ./MiniminiMotorways
cd ..