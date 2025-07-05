#pragma once
#include <cstdint>
#include <array>

// Message: NewOrder (type 0x01)
struct NewOrder {
    uint64 order_id; // 8 bytes
    char[8] symbol; // 8 bytes
    char side; // 1 bytes
    uint32 quantity; // 4 bytes
    uint64 price; // 8 bytes
    uint64 timestamp; // 8 bytes
};

// Message: ModifyOrder (type 0x02)
struct ModifyOrder {
    uint64 order_id; // 8 bytes
    uint32 new_quantity; // 4 bytes
    uint64 new_price; // 8 bytes
    uint64 timestamp; // 8 bytes
};

