# CboeBinaryOrderEntry

This project provides a C++ implementation for interacting with the Cboe Binary Order Entry (BOE) system that could be used for multiple different order types (ex. Options, Japan Equities, U.S Equities, Europe equities), focusing on efficient serialization and deserialization of BOE messages.

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Running Tests](#running-tests)
- [Usage](#usage)
- [Documentation](#documentation)
- [Coding Style and Linting](#coding-style-and-linting)
- [Performance Benchmarking](#performance-benchmarking)
- [Contributing](#contributing)
- [License](#license)

## Features

- **High-Performance Serialization/Deserialization:** Optimized for low-latency message processing.
- **Zero-Copy Buffer Handling:** Utilizes `Buffer.h` for efficient memory management.
- **Modular Design:** Separates concerns into distinct components (Framing, Serialization, Deserialization, Messages).
- **Comprehensive Test Suite:** Includes unit tests for core functionalities.
- **Configurable Allocation:** Supports custom memory allocators via `Allocator.h`.

## Project Structure

The project is organized as follows:

```
CboeBinaryOrderEntry/
├── CMakeLists.txt              # Top-level build configuration for the entire project
├── README.md                   # This overview document
├── docs/                       # Project documentation
│   └── US_Options_BOE_Specification.pdf # Original Cboe US Options BOE Specification (for reference)
├── include/                    # Public header files
│   └── cboe/                   # Cboe specific headers
│       ├── FramingEngine.h     # Handles BOE frame header/trailer, versioning, and checksums
│       ├── Serializer.h        # High-level interface for serializing Cboe BOE messages
│       ├── Deserializer.h      # High-level interface for deserializing Cboe BOE messages
│       ├── Message.h           # C++ struct definitions for all supported BOE messages
│       ├── Buffer.h            # Wrapper for zero-copy buffer operations
│       └── Allocator.h         # Abstract interface for custom memory allocators
├── src/                        # Source code files
│   ├── FramingEngine.cpp       # Implementation for FramingEngine.h
│   ├── Serializer.cpp          # Implementation for Serializer.h
│   ├── Deserializer.cpp        # Implementation for Deserializer.h
│   ├── Message.cpp             # Implementation for Message.h (if any, e.g., static data)
│   └── main.cpp                # Optional command-line interface (CLI) or demonstration application
├── tests/                      # Unit and integration tests
│   ├── CMakeLists.txt          # CMake build configuration for the test suite
│   ├── SerializerTests.cpp     # Google Test suite for various message serialization scenarios
│   ├── DeserializerTests.cpp   # Google Test suite for various message deserialization scenarios
│   └── FramingEngineTests.cpp  # Google Test suite for FramingEngine functionality
├── tools/                      # Development tools and scripts
│   ├── .clang-format           # ClangFormat configuration for consistent code styling
│   └── .clang-tidy             # ClangTidy configuration for static analysis and linting
│   └── scripts/                # Utility scripts
│       ├── run_tests.sh        # Script to build and execute all tests
│       └── bench_latency.sh    # Script for throughput and latency benchmarking
└── .gitignore                  # Specifies intentionally untracked files to ignore

```
