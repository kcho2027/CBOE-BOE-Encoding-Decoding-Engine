#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::LoginRequest cboe::parse_login_request(const uint8_t* data, size_t len) {
    LoginRequest m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.session_sub_id, 4); pos += 4;
    read_bytes(data + pos, m.username, 4); pos += 4;
    read_bytes(data + pos, m.password, 10); pos += 10;
    read_bytes(data + pos, m.number_of_param_groups, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::LogoutRequest cboe::parse_logout_request(const uint8_t* data, size_t len) {
    LogoutRequest m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::ClientHeartbeat cboe::parse_client_heartbeat(const uint8_t* data, size_t len) {
    ClientHeartbeat m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::LoginResponse cboe::parse_login_response(const uint8_t* data, size_t len) {
    LoginResponse m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.login_response_status, 1); pos += 1;
    read_bytes(data + pos, m.login_response_text, 60); pos += 60;
    read_bytes(data + pos, m.no_unspecified_unit_replay, 1); pos += 1;
    read_bytes(data + pos, m.last_received_sequence_number, 4); pos += 4;
    read_bytes(data + pos, m.number_of_units, 1); pos += 1;
    read_bytes(data + pos, m.number_of_param_groups, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::Logout cboe::parse_logout(const uint8_t* data, size_t len) {
    Logout m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.logout_reason, 1); pos += 1;
    read_bytes(data + pos, m.logout_reason_text, 60); pos += 60;
    read_bytes(data + pos, m.last_received_sequence_number, 4); pos += 4;
    read_bytes(data + pos, m.number_of_units, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::ServerHeartbeat cboe::parse_server_heartbeat(const uint8_t* data, size_t len) {
    ServerHeartbeat m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::ReplayComplete cboe::parse_replay_complete(const uint8_t* data, size_t len) {
    ReplayComplete m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::NewOrder cboe::parse_new_order(const uint8_t* data, size_t len) {
    NewOrder m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.side, 1); pos += 1;
    read_bytes(data + pos, m.order_qty, 4); pos += 4;
    read_bytes(data + pos, m.number_of_new_order_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.new_order_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::CancelOrder cboe::parse_cancel_order(const uint8_t* data, size_t len) {
    CancelOrder m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.orig_cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.number_of_cancel_order_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.cancel_order_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::ModifyOrder cboe::parse_modify_order(const uint8_t* data, size_t len) {
    ModifyOrder m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.orig_cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.number_of_modify_order_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.modify_order_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::NewOrderCross cboe::parse_new_order_cross(const uint8_t* data, size_t len) {
    NewOrderCross m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.cross_id, 20); pos += 20;
    read_bytes(data + pos, m.cross_type, 1); pos += 1;
    read_bytes(data + pos, m.cross_prioritization, 1); pos += 1;
    read_bytes(data + pos, m.price, 8); pos += 8;
    read_bytes(data + pos, m.order_qty, 4); pos += 4;
    read_bytes(data + pos, m.number_of_new_order_cross_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.new_order_cross_bitfield, 1); pos += 1;
    read_bytes(data + pos, m.group_cnt, 2); pos += 2;
    // Deserialize repeating group fields
    read_bytes(data + pos, m.side, 1); pos += 1;
    read_bytes(data + pos, m.alloc_qty, 4); pos += 4;
    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.capacity, 1); pos += 1;
    read_bytes(data + pos, m.open_close, 1); pos += 1;
    read_bytes(data + pos, m.clearing_firm, 4); pos += 4;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::QuoteUpdate cboe::parse_quote_update(const uint8_t* data, size_t len) {
    QuoteUpdate m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.quote_update_id, 16); pos += 16;
    read_bytes(data + pos, m.clearing_firm, 4); pos += 4;
    read_bytes(data + pos, m.clearing_account, 4); pos += 4;
    read_bytes(data + pos, m.cmta_number, 4); pos += 4;
    read_bytes(data + pos, m.account, 16); pos += 16;
    read_bytes(data + pos, m.custom_group_id, 2); pos += 2;
    read_bytes(data + pos, m.capacity, 1); pos += 1;
    read_bytes(data + pos, m.reserved, 15); pos += 15;
    m.send_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.posting_instruction, 1); pos += 1;
    read_bytes(data + pos, m.session_eligibility, 1); pos += 1;
    read_bytes(data + pos, m.quote_cnt, 1); pos += 1;
    // Deserialize repeating group fields
    read_bytes(data + pos, m.symbol, 6); pos += 6;
    read_bytes(data + pos, m.side, 1); pos += 1;
    read_bytes(data + pos, m.open_close, 1); pos += 1;
    read_bytes(data + pos, m.price, 8); pos += 8;
    read_bytes(data + pos, m.order_qty, 4); pos += 4;
    read_bytes(data + pos, m.reserved, 2); pos += 2;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::QuoteUpdateShort cboe::parse_quote_update_short(const uint8_t* data, size_t len) {
    QuoteUpdateShort m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.quote_update_id, 16); pos += 16;
    read_bytes(data + pos, m.clearing_firm, 4); pos += 4;
    read_bytes(data + pos, m.clearing_account, 4); pos += 4;
    read_bytes(data + pos, m.custom_group_id, 2); pos += 2;
    read_bytes(data + pos, m.capacity, 1); pos += 1;
    read_bytes(data + pos, m.reserved, 3); pos += 3;
    m.send_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.posting_instruction, 1); pos += 1;
    read_bytes(data + pos, m.session_eligibility, 1); pos += 1;
    read_bytes(data + pos, m.quote_cnt, 1); pos += 1;
    // Deserialize repeating group fields
    read_bytes(data + pos, m.symbol, 6); pos += 6;
    read_bytes(data + pos, m.side, 1); pos += 1;
    read_bytes(data + pos, m.open_close, 1); pos += 1;
    read_bytes(data + pos, m.price, 4); pos += 4;
    read_bytes(data + pos, m.order_qty, 2); pos += 2;
    read_bytes(data + pos, m.reserved, 2); pos += 2;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::NewComplexOrder cboe::parse_new_complex_order(const uint8_t* data, size_t len) {
    NewComplexOrder m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.side, 1); pos += 1;
    read_bytes(data + pos, m.order_qty, 4); pos += 4;
    read_bytes(data + pos, m.number_of_new_complex_order_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.new_complex_order_bitfield, 1); pos += 1;
    read_bytes(data + pos, m.no_legs, 1); pos += 1;
    // Deserialize repeating group fields
    read_bytes(data + pos, m.leg_position_effect, 1); pos += 1;
    read_bytes(data + pos, m.symbol, 8); pos += 8;
    read_bytes(data + pos, m.price, 8); pos += 8;
    read_bytes(data + pos, m.order_qty, 4); pos += 4;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::NewComplexInstrument cboe::parse_new_complex_instrument(const uint8_t* data, size_t len) {
    NewComplexInstrument m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.number_of_new_complex_instrument_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.new_complex_instrument_bitfield, 1); pos += 1;
    read_bytes(data + pos, m.no_legs, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::ResetRisk cboe::parse_reset_risk(const uint8_t* data, size_t len) {
    ResetRisk m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.risk_status_id, 16); pos += 16;
    read_bytes(data + pos, m.risk_reset, 8); pos += 8;
    read_bytes(data + pos, m.target_matching_unit, 1); pos += 1;
    read_bytes(data + pos, m.reserved, 3); pos += 3;
    read_bytes(data + pos, m.clearing_firm, 4); pos += 4;
    read_bytes(data + pos, m.risk_root, 6); pos += 6;
    read_bytes(data + pos, m.custom_group_id, 2); pos += 2;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::PurgeOrders cboe::parse_purge_orders(const uint8_t* data, size_t len) {
    PurgeOrders m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.reserved, 1); pos += 1;
    read_bytes(data + pos, m.number_of_purge, 1); pos += 1;
    read_bytes(data + pos, m.purge_orders_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.custom_group_id_cnt, 1); pos += 1;
    read_bytes(data + pos, m.clearing_firm, 4); pos += 4;
    read_bytes(data + pos, m.mass_cancel_inst, 20); pos += 20;
    read_bytes(data + pos, m.risk_root, 6); pos += 6;
    read_bytes(data + pos, m.mass_cancel_id, 20); pos += 20;
    m.send_time = read_uint(data + pos, 8); pos += 8;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::OrderAcknowledgment cboe::parse_order_acknowledgment(const uint8_t* data, size_t len) {
    OrderAcknowledgment m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    m.transaction_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.order_id, 8); pos += 8;
    read_bytes(data + pos, m.reserved_internal, 1); pos += 1;
    read_bytes(data + pos, m.number_of_return_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.return_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::OrderRejected cboe::parse_order_rejected(const uint8_t* data, size_t len) {
    OrderRejected m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    m.transaction_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.order_reject_reason, 1); pos += 1;
    read_bytes(data + pos, m.text, 60); pos += 60;
    read_bytes(data + pos, m.reserved_internal, 1); pos += 1;
    read_bytes(data + pos, m.number_of_return_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.return_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::OrderModified cboe::parse_order_modified(const uint8_t* data, size_t len) {
    OrderModified m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    m.transaction_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.order_id, 8); pos += 8;
    read_bytes(data + pos, m.orig_cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.number_of_return_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.return_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::OrderCancelled cboe::parse_order_cancelled(const uint8_t* data, size_t len) {
    OrderCancelled m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    m.transaction_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.order_id, 8); pos += 8;
    read_bytes(data + pos, m.cancel_reason, 1); pos += 1;
    read_bytes(data + pos, m.reserved_internal, 1); pos += 1;
    read_bytes(data + pos, m.number_of_return_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.return_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::OrderExecution cboe::parse_order_execution(const uint8_t* data, size_t len) {
    OrderExecution m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    m.transaction_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.exec_id, 16); pos += 16;
    read_bytes(data + pos, m.cl_ord_id, 20); pos += 20;
    read_bytes(data + pos, m.order_id, 8); pos += 8;
    read_bytes(data + pos, m.exec_type, 1); pos += 1;
    read_bytes(data + pos, m.last_qty, 4); pos += 4;
    read_bytes(data + pos, m.last_px, 8); pos += 8;
    read_bytes(data + pos, m.leaves_qty, 4); pos += 4;
    read_bytes(data + pos, m.cum_qty, 4); pos += 4;
    read_bytes(data + pos, m.avg_px, 8); pos += 8;
    read_bytes(data + pos, m.ord_status, 1); pos += 1;
    read_bytes(data + pos, m.reserved_internal, 1); pos += 1;
    read_bytes(data + pos, m.number_of_return_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.return_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::QuoteUpdateAcknowledgment cboe::parse_quote_update_acknowledgment(const uint8_t* data, size_t len) {
    QuoteUpdateAcknowledgment m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    m.transaction_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.quote_update_id, 16); pos += 16;
    read_bytes(data + pos, m.quote_reject_reason, 1); pos += 1;
    read_bytes(data + pos, m.reserved, 17); pos += 17;
    read_bytes(data + pos, m.quote_cnt, 1); pos += 1;
    // Deserialize repeating group fields
    read_bytes(data + pos, m.order_id, 8); pos += 8;
    read_bytes(data + pos, m.quote_result, 1); pos += 1;
    read_bytes(data + pos, m.sub_liquidity_indicator, 1); pos += 1;
    read_bytes(data + pos, m.subreason, 1); pos += 1;
    read_bytes(data + pos, m.reserved, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::RiskResetAcknowledgment cboe::parse_risk_reset_acknowledgment(const uint8_t* data, size_t len) {
    RiskResetAcknowledgment m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    m.transaction_time = read_uint(data + pos, 8); pos += 8;
    read_bytes(data + pos, m.risk_status_id, 16); pos += 16;
    read_bytes(data + pos, m.risk_reset, 8); pos += 8;
    read_bytes(data + pos, m.reserved_internal, 1); pos += 1;
    read_bytes(data + pos, m.number_of_return_bitfields, 1); pos += 1;
    read_bytes(data + pos, m.return_bitfield, 1); pos += 1;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::FloorTradeNotification cboe::parse_floor_trade_notification(const uint8_t* data, size_t len) {
    FloorTradeNotification m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.trade_id, 16); pos += 16;
    read_bytes(data + pos, m.symbol, 8); pos += 8;
    read_bytes(data + pos, m.side, 1); pos += 1;
    read_bytes(data + pos, m.order_qty, 4); pos += 4;
    read_bytes(data + pos, m.price, 8); pos += 8;
    read_bytes(data + pos, m.floor_trader_acronym, 4); pos += 4;
    m.floor_trade_time = read_uint(data + pos, 8); pos += 8;
    m.timestamp = read_uint(data + pos, 8); pos += 8;
    return m;
}

#include "cboe/Deserializer.h"
#include "util.h"
#include <vector>

cboe::PurgeNotification cboe::parse_purge_notification(const uint8_t* data, size_t len) {
    PurgeNotification m;
    size_t pos = 0;
    // Skip framing header
    pos += 2; // StartOfMessage
    pos += 2; // MessageLength
    pos += 1; // MessageType
    pos += 1; // MatchingUnit
    pos += 4; // SequenceNumber

    read_bytes(data + pos, m.port_id, 4); pos += 4;
    read_bytes(data + pos, m.purge_reason, 2); pos += 2;
    m.timestamp = read_uint(data + pos, 8); pos += 8;
    return m;
}

