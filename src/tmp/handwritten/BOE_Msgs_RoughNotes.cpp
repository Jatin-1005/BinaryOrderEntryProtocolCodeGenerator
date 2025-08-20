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

    uint16_t messageLength_; // Number of bytes for the message, including this field but not including the two bytes for the StartOfMessage field.

    struct Group_NumberOfParamGroups
    {
        uint8_t numberOfParamGroups_; // A number, n (possibly 0), of parameter groups to follow.

        struct Member
        {
            uint16_t paramGroupLength_; // Number of bytes for the parameter group, including this field.
            uint8_t paramGroupType_;    // 0x80.

            struct Type_NoUnspecifiedUnitReplay
            {
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
                uint8_t messageType_; // Return message type for which the bitfields are being specified (e.g., 0x25 for an Order Acknowledgment message).

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
    // Getters and Setters for the main class fields
    uint16_t getStartOfMessage() const { return startOfMessage_; }
    void setStartOfMessage(uint16_t startOfMessage) { startOfMessage_ = startOfMessage; }

    uint16_t getMessageLength() const { return messageLength_; }
    void setMessageLength(uint16_t messageLength) { messageLength_ = messageLength; }

    // Getters and Setters for Group_NumberOfParamGroups
    uint8_t getNumberOfParamGroups() const { return group_NumberOfParamGroups_.numberOfParamGroups_; }
    void setNumberOfParamGroups(uint8_t numberOfParamGroups) { group_NumberOfParamGroups_.numberOfParamGroups_ = numberOfParamGroups; }

    // Getters and Setters for Member inside Group_NumberOfParamGroups
    uint16_t getParamGroupLength(size_t index) const
    {
        return group_NumberOfParamGroups_.members_->at(index).paramGroupLength_;
    }

    void setParamGroupLength(size_t index, uint16_t paramGroupLength)
    {
        group_NumberOfParamGroups_.members_->at(index).paramGroupLength_ = paramGroupLength;
    }

    uint8_t getParamGroupType(size_t index) const
    {
        return group_NumberOfParamGroups_.members_->at(index).paramGroupType_;
    }

    void setParamGroupType(size_t index, uint8_t paramGroupType)
    {
        group_NumberOfParamGroups_.members_->at(index).paramGroupType_ = paramGroupType;
    }

    void addMember(uint16_t paramGroupLength, uint8_t paramGroupType, bool isNoUnspecifiedUnitReplay)
    {
        if (!group_NumberOfParamGroups_.members_)
        {
            group_NumberOfParamGroups_.members_ = std::make_unique<std::vector<Group_NumberOfParamGroups::Member>>();
        }

        // Use emplace_back with the constructor directly
        if (isNoUnspecifiedUnitReplay)
        {
            group_NumberOfParamGroups_.members_->emplace_back(
                Group_NumberOfParamGroups::Member{
                    paramGroupLength,
                    paramGroupType,
                    Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay{0, {}} // Initialize specific type
                });
        }
        else
        {
            group_NumberOfParamGroups_.members_->emplace_back(
                Group_NumberOfParamGroups::Member{
                    paramGroupLength,
                    paramGroupType,
                    Group_NumberOfParamGroups::Member::Type_MessageType{0, {}} // Initialize specific type
                });
        }

        std::cout << group_NumberOfParamGroups_.members_->size() << std::endl;
    }

    // Getters and Setters for Type_NoUnspecifiedUnitReplay
    uint8_t getNoUnspecifiedUnitReplay(size_t memberIndex) const
    {
        return std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).noUnspecifiedUnitReplay_;
    }

    void setNoUnspecifiedUnitReplay(size_t memberIndex, uint8_t noUnspecifiedUnitReplay)
    {
        std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).noUnspecifiedUnitReplay_ = noUnspecifiedUnitReplay;
    }

    // Example for Type_MessageType
    uint8_t getMessageType(size_t memberIndex) const
    {
        return std::get<Group_NumberOfParamGroups::Member::Type_MessageType>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).messageType_;
    }

    void setMessageType(size_t memberIndex, uint8_t messageType)
    {
        std::get<Group_NumberOfParamGroups::Member::Type_MessageType>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).messageType_ = messageType;
    }

    void addUnitMember(size_t memberIndex, uint8_t unitNumber, uint32_t unitSequence)
    {
        auto &group_NumberOfUnits = std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).group_NumberOfUnits_;

        if (!group_NumberOfUnits.members_)
        {
            group_NumberOfUnits.members_ = std::make_unique<std::vector<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay::Group_NumberOfUnits::Member>>();
        }

        group_NumberOfUnits.members_->emplace_back(Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay::Group_NumberOfUnits::Member{unitNumber, unitSequence});
    }

    // Getters and Setters for Group_NumberOfUnits
    uint8_t getNumberOfUnits(size_t memberIndex) const
    {
        return std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).group_NumberOfUnits_.numberOfUnits_;
    }

    void setNumberOfUnits(size_t memberIndex, uint8_t numberOfUnits)
    {
        std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).group_NumberOfUnits_.numberOfUnits_ = numberOfUnits;
    }

    uint8_t getUnitNumber(size_t memberIndex, size_t unitIndex) const
    {
        return std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_)
            .group_NumberOfUnits_.members_->at(unitIndex)
            .unitNumber_;
    }

    void setUnitNumber(size_t memberIndex, size_t unitIndex, uint8_t unitNumber)
    {
        std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_)
            .group_NumberOfUnits_.members_->at(unitIndex)
            .unitNumber_ = unitNumber;
    }

    uint32_t getUnitSequence(size_t memberIndex, size_t unitIndex) const
    {
        return std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_)
            .group_NumberOfUnits_.members_->at(unitIndex)
            .unitSequence_;
    }

    void setUnitSequence(size_t memberIndex, size_t unitIndex, uint32_t unitSequence)
    {
        std::get<Group_NumberOfParamGroups::Member::Type_NoUnspecifiedUnitReplay>(group_NumberOfParamGroups_.members_->at(memberIndex).type_)
            .group_NumberOfUnits_.members_->at(unitIndex)
            .unitSequence_ = unitSequence;
    }

    void addReturnBitfieldMember(size_t memberIndex, uint8_t returnBitfield)
    {
        auto &group_NumberOfReturnBitfields = std::get<Group_NumberOfParamGroups::Member::Type_MessageType>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).group_NumberOfReturnBitfields_;

        if (!group_NumberOfReturnBitfields.members_)
        {
            group_NumberOfReturnBitfields.members_ = std::make_unique<std::vector<Group_NumberOfParamGroups::Member::Type_MessageType::Group_NumberOfReturnBitfields::Member>>();
        }

        group_NumberOfReturnBitfields.members_->push_back(Group_NumberOfParamGroups::Member::Type_MessageType::Group_NumberOfReturnBitfields::Member{returnBitfield});
    }

    uint8_t getNumberOfReturnBitfields(size_t memberIndex) const
    {
        return std::get<Group_NumberOfParamGroups::Member::Type_MessageType>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).group_NumberOfReturnBitfields_.numberOfReturnBitfields_;
    }

    void setNumberOfReturnBitfields(size_t memberIndex, uint8_t numberOfReturnBitfields)
    {
        std::get<Group_NumberOfParamGroups::Member::Type_MessageType>(group_NumberOfParamGroups_.members_->at(memberIndex).type_).group_NumberOfReturnBitfields_.numberOfReturnBitfields_ = numberOfReturnBitfields;
    }

    uint8_t getReturnBitfield(size_t memberIndex, size_t bitfieldIndex) const
    {
        return std::get<Group_NumberOfParamGroups::Member::Type_MessageType>(group_NumberOfParamGroups_.members_->at(memberIndex).type_)
            .group_NumberOfReturnBitfields_.members_->at(bitfieldIndex)
            .returnBitfield_;
    }

    void setReturnBitfield(size_t memberIndex, size_t bitfieldIndex, uint8_t returnBitfield)
    {
        std::get<Group_NumberOfParamGroups::Member::Type_MessageType>(group_NumberOfParamGroups_.members_->at(memberIndex).type_)
            .group_NumberOfReturnBitfields_.members_->at(bitfieldIndex)
            .returnBitfield_ = returnBitfield;
    }
};

int main()
{
    LoginRequest loginRequest;

    // Set basic fields
    loginRequest.setStartOfMessage(0xABCD);
    loginRequest.setMessageLength(100);
    loginRequest.setNumberOfParamGroups(2);

    // Add a member with Type_NoUnspecifiedUnitReplay and Type_MessageType
    loginRequest.addMember(50, 0x80, 1); // First param group
    loginRequest.addMember(30, 0x80, 0); // Second param group

    // Set NoUnspecifiedUnitReplay flag for the first param group
    loginRequest.setNoUnspecifiedUnitReplay(0, 0x01);
    loginRequest.setMessageType(1, 0x25);

    // Set number of units in the first param group
    loginRequest.setNumberOfUnits(0, 2); // Two units

    loginRequest.addUnitMember(0, 0, 1);
    loginRequest.addUnitMember(0, 0, 2);

    // Set values for the first unit
    loginRequest.setUnitNumber(0, 0, 1);
    loginRequest.setUnitSequence(0, 0, 12345);

    // Set values for the second unit
    loginRequest.setUnitNumber(0, 1, 2);
    loginRequest.setUnitSequence(0, 1, 67890);
    // Set message type for the second param group
    // Set the number of return bitfields in the second param group
    loginRequest.setNumberOfReturnBitfields(1, 2);
    // Set the bitfield for the first return bitfield in the second param group
    loginRequest.addReturnBitfieldMember(1, 0xFF);
    loginRequest.addReturnBitfieldMember(1, 0xFF);

    // Set values for the first bitfield
    loginRequest.setReturnBitfield(1, 0, 0xA);
    loginRequest.setReturnBitfield(1, 1, 0xA);

    // Example usage
    std::cout << "Start of Message: " << loginRequest.getStartOfMessage() << std::endl;
    std::cout << "Message Length: " << loginRequest.getMessageLength() << std::endl;
    std::cout << "Number of Param Groups: " << static_cast<int>(loginRequest.getNumberOfParamGroups()) << std::endl;

    std::cout << "Param Group 1 Length: " << loginRequest.getParamGroupLength(0) << std::endl;
    std::cout << "NoUnspecifiedUnitReplay: " << static_cast<int>(loginRequest.getNoUnspecifiedUnitReplay(0)) << std::endl;
    std::cout << "Unit 1 Number: " << static_cast<int>(loginRequest.getUnitNumber(0, 0)) << std::endl;
    std::cout << "Unit 1 Sequence: " << loginRequest.getUnitSequence(0, 0) << std::endl;

    std::cout << "Message Type for Param Group 2: " << static_cast<int>(loginRequest.getMessageType(1)) << std::endl;
    std::cout << "Return Bitfield: " << static_cast<int>(loginRequest.getReturnBitfield(1, 0)) << std::endl;

    return 0;
}
