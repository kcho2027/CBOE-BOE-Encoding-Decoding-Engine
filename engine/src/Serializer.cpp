#include "Messages.h"
#include <vector>
#include "Util.h"

std::vector<uint8_t> serialize_new_order(const NewOrder& m) {
    std::vector<uint8_t> buf; buf.reserve(/* calc length */);
    // Frame header
    buf.push_back(0xBA); buf.push_back(0xBA); // sync
    buf.push_back(0x01); // message type
    append_uint(buf, m.order_id, 8);
    append_bytes(buf, m.symbol);
    append_bytes(buf, m.side);
    append_uint(buf, m.quantity, 4);
    append_uint(buf, m.price, 8);
    append_uint(buf, m.timestamp, 8);
    // TODO: checksum/trailer
    return buf;
}

NewOrder parse_new_order(const uint8_t* data, size_t len) {
    NewOrder m; size_t pos = 0;
    // skip sync & type header
    pos += 3;
    m.order_id = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.symbol, 8); pos += 8;
    read_bytes(data + pos, m.side, 1); pos += 1;
    m.quantity = read_uint(data + pos, 4); pos += 4;
    m.price = read_uint(data + pos, 8); pos += 8;
    m.timestamp = read_uint(data + pos, 8); pos += 8;
    return m;
}

std::vector<uint8_t> serialize_modify_order(const ModifyOrder& m) {
    std::vector<uint8_t> buf; buf.reserve(/* calc length */);
    // Frame header
    buf.push_back(0xBA); buf.push_back(0xBA); // sync
    buf.push_back(0x02); // message type
    append_uint(buf, m.order_id, 8);
    append_uint(buf, m.new_quantity, 4);
    append_uint(buf, m.new_price, 8);
    append_uint(buf, m.timestamp, 8);
    // TODO: checksum/trailer
    return buf;
}

ModifyOrder parse_modify_order(const uint8_t* data, size_t len) {
    ModifyOrder m; size_t pos = 0;
    // skip sync & type header
    pos += 3;
    m.order_id = read_uint(data + pos, 8); pos += 8;
    m.new_quantity = read_uint(data + pos, 4); pos += 4;
    m.new_price = read_uint(data + pos, 8); pos += 8;
    m.timestamp = read_uint(data + pos, 8); pos += 8;
    return m;
}

