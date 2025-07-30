#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::NewOrder cboe::parse_new_order(const uint8_t* data, size_t len) {
    NewOrder m; size_t pos = 0;
    // skip framing header
    pos += 3;
    m.order_id = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.symbol, 8); pos += 8;
    read_bytes(data + pos, m.side, 1); pos += 1;
    m.quantity = read_uint(data + pos, 4); pos += 4;
    m.price = read_uint(data + pos, 8); pos += 8;
    m.timestamp = read_uint(data + pos, 8); pos += 8;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::ModifyOrder cboe::parse_modify_order(const uint8_t* data, size_t len) {
    ModifyOrder m; size_t pos = 0;
    // skip framing header
    pos += 3;
    m.order_id = read_uint(data + pos, 8); pos += 8;
    m.new_quantity = read_uint(data + pos, 4); pos += 4;
    m.new_price = read_uint(data + pos, 8); pos += 8;
    m.timestamp = read_uint(data + pos, 8); pos += 8;
    return m;
}

