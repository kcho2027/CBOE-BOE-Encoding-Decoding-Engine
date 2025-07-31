#pragma once

#include <cstddef>
#include <memory>

namespace cboe {

/**
 * Abstract allocator interface for pluggable memory management
 */
class Allocator {
public:
    virtual ~Allocator() = default;
    
    /**
     * Allocate memory block of specified size
     * @param size Size in bytes to allocate
     * @return Pointer to allocated memory, or nullptr if allocation failed
     */
    virtual void* allocate(size_t size) = 0;
    
    /**
     * Deallocate previously allocated memory block
     * @param ptr Pointer to memory block to deallocate
     */
    virtual void deallocate(void* ptr) = 0;
    
    /**
     * Reallocate memory block to new size
     * @param ptr Pointer to existing memory block
     * @param old_size Current size of the block
     * @param new_size New size for the block
     * @return Pointer to reallocated memory, or nullptr if reallocation failed
     */
    virtual void* reallocate(void* ptr, size_t old_size, size_t new_size) = 0;
};

// Global allocator management
void set_allocator(std::unique_ptr<Allocator> allocator);
Allocator* get_allocator();

// Allocator factory functions
std::unique_ptr<Allocator> create_pool_allocator(size_t block_size, size_t initial_blocks = 32);

// Convenience allocation functions
void* allocate(size_t size);
void deallocate(void* ptr);
void* reallocate(void* ptr, size_t old_size, size_t new_size);

} // namespace cboe 