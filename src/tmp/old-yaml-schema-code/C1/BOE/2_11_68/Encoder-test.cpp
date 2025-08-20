#include "BOE_Msgs.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>  // For std::memcpy
#include <algorithm> // For std::min

enum class StatusEnum { INCOMPLETE, COMPLETE, ERROR, BUFFER_OVERFLOW };

class Status
{
public:
    StatusEnum status = StatusEnum::INCOMPLETE;
    char* nextStart = nullptr;
    constexpr static const char* InfoIncomplete = "Incomplete";
    constexpr static const char* InfoComplete = "Completed successfully";
    constexpr static const char* InfoBufferOverflow = "Buffer overflow";
    
    const char* getInfo() const {
        switch (status) {
            case StatusEnum::COMPLETE: return InfoComplete;
            case StatusEnum::BUFFER_OVERFLOW: return InfoBufferOverflow;
            case StatusEnum::ERROR: return "Error occurred";
            default: return InfoIncomplete;
        }
    }
};

class Encoder
{
private:
    // Encode primitive data types inline for performance
    template <typename U>
    inline void _encodePrimitive(char*& start, char* end, const U& field, Status& status) {
        if (start + sizeof(U) > end) {
            status.status = StatusEnum::BUFFER_OVERFLOW;
            return;
        }
        
        // Direct copy using pointer arithmetic instead of memcpy
        *reinterpret_cast<U*>(start) = field;
        start += sizeof(U);
    }

    // Main encoding logic for entire messages
    template <typename T>
    void _encode(char*& start, char* end, const T& msg, Status& status) {
        std::vector<std::vector<int>> myVec = {{47802, 47802}, {47802, 47802}};
        
        // Set message values for demonstration
        _encodePrimitive(start, end, msg.getStartOfMessage(), status);
        _encodeString(start, end, msg.getUsername(), status); // C-style string
        _encodeVector(start, end, myVec, status);

        if (status.status != StatusEnum::BUFFER_OVERFLOW) {
            status.status = StatusEnum::COMPLETE;
            status.nextStart = start;
        }
    }

    // Specialized template for encoding C-style strings
    void _encodeString(char*& start, char* end, const char* field, Status& status) {
        constexpr size_t len = 4;  // Example fixed-size string
        if (start + len > end) {
            status.status = StatusEnum::BUFFER_OVERFLOW;
            return;
        }

        // Manual copy for fixed-size string
        for (size_t i = 0; i < len; ++i) {
            start[i] = field[i];
        }
        start += len;  // Move the start pointer forward
    }

    // Template for encoding vectors efficiently
    template<typename U>
    void _encodeVector(char*& start, char* end, const std::vector<U>& vec, Status& status) {
        for (const auto& element : vec) {
            _encodePrimitive(start, end, element, status);  // Inline primitive encoding
            if (status.status == StatusEnum::BUFFER_OVERFLOW) break;
        }
    }

public:
    // Public encode function that starts the encoding process
    template <typename T>
    void encode(char*& start, char* end, const T& msg, Status& status) {
        _encode(start, end, msg, status);
    }
};

int main()
{
    LoginRequest loginRequest;
    Encoder encoder;

    // Properly allocating the buffer (start and end) based on required size
    constexpr size_t bufferSize = 20;
    alignas(8) char buffer[bufferSize];  // Aligned buffer for better performance
    char *start = buffer;
    char *end = buffer + bufferSize;

    // Encode the message
    Status status;
    encoder.encode(start, end, loginRequest, status);
    
    // Output encoding result
    std::cout << status.getInfo() << std::endl;
    std::cout << "Next start pointer: " << static_cast<void*>(status.nextStart) << std::endl;
    
    // Calculate how many bytes were written
    size_t bytesWritten = status.nextStart - buffer;

    // Print the buffer contents up to nextStart in hex
    std::cout << "Encoded buffer: ";
    for (size_t i = 0; i < bytesWritten; ++i) {
        std::cout << std::hex << static_cast<int>(static_cast<unsigned char>(buffer[i])) << " ";
    }
    std::cout << std::endl;

    return 0;
}
