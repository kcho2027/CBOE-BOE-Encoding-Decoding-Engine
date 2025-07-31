#pragma once
#include <vector>
#include "cboe/Messages.h"
#include "util.h"

namespace cboe {

std::vector<uint8_t> serializeLoginRequest(const LoginRequest& m);
std::vector<uint8_t> serializeLogoutRequest(const LogoutRequest& m);
std::vector<uint8_t> serializeClientHeartbeat(const ClientHeartbeat& m);
std::vector<uint8_t> serializeLoginResponse(const LoginResponse& m);
std::vector<uint8_t> serializeLogout(const Logout& m);
std::vector<uint8_t> serializeServerHeartbeat(const ServerHeartbeat& m);
std::vector<uint8_t> serializeReplayComplete(const ReplayComplete& m);
std::vector<uint8_t> serializeNewOrder(const NewOrder& m);
std::vector<uint8_t> serializeCancelOrder(const CancelOrder& m);
std::vector<uint8_t> serializeModifyOrder(const ModifyOrder& m);
std::vector<uint8_t> serializeNewOrderCross(const NewOrderCross& m);
std::vector<uint8_t> serializeQuoteUpdate(const QuoteUpdate& m);
std::vector<uint8_t> serializeQuoteUpdateShort(const QuoteUpdateShort& m);
std::vector<uint8_t> serializeNewComplexOrder(const NewComplexOrder& m);
std::vector<uint8_t> serializeNewComplexInstrument(const NewComplexInstrument& m);
std::vector<uint8_t> serializeResetRisk(const ResetRisk& m);
std::vector<uint8_t> serializePurgeOrders(const PurgeOrders& m);
std::vector<uint8_t> serializeOrderAcknowledgment(const OrderAcknowledgment& m);
std::vector<uint8_t> serializeOrderRejected(const OrderRejected& m);
std::vector<uint8_t> serializeOrderModified(const OrderModified& m);
std::vector<uint8_t> serializeOrderCancelled(const OrderCancelled& m);
std::vector<uint8_t> serializeOrderExecution(const OrderExecution& m);
std::vector<uint8_t> serializeQuoteUpdateAcknowledgment(const QuoteUpdateAcknowledgment& m);
std::vector<uint8_t> serializeRiskResetAcknowledgment(const RiskResetAcknowledgment& m);
std::vector<uint8_t> serializeFloorTradeNotification(const FloorTradeNotification& m);
std::vector<uint8_t> serializePurgeNotification(const PurgeNotification& m);
} // namespace cboe
