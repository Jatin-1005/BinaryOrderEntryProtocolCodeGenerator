#pragma once
#include "BOE_Msgs.cpp"
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
    void _encodeLoginRequest(char *&start, char *end, const LoginRequest &msg, Status &status)
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
    void _encode(char *&start, char *end, LoginResponse &msg, Status &status)
    {
        _encode(start, end, msg.getStartOfMessage(), status);
        _encode(start, end, msg.getMessageLength(), status);
        _encode(start, end, msg.getMessageType(), status);
        _encode(start, end, msg.getMatchingUnit(), status);
        _encode(start, end, msg.getSequenceNumber(), status);
        _encode(start, end, msg.getLoginResponseStatus(), status);
        _encode(start, end, msg.getLoginResponseText(), status);
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
        // Print(field);
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
        _encodeLoginRequest(start, end, msg, status);
    }
};

// int main()
// {
//     LoginRequest loginRequest;
//     Encoder encoder;

//     loginRequest.setStartOfMessage(47802);
//     loginRequest.setMessageLength(15616);
//     loginRequest.setMessageType(55);
//     loginRequest.setMatchingUnit(0);
//     loginRequest.setSequenceNumber(0);
//     loginRequest.setSessionSubID("0001");
//     loginRequest.setUsername("TEST");
//     loginRequest.setPassword("TESTING");

//     loginRequest.setNumberOfParamGroups(3);

//     loginRequest.setParamGroupLengthNoUnspecifiedUnitReplay(0, 3840);
//     loginRequest.setParamGroupTypeNoUnspecifiedUnitReplay(0, 128);
//     loginRequest.setNoUnspecifiedUnitReplay(0, 1);
//     loginRequest.setNumberOfUnits(0, 2);
//     loginRequest.setUnitNumber(0, 0, 1);
//     loginRequest.setUnitSequence(0, 0, 1253769472);
//     loginRequest.setUnitNumber(0, 1, 2);
//     loginRequest.setUnitSequence(0, 1, 0);

//     loginRequest.setParamGroupLengthMessageType(0, 2048);
//     loginRequest.setParamGroupTypeMessageType(0, 129);
//     loginRequest.setMessageType(0, 37);
//     loginRequest.setNumberOfReturnBitfields(0, 3);
//     loginRequest.setReturnBitfield(0, 0, 0);
//     loginRequest.setReturnBitfield(0, 1, 65);
//     loginRequest.setReturnBitfield(0, 2, 5);

//     loginRequest.setParamGroupLengthMessageType(1, 2816);
//     loginRequest.setParamGroupTypeMessageType(1, 129);
//     loginRequest.setMessageType(1, 44);
//     loginRequest.setNumberOfReturnBitfields(1, 6);
//     loginRequest.setReturnBitfield(1, 0, 0);
//     loginRequest.setReturnBitfield(1, 1, 65);
//     loginRequest.setReturnBitfield(1, 2, 7);
//     loginRequest.setReturnBitfield(1, 3, 0);
//     loginRequest.setReturnBitfield(1, 4, 64);
//     loginRequest.setReturnBitfield(1, 5, 0);

//     // Properly allocating the buffer (start and end) based on required size
//     constexpr size_t bufferSize = 1024;
//     alignas(8) char buffer[bufferSize];
//     char *start = buffer;
//     char *end = buffer + bufferSize;

//     // Encode the message
//     Status status;
//     status.updateNextStart(start);
//     encoder.encodeMessage(start, end, loginRequest, status);

//     // Output encoding result
//     std::cout << status.getInfo() << std::endl;
//     std::cout << "Next start pointer: " << static_cast<void *>(status.getNextStart()) << std::endl;

//     // Calculate how many bytes were written
//     size_t bytesWritten = status.getNextStart() - buffer;
//     std::cout << "bytesWritten: " << bytesWritten << std::endl;

//     // Print the buffer contents up to nextStart in hex
//     std::cout << "Encoded buffer: ";
//     for (size_t i = 0; i < bytesWritten; ++i)
//     {
//         std::cout << std::hex << static_cast<int>(static_cast<unsigned char>(buffer[i])) << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }