#!/bin/bash

# Run performance benchmarks for the CBOE BOE Engine
set -e

echo "Running performance benchmarks..."

# Check if we're in the right directory
if [ ! -f "engine/CMakeLists.txt" ]; then
    echo "Error: Please run this script from the project root directory"
    exit 1
fi

# Create build directory
BUILD_DIR="engine/build"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Configuring CMake with benchmarks..."
cmake .. -DCMAKE_BUILD_TYPE=Release

echo "Building project..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo "Running benchmarks..."
if [ -f "cboe_tests" ]; then
    echo "Running performance benchmarks..."
    ./cboe_tests --benchmark_format=console --benchmark_out=benchmark_results.json --benchmark_out_format=json
    
    echo "Benchmark results saved to benchmark_results.json"
    
    # Display a summary of key metrics
    echo ""
    echo "Benchmark Summary:"
    echo "=================="
    if command -v jq &> /dev/null; then
        echo "Top 5 fastest operations:"
        jq -r '.benchmarks[] | select(.run_type == "iteration") | "\(.name): \(.real_time)ns"' benchmark_results.json | sort -n | head -5
    else
        echo "Install 'jq' for detailed benchmark analysis"
    fi
else
    echo "Warning: Benchmark executable not found. Make sure Google Benchmark is installed."
fi

echo "Benchmark run completed!" 