#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include <variant>

class GroupNumberOfReturnBitfieldsMember
{
    std::vector<uint8_t> returnBitfield_; // Bitfield identifying fields to return.
public:
    GroupNumberOfReturnBitfieldsMember(uint8_t returnBitfield): returnBitfield_(returnBitfield) {};

    inline uint8_t getReturnBitfield() const { return returnBitfield_; }
    inline void setReturnBitfield(const uint8_t returnBitfield) { returnBitfield_ = returnBitfield; }
};

class GroupNumberOfUnitsMember
{
    uint8_t unitNumber_;    // Unit number.
    uint32_t unitSequence_; // Last received sequence number for the unit.

public:
    GroupNumberOfUnitsMember(uint8_t unitNumber_, uint32_t unitSequence_): unitNumber_(unitNumber_), unitSequence_(unitSequence_) {};

    inline uint8_t getUnitNumber() const { return unitNumber_; }
    inline void setUnitNumber(const uint8_t unitNumber) { unitNumber_ = unitNumber; }

    inline uint32_t getUnitSequence() const { return unitSequence_; }
    inline void setUnitSequence(const uint32_t unitSequence) { unitSequence_ = unitSequence; }
};

class TypeUnitSequences
{
private:
    uint16_t paramGroupLengthUnitSequences_; // Number of bytes for the parameter group, including this field.
    uint8_t paramGroupTypeUnitSequences_;    // 0x80.
    uint8_t noUnspecifiedUnitReplay_;        // Flag indicating whether to replay missed outgoing (Cboe to Member) messages for unspecified units. 0x00 = False, 0x01 = True.
    uint8_t numberOfUnits_;                  // Number of unit/sequence pairs to follow, one per unit from which the Member has received messages.
    std::vector<GroupNumberOfUnitsMember> groupNumberOfUnitsList_;

public:
    TypeUnitSequences(uint16_t paramGroupLengthUnitSequences, uint8_t paramGroupTypeUnitSequences, 
                      uint8_t noUnspecifiedUnitReplay, uint8_t numberOfUnits, 
                      std::initializer_list<GroupNumberOfUnitsMember> groupNumberOfUnitsList)
        : paramGroupLengthUnitSequences_(paramGroupLengthUnitSequences), 
          paramGroupTypeUnitSequences_(paramGroupTypeUnitSequences), 
          noUnspecifiedUnitReplay_(noUnspecifiedUnitReplay), 
          numberOfUnits_(numberOfUnits), 
          groupNumberOfUnitsList_(groupNumberOfUnitsList) {}
    
    TypeUnitSequences(uint16_t paramGroupLengthUnitSequences, uint8_t paramGroupTypeUnitSequences, 
                      uint8_t noUnspecifiedUnitReplay, uint8_t numberOfUnits, 
                      std::vector<GroupNumberOfUnitsMember>&& groupNumberOfUnitsList)
        : paramGroupLengthUnitSequences_(paramGroupLengthUnitSequences), 
          paramGroupTypeUnitSequences_(paramGroupTypeUnitSequences), 
          noUnspecifiedUnitReplay_(noUnspecifiedUnitReplay), 
          numberOfUnits_(numberOfUnits), 
          groupNumberOfUnitsList_(std::move(groupNumberOfUnitsList)) {}
    
    inline uint16_t getParamGroupLengthUnitSequences() const { return paramGroupLengthUnitSequences_; }
    inline void setParamGroupLengthUnitSequences(const uint16_t paramGroupLengthUnitSequences) { paramGroupLengthUnitSequences_ = paramGroupLengthUnitSequences; }

    inline uint8_t getParamGroupTypeUnitSequences() const { return paramGroupTypeUnitSequences_; }
    inline void setParamGroupTypeUnitSequences(const uint8_t paramGroupTypeUnitSequences) { paramGroupTypeUnitSequences_ = paramGroupTypeUnitSequences; }

    inline uint8_t getNoUnspecifiedUnitReplay() const { return noUnspecifiedUnitReplay_; }
    inline void setNoUnspecifiedUnitReplay(const uint8_t noUnspecifiedUnitReplay) { noUnspecifiedUnitReplay_ = noUnspecifiedUnitReplay; }

    inline uint8_t getNumberOfUnits() const { return numberOfUnits_; }
    inline void setNumberOfUnits(const uint8_t numberOfUnits) { numberOfUnits_ = numberOfUnits; }

    inline std::vector<GroupNumberOfUnitsMember> getGroupNumberOfUnits() const { return groupNumberOfUnitsList_; }
    inline void setGroupNumberOfUnits(std::vector<GroupNumberOfUnitsMember> groupNumberOfUnitsList) { groupNumberOfUnitsList_ = groupNumberOfUnitsList_; }

    inline uint8_t getUnitNumber(size_t groupNumberOfUnitsIdx) const
    {
        if (groupNumberOfUnitsIdx < groupNumberOfUnitsList_.size())
        {
            return groupNumberOfUnitsList_.at(groupNumberOfUnitsIdx).getUnitNumber();
        }
        else
        {
            throw std::out_of_range("Index out of range in getUnitNumber: groupNumberOfUnitsIdx exceeds size of groupNumberOfUnitsList_");
        }
    }
    inline void setUnitNumber(size_t groupNumberOfUnitsIdx, uint8_t unitNumber)
    {
        if (groupNumberOfUnitsIdx == groupNumberOfUnitsList_.size())
        {
            groupNumberOfUnitsList_.resize(groupNumberOfUnitsList_.size() + 1);
        }
        else if (groupNumberOfUnitsIdx > groupNumberOfUnitsList_.size())
        {
            throw std::out_of_range("Index out of range in setUnitNumber: groupNumberOfUnitsIdx exceeds size of groupNumberOfUnitsList_ + 1, add the elements sequentially");
        }
        groupNumberOfUnitsList_.at(groupNumberOfUnitsIdx).setUnitNumber(unitNumber);
    }

    inline uint32_t getUnitSequence(size_t groupNumberOfUnitsIdx) const
    {
        if (groupNumberOfUnitsIdx < groupNumberOfUnitsList_.size())
        {
            return groupNumberOfUnitsList_.at(groupNumberOfUnitsIdx).getUnitSequence();
        }
        else
        {
            throw std::out_of_range("Index out of range in getUnitSequence: groupNumberOfUnitsIdx exceeds size of groupNumberOfUnitsList_");
        }
    }
    inline void setUnitSequence(size_t groupNumberOfUnitsIdx, uint32_t unitSequence)
    {
        if (groupNumberOfUnitsIdx == groupNumberOfUnitsList_.size())
        {
            groupNumberOfUnitsList_.resize(groupNumberOfUnitsList_.size() + 1);
        }
        else if (groupNumberOfUnitsIdx > groupNumberOfUnitsList_.size())
        {
            throw std::out_of_range("Index out of range in setUnitSequence: groupNumberOfUnitsIdx exceeds size of groupNumberOfUnitsList_ + 1, add the elements sequentially");
        }
        groupNumberOfUnitsList_.at(groupNumberOfUnitsIdx).setUnitSequence(unitSequence);
    }
};

class TypeReturnBitfields
{
private:
    uint16_t paramGroupLengthReturnBitfields_; // Number of bytes for the parameter group, including this field.
    uint8_t paramGroupTypeReturnBitfields_;    // 0x80.
    uint8_t messageType_;                      // Return message type for which the bitfields are being specified (e.g., 0x25 for an Order Acknowledgment message).
    uint8_t numberOfReturnBitfields_;          // Number of bitfields to follow.
    std::vector<GroupNumberOfReturnBitfieldsMember> groupNumberOfReturnBitfieldsList_;

public:
    // Constructor with initializer list for readability
    TypeReturnBitfields(uint16_t paramGroupLength, uint8_t paramGroupType, uint8_t messageType, uint8_t numBitfields,
                        std::initializer_list<GroupNumberOfReturnBitfieldsMember> bitfieldList)
        : paramGroupLengthReturnBitfields_(paramGroupLength),
          paramGroupTypeReturnBitfields_(paramGroupType),
          messageType_(messageType),
          numberOfReturnBitfields_(numBitfields),
          groupNumberOfReturnBitfieldsList_(bitfieldList) {}

    // Constructor with move semantics for efficiency with large or dynamic lists
    TypeReturnBitfields(uint16_t paramGroupLength, uint8_t paramGroupType, uint8_t messageType, uint8_t numBitfields,
                        std::vector<GroupNumberOfReturnBitfieldsMember>&& bitfieldList)
        : paramGroupLengthReturnBitfields_(paramGroupLength),
          paramGroupTypeReturnBitfields_(paramGroupType),
          messageType_(messageType),
          numberOfReturnBitfields_(numBitfields),
          groupNumberOfReturnBitfieldsList_(std::move(bitfieldList)) {}

    inline uint16_t getParamGroupLengthReturnBitfields() const { return paramGroupLengthReturnBitfields_; }
    inline void setParamGroupLengthReturnBitfields(const uint16_t paramGroupLengthReturnBitfields) { paramGroupLengthReturnBitfields_ = paramGroupLengthReturnBitfields; }

    inline uint8_t getParamGroupTypeReturnBitfields() const { return paramGroupTypeReturnBitfields_; }
    inline void setParamGroupTypeReturnBitfields(const uint8_t paramGroupTypeReturnBitfields) { paramGroupTypeReturnBitfields_ = paramGroupTypeReturnBitfields; }

    inline uint8_t getMessageType() const { return messageType_; }
    inline void setMessageType(const uint8_t messageType) { messageType_ = messageType; }

    inline uint8_t getNumberOfReturnBitfields() const { return numberOfReturnBitfields_; }
    inline void setNumberOfReturnBitfields(const uint8_t numberOfReturnBitfields) { numberOfReturnBitfields_ = numberOfReturnBitfields; }

    inline std::vector<GroupNumberOfReturnBitfieldsMember> getGroupNumberOfReturnBitfields() const { return groupNumberOfReturnBitfieldsList_; }
    inline void setGroupNumberOfReturnBitfields(std::vector<GroupNumberOfReturnBitfieldsMember> groupNumberOfReturnBitfieldsList) { groupNumberOfReturnBitfieldsList_ = groupNumberOfReturnBitfieldsList_; }

    inline uint8_t getReturnBitfield(size_t groupNumberOfReturnBitfieldsIdx) const
    {
        if (groupNumberOfReturnBitfieldsIdx < groupNumberOfReturnBitfieldsList_.size())
        {
            return groupNumberOfReturnBitfieldsList_.at(groupNumberOfReturnBitfieldsIdx).getReturnBitfield();
        }
        else
        {
            throw std::out_of_range("Index out of range in getReturnBitfield: groupNumberOfReturnBitfieldsIdx exceeds size of groupNumberOfReturnBitfieldsList_");
        }
    }
    inline void setReturnBitfield(size_t groupNumberOfReturnBitfieldsIdx, uint8_t returnBitfield)
    {
        if (groupNumberOfReturnBitfieldsIdx == groupNumberOfReturnBitfieldsList_.size())
        {
            groupNumberOfReturnBitfieldsList_.resize(groupNumberOfReturnBitfieldsList_.size() + 1);
        }
        else if (groupNumberOfReturnBitfieldsIdx > groupNumberOfReturnBitfieldsList_.size())
        {
            throw std::out_of_range("Index out of range in setReturnBitfield: groupNumberOfReturnBitfieldsIdx exceeds size of groupNumberOfReturnBitfieldsList_ + 1, add the elements sequentially");
        }
        groupNumberOfReturnBitfieldsList_.at(groupNumberOfReturnBitfieldsIdx).setReturnBitfield(returnBitfield);
    }
};

class LoginRequest
{
private:
    uint16_t startOfMessage_;     // Must be 0xBA 0xBA.
    uint16_t messageLength_;      // Number of bytes for the message, including this field but not including the two bytes for the StartOfMessage field.
    uint8_t messageType_;         // Login Request (0x37).
    uint8_t matchingUnit_;        // Always 0 for inbound (Member to Cboe) messages.
    uint32_t sequenceNumber_;     // Always 0 for session level messages.
    char sessionSubID_[4];        // Session Sub ID supplied by Cboe.
    char username_[4];            // Username supplied by Cboe.
    char password_[10];           // Password supplied by Cboe.
    uint8_t numberOfParamGroups_; // A number, n (possibly 0), of parameter groups to follow.
    std::vector<TypeUnitSequences> typeUnitSequencesList_;
    std::vector<TypeReturnBitfields> typeReturnBitfieldsList_;

public:
    // Constructor to initialize all fields
    LoginRequest(uint16_t startOfMessage, uint16_t messageLength, uint8_t messageType, uint8_t matchingUnit,
                 uint32_t sequenceNumber, const char sessionSubID[4], const char username[4], const char password[10],
                 uint8_t numberOfParamGroups,
                 std::initializer_list<TypeUnitSequences> unitSequencesList = {},
                 std::initializer_list<TypeReturnBitfields> returnBitfieldsList = {})
        : startOfMessage_(startOfMessage),
          messageLength_(messageLength),
          messageType_(messageType),
          matchingUnit_(matchingUnit),
          sequenceNumber_(sequenceNumber),
          numberOfParamGroups_(numberOfParamGroups),
          typeUnitSequencesList_(unitSequencesList),
          typeReturnBitfieldsList_(returnBitfieldsList)
    {
        std::memcpy(sessionSubID_, sessionSubID, 4);
        std::memcpy(username_, username, 4);
        std::memcpy(password_, password, 10);
    }

    // Constructor for dynamically created lists (using move semantics)
    LoginRequest(uint16_t startOfMessage, uint16_t messageLength, uint8_t messageType, uint8_t matchingUnit,
                 uint32_t sequenceNumber, const char sessionSubID[4], const char username[4], const char password[10],
                 uint8_t numberOfParamGroups,
                 std::vector<TypeUnitSequences>&& unitSequencesList,
                 std::vector<TypeReturnBitfields>&& returnBitfieldsList)
        : startOfMessage_(startOfMessage),
          messageLength_(messageLength),
          messageType_(messageType),
          matchingUnit_(matchingUnit),
          sequenceNumber_(sequenceNumber),
          numberOfParamGroups_(numberOfParamGroups),
          typeUnitSequencesList_(std::move(unitSequencesList)),
          typeReturnBitfieldsList_(std::move(returnBitfieldsList))
    {
        std::memcpy(sessionSubID_, sessionSubID, 4);
        std::memcpy(username_, username, 4);
        std::memcpy(password_, password, 10);
    }

    inline uint16_t getStartOfMessage() const { return startOfMessage_; }
    inline void setStartOfMessage(const uint16_t startOfMessage) { startOfMessage_ = startOfMessage; }

    inline uint16_t getMessageLength() const { return messageLength_; }
    inline void setMessageLength(const uint16_t messageLength) { messageLength_ = messageLength; }

    inline uint8_t getMessageType() const { return messageType_; }
    inline void setMessageType(const uint8_t messageType) { messageType_ = messageType; }

    inline uint8_t getMatchingUnit() const { return matchingUnit_; }
    inline void setMatchingUnit(const uint8_t matchingUnit) { matchingUnit_ = matchingUnit; }

    inline uint32_t getSequenceNumber() const { return sequenceNumber_; }
    inline void setSequenceNumber(const uint32_t sequenceNumber) { sequenceNumber_ = sequenceNumber; }

    inline const char *getSessionSubID() const { return sessionSubID_; }
    inline void setSessionSubID(const char *sessionSubID)
    {
        strncpy(sessionSubID_, sessionSubID, 4);
    }

    inline const char *getUsername() const { return username_; }
    inline void setUsername(const char *username)
    {
        strncpy(username_, username, 4);
    }

    inline const char *getPassword() const { return password_; }
    inline void setPassword(const char *password)
    {
        strncpy(password_, password, 10);
    }

    inline uint8_t getNumberOfParamGroups() const { return numberOfParamGroups_; }
    inline void setNumberOfParamGroups(const uint8_t numberOfParamGroups) { numberOfParamGroups_ = numberOfParamGroups; }

    inline std::vector<TypeUnitSequences> getTypeUnitSequences() const { return typeUnitSequencesList_; }
    inline void setTypeUnitSequences(std::vector<TypeUnitSequences> typeUnitSequencesList) { typeUnitSequencesList_ = typeUnitSequencesList; }
    
    inline std::vector<TypeReturnBitfields> getTypeReturnBitfields() const { return typeReturnBitfieldsList_; }
    inline void setTypeReturnBitfields(std::vector<TypeReturnBitfields> typeReturnBitfieldsList) { typeReturnBitfieldsList_ = typeReturnBitfieldsList; }
    
    inline uint16_t getParamGroupLengthUnitSequences(size_t typeUnitSequencesIdx) const
    {
        if (typeUnitSequencesIdx < typeUnitSequencesList_.size())
        {
            return typeUnitSequencesList_.at(typeUnitSequencesIdx).getParamGroupLengthUnitSequences();
        }
        else
        {
            throw std::out_of_range("Index out of range in getParamGroupLengthUnitSequences: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_");
        }
    }
    inline void setParamGroupLengthUnitSequences(size_t typeUnitSequencesIdx, uint16_t paramGroupLengthUnitSequences)
    {
        if (typeUnitSequencesIdx == typeUnitSequencesList_.size())
        {
            typeUnitSequencesList_.resize(typeUnitSequencesList_.size() + 1);
        }
        else if (typeUnitSequencesIdx > typeUnitSequencesList_.size())
        {
            throw std::out_of_range("Index out of range in setParamGroupLengthUnitSequences: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_ + 1, add the elements sequentially");
        }
        typeUnitSequencesList_.at(typeUnitSequencesIdx).setParamGroupLengthUnitSequences(paramGroupLengthUnitSequences);
    }

    inline uint8_t getParamGroupTypeUnitSequences(size_t typeUnitSequencesIdx) const
    {
        if (typeUnitSequencesIdx < typeUnitSequencesList_.size())
        {
            return typeUnitSequencesList_.at(typeUnitSequencesIdx).getParamGroupTypeUnitSequences();
        }
        else
        {
            throw std::out_of_range("Index out of range in getParamGroupTypeUnitSequences: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_");
        }
    }
    inline void setParamGroupTypeUnitSequences(size_t typeUnitSequencesIdx, uint8_t paramGroupTypeUnitSequences)
    {
        if (typeUnitSequencesIdx == typeUnitSequencesList_.size())
        {
            typeUnitSequencesList_.resize(typeUnitSequencesList_.size() + 1);
        }
        else if (typeUnitSequencesIdx > typeUnitSequencesList_.size())
        {
            throw std::out_of_range("Index out of range in setParamGroupTypeUnitSequences: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_ + 1, add the elements sequentially");
        }
        typeUnitSequencesList_.at(typeUnitSequencesIdx).setParamGroupTypeUnitSequences(paramGroupTypeUnitSequences);
    }

    inline uint8_t getNoUnspecifiedUnitReplay(size_t typeUnitSequencesIdx) const
    {
        if (typeUnitSequencesIdx < typeUnitSequencesList_.size())
        {
            return typeUnitSequencesList_.at(typeUnitSequencesIdx).getNoUnspecifiedUnitReplay();
        }
        else
        {
            throw std::out_of_range("Index out of range in getNoUnspecifiedUnitReplay: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_");
        }
    }
    inline void setNoUnspecifiedUnitReplay(size_t typeUnitSequencesIdx, uint8_t noUnspecifiedUnitReplay)
    {
        if (typeUnitSequencesIdx == typeUnitSequencesList_.size())
        {
            typeUnitSequencesList_.resize(typeUnitSequencesList_.size() + 1);
        }
        else if (typeUnitSequencesIdx > typeUnitSequencesList_.size())
        {
            throw std::out_of_range("Index out of range in setNoUnspecifiedUnitReplay: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_ + 1, add the elements sequentially");
        }
        typeUnitSequencesList_.at(typeUnitSequencesIdx).setNoUnspecifiedUnitReplay(noUnspecifiedUnitReplay);
    }

    inline uint8_t getNumberOfUnits(size_t typeUnitSequencesIdx) const
    {
        if (typeUnitSequencesIdx < typeUnitSequencesList_.size())
        {
            return typeUnitSequencesList_.at(typeUnitSequencesIdx).getNumberOfUnits();
        }
        else
        {
            throw std::out_of_range("Index out of range in getNumberOfUnits: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_");
        }
    }
    inline void setNumberOfUnits(size_t typeUnitSequencesIdx, uint8_t numberOfUnits)
    {
        if (typeUnitSequencesIdx == typeUnitSequencesList_.size())
        {
            typeUnitSequencesList_.resize(typeUnitSequencesList_.size() + 1);
        }
        else if (typeUnitSequencesIdx > typeUnitSequencesList_.size())
        {
            throw std::out_of_range("Index out of range in setNumberOfUnits: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_ + 1, add the elements sequentially");
        }
        typeUnitSequencesList_.at(typeUnitSequencesIdx).setNumberOfUnits(numberOfUnits);
    }

    inline uint8_t getUnitNumber(size_t typeUnitSequencesIdx, size_t groupNumberOfUnitsIdx) const
    {
        if (typeUnitSequencesIdx < typeUnitSequencesList_.size())
        {
            return typeUnitSequencesList_.at(typeUnitSequencesIdx).getUnitNumber(groupNumberOfUnitsIdx);
        }
        else
        {
            throw std::out_of_range("Index out of range in getUnitNumber: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_");
        }
    }
    inline void setUnitNumber(size_t typeUnitSequencesIdx, size_t groupNumberOfUnitsIdx, uint8_t unitNumber)
    {
        if (typeUnitSequencesIdx == typeUnitSequencesList_.size())
        {
            typeUnitSequencesList_.resize(typeUnitSequencesList_.size() + 1);
        }
        else if (typeUnitSequencesIdx > typeUnitSequencesList_.size())
        {
            throw std::out_of_range("Index out of range in setUnitNumber: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_ + 1, add the elements sequentially");
        }
        typeUnitSequencesList_.at(typeUnitSequencesIdx).setUnitNumber(groupNumberOfUnitsIdx, unitNumber);
    }

    inline uint32_t getUnitSequence(size_t typeUnitSequencesIdx, size_t groupNumberOfUnitsIdx) const
    {
        if (typeUnitSequencesIdx < typeUnitSequencesList_.size())
        {
            return typeUnitSequencesList_.at(typeUnitSequencesIdx).getUnitSequence(groupNumberOfUnitsIdx);
        }
        else
        {
            throw std::out_of_range("Index out of range in getUnitSequence: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_");
        }
    }
    inline void setUnitSequence(size_t typeUnitSequencesIdx, size_t groupNumberOfUnitsIdx, uint32_t unitSequence)
    {
        if (typeUnitSequencesIdx == typeUnitSequencesList_.size())
        {
            typeUnitSequencesList_.resize(typeUnitSequencesList_.size() + 1);
        }
        else if (typeUnitSequencesIdx > typeUnitSequencesList_.size())
        {
            throw std::out_of_range("Index out of range in setUnitSequence: typeUnitSequencesIdx exceeds size of typeUnitSequencesList_ + 1, add the elements sequentially");
        }
        typeUnitSequencesList_.at(typeUnitSequencesIdx).setUnitSequence(groupNumberOfUnitsIdx, unitSequence);
    }

    inline uint16_t getParamGroupLengthReturnBitfields(size_t typeReturnBitfieldsIdx) const
    {
        if (typeReturnBitfieldsIdx < typeReturnBitfieldsList_.size())
        {
            return typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).getParamGroupLengthReturnBitfields();
        }
        else
        {
            throw std::out_of_range("Index out of range in getParamGroupLengthReturnBitfields: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_");
        }
    }
    inline void setParamGroupLengthReturnBitfields(size_t typeReturnBitfieldsIdx, uint16_t paramGroupLengthReturnBitfields)
    {
        if (typeReturnBitfieldsIdx == typeReturnBitfieldsList_.size())
        {
            typeReturnBitfieldsList_.resize(typeReturnBitfieldsList_.size() + 1);
        }
        else if (typeReturnBitfieldsIdx > typeReturnBitfieldsList_.size())
        {
            throw std::out_of_range("Index out of range in setParamGroupLengthReturnBitfields: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_ + 1, add the elements sequentially");
        }
        typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).setParamGroupLengthReturnBitfields(paramGroupLengthReturnBitfields);
    }

    inline uint8_t getParamGroupTypeReturnBitfields(size_t typeReturnBitfieldsIdx) const
    {
        if (typeReturnBitfieldsIdx < typeReturnBitfieldsList_.size())
        {
            return typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).getParamGroupTypeReturnBitfields();
        }
        else
        {
            throw std::out_of_range("Index out of range in getParamGroupTypeReturnBitfields: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_");
        }
    }
    inline void setParamGroupTypeReturnBitfields(size_t typeReturnBitfieldsIdx, uint8_t paramGroupTypeReturnBitfields)
    {
        if (typeReturnBitfieldsIdx == typeReturnBitfieldsList_.size())
        {
            typeReturnBitfieldsList_.resize(typeReturnBitfieldsList_.size() + 1);
        }
        else if (typeReturnBitfieldsIdx > typeReturnBitfieldsList_.size())
        {
            throw std::out_of_range("Index out of range in setParamGroupTypeReturnBitfields: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_ + 1, add the elements sequentially");
        }
        typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).setParamGroupTypeReturnBitfields(paramGroupTypeReturnBitfields);
    }

    inline uint8_t getMessageType(size_t typeReturnBitfieldsIdx) const
    {
        if (typeReturnBitfieldsIdx < typeReturnBitfieldsList_.size())
        {
            return typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).getMessageType();
        }
        else
        {
            throw std::out_of_range("Index out of range in getMessageType: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_");
        }
    }
    // inline void setMessageType(size_t typeReturnBitfieldsIdx, uint8_t messageType)
    // {
    //     if (typeReturnBitfieldsIdx == typeReturnBitfieldsList_.size())
    //     {
    //         typeReturnBitfieldsList_.resize(typeReturnBitfieldsList_.size() + 1);
    //     }
    //     else if (typeReturnBitfieldsIdx > typeReturnBitfieldsList_.size())
    //     {
    //         throw std::out_of_range("Index out of range in setMessageType: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_ + 1, add the elements sequentially");
    //     }
    //     typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).setMessageType(messageType);
    // }

    inline uint8_t getNumberOfReturnBitfields(size_t typeReturnBitfieldsIdx) const
    {
        if (typeReturnBitfieldsIdx < typeReturnBitfieldsList_.size())
        {
            return typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).getNumberOfReturnBitfields();
        }
        else
        {
            throw std::out_of_range("Index out of range in getNumberOfReturnBitfields: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_");
        }
    }
    inline void setNumberOfReturnBitfields(size_t typeReturnBitfieldsIdx, uint8_t numberOfReturnBitfields)
    {
        if (typeReturnBitfieldsIdx == typeReturnBitfieldsList_.size())
        {
            typeReturnBitfieldsList_.resize(typeReturnBitfieldsList_.size() + 1);
        }
        else if (typeReturnBitfieldsIdx > typeReturnBitfieldsList_.size())
        {
            throw std::out_of_range("Index out of range in setNumberOfReturnBitfields: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_ + 1, add the elements sequentially");
        }
        typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).setNumberOfReturnBitfields(numberOfReturnBitfields);
    }

    inline uint8_t getReturnBitfield(size_t typeReturnBitfieldsIdx, size_t groupNumberOfReturnBitfieldsIdx) const
    {
        if (typeReturnBitfieldsIdx < typeReturnBitfieldsList_.size())
        {
            return typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).getReturnBitfield(groupNumberOfReturnBitfieldsIdx);
        }
        else
        {
            throw std::out_of_range("Index out of range in getReturnBitfield: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_");
        }
    }
    inline void setReturnBitfield(size_t typeReturnBitfieldsIdx, size_t groupNumberOfReturnBitfieldsIdx, uint8_t returnBitfield)
    {
        if (typeReturnBitfieldsIdx == typeReturnBitfieldsList_.size())
        {
            typeReturnBitfieldsList_.resize(typeReturnBitfieldsList_.size() + 1);
        }
        else if (typeReturnBitfieldsIdx > typeReturnBitfieldsList_.size())
        {
            throw std::out_of_range("Index out of range in setReturnBitfield: typeReturnBitfieldsIdx exceeds size of typeReturnBitfieldsList_ + 1, add the elements sequentially");
        }
        typeReturnBitfieldsList_.at(typeReturnBitfieldsIdx).setReturnBitfield(groupNumberOfReturnBitfieldsIdx, returnBitfield);
    }
};
class LoginResponse
{
private:
    uint16_t startOfMessage_;             // Must be 0xBA 0xBA.
    uint16_t messageLength_;              // Number of bytes for the message, including this field but not including the two bytes for the StartOfMessage field.
    uint8_t messageType_;                 // Login Request (0x37).
    uint8_t matchingUnit_;                // Always 0 for inbound (Member to Cboe) messages.
    uint32_t sequenceNumber_;             // Always 0 for session level messages.
    char loginResponseStatus_[1];         // Accepted, or the reason for the rejection.
    char loginResponseText_[60];          // Human-readable text with additional information about the reason for rejection.
    uint8_t noUnspecifiedUnitReplay_;     // Echoed back from the original Login Request message.
    uint32_t lastReceivedSequenceNumber_; // Last inbound (Member to Cboe) message sequence number processed by Cboe
    uint8_t numberOfUnits_;               // Number of unit/sequence pairs to follow, one per unit from which the Member has received messages.
    std::vector<GroupNumberOfUnitsMember> groupNumberOfUnitsList_;

public:
    inline uint16_t getStartOfMessage() const { return startOfMessage_; }
    inline void setStartOfMessage(const uint16_t startOfMessage) { startOfMessage_ = startOfMessage; }

    inline uint16_t getMessageLength() const { return messageLength_; }
    inline void setMessageLength(const uint16_t messageLength) { messageLength_ = messageLength; }

    inline uint8_t getMessageType() const { return messageType_; }
    inline void setMessageType(const uint8_t messageType) { messageType_ = messageType; }

    inline uint8_t getMatchingUnit() const { return matchingUnit_; }
    inline void setMatchingUnit(const uint8_t matchingUnit) { matchingUnit_ = matchingUnit; }

    inline uint32_t getSequenceNumber() const { return sequenceNumber_; }
    inline void setSequenceNumber(const uint32_t sequenceNumber) { sequenceNumber_ = sequenceNumber; }

    inline const char *getLoginResponseStatus() const { return loginResponseStatus_; }
    inline void setLoginResponseStatus(const char *loginResponseStatus)
    {
        strncpy(loginResponseStatus_, loginResponseStatus, 1);
    }

    inline const char *getLoginResponseText() const { return loginResponseText_; }
    inline void setLoginResponseText(const char *loginResponseText)
    {
        strncpy(loginResponseText_, loginResponseText, 60);
    }

    inline uint8_t getNoUnspecifiedUnitReplay() const { return noUnspecifiedUnitReplay_; }
    inline void setNoUnspecifiedUnitReplay(const uint8_t noUnspecifiedUnitReplay) { noUnspecifiedUnitReplay_ = noUnspecifiedUnitReplay; }

    inline uint32_t getLastReceivedSequenceNumber() const { return lastReceivedSequenceNumber_; }
    inline void setLastReceivedSequenceNumber(const uint32_t lastReceivedSequenceNumber) { lastReceivedSequenceNumber_ = lastReceivedSequenceNumber; }

    inline uint8_t getNumberOfUnits() const { return numberOfUnits_; }
    inline void setNumberOfUnits(const uint8_t numberOfUnits) { numberOfUnits_ = numberOfUnits; }

    inline std::vector<GroupNumberOfUnitsMember> getGroupNumberOfUnits() const { return groupNumberOfUnitsList_; }
    inline void setGroupNumberOfUnits(std::vector<GroupNumberOfUnitsMember> groupNumberOfUnitsList) { groupNumberOfUnitsList_ = groupNumberOfUnitsList_; }

    inline uint8_t getUnitNumber(size_t groupNumberOfUnitsIdx) const
    {
        if (groupNumberOfUnitsIdx < groupNumberOfUnitsList_.size())
        {
            return groupNumberOfUnitsList_.at(groupNumberOfUnitsIdx).getUnitNumber();
        }
        else
        {
            throw std::out_of_range("Index out of range in getUnitNumber: groupNumberOfUnitsIdx exceeds size of groupNumberOfUnitsList_");
        }
    }
    inline void setUnitNumber(size_t groupNumberOfUnitsIdx, uint8_t unitNumber)
    {
        if (groupNumberOfUnitsIdx == groupNumberOfUnitsList_.size())
        {
            groupNumberOfUnitsList_.resize(groupNumberOfUnitsList_.size() + 1);
        }
        else if (groupNumberOfUnitsIdx > groupNumberOfUnitsList_.size())
        {
            throw std::out_of_range("Index out of range in setUnitNumber: groupNumberOfUnitsIdx exceeds size of groupNumberOfUnitsList_ + 1, add the elements sequentially");
        }
        groupNumberOfUnitsList_.at(groupNumberOfUnitsIdx).setUnitNumber(unitNumber);
    }

    inline uint32_t getUnitSequence(size_t groupNumberOfUnitsIdx) const
    {
        if (groupNumberOfUnitsIdx < groupNumberOfUnitsList_.size())
        {
            return groupNumberOfUnitsList_.at(groupNumberOfUnitsIdx).getUnitSequence();
        }
        else
        {
            throw std::out_of_range("Index out of range in getUnitSequence: groupNumberOfUnitsIdx exceeds size of groupNumberOfUnitsList_");
        }
    }
    inline void setUnitSequence(size_t groupNumberOfUnitsIdx, uint32_t unitSequence)
    {
        if (groupNumberOfUnitsIdx == groupNumberOfUnitsList_.size())
        {
            groupNumberOfUnitsList_.resize(groupNumberOfUnitsList_.size() + 1);
        }
        else if (groupNumberOfUnitsIdx > groupNumberOfUnitsList_.size())
        {
            throw std::out_of_range("Index out of range in setUnitSequence: groupNumberOfUnitsIdx exceeds size of groupNumberOfUnitsList_ + 1, add the elements sequentially");
        }
        groupNumberOfUnitsList_.at(groupNumberOfUnitsIdx).setUnitSequence(unitSequence);
    }
};
