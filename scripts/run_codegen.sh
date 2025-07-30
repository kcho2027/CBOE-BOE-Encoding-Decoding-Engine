#!/bin/bash
set -e

python3 codegen/codegen.py
# Optionally, copy generated files if codegen.py outputs to a temp dir
# cp generated/*.h engine/include/cboe/
# cp generated/*.cpp engine/src/ 