#pragma once
#include <iostream>
#include <bitset>
#include <vector>
#include <memory>
#include <variant>

class LoginRequest
{
private:
    uint16_t startOfMessage_;  // Must be 0xBA 0xBA.
    uint16_t messageLength_;   // Number of bytes for the message, including this field but not including the two bytes for the StartOfMessage field.
    uint8_t messageType_;      // Login Request (0x37).
    uint8_t matchingUnit_;     // Always 0 for inbound (Member to Cboe) messages.
    uint32_t sequenceNumber_;  // Always 0 for session level messages.
    uint32_t sessionSubID_;    // Session Sub ID supplied by Cboe.
    uint32_t username_;        // Username supplied by Cboe.
    std::bitset<80> password_; // Password supplied by Cboe.
    struct GroupNumberOfParamGroups
    {
        uint8_t numberOfParamGroups_; // A number, n (possibly 0), of parameter groups to follow.
        struct Member
        {
            struct TypeNoUnspecifiedUnitReplay
            {
                uint8_t noUnspecifiedUnitReplay_; // Flag indicating whether to replay missed outgoing (Cboe to Member) messages for unspecified units. 0x00 = False, 0x01 = True.
                uint16_t paramGroupLength_;       // Number of bytes for the parameter group, including this field.
                uint8_t paramGroupType_;          // 0x80.
                struct GroupNumberOfUnits
                {
                    uint8_t numberOfUnits_; // Number of unit/sequence pairs to follow, one per unit from which the Member has received messages.
                    struct Member
                    {
                        uint8_t unitNumber_;    // Unit number.
                        uint32_t unitSequence_; // Last received sequence number for the unit.
                    };
                    std::unique_ptr<std::vector<Member>> members_;
                };
                GroupNumberOfUnits groupNumberOfUnits_;
            };
            std::vector<TypeNoUnspecifiedUnitReplay> typeNoUnspecifiedUnitReplayList_;
            struct TypeMessageType
            {
                uint8_t messageType_;       // Return message type for which the bitfields are being specified (e.g., 0x25 for an Order Acknowledgment message).
                uint16_t paramGroupLength_; // Number of bytes for the parameter group, including this field.
                uint8_t paramGroupType_;    // 0x80.
                struct GroupNumberOfReturnBitfields
                {
                    uint8_t numberOfReturnBitfields_; // Number of bitfields to follow.
                    struct Member
                    {
                        uint8_t returnBitfield_; // Bitfield identifying fields to return.
                    };
                    std::unique_ptr<std::vector<Member>> members_;
                };
                GroupNumberOfReturnBitfields groupNumberOfReturnBitfields_;
            };
            std::vector<TypeMessageType> typeMessageTypeList_;
        };
        std::unique_ptr<std::vector<Member>> members_;
    };
    GroupNumberOfParamGroups groupNumberOfParamGroups_;

public:
    uint16_t getStartOfMessage() const { return startOfMessage_; }
    uint16_t getMessageLength() const { return messageLength_; }
    uint8_t getMessageType() const { return messageType_; }
    uint8_t getMatchingUnit() const { return matchingUnit_; }
    uint32_t getSequenceNumber() const { return sequenceNumber_; }
    uint32_t getSessionSubID() const { return sessionSubID_; }
    uint32_t getUsername() const { return username_; }
    std::bitset<80> getPassword() const { return password_; }
    uint8_t getNumberOfParamGroups() const { return groupNumberOfParamGroups_.numberOfParamGroups_; }
    uint8_t getNoUnspecifiedUnitReplay(size_t memberIndex, ) const { return groupNumberOfParamGroups_.members_->at(memberIndex).typeNoUnspecifiedUnitReplay_.noUnspecifiedUnitReplay_; }
    uint16_t getParamGroupLength() const { return paramGroupLength_; }
    uint8_t getParamGroupType() const { return paramGroupType_; }
    uint8_t getNumberOfUnits() const { return groupNumberOfParamGroups_.members_->at(memberIndex).typeNoUnspecifiedUnitReplay_.groupNumberOfUnits_.numberOfUnits_; }
    uint8_t getUnitNumber() const { return unitNumber_; }
    uint32_t getUnitSequence() const { return unitSequence_; }
    uint8_t getMessageType(size_t memberIndex, ) const { return groupNumberOfParamGroups_.members_->at(memberIndex).typeMessageType_.messageType_; }
    uint16_t getParamGroupLength() const { return paramGroupLength_; }
    uint8_t getParamGroupType() const { return paramGroupType_; }
    uint8_t getNumberOfReturnBitfields() const { return groupNumberOfParamGroups_.members_->at(memberIndex).typeMessageType_.groupNumberOfReturnBitfields_.numberOfReturnBitfields_; }
    uint8_t getReturnBitfield() const { return returnBitfield_; }
};

int main()
{
    LoginRequest loginRequest;
    return 0;
}