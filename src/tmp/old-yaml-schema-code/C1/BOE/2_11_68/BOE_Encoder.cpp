#pragma once
#include <iostream>
#include <string>
#include <vector>
class Encoder
{
private:
    void _encode(char *&start, char *end, const GroupNumberOfReturnBitfields &field, Status &status)
    {
        _encode(start, end, field.getReturnBitfield(), status);
    }
    void _encode(char *&start, char *end, const GroupNumberOfUnits &field, Status &status)
    {
        _encode(start, end, field.getUnitNumber(), status);
        _encode(start, end, field.getUnitSequence(), status);
    }
    void _encode(char *&start, char *end, const TypeUnitSequences &field, Status &status)
    {
        _encode(start, end, field.getParamGroupLengthUnitSequences(), status);
        _encode(start, end, field.getParamGroupTypeUnitSequences(), status);
        _encode(start, end, field.getNoUnspecifiedUnitReplay(), status);
        _encode(start, end, field.getNumberOfUnits(), status);
        _encode(start, end, field.getGroupNumberOfUnits(), status);
    }
    void _encode(char *&start, char *end, const TypeReturnBitfields &field, Status &status)
    {
        _encode(start, end, field.getParamGroupLengthReturnBitfields(), status);
        _encode(start, end, field.getParamGroupTypeReturnBitfields(), status);
        _encode(start, end, field.getMessageType(), status);
        _encode(start, end, field.getNumberOfReturnBitfields(), status);
        _encode(start, end, field.getGroupNumberOfReturnBitfields(), status);
    }
    void _encode(char *&start, char *end, const LoginRequest &msg, Status &status)
    {
        _encode(start, end, msg.getStartOfMessage(), status);
        _encode(start, end, msg.getMessageLength(), status);
        _encode(start, end, msg.getMessageType(), status);
        _encode(start, end, msg.getMatchingUnit(), status);
        _encode(start, end, msg.getSequenceNumber(), status);
        _encode<4>(start, end, msg.getSessionSubID(), status);
        _encode<4>(start, end, msg.getUsername(), status);
        _encode<10>(start, end, msg.getPassword(), status);
        _encode(start, end, msg.getNumberOfParamGroups(), status);
        _encode(start, end, msg.getTypeUnitSequences(), status);
        _encode(start, end, msg.getTypeReturnBitfields(), status);
        status.updateStatus(StatusEnum::COMPLETE);
    }
    void _encode(char *&start, char *end, const LoginResponse &msg, Status &status)
    {
        _encode(start, end, msg.getStartOfMessage(), status);
        _encode(start, end, msg.getMessageLength(), status);
        _encode(start, end, msg.getMessageType(), status);
        _encode(start, end, msg.getMatchingUnit(), status);
        _encode(start, end, msg.getSequenceNumber(), status);
        _encode<1>(start, end, msg.getLoginResponseStatus(), status);
        _encode<60>(start, end, msg.getLoginResponseText(), status);
        _encode(start, end, msg.getNoUnspecifiedUnitReplay(), status);
        _encode(start, end, msg.getLastReceivedSequenceNumber(), status);
        _encode(start, end, msg.getNumberOfUnits(), status);
        _encode(start, end, msg.getGroupNumberOfUnits(), status);
        status.updateStatus(StatusEnum::COMPLETE);
    }
    template <typename U>
    void _encode(char *&start, char *end, U field, Status &status)
    {
        if (start + sizeof(field) > end)
        {
            status.updateStatus(StatusEnum::BUFFER_OVERFLOW);
            return;
        }

        *reinterpret_cast<U *>(start) = field;

        start += sizeof(field);
        status.updateNextStart(start);
    }

    template <size_t len>
    void _encode(char *&start, char *end, const char *field, Status &status)
    {
        if (start + len > end)
        {
            status.updateStatus(StatusEnum::BUFFER_OVERFLOW);
            return;
        }

        for (size_t i = 0; i < len; i++)
        {
            start[i] = field[i];
        }

        start += len;
        status.updateNextStart(start);
    }

    template <typename U>
    void _encode(char *&start, char *end, const std::vector<U> &field, Status &status)
    {
        for (const auto &element : field)
        {
            _encode(start, end, element, status); // won't work for vector of strings
            if (status.getStatus() == StatusEnum::BUFFER_OVERFLOW)
            {
                return;
            }
        }
    }

public:
    template <typename T>
    void encodeMessage(char *&start, char *end, const T &msg, Status &status)
    {
        _encode(start, end, msg, status);
    }
};