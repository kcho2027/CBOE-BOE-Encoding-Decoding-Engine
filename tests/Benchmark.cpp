#include <benchmark/benchmark.h>
#include "cboe/Messages.h"
#include "cboe/Serializer.h"
#include "cboe/Deserializer.h"
#include "cboe/FramingEngine.h"
#include "cboe/Buffer.h"
#include "cboe/Allocator.h"
#include <vector>
#include <cstring>

namespace cboe {
namespace benchmark {

// Benchmark serialization performance
static void BM_LoginRequestSerialize(::benchmark::State& state) {
    LoginRequest request;
    std::memset(&request, 0, sizeof(request));
    std::strcpy(request.session_sub_id, "TEST");
    std::strcpy(request.username, "USER");
    std::strcpy(request.password, "PASS12345");
    request.number_of_param_groups[0] = 1;
    
    for (auto _ : state) {
        auto serialized = serializeLoginRequest(request);
        ::benchmark::DoNotOptimize(serialized);
    }
}
BENCHMARK(BM_LoginRequestSerialize);

static void BM_NewOrderSerialize(::benchmark::State& state) {
    NewOrder order;
    std::memset(&order, 0, sizeof(order));
    std::strcpy(order.cl_ord_id, "ORDER123456789");
    order.side[0] = '1';
    order.order_qty[0] = 100;
    order.number_of_new_order_bitfields[0] = 1;
    order.new_order_bitfield[0] = 0x01;
    
    for (auto _ : state) {
        auto serialized = serializeNewOrder(order);
        ::benchmark::DoNotOptimize(serialized);
    }
}
BENCHMARK(BM_NewOrderSerialize);

// Benchmark deserialization performance
static void BM_LoginRequestDeserialize(::benchmark::State& state) {
    LoginRequest request;
    std::memset(&request, 0, sizeof(request));
    std::strcpy(request.session_sub_id, "TEST");
    std::strcpy(request.username, "USER");
    std::strcpy(request.password, "PASS12345");
    request.number_of_param_groups[0] = 1;
    
    auto serialized = serializeLoginRequest(request);
    
    for (auto _ : state) {
        auto parsed = parse_login_request(serialized.data(), serialized.size());
        ::benchmark::DoNotOptimize(parsed);
    }
}
BENCHMARK(BM_LoginRequestDeserialize);

static void BM_NewOrderDeserialize(::benchmark::State& state) {
    NewOrder order;
    std::memset(&order, 0, sizeof(order));
    std::strcpy(order.cl_ord_id, "ORDER123456789");
    order.side[0] = '1';
    order.order_qty[0] = 100;
    order.number_of_new_order_bitfields[0] = 1;
    order.new_order_bitfield[0] = 0x01;
    
    auto serialized = serializeNewOrder(order);
    
    for (auto _ : state) {
        auto parsed = parse_new_order(serialized.data(), serialized.size());
        ::benchmark::DoNotOptimize(parsed);
    }
}
BENCHMARK(BM_NewOrderDeserialize);

// Benchmark framing performance
static void BM_FramingEngineWrap(::benchmark::State& state) {
    std::vector<uint8_t> message(100, 0x42);
    
    for (auto _ : state) {
        auto framed = FramingEngine::wrapMessage(message);
        ::benchmark::DoNotOptimize(framed);
    }
}
BENCHMARK(BM_FramingEngineWrap);

static void BM_FramingEngineUnwrap(::benchmark::State& state) {
    std::vector<uint8_t> message(100, 0x42);
    auto framed = FramingEngine::wrapMessage(message);
    
    for (auto _ : state) {
        std::vector<uint8_t> unwrapped;
        bool success = FramingEngine::unwrapMessage(framed.data(), framed.size(), unwrapped);
        ::benchmark::DoNotOptimize(success);
        ::benchmark::DoNotOptimize(unwrapped);
    }
}
BENCHMARK(BM_FramingEngineUnwrap);

// Benchmark Buffer performance
static void BM_BufferWrite(::benchmark::State& state) {
    Buffer buffer(1024);
    std::vector<uint8_t> data(100, 0x42);
    
    for (auto _ : state) {
        buffer.clear();
        buffer.write(data.data(), data.size());
        ::benchmark::DoNotOptimize(buffer);
    }
}
BENCHMARK(BM_BufferWrite);

static void BM_BufferRead(::benchmark::State& state) {
    Buffer buffer(1024);
    std::vector<uint8_t> data(100, 0x42);
    buffer.write(data.data(), data.size());
    
    for (auto _ : state) {
        buffer.set_read_position(0);
        uint8_t read_data[100];
        bool success = buffer.read(read_data, 100);
        ::benchmark::DoNotOptimize(success);
        ::benchmark::DoNotOptimize(read_data);
    }
}
BENCHMARK(BM_BufferRead);

// Benchmark round-trip performance
static void BM_LoginRequestRoundTrip(::benchmark::State& state) {
    LoginRequest request;
    std::memset(&request, 0, sizeof(request));
    std::strcpy(request.session_sub_id, "TEST");
    std::strcpy(request.username, "USER");
    std::strcpy(request.password, "PASS12345");
    request.number_of_param_groups[0] = 1;
    
    for (auto _ : state) {
        auto serialized = serializeLoginRequest(request);
        auto parsed = parse_login_request(serialized.data(), serialized.size());
        ::benchmark::DoNotOptimize(parsed);
    }
}
BENCHMARK(BM_LoginRequestRoundTrip);

static void BM_NewOrderRoundTrip(::benchmark::State& state) {
    NewOrder order;
    std::memset(&order, 0, sizeof(order));
    std::strcpy(order.cl_ord_id, "ORDER123456789");
    order.side[0] = '1';
    order.order_qty[0] = 100;
    order.number_of_new_order_bitfields[0] = 1;
    order.new_order_bitfield[0] = 0x01;
    
    for (auto _ : state) {
        auto serialized = serializeNewOrder(order);
        auto parsed = parse_new_order(serialized.data(), serialized.size());
        ::benchmark::DoNotOptimize(parsed);
    }
}
BENCHMARK(BM_NewOrderRoundTrip);

// Benchmark memory allocation performance
static void BM_AllocatorAllocate(::benchmark::State& state) {
    for (auto _ : state) {
        void* ptr = allocate(1024);
        deallocate(ptr);
        ::benchmark::DoNotOptimize(ptr);
    }
}
BENCHMARK(BM_AllocatorAllocate);

} // namespace benchmark
} // namespace cboe

// Main function for benchmarks
int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
} 