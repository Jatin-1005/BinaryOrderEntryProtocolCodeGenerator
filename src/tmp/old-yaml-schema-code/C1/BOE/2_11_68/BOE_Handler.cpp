#include <iomanip>

class CustomHandler
{
public:
    bool operator()(const LoginRequest& msg){
        Encoder encoder;
        constexpr size_t bufferSize = 1024;
        char buffer[bufferSize];
        char *start = buffer;
        char *end = buffer + bufferSize;

        // Encode the message
        Status status;
        status.updateNextStart(start);
        encoder.encodeMessage(start, end, msg, status);

        // Output encoding result
        std::cout << status.getInfo() << std::endl;
        std::cout << "Next start pointer: " << static_cast<void *>(status.getNextStart()) << std::endl;
        

        // Calculate how many bytes were written
        size_t bytesWritten = status.getNextStart() - buffer;
        std::cout << "bytesWritten: " << bytesWritten << std::endl;

        // Print the buffer contents up to nextStart in hex
        std::cout << "Encoded buffer: " << std::endl;
        for (size_t i = 0; i < bytesWritten; ++i)
        {
            std::cout << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(static_cast<unsigned char>(buffer[i]));
        }
        std::cout << std::endl;
        return true;
    }
};