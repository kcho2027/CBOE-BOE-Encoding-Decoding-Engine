#pragma once
#include <vector>
#include <cstdint>
namespace cboe {
struct FramingEngine {
    static std::vector<uint8_t> wrapMessage(const std::vector<uint8_t>& body);
    static bool unwrapMessage(const uint8_t* data, size_t len, std::vector<uint8_t>& out);
};
} // namespace cboe
