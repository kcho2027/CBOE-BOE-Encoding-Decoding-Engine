#include <benchmark/benchmark.h>
#include "cboe/Messages.h"
#include "cboe/Serializer.h"
#include "cboe/Deserializer.h"

static void BM_EncodeDecode(benchmark::State& state) {
    for (auto _ : state) {
        // TODO: Encode and decode a message
    }
}
BENCHMARK(BM_EncodeDecode);

BENCHMARK_MAIN(); 