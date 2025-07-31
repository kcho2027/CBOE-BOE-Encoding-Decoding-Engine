#!/bin/bash

# Run codegen script to generate C++ code from YAML spec
set -e

echo "Running code generation..."

# Check if Python and required packages are available
if ! command -v python3 &> /dev/null; then
    echo "Error: python3 is required but not installed"
    exit 1
fi

# Check if PyYAML is installed
if ! python3 -c "import yaml" &> /dev/null; then
    echo "Installing PyYAML..."
    pip3 install PyYAML
fi

# Run the codegen
echo "Generating C++ code from YAML specification..."
python3 codegen/codegen.py codegen/cboe_spec.yaml engine/

echo "Code generation completed successfully!"
echo "Generated files:"
echo "  - engine/include/cboe/Messages.h"
echo "  - engine/include/cboe/Serializer.h"
echo "  - engine/include/cboe/Deserializer.h"
echo "  - engine/include/cboe/util.h"
echo "  - engine/include/cboe/FramingEngine.h"
echo "  - engine/src/Serializer.cpp"
echo "  - engine/src/Deserializer.cpp"
echo "  - engine/src/FramingEngine.cpp" 