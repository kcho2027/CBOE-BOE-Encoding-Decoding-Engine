#pragma once
#include <cstdint>
#include <vector>
#include <cstring>
#include <array>

// Append an unsigned integer (little-endian) of byte-width `size` into `buf`.
inline void append_uint(std::vector<uint8_t> &buf, uint64_t value, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        buf.push_back(static_cast<uint8_t>(value & 0xFF));
        value >>= 8;
    }
}

// Append a raw byte sequence (e.g. a char array or std::array<uint8_t,N>).
inline void append_bytes(std::vector<uint8_t> &buf, const void *data, size_t size)
{
    const uint8_t *ptr = reinterpret_cast<const uint8_t *>(data);
    buf.insert(buf.end(), ptr, ptr + size);
}

// Read a little-endian unsigned integer of byte-width `size`.
inline uint64_t read_uint(const uint8_t *data, size_t size)
{
    uint64_t value = 0;
    for (size_t i = 0; i < size; ++i)
    {
        value |= (static_cast<uint64_t>(data[i]) << (8 * i));
    }
    return value;
}

// Copy `size` bytes from `data` into a destination buffer (e.g. a char array).
inline void read_bytes(const uint8_t *data, void *dest, size_t size)
{
    std::memcpy(dest, data, size);
}

// (Optional) Compute a simple checksum; replace with CRC32 if desired.
inline uint32_t simple_checksum(const uint8_t *data, size_t len)
{
    uint32_t sum = 0;
    for (size_t i = 0; i < len; ++i)
    {
        sum += data[i];
    }
    return sum;
}
