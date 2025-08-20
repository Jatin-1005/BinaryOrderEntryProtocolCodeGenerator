// HandWritten File can make any changes to this, won't be affected by generation process.

#pragma once
#include <iostream>
#include <bitset>
#include <vector>
#include <memory>
#include <variant>

// Unit Sequence Struct
struct Unit
{
private:
    uint8_t unitNumber_;    // Unit number.
    uint32_t unitSequence_; // Last received sequence number for the unit.

public:
    uint8_t getUnitNumber() const { return unitNumber_; }
    uint32_t getUnitSequence() const { return unitSequence_; }
};

// Group of Units
struct GroupOfUnits
{
private:
    uint8_t numberOfUnits_; // Number of unit/sequence pairs to follow, one per unit from which the Member has received messages.
    std::unique_ptr<std::vector<Unit>> units_;

public:
    uint8_t getNumberOfUnits() const { return numberOfUnits_; }
    uint8_t getUnitNumber(size_t unitIndex) const { return units_->at(unitIndex).getUnitNumber(); }
    uint32_t getUnitSequence(size_t unitIndex) const { return units_->at(unitIndex).getUnitSequence(); }
};

// Param Group for No Unspecified Unit Replay
struct ParamGroupNoUnspecifiedUnitReplay
{
private:
    uint16_t paramGroupLength_;       // Number of bytes for the parameter group, including this field.
    uint8_t paramGroupType_;          // 0x80.
    uint8_t noUnspecifiedUnitReplay_; // Flag indicating whether to replay missed outgoing (Cboe to Member) messages for unspecified units. 0x00 = False, 0x01 = True.
    GroupOfUnits groupOfUnits_;       // Group of units.

public:
    uint8_t getNoUnspecifiedUnitReplay() const { return noUnspecifiedUnitReplay_; }
    uint16_t getParamGroupLength() const { return paramGroupLength_; }
    uint8_t getParamGroupType() const { return paramGroupType_; }
    uint8_t getNumberOfUnits() const { return groupOfUnits_.getNumberOfUnits(); }
    uint8_t getUnitNumber(size_t unitIndex) const { return groupOfUnits_.getUnitNumber(unitIndex); }
    uint32_t getUnitSequence(size_t unitIndex) const { return groupOfUnits_.getUnitSequence(unitIndex); }
};

// ParamGroup Container
struct ParamGroup
{
private:
    std::vector<ParamGroupNoUnspecifiedUnitReplay> paramGroupList_; // List of ParamGroups

public:
    uint8_t getNoUnspecifiedUnitReplay(size_t groupIndex) const { return paramGroupList_.at(groupIndex).getNoUnspecifiedUnitReplay(); }
    uint16_t getParamGroupLength(size_t groupIndex) const { return paramGroupList_.at(groupIndex).getParamGroupLength(); }
    uint8_t getParamGroupType(size_t groupIndex) const { return paramGroupList_.at(groupIndex).getParamGroupType(); }
    uint8_t getNumberOfUnits(size_t groupIndex) const { return paramGroupList_.at(groupIndex).getNumberOfUnits(); }
    uint8_t getUnitNumber(size_t groupIndex, size_t unitIndex) const { return paramGroupList_.at(groupIndex).getUnitNumber(unitIndex); }
    uint32_t getUnitSequence(size_t groupIndex, size_t unitIndex) const { return paramGroupList_.at(groupIndex).getUnitSequence(unitIndex); }
};

// Group of ParamGroups
struct GroupOfParamGroups
{
private:
    uint8_t numberOfParamGroups_;                          // A number, n (possibly 0), of parameter groups to follow.
    std::unique_ptr<std::vector<ParamGroup>> paramGroups_; // List of param groups

public:
    uint8_t getNumberOfParamGroups() const { return numberOfParamGroups_; }
    uint8_t getNoUnspecifiedUnitReplay(size_t groupIndex, size_t paramIndex) const { return paramGroups_->at(groupIndex).getNoUnspecifiedUnitReplay(paramIndex); }
    uint16_t getParamGroupLength(size_t groupIndex, size_t paramIndex) const { return paramGroups_->at(groupIndex).getParamGroupLength(paramIndex); }
    uint8_t getParamGroupType(size_t groupIndex, size_t paramIndex) const { return paramGroups_->at(groupIndex).getParamGroupType(paramIndex); }
    uint8_t getNumberOfUnits(size_t groupIndex, size_t paramIndex) const { return paramGroups_->at(groupIndex).getNumberOfUnits(paramIndex); }
    uint8_t getUnitNumber(size_t groupIndex, size_t paramIndex, size_t unitIndex) const { return paramGroups_->at(groupIndex).getUnitNumber(paramIndex, unitIndex); }
    uint32_t getUnitSequence(size_t groupIndex, size_t paramIndex, size_t unitIndex) const { return paramGroups_->at(groupIndex).getUnitSequence(paramIndex, unitIndex); }
};

// Main Login Request
class LoginRequest
{
private:
    uint16_t startOfMessage_;               // Must be 0xBA 0xBA.
    uint16_t messageLength_;                // Number of bytes for the message, including this field but not including the two bytes for the StartOfMessage field.
    uint8_t messageType_;                   // Login Request (0x37).
    uint8_t matchingUnit_;                  // Always 0 for inbound (Member to Cboe) messages.
    uint32_t sequenceNumber_;               // Always 0 for session level messages.
    uint32_t sessionSubID_;                 // Session Sub ID supplied by Cboe.
    uint32_t username_;                     // Username supplied by Cboe.
    std::bitset<80> password_;              // Password supplied by Cboe.
    GroupOfParamGroups groupOfParamGroups_; // Param group data

public:
    uint16_t getStartOfMessage() const { return startOfMessage_; }
    uint16_t getMessageLength() const { return messageLength_; }
    uint8_t getMessageType() const { return messageType_; }
    uint8_t getMatchingUnit() const { return matchingUnit_; }
    uint32_t getSequenceNumber() const { return sequenceNumber_; }
    uint32_t getSessionSubID() const { return sessionSubID_; }
    uint32_t getUsername() const { return username_; }
    std::bitset<80> getPassword() const { return password_; }
    uint8_t getNumberOfParamGroups() const { return groupOfParamGroups_.getNumberOfParamGroups(); }
    uint8_t getNoUnspecifiedUnitReplay(size_t groupIndex, size_t paramIndex) const { return groupOfParamGroups_.getNoUnspecifiedUnitReplay(groupIndex, paramIndex); }
    uint16_t getParamGroupLength(size_t groupIndex, size_t paramIndex) const { return groupOfParamGroups_.getParamGroupLength(groupIndex, paramIndex); }
    uint8_t getParamGroupType(size_t groupIndex, size_t paramIndex) const { return groupOfParamGroups_.getParamGroupType(groupIndex, paramIndex); }
    uint8_t getNumberOfUnits(size_t groupIndex, size_t paramIndex) const { return groupOfParamGroups_.getNumberOfUnits(groupIndex, paramIndex); }
    uint8_t getUnitNumber(size_t groupIndex, size_t paramIndex, size_t unitIndex) const { return groupOfParamGroups_.getUnitNumber(groupIndex, paramIndex, unitIndex); }
    uint32_t getUnitSequence(size_t groupIndex, size_t paramIndex, size_t unitIndex) const { return groupOfParamGroups_.getUnitSequence(groupIndex, paramIndex, unitIndex); }
};

int main()
{
    LoginRequest loginRequest;
    return 0;
}

#pragma once
#include <iostream>
#include <bitset>
#include <vector>
#include <memory>
#include <variant>

struct GroupNumberOfUnitsMember
{
private:
    uint8_t unitNumber_;    // Unit number.
    uint32_t unitSequence_; // Last received sequence number for the unit.
public:
    uint8_t getUnitNumber() const { return unitNumber_; }
    uint32_t getUnitSequence() const { return unitSequence_; }
};

struct GroupNoUnspecifiedUnitReplayMember
{
private:
    uint16_t paramGroupLength_; // Number of bytes for the parameter group, including this field.
    uint8_t paramGroupType_;    // 0x80.
    uint8_t numberOfUnits_;     // Number of unit/sequence pairs to follow, one per unit from which the Member has received messages.
    std::vector<GroupNumberOfUnitsMember> groupNumberOfUnitsList_;

public:
    uint16_t getParamGroupLength() const { return paramGroupLength_; }
    uint8_t getParamGroupType() const { return paramGroupType_; }
    uint8_t getNumberOfUnits() const { return numberOfUnits_; }
    uint8_t getUnitNumber(size_t GroupNumberOfUnitsMemberIndex) const { return groupNumberOfUnitsList_.at(GroupNumberOfUnitsMemberIndex).getUnitNumber(); }
    uint8_t getUnitSequence(size_t GroupNumberOfUnitsMemberIndex) const { return groupNumberOfUnitsList_.at(GroupNumberOfUnitsMemberIndex).getUnitSequence(); }
};

struct GroupNumberOfParamGroupsMember
{
private:
    uint8_t noUnspecifiedUnitReplay_; // Flag indicating whether to replay missed outgoing (Cboe to Member) messages for unspecified units. 0x00 = False, 0x01 = True.
    std::vector<GroupNoUnspecifiedUnitReplayMember> groupNoUnspecifiedUnitReplayList_;

public:
    uint8_t getNoUnspecifiedUnitReplay() const { return noUnspecifiedUnitReplay_; }
    uint16_t getParamGroupLength(size_t GroupNoUnspecifiedUnitReplayMemberIndex) const { return groupNoUnspecifiedUnitReplayList_.at(GroupNoUnspecifiedUnitReplayMemberIndex).getParamGroupLength(); }
    uint8_t getParamGroupType(size_t GroupNoUnspecifiedUnitReplayMemberIndex) const { return groupNoUnspecifiedUnitReplayList_.at(GroupNoUnspecifiedUnitReplayMemberIndex).getParamGroupType(); }
    uint8_t getNumberOfUnits(size_t GroupNoUnspecifiedUnitReplayMemberIndex) const { return groupNoUnspecifiedUnitReplayList_.at(GroupNoUnspecifiedUnitReplayMemberIndex).getNumberOfUnits(); }
    uint8_t getUnitNumber(size_t GroupNoUnspecifiedUnitReplayMemberIndex, size_t GroupNumberOfUnitsMemberIndex) const { return groupNoUnspecifiedUnitReplayList_.at(GroupNoUnspecifiedUnitReplayMemberIndex).getUnitNumber(GroupNumberOfUnitsMemberIndex); }
    uint8_t getUnitSequence(size_t GroupNoUnspecifiedUnitReplayMemberIndex, size_t GroupNumberOfUnitsMemberIndex) const { return groupNoUnspecifiedUnitReplayList_.at(GroupNoUnspecifiedUnitReplayMemberIndex).getUnitSequence(GroupNumberOfUnitsMemberIndex); }
};

class LoginRequest
{
private:
    uint16_t startOfMessage_;     // Must be 0xBA 0xBA.
    uint8_t numberOfParamGroups_; // A number, n (possibly 0), of parameter groups to follow.
    std::vector<GroupNumberOfParamGroupsMember> groupNumberOfParamGroupsList_;

public:
    uint16_t getStartOfMessage() const { return startOfMessage_; }
    uint8_t getNumberOfParamGroups() const { return numberOfParamGroups_; }

    // renderInnerAccessors
};
