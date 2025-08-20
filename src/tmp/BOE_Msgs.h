#pragma once
#include <iostream>
#include <bitset>
#include <vector>
#include <memory>
#include <variant>

class LoginRequest
{
private:
    uint16_t startOfMessage_; //
    uint16_t messageLength_;  // Number of bytes for the message, including this field but not including the two bytes for the StartOfMessage field.
    struct Group_NumberOfParamGroups
    {
        uint8_t numberOfParamGroups_; // A number, n (possibly 0), of parameter groups to follow.
        struct Member
        {
            struct Type_NoUnspecifiedUnitReplay
            {
                uint16_t paramGroupLength_;       // Number of bytes for the parameter group, including this field.
                uint8_t paramGroupType_;          // 0x80.
                uint8_t noUnspecifiedUnitReplay_; // Flag indicating whether to replay missed outgoing (Cboe to Member) messages for unspecified units. 0x00 = False, 0x01 = True.
                struct Group_NumberOfUnits
                {
                    uint8_t numberOfUnits_; // Number of unit/sequence pairs to follow, one per unit from which the Member has received messages.
                    struct Member
                    {
                        uint8_t unitNumber_;    // Unit number.
                        uint32_t unitSequence_; // Last received sequence number for the unit.
                    };
                    std::unique_ptr<std::vector<Member>> members_;
                };
                Group_NumberOfUnits group_NumberOfUnits_;
            };
            struct Type_MessageType
            {
                uint16_t paramGroupLength_; // Number of bytes for the parameter group, including this field.
                uint8_t paramGroupType_;    // 0x80.
                uint8_t messageType_;       // Return message type for which the bitfields are being specified (e.g., 0x25 for an Order Acknowledgment message).
                struct Group_NumberOfReturnBitfields
                {
                    uint8_t numberOfReturnBitfields_; // Number of bitfields to follow.
                    struct Member
                    {
                        uint8_t returnBitfield_; // Bitfield identifying fields to return.
                    };
                    std::unique_ptr<std::vector<Member>> members_;
                };
                Group_NumberOfReturnBitfields group_NumberOfReturnBitfields_;
            };
            std::variant<
                Type_NoUnspecifiedUnitReplay,
                Type_MessageType>
                type_;
        };
        std::unique_ptr<std::vector<Member>> members_;
    };
    Group_NumberOfParamGroups group_NumberOfParamGroups_;

public:
    uint16_t getStartOfMessage() const { return startOfMessage_; }
    void setStartOfMessage(uint16_t startOfMessage) { startOfMessage_ = startOfMessage; };

    uint16_t getMessageLength() const { return messageLength_; }
    void setMessageLength(uint16_t messageLength) { messageLength_ = messageLength; };

    uint8_t getNumberOfParamGroups() const { return group_NumberOfParamGroups_.numberOfParamGroups_; }
    void setNumberOfParamGroups(uint8_t numberOfParamGroups) { group_NumberOfParamGroups_.numberOfParamGroups_ = numberOfParamGroups; }
};

int main()
{
    LoginRequest loginRequest;
    return 0;
}

// convert the code into render_group, render_types, etc etc.
// can remove  //using loop.last ig, try it out later.