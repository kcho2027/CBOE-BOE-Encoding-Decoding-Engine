#pragma once
#include <cstdint>
#include <array>

namespace cboe {

// Generated struct for LoginRequest
struct LoginRequest {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x37
    uint8_t matching_unit[1]; // Always 0 for inbound session messages
    uint8_t sequence_number[4]; // Always 0 for session messages
    char session_sub_id[4]; // Session Sub ID supplied by Cboe
    char username[4]; // Username supplied by Cboe
    char password[10]; // Password supplied by Cboe
    uint8_t number_of_param_groups[1]; // Number of parameter groups to follow
};

// Generated struct for LogoutRequest
struct LogoutRequest {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x02
    uint8_t matching_unit[1]; // Always 0 for inbound session messages
    uint8_t sequence_number[4]; // Always 0 for session messages
};

// Generated struct for ClientHeartbeat
struct ClientHeartbeat {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x03
    uint8_t matching_unit[1]; // Always 0 for inbound session messages
    uint8_t sequence_number[4]; // Always 0 for session messages
};

// Generated struct for LoginResponse
struct LoginResponse {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x24
    uint8_t matching_unit[1]; // Always 0 for session messages
    uint8_t sequence_number[4]; // Always 0 for session messages
    char login_response_status[1]; // A=Accepted, N=Not authorized, D=Disabled, B=In use, S=Invalid session, Q=Seq ahead, I=Invalid unit, F=Invalid bitfield, M=Bad structure
    char login_response_text[60]; // Human-readable status or failure reason (ASCII NUL-padded)
    uint8_t no_unspecified_unit_replay[1]; // Echoed NoUnspec flag from request
    uint8_t last_received_sequence_number[4]; // Last inbound msg seq processed by Cboe
    uint8_t number_of_units[1]; // Number of unit/sequence pairs to follow
    uint8_t number_of_param_groups[1]; // Echoed from LoginRequest
};

// Generated struct for Logout
struct Logout {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x08
    uint8_t matching_unit[1]; // Always 0 for session messages
    uint8_t sequence_number[4]; // Always 0 for session messages
    char logout_reason[1]; // U=User, E=EOD, A=Admin, !=Protocol Violation
    char logout_reason_text[60]; // Free-form reason if Protocol Violation
    uint8_t last_received_sequence_number[4]; // Last inbound msg seq processed by Cboe
    uint8_t number_of_units[1]; // Number of unit/sequence pairs to follow
};

// Generated struct for ServerHeartbeat
struct ServerHeartbeat {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x09
    uint8_t matching_unit[1]; // Always 0 for inbound session messages
    uint8_t sequence_number[4]; // Always 0 for session messages
};

// Generated struct for ReplayComplete
struct ReplayComplete {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x13
    uint8_t matching_unit[1]; // Always 0 for inbound session messages
    uint8_t sequence_number[4]; // Always 0 for session messages
};

// Generated struct for NewOrder
struct NewOrder {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x38
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char cl_ord_id[20]; // Client order ID
    char side[1]; // 1=Buy, 2=Sell
    uint8_t order_qty[4]; // Contract quantity
    uint8_t number_of_new_order_bitfields[1]; // Count of bitfields to follow
    uint8_t new_order_bitfield[1]; // Each bitfield flags an optional field
};

// Generated struct for CancelOrder
struct CancelOrder {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x39
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char orig_cl_ord_id[20]; // ClOrdID of order to cancel; all zeros for mass cancel
    uint8_t number_of_cancel_order_bitfields[1]; // Count of bitfields to follow
    uint8_t cancel_order_bitfield[1]; // Each bitfield flags an optional field
};

// Generated struct for ModifyOrder
struct ModifyOrder {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x3A
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char cl_ord_id[20]; // Client order ID
    char orig_cl_ord_id[20]; // Original client order ID
    uint8_t number_of_modify_order_bitfields[1]; // Count of bitfields to follow
    uint8_t modify_order_bitfield[1]; // Each bitfield flags an optional field
};

// Generated struct for NewOrderCross
struct NewOrderCross {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x41
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char cross_id[20]; // Cross identifier
    char cross_type[1]; // Cross type
    char cross_prioritization[1]; // Agency side priority
    uint8_t price[8]; // Cross price
    uint8_t order_qty[4]; // Total quantity
    uint8_t number_of_new_order_cross_bitfields[1]; // Count of bitfields to follow
    uint8_t new_order_cross_bitfield[1]; // Each bitfield flags an optional field
    uint8_t group_cnt[2]; // Number of legs in the cross
    // Repeating group fields
    char side[1]; // 1=Buy, 2=Sell
    uint8_t alloc_qty[4]; // Quantity for this leg
    char cl_ord_id[20]; // Client order ID for this leg
    char capacity[1]; // Order capacity
    char open_close[1]; // O=Open, C=Close
    char clearing_firm[4]; // Clearing firm
};

// Generated struct for QuoteUpdate
struct QuoteUpdate {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x55
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char quote_update_id[16]; // Quote update identifier
    char clearing_firm[4]; // Clearing firm
    char clearing_account[4]; // Clearing account
    uint8_t cmta_number[4]; // CMTA number
    char account[16]; // Account
    uint8_t custom_group_id[2]; // Custom group ID
    char capacity[1]; // Order capacity
    uint8_t reserved[15]; // Reserved field
    uint64_t send_time; // Send time
    char posting_instruction[1]; // Posting instruction
    char session_eligibility[1]; // Session eligibility
    uint8_t quote_cnt[1]; // Number of quotes
    // Repeating group fields
    char symbol[6]; // Symbol
    char side[1]; // Side
    char open_close[1]; // Open/Close
    uint8_t price[8]; // Price
    uint8_t order_qty[4]; // Order quantity
    uint8_t reserved_1[2]; // Reserved field
};

// Generated struct for QuoteUpdateShort
struct QuoteUpdateShort {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x59
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char quote_update_id[16]; // Quote update identifier
    char clearing_firm[4]; // Clearing firm
    char clearing_account[4]; // Clearing account
    uint8_t custom_group_id[2]; // Custom group ID
    char capacity[1]; // Order capacity
    uint8_t reserved[3]; // Reserved field
    uint64_t send_time; // Send time
    char posting_instruction[1]; // Posting instruction
    char session_eligibility[1]; // Session eligibility
    uint8_t quote_cnt[1]; // Number of quotes
    // Repeating group fields
    char symbol[6]; // Symbol
    char side[1]; // Side
    char open_close[1]; // Open/Close
    uint8_t price[4]; // Price
    uint8_t order_qty[2]; // Order quantity
    uint8_t reserved_1[2]; // Reserved field
};

// Generated struct for NewComplexOrder
struct NewComplexOrder {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message, incl. this field (excl. StartOfMessage)
    uint8_t message_type[1]; // 0x4B
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char cl_ord_id[20]; // Client order ID
    char side[1]; // 1=Buy, 2=Sell
    uint8_t order_qty[4]; // Contract quantity
    uint8_t number_of_new_complex_order_bitfields[1]; // Count of bitfields to follow
    uint8_t new_complex_order_bitfield[1]; // Each bitfield flags an optional field
    uint8_t no_legs[1]; // Number of repeating ComplexLeg groups (2–16)
    // Repeating group fields
    char leg_position_effect[1]; // O=Open, C=Close, N=None
    char symbol[8]; // Leg symbol (OSI or Cboe format)
    uint8_t price[8]; // Leg price
    uint8_t order_qty_1[4]; // Leg quantity
};

// Generated struct for NewComplexInstrument
struct NewComplexInstrument {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x4C
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char cl_ord_id[20]; // Client order ID
    uint8_t number_of_new_complex_instrument_bitfields[1]; // Count of bitfields to follow
    uint8_t new_complex_instrument_bitfield[1]; // Each bitfield flags an optional field
    uint8_t no_legs[1]; // Number of legs
};

// Generated struct for ResetRisk
struct ResetRisk {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x56
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    char risk_status_id[16]; // Risk status ID
    char risk_reset[8]; // Risk reset
    uint8_t target_matching_unit[1]; // Target matching unit
    uint8_t reserved[3]; // Reserved field
    char clearing_firm[4]; // Clearing firm
    char risk_root[6]; // Risk root
    uint8_t custom_group_id[2]; // Custom group ID
};

// Generated struct for PurgeOrders
struct PurgeOrders {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x47
    uint8_t matching_unit[1]; // Always 0 for inbound
    uint8_t sequence_number[4]; // Inbound message sequence
    uint8_t reserved[1]; // Reserved field
    uint8_t number_of_purge[1]; // Number of purge orders
    uint8_t purge_orders_bitfields[1]; // Purge order bitfields
    uint8_t custom_group_id_cnt[1]; // Custom group ID count
    char clearing_firm[4]; // Clearing firm
    char mass_cancel_inst[20]; // Mass cancel instruction
    char risk_root[6]; // Risk root
    char mass_cancel_id[20]; // Mass cancel ID
    uint64_t send_time; // Send time
};

// Generated struct for OrderAcknowledgment
struct OrderAcknowledgment {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x25
    uint8_t matching_unit[1]; // Matching unit ID
    uint8_t sequence_number[4]; // Per-unit seq no.
    uint64_t transaction_time; // Engine event time
    char cl_ord_id[20]; // Echoed client ID
    uint8_t order_id[8]; // Order ID assigned by engine
    uint8_t reserved_internal[1]; // Reserved (ignore)
    uint8_t number_of_return_bitfields[1]; // Count of return bitfields
    uint8_t return_bitfield[1]; // Each bitfield flags an optional field returned
};

// Generated struct for OrderRejected
struct OrderRejected {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x26
    uint8_t matching_unit[1]; // Always 0 (unsequenced)
    uint8_t sequence_number[4]; // Always 0
    uint64_t transaction_time; // Engine event time
    char cl_ord_id[20]; // Client order ID
    char order_reject_reason[1]; // Reject reason
    char text[60]; // Human-readable reason
    uint8_t reserved_internal[1]; // Reserved (ignore)
    uint8_t number_of_return_bitfields[1]; // Count of return bitfields
    uint8_t return_bitfield[1]; // Each bitfield flags an optional field returned
};

// Generated struct for OrderModified
struct OrderModified {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x27
    uint8_t matching_unit[1]; // Matching unit ID
    uint8_t sequence_number[4]; // Per-unit seq no.
    uint64_t transaction_time; // Engine event time
    char cl_ord_id[20]; // Client order ID
    uint8_t order_id[8]; // Order ID assigned by engine
    char orig_cl_ord_id[20]; // Original client order ID
    uint8_t number_of_return_bitfields[1]; // Count of return bitfields
    uint8_t return_bitfield[1]; // Each bitfield flags an optional field returned
};

// Generated struct for OrderCancelled
struct OrderCancelled {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x2A
    uint8_t matching_unit[1]; // Matching unit ID
    uint8_t sequence_number[4]; // Per-unit seq no.
    uint64_t transaction_time; // Engine event time
    char cl_ord_id[20]; // Client order ID
    uint8_t order_id[8]; // Order ID assigned by engine
    char cancel_reason[1]; // Cancel reason
    uint8_t reserved_internal[1]; // Reserved (ignore)
    uint8_t number_of_return_bitfields[1]; // Count of return bitfields
    uint8_t return_bitfield[1]; // Each bitfield flags an optional field returned
};

// Generated struct for OrderExecution
struct OrderExecution {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x2C
    uint8_t matching_unit[1]; // Matching unit ID
    uint8_t sequence_number[4]; // Per-unit seq no.
    uint64_t transaction_time; // Engine event time
    char exec_id[16]; // Execution ID
    char cl_ord_id[20]; // Client order ID
    uint8_t order_id[8]; // Order ID assigned by engine
    char exec_type[1]; // Execution type
    uint8_t last_qty[4]; // Last quantity
    uint8_t last_px[8]; // Last price
    uint8_t leaves_qty[4]; // Leaves quantity
    uint8_t cum_qty[4]; // Cumulative quantity
    uint8_t avg_px[8]; // Average price
    char ord_status[1]; // Order status
    uint8_t reserved_internal[1]; // Reserved (ignore)
    uint8_t number_of_return_bitfields[1]; // Count of return bitfields
    uint8_t return_bitfield[1]; // Each bitfield flags an optional field returned
};

// Generated struct for QuoteUpdateAcknowledgment
struct QuoteUpdateAcknowledgment {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x51
    uint8_t matching_unit[1]; // Always 0
    uint8_t sequence_number[4]; // Always 0
    uint64_t transaction_time; // Engine event time
    char quote_update_id[16]; // Quote update ID
    char quote_reject_reason[1]; // Quote reject reason
    uint8_t reserved[17]; // Reserved field
    uint8_t quote_cnt[1]; // Number of quotes
    // Repeating group fields
    uint8_t order_id[8]; // Order ID
    char quote_result[1]; // Quote result
    char sub_liquidity_indicator[1]; // Sub liquidity indicator
    char subreason[1]; // Sub reason
    uint8_t reserved_1[1]; // Reserved field
};

// Generated struct for RiskResetAcknowledgment
struct RiskResetAcknowledgment {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x57
    uint8_t matching_unit[1]; // Matching unit ID
    uint8_t sequence_number[4]; // Per-unit seq no.
    uint64_t transaction_time; // Engine event time
    char risk_status_id[16]; // Risk status ID
    char risk_reset[8]; // Risk reset
    uint8_t reserved_internal[1]; // Reserved (ignore)
    uint8_t number_of_return_bitfields[1]; // Count of return bitfields
    uint8_t return_bitfield[1]; // Each bitfield flags an optional field returned
};

// Generated struct for FloorTradeNotification
struct FloorTradeNotification {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x5C
    uint8_t matching_unit[1]; // Matching unit ID
    uint8_t sequence_number[4]; // Per-unit seq no.
    char trade_id[16]; // Trade ID
    char symbol[8]; // Symbol
    char side[1]; // Side
    uint8_t order_qty[4]; // Order quantity
    uint8_t price[8]; // Price
    char floor_trader_acronym[4]; // Floor trader acronym
    uint64_t floor_trade_time; // Floor trade time
    uint64_t timestamp; // Timestamp
};

// Generated struct for PurgeNotification
struct PurgeNotification {
    uint8_t start_of_message[2]; // Must be 0xBA 0xBA
    uint8_t message_length[2]; // Bytes in message (incl. this field)
    uint8_t message_type[1]; // 0x07
    uint8_t matching_unit[1]; // Matching unit ID
    uint8_t sequence_number[4]; // Per-unit seq no.
    char port_id[4]; // Port ID
    char purge_reason[2]; // Purge reason
    uint64_t timestamp; // Timestamp
};

} // namespace cboe
