#pragma once
#include <iostream>
#include <cstdint>
#include <chrono>

template <typename T>
inline void print(T value, size_t width = sizeof(T))
{
    std::cout << static_cast<int>(value) << std::endl;
}

void print(const char *start, int width = sizeof(char *))
{
    for (int i = 0; i < width; i++)
    {
        std::cout << static_cast<int>(start[i]);
    }
    std::cout << std::endl;
    return;
}

template <typename T>
inline void Print(T value, size_t width = sizeof(T))
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