#!/bin/bash
set -e

cd engine
mkdir -p build
cd build
cmake ..
make -j
ctest --output-on-failure 