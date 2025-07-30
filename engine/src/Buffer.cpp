// Buffer.cpp
#include "cboe/util.h"
#include <cstdint>
#include <vector>

namespace cboe {
class Buffer {
public:
    Buffer(uint8_t* data, size_t size) : data_(data), size_(size), cursor_(0) {}
    // ... zero-copy buffer methods ...
private:
    uint8_t* data_;
    size_t size_;
    size_t cursor_;
};
} // namespace cboe 