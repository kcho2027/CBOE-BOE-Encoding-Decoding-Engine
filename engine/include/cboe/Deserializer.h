#pragma once
#include "cboe/Messages.h"
#include "util.h"

namespace cboe {

NewOrder parse_new_order(const uint8_t* data, size_t len);
ModifyOrder parse_modify_order(const uint8_t* data, size_t len);
} // namespace cboe
