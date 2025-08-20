
#pragma once
#include "/root/Subhash/src/common/status.h"
#include "/root/Subhash/src/common/utils.h"
#include "BOE_Handler.h"
#include "BOE_Msgs.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
enum TypeLocationEnum : size_t
{
    MESSAGE_LOC = 4,   // Location of message type in the payload
    PARAMGROUP_LOC = 2 // Location of param group type in the payload
};

template <typename HandlerType>
class Decoder
{

    // Member variables to hold decoded fields for various custom datatypes
    GroupNumberOfNewOrderCrossBitfields groupNumberOfNewOrderCrossBitfields_;
    GroupRepeatingGroupsOfNewOrderCross groupRepeatingGroupsOfNewOrderCross_;
    GroupNumberOfUnits groupNumberOfUnits_;
    GroupUnitSequences groupUnitSequences_;
    GroupNumberOfReturnBitfields groupNumberOfReturnBitfields_;
    GroupReturnBitfields groupReturnBitfields_;
    LoginRequest loginRequest_;
    NewOrderCross newOrderCross_;

    // Extracts the type (e.g., message or param group type) from a specific location
    inline uint8_t _getType(char *&start, char *&end, size_t loc, Status &status)
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return 0;
        if (start + loc + sizeof(uint8_t) > end)
        {
            status.updateStatus(StatusEnum::NEED_MORE_DATA);
            return 0;
        }
        uint8_t type(*reinterpret_cast<uint8_t *>(start + loc));
        return type;
    }

    // Decodes a field of the given type
    template <typename FieldType>
    inline FieldType _decode(char *&start, char *end, Status &status)
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return FieldType{};
        if (start + sizeof(FieldType) > end)
        {
            status.updateStatus(StatusEnum::NEED_MORE_DATA);
            return FieldType{};
        }

        FieldType field(*reinterpret_cast<FieldType *>(start));
        start += sizeof(FieldType);
        return field;
    }

    // Verifies a field against an expected value
    template <typename FieldType>
    inline void _verifyField(char *&start, char *end, FieldType verify, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;
        if (start + sizeof(FieldType) > end)
        {
            status.updateStatus(StatusEnum::NEED_MORE_DATA);
            return;
        }

        FieldType field(*reinterpret_cast<FieldType *>(start));
        start += sizeof(FieldType);

        if (field != verify)
        {
            status.updateStatus(StatusEnum::CORRUPTED_PAYLOAD);
            return;
        }
        return;
    }

    void _decodeGroupNumberOfNewOrderCrossBitfields(char *&start, char *end, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;

        groupNumberOfNewOrderCrossBitfields_.setNewOrderCrossBitfield(_decode<uint8_t>(start, end, status));
    }

    void _decodeGroupRepeatingGroupsOfNewOrderCross(char *&start, char *end, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;

        // verification for constant field
        char side = _decode<char>(start, end, status);
        if (!sideEnumOptions.count(side))
        {
            status.updateStatus(StatusEnum::INVALID_PAYLOAD);
            return;
        }
        groupRepeatingGroupsOfNewOrderCross_.setSide(static_cast<GroupRepeatingGroupsOfNewOrderCross::SideEnum>(side));

        groupRepeatingGroupsOfNewOrderCross_.setAllocQty(_decode<uint32_t>(start, end, status));

        const char *clOrdID = start;
        groupRepeatingGroupsOfNewOrderCross_.setClOrdID(clOrdID);
        start += StringLengthsEnum::CLORDID;

        // verification for constant field
        char capacity = _decode<char>(start, end, status);
        if (!capacityEnumOptions.count(capacity))
        {
            status.updateStatus(StatusEnum::INVALID_PAYLOAD);
            return;
        }
        groupRepeatingGroupsOfNewOrderCross_.setCapacity(static_cast<GroupRepeatingGroupsOfNewOrderCross::CapacityEnum>(capacity));

        // verification for constant field
        char openClose = _decode<char>(start, end, status);
        if (!openCloseEnumOptions.count(openClose))
        {
            status.updateStatus(StatusEnum::INVALID_PAYLOAD);
            return;
        }
        groupRepeatingGroupsOfNewOrderCross_.setOpenClose(static_cast<GroupRepeatingGroupsOfNewOrderCross::OpenCloseEnum>(openClose));

        const char *giveUpFirmID = start;
        groupRepeatingGroupsOfNewOrderCross_.setGiveUpFirmID(giveUpFirmID);
        start += StringLengthsEnum::GIVEUPFIRMID;
        if (newOrderCross_.getGroupNumberOfNewOrderCrossBitfields()[static_cast<uint8_t>(NewOrderCrossBitfieldIdx::ACCOUNT)].getNewOrderCrossBitfield() & (1 << static_cast<uint8_t>(NewOrderCrossBitIdx::ACCOUNT)))
        {
            const char *account = start;
            groupRepeatingGroupsOfNewOrderCross_.setAccount(account);
            start += StringLengthsEnum::ACCOUNT;
        }
        if (newOrderCross_.getGroupNumberOfNewOrderCrossBitfields()[static_cast<uint8_t>(NewOrderCrossBitfieldIdx::CMTANUMBER)].getNewOrderCrossBitfield() & (1 << static_cast<uint8_t>(NewOrderCrossBitIdx::CMTANUMBER)))
        {
            const char *cMTANumber = start;
            groupRepeatingGroupsOfNewOrderCross_.setCMTANumber(cMTANumber);
            start += StringLengthsEnum::CMTANUMBER;
        }
        if (newOrderCross_.getGroupNumberOfNewOrderCrossBitfields()[static_cast<uint8_t>(NewOrderCrossBitfieldIdx::CLEARINGACCOUNT)].getNewOrderCrossBitfield() & (1 << static_cast<uint8_t>(NewOrderCrossBitIdx::CLEARINGACCOUNT)))
        {
            const char *clearingAccount = start;
            groupRepeatingGroupsOfNewOrderCross_.setClearingAccount(clearingAccount);
            start += StringLengthsEnum::CLEARINGACCOUNT;
        }
        if (newOrderCross_.getGroupNumberOfNewOrderCrossBitfields()[static_cast<uint8_t>(NewOrderCrossBitfieldIdx::CLEARINGOPTIONALDATA)].getNewOrderCrossBitfield() & (1 << static_cast<uint8_t>(NewOrderCrossBitIdx::CLEARINGOPTIONALDATA)))
        {
            const char *clearingOptionalData = start;
            groupRepeatingGroupsOfNewOrderCross_.setClearingOptionalData(clearingOptionalData);
            start += StringLengthsEnum::CLEARINGOPTIONALDATA;
        }
    }

    void _decodeGroupNumberOfUnits(char *&start, char *end, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;

        groupNumberOfUnits_.setUnitNumber(_decode<uint8_t>(start, end, status));

        groupNumberOfUnits_.setUnitSequence(_decode<uint32_t>(start, end, status));
    }

    void _decodeGroupUnitSequences(char *&start, char *end, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;

        groupUnitSequences_.setParamGroupLength(_decode<uint16_t>(start, end, status));

        _verifyField(start, end, ParamGroupTypesEnum::UNITSEQUENCES, status);

        // verification for constant field
        uint8_t noUnspecifiedUnitReplay = _decode<uint8_t>(start, end, status);
        if (!noUnspecifiedUnitReplayEnumOptions.count(noUnspecifiedUnitReplay))
        {
            status.updateStatus(StatusEnum::INVALID_PAYLOAD);
            return;
        }
        groupUnitSequences_.setNoUnspecifiedUnitReplay(static_cast<GroupUnitSequences::NoUnspecifiedUnitReplayEnum>(noUnspecifiedUnitReplay));

        // decoding group count, and respective groups/types from the payload
        uint8_t numberOfUnits = _decode<uint8_t>(start, end, status);
        for (uint8_t i = 0; i < numberOfUnits; ++i)
        {

            _decodeGroupNumberOfUnits(start, end, status);
            if (status.getStatus() != StatusEnum::PARSING)
                return;
            groupUnitSequences_.setGroupNumberOfUnits(std::move(groupNumberOfUnits_));
        }
    }

    void _decodeGroupNumberOfReturnBitfields(char *&start, char *end, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;

        groupNumberOfReturnBitfields_.setReturnBitfield(_decode<uint8_t>(start, end, status));
    }

    void _decodeGroupReturnBitfields(char *&start, char *end, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;

        groupReturnBitfields_.setParamGroupLength(_decode<uint16_t>(start, end, status));

        _verifyField(start, end, ParamGroupTypesEnum::RETURNBITFIELDS, status);

        groupReturnBitfields_.setMessageType(_decode<uint8_t>(start, end, status));

        // decoding group count, and respective groups/types from the payload
        uint8_t numberOfReturnBitfields = _decode<uint8_t>(start, end, status);
        for (uint8_t i = 0; i < numberOfReturnBitfields; ++i)
        {

            _decodeGroupNumberOfReturnBitfields(start, end, status);
            if (status.getStatus() != StatusEnum::PARSING)
                return;
            groupReturnBitfields_.setGroupNumberOfReturnBitfields(std::move(groupNumberOfReturnBitfields_));
        }
    }

    // Decode for LoginRequest class
    void _decodeLoginRequest(char *&start, char *end, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;

        _verifyField(start, end, StartOfMessageEnum::STARTOFMESSAGE, status);

        loginRequest_.setMessageLength(_decode<uint16_t>(start, end, status));

        _verifyField(start, end, MessagesEnum::LOGINREQUEST, status);

        _verifyField(start, end, MatchingUnitEnum::MATCHINGUNIT, status);

        _verifyField(start, end, SequenceNumberEnum::SEQUENCENUMBER, status);

        const char *sessionSubID = start;
        loginRequest_.setSessionSubID(sessionSubID);
        start += StringLengthsEnum::SESSIONSUBID;

        const char *username = start;
        loginRequest_.setUsername(username);
        start += StringLengthsEnum::USERNAME;

        const char *password = start;
        loginRequest_.setPassword(password);
        start += StringLengthsEnum::PASSWORD;

        // decoding group count, and respective groups/types from the payload
        uint8_t numberOfParamGroups = _decode<uint8_t>(start, end, status);
        for (uint8_t i = 0; i < numberOfParamGroups; ++i)
        {
            ParamGroupTypesEnum type = static_cast<ParamGroupTypesEnum>(_getType(start, end, TypeLocationEnum::PARAMGROUP_LOC, status));
            if (status.getStatus() != StatusEnum::PARSING)
                return;
            if (type == ParamGroupTypesEnum::UNITSEQUENCES)
            {
                _decodeGroupUnitSequences(start, end, status);
                if (status.getStatus() != StatusEnum::PARSING)
                    return;
                loginRequest_.setGroupUnitSequences(std::move(groupUnitSequences_));
                groupUnitSequences_.reset();
            }
            else if (type == ParamGroupTypesEnum::RETURNBITFIELDS)
            {
                _decodeGroupReturnBitfields(start, end, status);
                if (status.getStatus() != StatusEnum::PARSING)
                    return;
                loginRequest_.setGroupReturnBitfields(std::move(groupReturnBitfields_));
                groupReturnBitfields_.reset();
            }
        }
        if (status.getStatus() == StatusEnum::PARSING)
            status.updateStatus(StatusEnum::COMPLETE);
    }

    // Decode for NewOrderCross class
    void _decodeNewOrderCross(char *&start, char *end, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;

        _verifyField(start, end, StartOfMessageEnum::STARTOFMESSAGE, status);

        newOrderCross_.setMessageLength(_decode<uint16_t>(start, end, status));

        _verifyField(start, end, MessagesEnum::NEWORDERCROSS, status);

        _verifyField(start, end, MatchingUnitEnum::MATCHINGUNIT, status);

        newOrderCross_.setSequenceNumber(_decode<uint32_t>(start, end, status));

        const char *crossID = start;
        newOrderCross_.setCrossID(crossID);
        start += StringLengthsEnum::CROSSID;

        // verification for constant field
        char crossType = _decode<char>(start, end, status);
        if (!crossTypeEnumOptions.count(crossType))
        {
            status.updateStatus(StatusEnum::INVALID_PAYLOAD);
            return;
        }
        newOrderCross_.setCrossType(static_cast<NewOrderCross::CrossTypeEnum>(crossType));

        // verification for constant field
        char crossPrioritization = _decode<char>(start, end, status);
        if (!crossPrioritizationEnumOptions.count(crossPrioritization))
        {
            status.updateStatus(StatusEnum::INVALID_PAYLOAD);
            return;
        }
        newOrderCross_.setCrossPrioritization(static_cast<NewOrderCross::CrossPrioritizationEnum>(crossPrioritization));

        newOrderCross_.setPrice(_decode<uint64_t>(start, end, status));

        newOrderCross_.setOrderQty(_decode<uint32_t>(start, end, status));

        // decoding group count, and respective groups/types from the payload
        uint8_t numberOfNewOrderCrossBitfields = _decode<uint8_t>(start, end, status);
        for (uint8_t i = 0; i < numberOfNewOrderCrossBitfields; ++i)
        {

            _decodeGroupNumberOfNewOrderCrossBitfields(start, end, status);
            if (status.getStatus() != StatusEnum::PARSING)
                return;
            newOrderCross_.setGroupNumberOfNewOrderCrossBitfields(std::move(groupNumberOfNewOrderCrossBitfields_));
        }

        // decoding group count, and respective groups/types from the payload
        uint16_t groupCnt = _decode<uint16_t>(start, end, status);
        for (uint16_t i = 0; i < groupCnt; ++i)
        {

            _decodeGroupRepeatingGroupsOfNewOrderCross(start, end, status);
            if (status.getStatus() != StatusEnum::PARSING)
                return;
            newOrderCross_.setGroupRepeatingGroupsOfNewOrderCross(std::move(groupRepeatingGroupsOfNewOrderCross_));
        }

        // using bitfields to check which optionals fields are present at the end, and should be decoded.
        auto bitfields = newOrderCross_.getGroupNumberOfNewOrderCrossBitfields();
        size_t bitfieldIdx = 0;
        size_t bitIdx = 0;
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::SYMBOL);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::SYMBOL);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            const char *symbol = start;
            newOrderCross_.setSymbol(symbol);
            start += StringLengthsEnum::SYMBOL;
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::MATURITYDATE);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::MATURITYDATE);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            newOrderCross_.setMaturityDate(_decode<uint32_t>(start, end, status));
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::STRIKEPRICE);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::STRIKEPRICE);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            newOrderCross_.setStrikePrice(_decode<uint64_t>(start, end, status));
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::PUTORCALL);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::PUTORCALL);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            newOrderCross_.setPutOrCall(_decode<char>(start, end, status));
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::EXECINST);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::EXECINST);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            newOrderCross_.setExecInst(_decode<char>(start, end, status));
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::ATTRIBUTEDQUOTE);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::ATTRIBUTEDQUOTE);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            newOrderCross_.setAttributedQuote(_decode<char>(start, end, status));
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::TARGETPARTYID);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::TARGETPARTYID);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            const char *targetPartyID = start;
            newOrderCross_.setTargetPartyID(targetPartyID);
            start += StringLengthsEnum::TARGETPARTYID;
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::PREVENTMATCH);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::PREVENTMATCH);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            const char *preventMatch = start;
            newOrderCross_.setPreventMatch(preventMatch);
            start += StringLengthsEnum::PREVENTMATCH;
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::AUTOMATCH);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::AUTOMATCH);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            newOrderCross_.setAutoMatch(_decode<char>(start, end, status));
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::AUTOMATCHPRICE);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::AUTOMATCHPRICE);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            newOrderCross_.setAutoMatchPrice(_decode<uint64_t>(start, end, status));
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::LASTPRIORITY);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::LASTPRIORITY);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            newOrderCross_.setLastPriority(_decode<char>(start, end, status));
        }
        bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::ROUTINGFIRMID);
        bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::ROUTINGFIRMID);
        if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
        {
            const char *routingFirmID = start;
            newOrderCross_.setRoutingFirmID(routingFirmID);
            start += StringLengthsEnum::ROUTINGFIRMID;
        }
        if (status.getStatus() == StatusEnum::PARSING)
            status.updateStatus(StatusEnum::COMPLETE);
    }

public:
    void decode(const std::vector<char> &hexPayload, Status &status) noexcept
    {
        // Convert hexadecimal payload to binary data
        std::vector<char> payload(hexPayload.size() / 2);
        for (size_t i = 0; i < hexPayload.size(); i += 2)
        {
            payload[i / 2] = static_cast<char>(hexPairToByte(hexPayload[i], hexPayload[i + 1]));
        }
        char *start = const_cast<char *>(payload.data());
        char *end = start + payload.size();

        HandlerType handler;
        MessagesEnum messageType = static_cast<MessagesEnum>(_getType(start, end, TypeLocationEnum::MESSAGE_LOC, status));
        if (messageType == MessagesEnum::LOGINREQUEST)
        {
            _decodeLoginRequest(start, end, status);
            handler(loginRequest_, status);
        }
        else if (messageType == MessagesEnum::NEWORDERCROSS)
        {
            _decodeNewOrderCross(start, end, status);
            handler(newOrderCross_, status);
        }
        else
        {
            status.updateStatus(StatusEnum::INVALID_MESSAGE_TYPE);
            handler(status);
        }
    }
    LoginRequest getLoginRequest()
    {
        return loginRequest_;
    }
    NewOrderCross getNewOrderCross()
    {
        return newOrderCross_;
    }
};
