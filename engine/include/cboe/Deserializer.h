#pragma once
#include "cboe/Messages.h"
#include "util.h"

namespace cboe {

LoginRequest parse_login_request(const uint8_t* data, size_t len);
LogoutRequest parse_logout_request(const uint8_t* data, size_t len);
ClientHeartbeat parse_client_heartbeat(const uint8_t* data, size_t len);
LoginResponse parse_login_response(const uint8_t* data, size_t len);
Logout parse_logout(const uint8_t* data, size_t len);
ServerHeartbeat parse_server_heartbeat(const uint8_t* data, size_t len);
ReplayComplete parse_replay_complete(const uint8_t* data, size_t len);
NewOrder parse_new_order(const uint8_t* data, size_t len);
CancelOrder parse_cancel_order(const uint8_t* data, size_t len);
ModifyOrder parse_modify_order(const uint8_t* data, size_t len);
NewOrderCross parse_new_order_cross(const uint8_t* data, size_t len);
QuoteUpdate parse_quote_update(const uint8_t* data, size_t len);
QuoteUpdateShort parse_quote_update_short(const uint8_t* data, size_t len);
NewComplexOrder parse_new_complex_order(const uint8_t* data, size_t len);
NewComplexInstrument parse_new_complex_instrument(const uint8_t* data, size_t len);
ResetRisk parse_reset_risk(const uint8_t* data, size_t len);
PurgeOrders parse_purge_orders(const uint8_t* data, size_t len);
OrderAcknowledgment parse_order_acknowledgment(const uint8_t* data, size_t len);
OrderRejected parse_order_rejected(const uint8_t* data, size_t len);
OrderModified parse_order_modified(const uint8_t* data, size_t len);
OrderCancelled parse_order_cancelled(const uint8_t* data, size_t len);
OrderExecution parse_order_execution(const uint8_t* data, size_t len);
QuoteUpdateAcknowledgment parse_quote_update_acknowledgment(const uint8_t* data, size_t len);
RiskResetAcknowledgment parse_risk_reset_acknowledgment(const uint8_t* data, size_t len);
FloorTradeNotification parse_floor_trade_notification(const uint8_t* data, size_t len);
PurgeNotification parse_purge_notification(const uint8_t* data, size_t len);
} // namespace cboe
