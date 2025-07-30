#pragma once
#include <vector>
#include "cboe/Messages.h"
#include "util.h"

namespace cboe {

std::vector<uint8_t> serializeNewOrder(const NewOrder& m);
std::vector<uint8_t> serializeModifyOrder(const ModifyOrder& m);
} // namespace cboe
