#include "BOE_Msgs.cpp"
#include "BOE_Common.cpp"
#include "BOE_Decoder.cpp"
#include "BOE_Encoder.cpp"
#include "BOE_Handler.cpp"



int main(){
    char charBuffer[] = "BABA3D00370000000000303030315445535454455354494E47000000030F00800102014ABB0100020000000008008125030041050B00812C06004107004000";
    const size_t bufferSize = strlen(charBuffer);
    char buffer[bufferSize/2];
    for(int i = 0; i < bufferSize; i+=2)
    {
        buffer[i/2] = static_cast<char>(hexPairToByte(charBuffer[i], charBuffer[i+1]));
    }
    char* start = buffer;
    char* end = buffer + bufferSize/2;
    Decoder<CustomHandler> decoder;
    Status status;
    CustomHandler handler;
    decoder.decode(start, end, handler, status);

    // Properly allocating the buffer (start and end) based on required size


    // decoder.decode(string, status);
    return 0;
}


// template <size_t U>
// inline std::span<char, U> _getCharField(uint8_t*& start)
// {
//     std::span<char, U> spanField = std::span<char, U>(reinterpret_cast<char*>(start), U);
//     start += U;
//     return spanField;

// }
//     std::span<char, 4Z> spanView = _getCharField<4Z>(start);
//     spanView = _getCharField<4Z>(start);
//     for(int i = 0; i < 4; i++)
//     {
//         std::cout << spanView[i];
//     }
//     std::cout << std::endl;