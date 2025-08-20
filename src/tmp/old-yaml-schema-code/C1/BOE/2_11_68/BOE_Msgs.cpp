#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include <variant>

enum class MessageEnum
{
    LOGINREQUEST = 55,
    LOGINRESPONSE = 36
};

enum class TypeEnum
{
    UNITSEQUENCES = 128,
    RETURNBITFIELDS = 129
};


struct GroupNumberOfReturnBitfields
{
private:
    uint8_t returnBitfield_; // Bitfield identifying fields to return.

public:
    inline uint8_t getReturnBitfield() const { return returnBitfield_; }
    inline void setReturnBitfield(const uint8_t returnBitfield) { returnBitfield_ = returnBitfield; }
};

struct GroupNumberOfUnits
{
private:
    uint8_t unitNumber_;    // Unit number.
    uint32_t unitSequence_; // Last received sequence number for the unit.

public:
    inline uint8_t getUnitNumber() const { return unitNumber_; }
    inline void setUnitNumber(const uint8_t unitNumber) { unitNumber_ = unitNumber; }

    inline uint32_t getUnitSequence() const { return unitSequence_; }
    inline void setUnitSequence(const uint32_t unitSequence) { unitSequence_ = unitSequence; }
};

struct TypeUnitSequences
{
private:
    uint16_t paramGroupLengthUnitSequences_; // Number of bytes for the parameter group, including this field.
    uint8_t paramGroupTypeUnitSequences_;    // 0x80.
    uint8_t noUnspecifiedUnitReplay_;        // Flag indicating whether to replay missed outgoing (Cboe to Member) messages for unspecified units. 0x00 = False, 0x01 = True.
    uint8_t numberOfUnits_;                  // Number of unit/sequence pairs to follow, one per unit from which the Member has received messages.
    std::vector<GroupNumberOfUnits> groupNumberOfUnitsList_;

public:
    inline uint16_t getParamGroupLengthUnitSequences() const { return paramGroupLengthUnitSequences_; }
    inline void setParamGroupLengthUnitSequences(const uint16_t paramGroupLengthUnitSequences) { paramGroupLengthUnitSequences_ = paramGroupLengthUnitSequences; }

    inline uint8_t getParamGroupTypeUnitSequences() const { return paramGroupTypeUnitSequences_; }
    inline void setParamGroupTypeUnitSequences(const uint8_t paramGroupTypeUnitSequences) { paramGroupTypeUnitSequences_ = paramGroupTypeUnitSequences; }

    inline uint8_t getNoUnspecifiedUnitReplay() const { return noUnspecifiedUnitReplay_; }
    inline void setNoUnspecifiedUnitReplay(const uint8_t noUnspecifiedUnitReplay) { noUnspecifiedUnitReplay_ = noUnspecifiedUnitReplay; }

    inline uint8_t getNumberOfUnits() const { return numberOfUnits_; }
    inline void setNumberOfUnits(const uint8_t numberOfUnits) { numberOfUnits_ = numberOfUnits; }

    inline std::vector<GroupNumberOfUnits> getGroupNumberOfUnits() const { return groupNumberOfUnitsList_; }
    inline void setGroupNumberOfUnits(GroupNumberOfUnits groupNumberOfUnits) { groupNumberOfUnitsList_.push_back(groupNumberOfUnits); }
};

struct TypeReturnBitfields
{
private:
    uint16_t paramGroupLengthReturnBitfields_; // Number of bytes for the parameter group, including this field.
    uint8_t paramGroupTypeReturnBitfields_;    // 0x80.
    uint8_t messageType_;                      // Return message type for which the bitfields are being specified (e.g., 0x25 for an Order Acknowledgment message).
    uint8_t numberOfReturnBitfields_;          // Number of bitfields to follow.
    std::vector<GroupNumberOfReturnBitfields> groupNumberOfReturnBitfieldsList_;

public:
    inline uint16_t getParamGroupLengthReturnBitfields() const { return paramGroupLengthReturnBitfields_; }
    inline void setParamGroupLengthReturnBitfields(const uint16_t paramGroupLengthReturnBitfields) { paramGroupLengthReturnBitfields_ = paramGroupLengthReturnBitfields; }

    inline uint8_t getParamGroupTypeReturnBitfields() const { return paramGroupTypeReturnBitfields_; }
    inline void setParamGroupTypeReturnBitfields(const uint8_t paramGroupTypeReturnBitfields) { paramGroupTypeReturnBitfields_ = paramGroupTypeReturnBitfields; }

    inline uint8_t getMessageType() const { return messageType_; }
    inline void setMessageType(const uint8_t messageType) { messageType_ = messageType; }

    inline uint8_t getNumberOfReturnBitfields() const { return numberOfReturnBitfields_; }
    inline void setNumberOfReturnBitfields(const uint8_t numberOfReturnBitfields) { numberOfReturnBitfields_ = numberOfReturnBitfields; }

    inline std::vector<GroupNumberOfReturnBitfields> getGroupNumberOfReturnBitfields() const { return groupNumberOfReturnBitfieldsList_; }
    inline void setGroupNumberOfReturnBitfields(GroupNumberOfReturnBitfields groupNumberOfReturnBitfields) { groupNumberOfReturnBitfieldsList_.push_back(groupNumberOfReturnBitfields); }
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
    inline void setTypeUnitSequences(TypeUnitSequences typeUnitSequences) { typeUnitSequencesList_.push_back(typeUnitSequences); }
    inline std::vector<TypeReturnBitfields> getTypeReturnBitfields() const { return typeReturnBitfieldsList_; }
    inline void setTypeReturnBitfields(TypeReturnBitfields typeReturnBitfields) { typeReturnBitfieldsList_.push_back(typeReturnBitfields); }
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
    std::vector<GroupNumberOfUnits> groupNumberOfUnitsList_;

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

    inline std::vector<GroupNumberOfUnits> getGroupNumberOfUnits() const { return groupNumberOfUnitsList_; }
    inline void setGroupNumberOfUnits(GroupNumberOfUnits groupNumberOfUnits) { groupNumberOfUnitsList_.push_back(groupNumberOfUnits); }
};
