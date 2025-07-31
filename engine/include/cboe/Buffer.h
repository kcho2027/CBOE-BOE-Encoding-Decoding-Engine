#pragma once

#include <cstdint>
#include <memory>
#include <cstddef>

namespace cboe {

/**
 * Zero-copy buffer for efficient message serialization/deserialization
 */
class Buffer {
public:
    // Constructors
    explicit Buffer(size_t initial_capacity = 1024);
    Buffer(const uint8_t* data, size_t len);
    
    // Move semantics
    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;
    
    // Destructor
    ~Buffer();
    
    // Copy operations are deleted
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    
    // Write operations
    void write(const uint8_t* data, size_t len);
    void write_uint8(uint8_t value);
    void write_uint16(uint16_t value);
    void write_uint32(uint32_t value);
    void write_uint64(uint64_t value);
    
    // Read operations
    bool read(uint8_t* data, size_t len);
    bool read_uint8(uint8_t& value);
    bool read_uint16(uint16_t& value);
    bool read_uint32(uint32_t& value);
    bool read_uint64(uint64_t& value);
    
    // Buffer management
    void reserve(size_t new_capacity);
    void reset();
    void clear();
    
    // Accessors
    const uint8_t* data() const;
    uint8_t* data();
    size_t size() const;
    size_t capacity() const;
    size_t read_position() const;
    void set_read_position(size_t pos);
    
    // State queries
    bool empty() const;
    bool eof() const;

private:
    std::unique_ptr<uint8_t[]> data_;
    size_t capacity_;
    size_t size_;
    size_t read_pos_;
};

} // namespace cboe 