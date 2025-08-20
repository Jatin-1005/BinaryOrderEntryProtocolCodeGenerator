// HandWritten File can make any changes to this, won't be affected by generation process.

#pragma once
#include <iostream>
#include <bitset>
#include <vector>
#include <memory>
#include <variant>
struct GroupNumberOfParamGroups
{
    uint8_t numberOfParamGroups_; // A number, n (possibly 0), of parameter groups to follow.
    struct Member
    {
    private:
        struct TypeNoUnspecifiedUnitReplay
        {
        private:
            uint8_t noUnspecifiedUnitReplay_; // Flag indicating whether to replay missed outgoing (Cboe to Member) messages for unspecified units. 0x00 = False, 0x01 = True.
            uint16_t paramGroupLength_;       // Number of bytes for the parameter group, including this field.
            uint8_t paramGroupType_;          // 0x80.
            struct GroupNumberOfUnits
            {
            private:
                uint8_t numberOfUnits_; // Number of unit/sequence pairs to follow, one per unit from which the Member has received messages.
                struct Member
                {
                private:
                    uint8_t unitNumber_;    // Unit number.
                    uint32_t unitSequence_; // Last received sequence number for the unit.
                public:
                    uint8_t getUnitNumber() const { return unitNumber_; }
                    uint32_t getUnitSequence() const { return unitSequence_; }
                };
                std::unique_ptr<std::vector<Member>> members_;

            public:
                uint8_t getNumberOfUnits() const { return numberOfUnits_; }
                uint8_t getUnitNumber(size_t memberIndex) const { return members_->at(memberIndex).getUnitNumber(); }
                uint32_t getUnitSequence(size_t memberIndex) const { return members_->at(memberIndex).getUnitSequence(); }
            };
            GroupNumberOfUnits groupNumberOfUnits_;

        public:
            uint8_t getNoUnspecifiedUnitReplay() const { return noUnspecifiedUnitReplay_; };
            uint16_t getParamGroupLength() const { return paramGroupLength_; };
            uint8_t getParamGroupType() const { return paramGroupType_; };
            uint8_t getNumberOfUnits() const { return groupNumberOfUnits_.getNumberOfUnits(); }
            uint8_t getUnitNumber(size_t memberIndex) const { return groupNumberOfUnits_.getUnitNumber(memberIndex); }
            uint32_t getUnitSequence(size_t memberIndex) const { return groupNumberOfUnits_.getUnitSequence(memberIndex); }
        };
        std::vector<TypeNoUnspecifiedUnitReplay> typeNoUnspecifiedUnitReplayList_;

    public:
        uint8_t getNoUnspecifiedUnitReplay(size_t memberIndex) const { return typeNoUnspecifiedUnitReplayList_.at(memberIndex).getNoUnspecifiedUnitReplay(); };
        uint16_t getParamGroupLength(size_t memberIndex) const { return typeNoUnspecifiedUnitReplayList_.at(memberIndex).getParamGroupLength(); };
        uint8_t getParamGroupType(size_t memberIndex) const { return typeNoUnspecifiedUnitReplayList_.at(memberIndex).getParamGroupType(); };
        uint8_t getNumberOfUnits(size_t memberIndex) const { return typeNoUnspecifiedUnitReplayList_.at(memberIndex).getNumberOfUnits(); }
        uint8_t getUnitNumber(size_t index1, size_t index2) const { return typeNoUnspecifiedUnitReplayList_.at(index1).getUnitNumber(index2); }
        uint32_t getUnitSequence(size_t index1, size_t index2) const { return typeNoUnspecifiedUnitReplayList_.at(index1).getUnitSequence(index2); }
        // struct TypeMessageType
        // {
        //     uint8_t messageType_;       // Return message type for which the bitfields are being specified (e.g., 0x25 for an Order Acknowledgment message).
        //     uint16_t paramGroupLength_; // Number of bytes for the parameter group, including this field.
        //     uint8_t paramGroupType_;    // 0x80.
        //     struct GroupNumberOfReturnBitfields
        //     {
        //         uint8_t numberOfReturnBitfields_; // Number of bitfields to follow.
        //         struct Member
        //         {
        //             uint8_t returnBitfield_; // Bitfield identifying fields to return.
        //         };
        //         std::unique_ptr<std::vector<Member>> members_;
        //     };
        //     GroupNumberOfReturnBitfields groupNumberOfReturnBitfields_;
        // };
        // std::vector<TypeMessageType> typeMessageTypeList_;
    };
    std::unique_ptr<std::vector<Member>> members_;

public:
    uint8_t getNumberOfParamGroups() const { return numberOfParamGroups_; };
    uint8_t getNoUnspecifiedUnitReplay(size_t index1, size_t index2) const { return members_->at(index1).getNoUnspecifiedUnitReplay(index2); };
    uint16_t getParamGroupLength(size_t index1, size_t index2) const { return members_->at(index1).getParamGroupLength(index2); };
    uint8_t getParamGroupType(size_t index1, size_t index2) const { return members_->at(index1).getParamGroupType(index2); };
    uint8_t getNumberOfUnits(size_t index1, size_t index2) const { return members_->at(index1).getNumberOfUnits(index2); }
    uint8_t getUnitNumber(size_t index1, size_t index2, size_t index3) const { return members_->at(index1).getUnitNumber(index2, index3); }
    uint32_t getUnitSequence(size_t index1, size_t index2, size_t index3) const { return members_->at(index1).getUnitSequence(index2, index3); }
};

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
    uint8_t getNumberOfParamGroups() const { return groupNumberOfParamGroups_.getNumberOfParamGroups(); };
    uint8_t getNoUnspecifiedUnitReplay(size_t index1, size_t index2) const { return groupNumberOfParamGroups_.getNoUnspecifiedUnitReplay(index1, index2); };
    uint16_t getParamGroupLength(size_t index1, size_t index2) const { return groupNumberOfParamGroups_.getParamGroupLength(index1, index2); };
    uint8_t getParamGroupType(size_t index1, size_t index2) const { return groupNumberOfParamGroups_.getParamGroupType(index1, index2); };
    uint8_t getNumberOfUnits(size_t index1, size_t index2) const { return groupNumberOfParamGroups_.getNumberOfUnits(index1, index2); }
    uint8_t getUnitNumber(size_t index1, size_t index2, size_t index3) const { return groupNumberOfParamGroups_.getUnitNumber(index1, index2, index3); }
    uint32_t getUnitSequence(size_t index1, size_t index2, size_t index3) const { return groupNumberOfParamGroups_.getUnitSequence(index1, index2, index3); }
};

int main()
{
    LoginRequest loginRequest;
    return 0;
}