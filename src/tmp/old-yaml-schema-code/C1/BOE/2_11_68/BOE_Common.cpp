#include <iostream>
#include <cstdint>

template <typename T>
void Print(T value, size_t width = sizeof(T))
{
    std::cout << std::hex << static_cast<int>(value) << std::endl;
}

void Print(const char *start, int width = sizeof(char *))
{
    for (int i = 0; i < width; i++)
    {
        std::cout << std::hex << static_cast<int>(start[i]);
    }
    std::cout << std::endl;
    return;
}

inline uint8_t hexCharToByte(char c)
{
    return (c >= '0' && c <= '9') ? (c - '0') : (c >= 'A' && c <= 'F') ? (c - 'A' + 10)
                                                                       : (c - 'a' + 10);
}

inline uint8_t hexPairToByte(char hexPair0, char hexPair1)
{
    return ((hexCharToByte(hexPair0) << 4) | hexCharToByte(hexPair1));
}

enum class StatusEnum
{
    COMPLETE,
    INCOMPLETE,
    BUFFER_OVERFLOW
};

class Status
{
private:
    StatusEnum status = StatusEnum::INCOMPLETE;
    char *nextStart = nullptr;
    constexpr static const char *InfoIncomplete = "Incomplete";
    constexpr static const char *InfoComplete = "Completed successfully";
    constexpr static const char *InfoBufferOverflow = "Buffer overflow";

public:
    const char *getInfo() const
    {
        switch (status)
        {
        case StatusEnum::COMPLETE:
            return InfoComplete;
        case StatusEnum::BUFFER_OVERFLOW:
            return InfoBufferOverflow;
        default:
            return InfoIncomplete;
        }
    }

    StatusEnum getStatus()
    {
        return status;
    }
    inline void updateStatus(StatusEnum currStatus)
    {
        status = currStatus;
    }

    char *getNextStart()
    {
        return nextStart;
    }
    inline void updateNextStart(char *start)
    {
        nextStart = start;
    }
};