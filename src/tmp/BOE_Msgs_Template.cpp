#pragma once
#include <iostream>
#include <bitset>
#include <vector>
#include <memory>
#include <variant>

// Define a common Group template
// can we make this take any number of types as input to the template, and make the vector<T> to vector<variant<T1, T2, ...>, then code generation is very chimple.
// Right now the code assumes that Group contains a single quantity for the group members.
template <typename T>
struct Group
{
    uint8_t numberOfGroups_;
    std::unique_ptr<std::vector<T>> members_;

    Group() : numberOfGroups_(0), members_(std::make_unique<std::vector<T>>()) {}
};

// Define a common template for param groups
// here the typename T is redundant, need to remove this, and
template <typename T, typename GroupType>
struct ParamGroupBase
{
    uint16_t paramGroupLength_;
    uint8_t paramGroupType_;
    GroupType group_;

    ParamGroupBase(uint16_t length, uint8_t type) : paramGroupLength_(length), paramGroupType_(type), group_() {}
};

// Specialization for Type_NoUnspecifiedUnitReplay
// type internally has a group, it is not seen here, how to handle group inside type, can this be done using templates, similar to type inside group.
struct Type_NoUnspecifiedUnitReplay
{
    uint8_t noUnspecifiedUnitReplay_; // Specific field for this type
};

// Specialization for Type_MessageType
struct Type_MessageType
{
    uint8_t messageType_; // Specific field for this type
};

// Define member struct template
// template for member which will be major part of types, and group
template <typename T>
struct Member
{
    T data_;
};

// Using templates to define both types
using NoUnspecifiedUnitReplayParamGroup = ParamGroupBase<Type_NoUnspecifiedUnitReplay, Group<Member<uint32_t>>>;
using MessageTypeParamGroup = ParamGroupBase<Type_MessageType, Group<Member<uint8_t>>>;

class LoginRequest
{
private:
    uint16_t startOfMessage_;
    uint16_t messageLength_;

    // Group of parameter groups, containing either NoUnspecifiedUnitReplayParamGroup or MessageTypeParamGroup
    using ParamGroupVariant = std::variant<NoUnspecifiedUnitReplayParamGroup, MessageTypeParamGroup>;
    Group<Member<ParamGroupVariant>> group_NumberOfParamGroups_;
};

int main()
{
    LoginRequest loginRequest;
    loginRequest.setStartOfMessage(0xABCD);
    loginRequest.setMessageLength(100);

    // Add NoUnspecifiedUnitReplay group
    loginRequest.addNoUnspecifiedUnitReplayGroup(10, 0x80, 1);

    // Add MessageType group
    loginRequest.addMessageTypeGroup(20, 0x80, 0x25);

    std::cout << "Start of Message: " << loginRequest.getStartOfMessage() << std::endl;
    std::cout << "Message Length: " << loginRequest.getMessageLength() << std::endl;
    std::cout << "Number of Param Groups: " << static_cast<int>(loginRequest.getNumberOfParamGroups()) << std::endl;

    return 0;
}
