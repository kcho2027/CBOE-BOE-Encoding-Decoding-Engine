// Allocator.cpp
#include <cstddef>

namespace cboe {
class Allocator {
public:
    virtual void* allocate(size_t size) = 0;
    virtual void deallocate(void* ptr) = 0;
    virtual ~Allocator() = default;
};
// Default slab allocator stub
} // namespace cboe 