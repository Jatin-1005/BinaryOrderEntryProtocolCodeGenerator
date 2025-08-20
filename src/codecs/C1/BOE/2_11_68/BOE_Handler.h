#pragma once
#include <iomanip>
#include "BOE_Stream.h"
#include "BOE_Msgs.h"
#include "BOE_Encoder.h"

class CustomHandler
{
public:
    bool operator()(const Status &status)
    {
        std::cout << status.getInfo() << std::endl;
        return true;
    }
    template <typename T>
    bool operator()(const T &msg, const Status &status)
    {
        std::cout << status.getInfo() << std::endl;
        if (status.getStatus() == StatusEnum::COMPLETE)
        {
            std::cout << std::hex << std::uppercase << msg << std::endl;
        }
        return true;
    }
};