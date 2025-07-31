// Buffer.cpp
#include "cboe/Buffer.h"
#include <cstring>
#include <stdexcept>
#include <algorithm>

namespace cboe {

Buffer::Buffer(size_t initial_capacity) 
    : data_(new uint8_t[initial_capacity])
    , capacity_(initial_capacity)
    , size_(0)
    , read_pos_(0) {
}

Buffer::Buffer(const uint8_t* data, size_t len)
    : data_(new uint8_t[len])
    , capacity_(len)
    , size_(len)
    , read_pos_(0) {
    std::memcpy(data_.get(), data, len);
}

Buffer::Buffer(Buffer&& other) noexcept
    : data_(std::move(other.data_))
    , capacity_(other.capacity_)
    , size_(other.size_)
    , read_pos_(other.read_pos_) {
    other.capacity_ = 0;
    other.size_ = 0;
    other.read_pos_ = 0;
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        capacity_ = other.capacity_;
        size_ = other.size_;
        read_pos_ = other.read_pos_;
        
        other.capacity_ = 0;
        other.size_ = 0;
        other.read_pos_ = 0;
    }
    return *this;
}

Buffer::~Buffer() = default;

void Buffer::reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) return;
    
    auto new_data = std::make_unique<uint8_t[]>(new_capacity);
    if (size_ > 0) {
        std::memcpy(new_data.get(), data_.get(), size_);
    }
    
    data_ = std::move(new_data);
    capacity_ = new_capacity;
}

void Buffer::write(const uint8_t* data, size_t len) {
    if (size_ + len > capacity_) {
        reserve(std::max(capacity_ * 2, size_ + len));
    }
    
    std::memcpy(data_.get() + size_, data, len);
    size_ += len;
}

void Buffer::write_uint8(uint8_t value) {
    write(&value, 1);
}

void Buffer::write_uint16(uint16_t value) {
    uint8_t bytes[2];
    bytes[0] = (value >> 8) & 0xFF;
    bytes[1] = value & 0xFF;
    write(bytes, 2);
}

void Buffer::write_uint32(uint32_t value) {
    uint8_t bytes[4];
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
    write(bytes, 4);
}

void Buffer::write_uint64(uint64_t value) {
    uint8_t bytes[8];
    bytes[0] = (value >> 56) & 0xFF;
    bytes[1] = (value >> 48) & 0xFF;
    bytes[2] = (value >> 40) & 0xFF;
    bytes[3] = (value >> 32) & 0xFF;
    bytes[4] = (value >> 24) & 0xFF;
    bytes[5] = (value >> 16) & 0xFF;
    bytes[6] = (value >> 8) & 0xFF;
    bytes[7] = value & 0xFF;
    write(bytes, 8);
}

bool Buffer::read(uint8_t* data, size_t len) {
    if (read_pos_ + len > size_) {
        return false;
    }
    
    std::memcpy(data, data_.get() + read_pos_, len);
    read_pos_ += len;
    return true;
}

bool Buffer::read_uint8(uint8_t& value) {
    return read(&value, 1);
}

bool Buffer::read_uint16(uint16_t& value) {
    uint8_t bytes[2];
    if (!read(bytes, 2)) return false;
    
    value = (static_cast<uint16_t>(bytes[0]) << 8) | bytes[1];
    return true;
}

bool Buffer::read_uint32(uint32_t& value) {
    uint8_t bytes[4];
    if (!read(bytes, 4)) return false;
    
    value = (static_cast<uint32_t>(bytes[0]) << 24) |
            (static_cast<uint32_t>(bytes[1]) << 16) |
            (static_cast<uint32_t>(bytes[2]) << 8) |
            bytes[3];
    return true;
}

bool Buffer::read_uint64(uint64_t& value) {
    uint8_t bytes[8];
    if (!read(bytes, 8)) return false;
    
    value = (static_cast<uint64_t>(bytes[0]) << 56) |
            (static_cast<uint64_t>(bytes[1]) << 48) |
            (static_cast<uint64_t>(bytes[2]) << 40) |
            (static_cast<uint64_t>(bytes[3]) << 32) |
            (static_cast<uint64_t>(bytes[4]) << 24) |
            (static_cast<uint64_t>(bytes[5]) << 16) |
            (static_cast<uint64_t>(bytes[6]) << 8) |
            bytes[7];
    return true;
}

void Buffer::reset() {
    size_ = 0;
    read_pos_ = 0;
}

void Buffer::clear() {
    size_ = 0;
    read_pos_ = 0;
}

const uint8_t* Buffer::data() const {
    return data_.get();
}

uint8_t* Buffer::data() {
    return data_.get();
}

size_t Buffer::size() const {
    return size_;
}

size_t Buffer::capacity() const {
    return capacity_;
}

size_t Buffer::read_position() const {
    return read_pos_;
}

void Buffer::set_read_position(size_t pos) {
    if (pos > size_) {
        throw std::out_of_range("Read position exceeds buffer size");
    }
    read_pos_ = pos;
}

bool Buffer::empty() const {
    return size_ == 0;
}

bool Buffer::eof() const {
    return read_pos_ >= size_;
}

} // namespace cboe 