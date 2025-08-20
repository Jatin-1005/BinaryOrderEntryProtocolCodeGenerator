#pragma once
enum class StatusEnum
{
    COMPLETE,
    PARSING,
    BUFFER_OVERFLOW,
    INVALID_PAYLOAD,
    INVALID_OBJECT,
    NEED_MORE_DATA,
    CORRUPTED_PAYLOAD,
    INVALID_MESSAGE_TYPE
};

class Status
{
private:
    StatusEnum status = StatusEnum::PARSING;
    char *nextStart = nullptr;

    constexpr static const char *InfoParsing = "Parsing";
    constexpr static const char *InfoComplete = "Completed successfully";
    constexpr static const char *InfoBufferOverflow = "Buffer overflow";
    constexpr static const char *InfoInvalidPayload = "Invalid payload";
    constexpr static const char *InfoInvalidObject = "Invalid object";
    constexpr static const char *InfoNeedMoreData = "Need more data";
    constexpr static const char *InfoCorruptedPayload = "Corrupted payload";
    constexpr static const char *InfoInvalidMessageType = "Invalid message type payload";

public:
    inline const char *getInfo() const
    {
        switch (status)
        {
        case StatusEnum::COMPLETE:
            return InfoComplete;
        case StatusEnum::BUFFER_OVERFLOW:
            return InfoBufferOverflow;
        case StatusEnum::INVALID_OBJECT:
            return InfoInvalidObject;
        case StatusEnum::INVALID_PAYLOAD:
            return InfoInvalidPayload;
        case StatusEnum::NEED_MORE_DATA:
            return InfoNeedMoreData;
        case StatusEnum::CORRUPTED_PAYLOAD:
            return InfoCorruptedPayload;
        case StatusEnum::INVALID_MESSAGE_TYPE:
            return InfoInvalidMessageType;
        default:
            return InfoParsing;
        }
    }

    inline StatusEnum getStatus() const
    {
        return status;
    }

    inline void updateStatus(StatusEnum currStatus)
    {
        status = currStatus;
    }

    inline char *getNextStart() const
    {
        return nextStart;
    }

    inline void updateNextStart(char *start)
    {
        nextStart = start;
    }

    inline char *reset()
    {
        status = StatusEnum::PARSING;
        return nextStart;
    }
};
