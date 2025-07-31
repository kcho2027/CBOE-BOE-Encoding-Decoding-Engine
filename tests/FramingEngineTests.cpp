#include <gtest/gtest.h>
#include "cboe/FramingEngine.h"
#include <vector>
#include <cstdint>

namespace cboe {
namespace test {

class FramingEngineTests : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize test data
    }
};

TEST_F(FramingEngineTests, WrapMessageBasic) {
    std::vector<uint8_t> message = {0x01, 0x02, 0x03, 0x04};
    
    auto framed = FramingEngine::wrapMessage(message);
    
    // Check size
    EXPECT_EQ(framed.size(), message.size() + 4);
    
    // Check sync bytes
    EXPECT_EQ(framed[0], 0xBA);
    EXPECT_EQ(framed[1], 0xBA);
    
    // Check length (big-endian)
    uint16_t length = (framed[2] << 8) | framed[3];
    EXPECT_EQ(length, message.size());
    
    // Check message content
    for (size_t i = 0; i < message.size(); ++i) {
        EXPECT_EQ(framed[i + 4], message[i]);
    }
}

TEST_F(FramingEngineTests, WrapMessageEmpty) {
    std::vector<uint8_t> message;
    
    auto framed = FramingEngine::wrapMessage(message);
    
    EXPECT_EQ(framed.size(), 4);
    EXPECT_EQ(framed[0], 0xBA);
    EXPECT_EQ(framed[1], 0xBA);
    EXPECT_EQ(framed[2], 0x00);
    EXPECT_EQ(framed[3], 0x00);
}

TEST_F(FramingEngineTests, WrapMessageLarge) {
    std::vector<uint8_t> message(1000, 0x42);
    
    auto framed = FramingEngine::wrapMessage(message);
    
    EXPECT_EQ(framed.size(), 1004);
    EXPECT_EQ(framed[0], 0xBA);
    EXPECT_EQ(framed[1], 0xBA);
    
    uint16_t length = (framed[2] << 8) | framed[3];
    EXPECT_EQ(length, 1000);
}

TEST_F(FramingEngineTests, UnwrapMessageValid) {
    std::vector<uint8_t> original = {0x01, 0x02, 0x03, 0x04, 0x05};
    auto framed = FramingEngine::wrapMessage(original);
    
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(framed.data(), framed.size(), unwrapped);
    
    EXPECT_TRUE(success);
    EXPECT_EQ(unwrapped, original);
}

TEST_F(FramingEngineTests, UnwrapMessageInvalidSyncBytes) {
    std::vector<uint8_t> invalid_data = {0x00, 0x00, 0x00, 0x04, 0x01, 0x02, 0x03, 0x04};
    
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(invalid_data.data(), invalid_data.size(), unwrapped);
    
    EXPECT_FALSE(success);
}

TEST_F(FramingEngineTests, UnwrapMessageTooShort) {
    std::vector<uint8_t> short_data = {0xBA, 0xBA};
    
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(short_data.data(), short_data.size(), unwrapped);
    
    EXPECT_FALSE(success);
}

TEST_F(FramingEngineTests, UnwrapMessageIncompleteLength) {
    std::vector<uint8_t> incomplete_data = {0xBA, 0xBA, 0x00};
    
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(incomplete_data.data(), incomplete_data.size(), unwrapped);
    
    EXPECT_FALSE(success);
}

TEST_F(FramingEngineTests, UnwrapMessageLengthMismatch) {
    std::vector<uint8_t> data = {0xBA, 0xBA, 0x00, 0x10, 0x01, 0x02, 0x03, 0x04};
    // Length says 16 bytes but only 4 bytes of data
    
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(data.data(), data.size(), unwrapped);
    
    EXPECT_FALSE(success);
}

TEST_F(FramingEngineTests, RoundTripTest) {
    std::vector<uint8_t> original = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    
    // Wrap
    auto framed = FramingEngine::wrapMessage(original);
    
    // Unwrap
    std::vector<uint8_t> unwrapped;
    bool success = FramingEngine::unwrapMessage(framed.data(), framed.size(), unwrapped);
    
    EXPECT_TRUE(success);
    EXPECT_EQ(unwrapped, original);
}

TEST_F(FramingEngineTests, MultipleRoundTrips) {
    std::vector<std::vector<uint8_t>> test_messages = {
        {0x01},
        {0x01, 0x02, 0x03},
        {0x01, 0x02, 0x03, 0x04, 0x05},
        std::vector<uint8_t>(100, 0x42),
        std::vector<uint8_t>(1000, 0xAA)
    };
    
    for (const auto& message : test_messages) {
        auto framed = FramingEngine::wrapMessage(message);
        std::vector<uint8_t> unwrapped;
        bool success = FramingEngine::unwrapMessage(framed.data(), framed.size(), unwrapped);
        
        EXPECT_TRUE(success) << "Failed for message of size " << message.size();
        EXPECT_EQ(unwrapped, message) << "Round-trip failed for message of size " << message.size();
    }
}

} // namespace test
} // namespace cboe 