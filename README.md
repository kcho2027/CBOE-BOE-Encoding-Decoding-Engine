# CBOE BOE Encoding/Decoding Engine

A high-performance, cross-platform C++ engine for encoding and decoding Cboe Binary Order Entry (BOE) messages, with comprehensive message support, zero-copy buffer operations, pluggable memory allocation, and automated code generation from YAML specifications.

## 🚀 Features

- **Comprehensive Message Support**: Complete coverage of CBOE BOE protocol messages including session management, order management, quote management, and complex orders
- **High Performance**: Zero-copy buffer operations, optimized serialization/deserialization, and low-latency message processing
- **Code Generation**: Automated C++ code generation from YAML specifications with support for repeating groups and bitfields
- **Pluggable Architecture**: Customizable memory allocators and buffer management
- **Cross-Platform**: Support for Linux, macOS, and Windows
- **Comprehensive Testing**: Unit tests, integration tests, and performance benchmarks
- **Modern C++**: C++17 standard with RAII, move semantics, and exception safety

## 📋 Project Structure

```
.
├── codegen/                      # YAML → C++ code generator
│   ├── cboe_spec.yaml            # Complete CBOE BOE specification
│   ├── codegen.py                # Enhanced code generator
│   └── requirements.txt           # Python dependencies
│
├── engine/                       # Core C++ library
│   ├── include/cboe/             # Public API headers
│   │   ├── Messages.h            # Generated message structs
│   │   ├── Serializer.h          # Serialization API
│   │   ├── Deserializer.h        # Deserialization API
│   │   ├── Buffer.h              # Zero-copy buffer API
│   │   ├── Allocator.h           # Pluggable allocator API
│   │   ├── FramingEngine.h       # Message framing API
│   │   └── util.h                # Utility functions
│   │
│   ├── src/                      # Core implementation
│   │   ├── Serializer.cpp        # Generated serializers
│   │   ├── Deserializer.cpp      # Generated deserializers
│   │   ├── FramingEngine.cpp     # Message framing implementation
│   │   ├── Buffer.cpp            # Zero-copy buffer implementation
│   │   └── Allocator.cpp         # Memory allocator implementations
│   │
│   ├── cmake/                    # CMake configuration
│   │   └── cboe_coreConfig.cmake.in
│   │
│   └── CMakeLists.txt            # Build configuration
│
├── tests/                        # Test suite
│   ├── CMakeLists.txt            # Test build configuration
│   ├── SerializerTests.cpp       # Serialization tests
│   ├── FramingEngineTests.cpp    # Framing engine tests
│   └── Benchmark.cpp             # Performance benchmarks
│
├── scripts/                      # Build and test scripts
│   ├── run_codegen.sh            # Code generation script
│   ├── run_tests.sh              # Test execution script
│   ├── bench_latency.sh          # Performance benchmarking
│   └── build_yaml.py             # YAML specification builder
│
└── README.md                     # This file
```

## 🛠️ Quick Start

### Prerequisites

- **C++17 compatible compiler** (GCC 7+, Clang 5+, MSVC 2017+)
- **CMake 3.16+**
- **Python 3.6+** (for code generation)
- **Google Test** (for testing)
- **Google Benchmark** (for benchmarking, optional)

### Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/your-org/cboe-boe-engine.git
   cd cboe-boe-engine
   ```

2. **Install Python dependencies**:

   ```bash
   pip install -r codegen/requirements.txt
   ```

3. **Generate C++ code from YAML specification**:

   ```bash
   ./scripts/run_codegen.sh
   ```

4. **Build the engine**:

   ```bash
   cd engine
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   make -j$(nproc)
   ```

5. **Run tests**:

   ```bash
   ./scripts/run_tests.sh
   ```

6. **Run benchmarks** (optional):
   ```bash
   ./scripts/bench_latency.sh
   ```

## 📖 Usage Examples

### Basic Message Serialization

```cpp
#include "cboe/Messages.h"
#include "cboe/Serializer.h"
#include "cboe/Deserializer.h"

// Create a login request
cboe::LoginRequest request;
std::strcpy(request.session_sub_id, "TEST");
std::strcpy(request.username, "USER");
std::strcpy(request.password, "PASS12345");
request.number_of_param_groups = 1;

// Serialize the message
auto serialized = cboe::serializeLoginRequest(request);

// Deserialize the message
auto parsed = cboe::parse_login_request(serialized.data(), serialized.size());
```

### Using the Buffer API

```cpp
#include "cboe/Buffer.h"

// Create a buffer
cboe::Buffer buffer(1024);

// Write data
buffer.write_uint32(12345);
buffer.write_uint64(987654321);

// Read data
uint32_t value1;
uint64_t value2;
buffer.set_read_position(0);
buffer.read_uint32(value1);
buffer.read_uint64(value2);
```

### Custom Memory Allocation

```cpp
#include "cboe/Allocator.h"

// Create a pool allocator
auto pool_allocator = cboe::create_pool_allocator(1024, 32);

// Set as global allocator
cboe::set_allocator(std::move(pool_allocator));

// Use the allocator
void* ptr = cboe::allocate(512);
// ... use memory ...
cboe::deallocate(ptr);
```

### Message Framing

```cpp
#include "cboe/FramingEngine.h"

// Wrap a message with framing
std::vector<uint8_t> message_data = {0x01, 0x02, 0x03, 0x04};
auto framed = cboe::FramingEngine::wrapMessage(message_data);

// Unwrap a message
std::vector<uint8_t> unwrapped;
bool success = cboe::FramingEngine::unwrapMessage(
    framed.data(), framed.size(), unwrapped);
```

## 🧪 Testing

The project includes comprehensive tests:

- **Unit Tests**: Test individual components and message types
- **Integration Tests**: Test complete message round-trips
- **Performance Tests**: Benchmark serialization/deserialization performance

Run tests with:

```bash
./scripts/run_tests.sh
```

## 📊 Performance

The engine is optimized for high-performance trading applications:

- **Low Latency**: Sub-microsecond message serialization/deserialization
- **Zero-Copy**: Efficient buffer management with minimal memory allocations
- **Memory Efficient**: Pluggable allocators for custom memory management strategies

Run benchmarks with:

```bash
./scripts/bench_latency.sh
```

## 🔧 Configuration

### Build Options

- `CMAKE_BUILD_TYPE`: Set to `Debug`, `Release`, or `RelWithDebInfo`
- `BUILD_TESTS`: Enable/disable test building (default: ON)
- `BUILD_BENCHMARKS`: Enable/disable benchmark building (default: ON)

### Message Types Supported

The engine supports all major CBOE BOE message types:

**Session Management**:

- LoginRequest (0x37)
- LogoutRequest (0x02)
- ClientHeartbeat (0x03)
- LoginResponse (0x24)
- Logout (0x08)
- ServerHeartbeat (0x09)
- ReplayComplete (0x13)

**Order Management**:

- NewOrder (0x38)
- CancelOrder (0x39)
- ModifyOrder (0x3A)
- NewOrderCross (0x41)

**Quote Management**:

- QuoteUpdate (0x55)
- QuoteUpdateShort (0x59)
- QuoteUpdateAcknowledgment (0x51)

**Complex Orders**:

- NewComplexOrder (0x4B)
- NewComplexInstrument (0x4C)

**Risk Management**:

- ResetRisk (0x56)
- RiskResetAcknowledgment (0x57)

**System Messages**:

- OrderAcknowledgment (0x25)
- OrderRejected (0x26)
- OrderModified (0x27)
- OrderCancelled (0x2A)
- OrderExecution (0x2C)

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- CBOE for the Binary Order Entry protocol specification
- Google Test for the testing framework
- Google Benchmark for the benchmarking framework
- The C++ community for best practices and guidance

## 📞 Support

For questions, issues, or contributions, please:

- Open an issue on GitHub
- Check the documentation in the `docs/` directory
- Review the test examples for usage patterns
