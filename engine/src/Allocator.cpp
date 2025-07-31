// Allocator.cpp
#include "cboe/Allocator.h"
#include <cassert>
#include <cstring>

namespace cboe {

// Default allocator implementation
class DefaultAllocator : public Allocator {
public:
    void* allocate(size_t size) override {
        return ::operator new(size);
    }
    
    void deallocate(void* ptr) override {
        ::operator delete(ptr);
    }
    
    void* reallocate(void* ptr, size_t old_size, size_t new_size) override {
        if (new_size == 0) {
            deallocate(ptr);
            return nullptr;
        }
        
        void* new_ptr = allocate(new_size);
        if (ptr && new_ptr) {
            std::memcpy(new_ptr, ptr, std::min(old_size, new_size));
            deallocate(ptr);
        }
        return new_ptr;
    }
};

// Pool allocator implementation
class PoolAllocator : public Allocator {
public:
    explicit PoolAllocator(size_t block_size, size_t initial_blocks = 32)
        : block_size_(block_size)
        , initial_blocks_(initial_blocks)
        , free_list_(nullptr) {
        
        // Allocate initial pool
        for (size_t i = 0; i < initial_blocks; ++i) {
            void* block = ::operator new(block_size_);
            push_free_block(block);
        }
    }
    
    ~PoolAllocator() {
        // Free all remaining blocks
        while (free_list_) {
            void* block = pop_free_block();
            ::operator delete(block);
        }
    }
    
    void* allocate(size_t size) override {
        if (size > block_size_) {
            return ::operator new(size);
        }
        
        if (free_list_) {
            return pop_free_block();
        }
        
        // Allocate new block
        return ::operator new(block_size_);
    }
    
    void deallocate(void* ptr) override {
        if (!ptr) return;
        
        // For simplicity, we'll just use the default deallocator
        // In a real implementation, you'd want to track which blocks
        // belong to the pool and return them to the free list
        ::operator delete(ptr);
    }
    
    void* reallocate(void* ptr, size_t old_size, size_t new_size) override {
        if (new_size == 0) {
            deallocate(ptr);
            return nullptr;
        }
        
        if (new_size <= block_size_ && old_size <= block_size_) {
            // Both sizes fit in pool blocks, no need to reallocate
            return ptr;
        }
        
        // Need to reallocate
        void* new_ptr = allocate(new_size);
        if (ptr && new_ptr) {
            std::memcpy(new_ptr, ptr, std::min(old_size, new_size));
            deallocate(ptr);
        }
        return new_ptr;
    }

private:
    struct FreeBlock {
        FreeBlock* next;
    };
    
    void push_free_block(void* block) {
        FreeBlock* fb = static_cast<FreeBlock*>(block);
        fb->next = free_list_;
        free_list_ = fb;
    }
    
    void* pop_free_block() {
        if (!free_list_) return nullptr;
        
        FreeBlock* fb = free_list_;
        free_list_ = fb->next;
        return fb;
    }
    
    size_t block_size_;
    size_t initial_blocks_;
    FreeBlock* free_list_;
};

// Global allocator instance
static std::unique_ptr<Allocator> g_allocator = std::make_unique<DefaultAllocator>();

// Allocator interface functions
void set_allocator(std::unique_ptr<Allocator> allocator) {
    g_allocator = std::move(allocator);
}

Allocator* get_allocator() {
    return g_allocator.get();
}

std::unique_ptr<Allocator> create_pool_allocator(size_t block_size, size_t initial_blocks) {
    return std::make_unique<PoolAllocator>(block_size, initial_blocks);
}

// Memory allocation functions
void* allocate(size_t size) {
    return g_allocator->allocate(size);
}

void deallocate(void* ptr) {
    g_allocator->deallocate(ptr);
}

void* reallocate(void* ptr, size_t old_size, size_t new_size) {
    return g_allocator->reallocate(ptr, old_size, new_size);
}

} // namespace cboe 