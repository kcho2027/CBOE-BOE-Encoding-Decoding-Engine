# CBOE BOE Encoding/Decoding Engine

A high-performance, cross-platform C++ engine for encoding and decoding Cboe Binary Order Entry (BOE) messages, with code generation from YAML spec, zero-copy support, and CI/CD integration.

## Project Structure

```
.
├── codegen/                      # YAML → C++ code generator
│   ├── cboe_spec.yaml            # Full spec in YAML
│   └── codegen.py                # Emits headers + sources
│
├── engine/                       # Core C++ library
│   ├── include/cboe/             # Public API headers
│   │   ├── Messages.h            # Generated structs
│   │   ├── Serializer.h          # Declarations
│   │   ├── Deserializer.h
│   │   ├── Util.h                # Helpers (append_uint, read_uint…)
│   │   └── FramingEngine.h       # Framing/versioning API
│   │
│   ├── src/                      # Core implementation
│   │   ├── Serializer.cpp        # Generated serialize defs
│   │   ├── Deserializer.cpp      # Generated parse defs
│   │   ├── FramingEngine.cpp     # Sync bytes, length, checksum
│   │   ├── Buffer.cpp            # Zero-copy buffer implementation
│   │   └── Allocator.cpp         # Pluggable memory pool
│   │
│   └── CMakeLists.txt            # Build library
│
├── tests/                        # Unit, integration & bench
│   ├── SerializerTests.cpp       # GoogleTest round-trip
│   ├── FramingEngineTests.cpp
│   └── Benchmark.cpp             # Google Benchmark harness
│
├── ui/ (optional)                # Spec editor / dashboard
│   ├── web/ReactApp/             # React + Tailwind dashboard
│   └── cli/                      # Python Typer CLI for spec regen
│
├── scripts/                      # Helpers
│   ├── run_codegen.sh            # codegen → engine/
│   ├── run_tests.sh              # build & run all tests
│   └── bench_latency.sh          # perf harness
│
├── .github/workflows/            # CI: codegen, build, tests, benchmarks
│   ├── build.yml
│   └── benchmark.yml
│
├── Dockerfile                    # containerize engine + tools
└── README.md
```

## Quick Start

1. Install Python dependencies:
   ```sh
   pip install -r codegen/requirements.txt
   ```
2. Generate C++ code from YAML spec:
   ```sh
   ./scripts/run_codegen.sh
   ```
3. Build the engine:
   ```sh
   cd engine && mkdir build && cd build && cmake .. && make -j
   ```
4. Run tests:
   ```sh
   ./scripts/run_tests.sh
   ```

## Features

- High-throughput, low-latency encode/decode
- Zero-copy buffer support
- Pluggable allocator
- Codegen from YAML spec
- Cross-platform (Linux, macOS, Windows)
- CI/CD, code coverage, benchmarks
- (Optional) UI/dashboard for spec editing and monitoring

## License

MIT
