#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeLoginRequest(const cboe::LoginRequest& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x37); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.session_sub_id, 4);
    append_bytes(buf, m.username, 4);
    append_bytes(buf, m.password, 10);
    append_bytes(buf, m.number_of_param_groups, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeLogoutRequest(const cboe::LogoutRequest& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x02); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeClientHeartbeat(const cboe::ClientHeartbeat& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x03); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeLoginResponse(const cboe::LoginResponse& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x24); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.login_response_status, 1);
    append_bytes(buf, m.login_response_text, 60);
    append_bytes(buf, m.no_unspecified_unit_replay, 1);
    append_bytes(buf, m.last_received_sequence_number, 4);
    append_bytes(buf, m.number_of_units, 1);
    append_bytes(buf, m.number_of_param_groups, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeLogout(const cboe::Logout& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x08); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.logout_reason, 1);
    append_bytes(buf, m.logout_reason_text, 60);
    append_bytes(buf, m.last_received_sequence_number, 4);
    append_bytes(buf, m.number_of_units, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeServerHeartbeat(const cboe::ServerHeartbeat& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x09); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeReplayComplete(const cboe::ReplayComplete& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x13); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeNewOrder(const cboe::NewOrder& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x38); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.side, 1);
    append_bytes(buf, m.order_qty, 4);
    append_bytes(buf, m.number_of_new_order_bitfields, 1);
    append_bytes(buf, m.new_order_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeCancelOrder(const cboe::CancelOrder& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x39); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.orig_cl_ord_id, 20);
    append_bytes(buf, m.number_of_cancel_order_bitfields, 1);
    append_bytes(buf, m.cancel_order_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeModifyOrder(const cboe::ModifyOrder& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x3A); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.orig_cl_ord_id, 20);
    append_bytes(buf, m.number_of_modify_order_bitfields, 1);
    append_bytes(buf, m.modify_order_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeNewOrderCross(const cboe::NewOrderCross& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x41); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.cross_id, 20);
    append_bytes(buf, m.cross_type, 1);
    append_bytes(buf, m.cross_prioritization, 1);
    append_bytes(buf, m.price, 8);
    append_bytes(buf, m.order_qty, 4);
    append_bytes(buf, m.number_of_new_order_cross_bitfields, 1);
    append_bytes(buf, m.new_order_cross_bitfield, 1);
    append_bytes(buf, m.group_cnt, 2);
    // Serialize repeating group fields
    append_bytes(buf, m.side, 1);
    append_bytes(buf, m.alloc_qty, 4);
    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.capacity, 1);
    append_bytes(buf, m.open_close, 1);
    append_bytes(buf, m.clearing_firm, 4);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeQuoteUpdate(const cboe::QuoteUpdate& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x55); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.quote_update_id, 16);
    append_bytes(buf, m.clearing_firm, 4);
    append_bytes(buf, m.clearing_account, 4);
    append_bytes(buf, m.cmta_number, 4);
    append_bytes(buf, m.account, 16);
    append_bytes(buf, m.custom_group_id, 2);
    append_bytes(buf, m.capacity, 1);
    append_bytes(buf, m.reserved, 15);
    append_uint(buf, m.send_time, 8);
    append_bytes(buf, m.posting_instruction, 1);
    append_bytes(buf, m.session_eligibility, 1);
    append_bytes(buf, m.quote_cnt, 1);
    // Serialize repeating group fields
    append_bytes(buf, m.symbol, 6);
    append_bytes(buf, m.side, 1);
    append_bytes(buf, m.open_close, 1);
    append_bytes(buf, m.price, 8);
    append_bytes(buf, m.order_qty, 4);
    append_bytes(buf, m.reserved, 2);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeQuoteUpdateShort(const cboe::QuoteUpdateShort& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x59); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.quote_update_id, 16);
    append_bytes(buf, m.clearing_firm, 4);
    append_bytes(buf, m.clearing_account, 4);
    append_bytes(buf, m.custom_group_id, 2);
    append_bytes(buf, m.capacity, 1);
    append_bytes(buf, m.reserved, 3);
    append_uint(buf, m.send_time, 8);
    append_bytes(buf, m.posting_instruction, 1);
    append_bytes(buf, m.session_eligibility, 1);
    append_bytes(buf, m.quote_cnt, 1);
    // Serialize repeating group fields
    append_bytes(buf, m.symbol, 6);
    append_bytes(buf, m.side, 1);
    append_bytes(buf, m.open_close, 1);
    append_bytes(buf, m.price, 4);
    append_bytes(buf, m.order_qty, 2);
    append_bytes(buf, m.reserved, 2);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeNewComplexOrder(const cboe::NewComplexOrder& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x4B); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.side, 1);
    append_bytes(buf, m.order_qty, 4);
    append_bytes(buf, m.number_of_new_complex_order_bitfields, 1);
    append_bytes(buf, m.new_complex_order_bitfield, 1);
    append_bytes(buf, m.no_legs, 1);
    // Serialize repeating group fields
    append_bytes(buf, m.leg_position_effect, 1);
    append_bytes(buf, m.symbol, 8);
    append_bytes(buf, m.price, 8);
    append_bytes(buf, m.order_qty, 4);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeNewComplexInstrument(const cboe::NewComplexInstrument& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x4C); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.number_of_new_complex_instrument_bitfields, 1);
    append_bytes(buf, m.new_complex_instrument_bitfield, 1);
    append_bytes(buf, m.no_legs, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeResetRisk(const cboe::ResetRisk& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x56); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.risk_status_id, 16);
    append_bytes(buf, m.risk_reset, 8);
    append_bytes(buf, m.target_matching_unit, 1);
    append_bytes(buf, m.reserved, 3);
    append_bytes(buf, m.clearing_firm, 4);
    append_bytes(buf, m.risk_root, 6);
    append_bytes(buf, m.custom_group_id, 2);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializePurgeOrders(const cboe::PurgeOrders& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x47); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.reserved, 1);
    append_bytes(buf, m.number_of_purge, 1);
    append_bytes(buf, m.purge_orders_bitfields, 1);
    append_bytes(buf, m.custom_group_id_cnt, 1);
    append_bytes(buf, m.clearing_firm, 4);
    append_bytes(buf, m.mass_cancel_inst, 20);
    append_bytes(buf, m.risk_root, 6);
    append_bytes(buf, m.mass_cancel_id, 20);
    append_uint(buf, m.send_time, 8);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeOrderAcknowledgment(const cboe::OrderAcknowledgment& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x25); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_uint(buf, m.transaction_time, 8);
    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.order_id, 8);
    append_bytes(buf, m.reserved_internal, 1);
    append_bytes(buf, m.number_of_return_bitfields, 1);
    append_bytes(buf, m.return_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeOrderRejected(const cboe::OrderRejected& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x26); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_uint(buf, m.transaction_time, 8);
    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.order_reject_reason, 1);
    append_bytes(buf, m.text, 60);
    append_bytes(buf, m.reserved_internal, 1);
    append_bytes(buf, m.number_of_return_bitfields, 1);
    append_bytes(buf, m.return_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeOrderModified(const cboe::OrderModified& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x27); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_uint(buf, m.transaction_time, 8);
    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.order_id, 8);
    append_bytes(buf, m.orig_cl_ord_id, 20);
    append_bytes(buf, m.number_of_return_bitfields, 1);
    append_bytes(buf, m.return_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeOrderCancelled(const cboe::OrderCancelled& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x2A); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_uint(buf, m.transaction_time, 8);
    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.order_id, 8);
    append_bytes(buf, m.cancel_reason, 1);
    append_bytes(buf, m.reserved_internal, 1);
    append_bytes(buf, m.number_of_return_bitfields, 1);
    append_bytes(buf, m.return_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeOrderExecution(const cboe::OrderExecution& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x2C); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_uint(buf, m.transaction_time, 8);
    append_bytes(buf, m.exec_id, 16);
    append_bytes(buf, m.cl_ord_id, 20);
    append_bytes(buf, m.order_id, 8);
    append_bytes(buf, m.exec_type, 1);
    append_bytes(buf, m.last_qty, 4);
    append_bytes(buf, m.last_px, 8);
    append_bytes(buf, m.leaves_qty, 4);
    append_bytes(buf, m.cum_qty, 4);
    append_bytes(buf, m.avg_px, 8);
    append_bytes(buf, m.ord_status, 1);
    append_bytes(buf, m.reserved_internal, 1);
    append_bytes(buf, m.number_of_return_bitfields, 1);
    append_bytes(buf, m.return_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeQuoteUpdateAcknowledgment(const cboe::QuoteUpdateAcknowledgment& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x51); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_uint(buf, m.transaction_time, 8);
    append_bytes(buf, m.quote_update_id, 16);
    append_bytes(buf, m.quote_reject_reason, 1);
    append_bytes(buf, m.reserved, 17);
    append_bytes(buf, m.quote_cnt, 1);
    // Serialize repeating group fields
    append_bytes(buf, m.order_id, 8);
    append_bytes(buf, m.quote_result, 1);
    append_bytes(buf, m.sub_liquidity_indicator, 1);
    append_bytes(buf, m.subreason, 1);
    append_bytes(buf, m.reserved, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeRiskResetAcknowledgment(const cboe::RiskResetAcknowledgment& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x57); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_uint(buf, m.transaction_time, 8);
    append_bytes(buf, m.risk_status_id, 16);
    append_bytes(buf, m.risk_reset, 8);
    append_bytes(buf, m.reserved_internal, 1);
    append_bytes(buf, m.number_of_return_bitfields, 1);
    append_bytes(buf, m.return_bitfield, 1);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializeFloorTradeNotification(const cboe::FloorTradeNotification& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x5C); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.trade_id, 16);
    append_bytes(buf, m.symbol, 8);
    append_bytes(buf, m.side, 1);
    append_bytes(buf, m.order_qty, 4);
    append_bytes(buf, m.price, 8);
    append_bytes(buf, m.floor_trader_acronym, 4);
    append_uint(buf, m.floor_trade_time, 8);
    append_uint(buf, m.timestamp, 8);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

#include "cboe/Serializer.h"
#include <vector>
#include "util.h"

std::vector<uint8_t> cboe::serializePurgeNotification(const cboe::PurgeNotification& m) {
    std::vector<uint8_t> buf;
    // Add framing header
    uint8_t start_bytes[] = {0xBA, 0xBA};
    buf.insert(buf.end(), start_bytes, start_bytes + 2);
    // Message length will be calculated later
    buf.resize(buf.size() + 2);
    buf.push_back(0x07); // MessageType
    buf.push_back(0); // MatchingUnit
    // SequenceNumber placeholder
    for (int i = 0; i < 4; ++i) buf.push_back(0);

    append_bytes(buf, m.port_id, 4);
    append_bytes(buf, m.purge_reason, 2);
    append_uint(buf, m.timestamp, 8);
    // Update message length
    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage
    buf[2] = (msg_len >> 8) & 0xFF;
    buf[3] = msg_len & 0xFF;
    return buf;
}

