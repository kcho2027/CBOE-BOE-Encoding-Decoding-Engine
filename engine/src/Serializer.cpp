#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeNewOrder(const cboe::NewOrder& m) {
    std::vector<uint8_t> buf;
    // framing, fields...
    append_uint(buf, m.order_id, 8);
    append_bytes(buf, m.symbol, 8);
    append_bytes(buf, m.side, 1);
    append_uint(buf, m.quantity, 4);
    append_uint(buf, m.price, 8);
    append_uint(buf, m.timestamp, 8);
    return buf;
}



