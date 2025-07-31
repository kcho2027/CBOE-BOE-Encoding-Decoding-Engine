#include "cboe/FramingEngine.h"
#include <vector>
#include <cstdint>

namespace cboe {

std::vector<uint8_t> FramingEngine::wrapMessage(const std::vector<uint8_t>& body) {
    std::vector<uint8_t> framed;
    // Add sync bytes
    framed.push_back(0xBA);
    framed.push_back(0xBA);
    
    // Add length (excluding sync bytes)
    uint16_t length = body.size();
    framed.push_back((length >> 8) & 0xFF);
    framed.push_back(length & 0xFF);
    
    // Add body
    framed.insert(framed.end(), body.begin(), body.end());
    
    return framed;
}

bool FramingEngine::unwrapMessage(const uint8_t* data, size_t len, std::vector<uint8_t>& out) {
    if (len < 4) return false;
    
    // Check sync bytes
    if (data[0] != 0xBA || data[1] != 0xBA) return false;
    
    // Extract length
    uint16_t msg_len = (data[2] << 8) | data[3];
    
    if (len < 4 + msg_len) return false;
    
    // Copy message body
    out.assign(data + 4, data + 4 + msg_len);
    return true;
}

} // namespace cboe
