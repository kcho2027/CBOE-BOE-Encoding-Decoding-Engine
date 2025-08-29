#!/bin/bash

# Build and run tests for the CBOE BOE Engine
set -e

echo "Building and running tests..."

# Check if we're in the right directory
if [ ! -f "engine/CMakeLists.txt" ]; then
    echo "Error: Please run this script from the project root directory"
    exit 1
fi

# Create build directory
BUILD_DIR="engine/build"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Configuring CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Debug

echo "Building project..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo "Running tests..."
if [ -f "cboe_tests" ]; then
    echo "Running unit tests..."
    ./cboe_tests --gtest_output=xml:test_results.xml
    
    # Display test summary
    if [ $? -eq 0 ]; then
        echo "✅ All tests passed!"
    else
        echo "❌ Some tests failed!"
        exit 1
    fi
else
    echo "Warning: Test executable not found. Make sure GTest is installed."
fi

echo "Test run completed!" 