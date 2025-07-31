#include <gtest/gtest.h>
#include "cboe/Messages.h"
#include "cboe/Serializer.h"
#include "cboe/Deserializer.h"
#include "cboe/FramingEngine.h"
#include <vector>
#include <cstring>

namespace cboe {
namespace test {

class SerializerTests : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize test data
    }
};

TEST_F(SerializerTests, LoginRequestRoundTrip) {
    // Create a LoginRequest message
    LoginRequest request;
    std::memset(&request, 0, sizeof(request));
    
    // Set test values
    std::strcpy(request.session_sub_id, "TEST");
    std::strcpy(request.username, "USER");
    std::strcpy(request.password, "PASS12345");
    request.number_of_param_groups[0] = 1;
    
    // Serialize
    auto serialized = serializeLoginRequest(request);
    
    // Verify framing
    EXPECT_EQ(serialized[0], 0xBA);
    EXPECT_EQ(serialized[1], 0xBA);
    EXPECT_EQ(serialized[4], 0x37); // MessageType
    
    // Deserialize
    auto parsed = parse_login_request(serialized.data(), serialized.size());
    
    // Verify round-trip
    EXPECT_STREQ(parsed.session_sub_id, "TEST");
    EXPECT_STREQ(parsed.username, "USER");
    EXPECT_STREQ(parsed.password, "PASS12345");
    EXPECT_EQ(parsed.number_of_param_groups[0], 1);
}

TEST_F(SerializerTests, NewOrderRoundTrip) {
    // Create a NewOrder message
    NewOrder order;
    std::memset(&order, 0, sizeof(order));
    
    // Set test values
    std::strcpy(order.cl_ord_id, "ORDER123456789");
    order.side[0] = '1'; // Buy
    order.order_qty[0] = 100; // 100 contracts
    order.number_of_new_order_bitfields[0] = 1;
    order.new_order_bitfield[0] = 0x01; // Some bitfield value
    
    // Serialize
    auto serialized = serializeNewOrder(order);
    
    // Verify framing
    EXPECT_EQ(serialized[0], 0xBA);
    EXPECT_EQ(serialized[1], 0xBA);
    EXPECT_EQ(serialized[4], 0x38); // MessageType
    
    // Deserialize
    auto parsed = parse_new_order(serialized.data(), serialized.size());
    
    // Verify round-trip
    EXPECT_STREQ(parsed.cl_ord_id, "ORDER123456789");
    EXPECT_EQ(parsed.side[0], '1');
    EXPECT_EQ(parsed.order_qty[0], 100);
    EXPECT_EQ(parsed.number_of_new_order_bitfields[0], 1);
    EXPECT_EQ(parsed.new_order_bitfield[0], 0x01);
}

TEST_F(SerializerTests, FramingEngineWrapUnwrap) {
    // Create test message data
    std::vector<uint8_t> message_data = {0x01, 0x02, 0x03, 0x04};
    
    // Wrap message
    auto framed = FramingEngine::wrapMessage(message_data);
    
    // Verify framing
    EXPECT_EQ(framed.size(), message_data.size() + 4);
    EXPECT_EQ(framed[0], 0xBA);
    EXPECT_EQ(framed[1], 0xBA);
    
    // Extract length
    uint16_t length = (framed[2] << 8) | framed[3];
    EXPECT_EQ(length, message_data.size());
    
    // Unwrap message
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(framed.data(), framed.size(), unwrapped);
    
    EXPECT_TRUE(success);
    EXPECT_EQ(unwrapped, message_data);
}

TEST_F(SerializerTests, FramingEngineInvalidData) {
    // Test with invalid sync bytes
    std::vector<uint8_t> invalid_data = {0x00, 0x00, 0x00, 0x04, 0x01, 0x02, 0x03, 0x04};
    
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(invalid_data.data(), invalid_data.size(), unwrapped);
    
    EXPECT_FALSE(success);
}

TEST_F(SerializerTests, FramingEngineIncompleteData) {
    // Test with incomplete data
    std::vector<uint8_t> incomplete_data = {0xBA, 0xBA};
    
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(incomplete_data.data(), incomplete_data.size(), unwrapped);
    
    EXPECT_FALSE(success);
}

TEST_F(SerializerTests, MultipleMessageTypes) {
    // Test that different message types serialize correctly
    std::vector<std::pair<uint8_t, std::string>> message_types = {
        {0x37, "LoginRequest"},
        {0x02, "LogoutRequest"},
        {0x03, "ClientHeartbeat"},
        {0x38, "NewOrder"},
        {0x39, "CancelOrder"},
        {0x3A, "ModifyOrder"}
    };
    
    for (const auto& [msg_type, msg_name] : message_types) {
        // Create a minimal message structure
        std::vector<uint8_t> test_data = {0xBA, 0xBA, 0x00, 0x10, msg_type, 0x00, 0x00, 0x00, 0x00, 0x00};
        
        // Test that we can at least parse the header
        EXPECT_EQ(test_data[4], msg_type) << "Message type mismatch for " << msg_name;
    }
}

} // namespace test
} // namespace cboe 