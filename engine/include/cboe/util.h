#pragma once
#include <cstdint>
#include <vector>
#include <cstring>
#include <algorithm>

inline void append_uint(std::vector<uint8_t>& buf, uint64_t v, size_t s) { 
    for(size_t i=0;i<s;++i){ 
        buf.push_back(v & 0xFF); 
        v >>= 8; 
    } 
}
inline void append_bytes(std::vector<uint8_t>& buf, const void* d, size_t s){ 
    buf.insert(buf.end(), (uint8_t*)d, (uint8_t*)d+s); 
}
inline uint64_t read_uint(const uint8_t* d, size_t s){ 
    uint64_t v=0; 
    for(size_t i=0;i<s;++i) v |= (uint64_t(d[i]) << (8*i)); 
    return v; 
}
inline void read_bytes(const uint8_t* d, void* dst, size_t s){ 
    memcpy(dst,d,s); 
}
