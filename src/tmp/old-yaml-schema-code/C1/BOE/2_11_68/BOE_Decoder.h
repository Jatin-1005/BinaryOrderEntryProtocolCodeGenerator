#include "BOE_Msgs.cpp"
#include <string>
#include <functional>
#include "BOE_Encoder.cpp"

template <typename T>
class Decoder {
private:
    // decoder calling can be done, using paramgrouptype, and keeping a map to track b/w the type, and the datatype, might make things smoother.
    // read reserved object which are there in rust, and c3, it can either give a value or give an exception.
    // In c++ why we should ot throw expection in high frequency trading. unrolling of the stack happens, which takes time.
    void _decodeGroupMember(char*& start, char*& end, TypeUnitSequences& groupMember, Status& status) {
        _decode<uint16_t, 4>(start, end, std::move(std::bind(&TypeUnitSequences::setParamGroupLengthUnitSequences, &groupMember, std::placeholders::_1)), status);
        _decode<uint8_t, 2>(start, end, std::move(std::bind(&TypeUnitSequences::setParamGroupTypeUnitSequences, &groupMember, std::placeholders::_1)), status);
        // caveat with bind, once we bind, In thread there is no call by reference, only call by value. std::bind, and std::move are highly prefered in asyncronous, singel process environment.
        // func(arg1, arg2)
        // In a thread the call by reference won't happen, so the value inside the thread might be modified, but won't be modified in the main.
        _decode<uint8_t, 2>(start, end, std::move(std::bind(&TypeUnitSequences::setNoUnspecifiedUnitReplay, &groupMember, std::placeholders::_1)), status);
    }

    // void _decodeGroupMember(char*& start, char*& end, TypeReturnBitfields& groupMember, Status& status) {
    //     _decode<uint16_t, 4>(start, end, std::move(std::bind(&TypeReturnBitfields::getParamGroupLengthMessageType, &groupMember, std::placeholders::_1)), status);
    //     _decode<uint8_t, 2>(start, end, std::move(std::bind(&TypeReturnBitfields::getParamGroupTypeReturnBitfields, &groupMember, std::placeholders::_1)), status);
    //     _decode<uint8_t, 2>(start, end, std::move(std::bind(&TypeReturnBitfields::getMessageType, &groupMember, std::placeholders::_1)), status);
    // }

    // approach-2 interface.
    template<typename U, int len, typename G>
    void _decodeGroup(char*& start, char*& end, std::function<void(U)> setter, std::function<void(std::vector<G>)> groupSetter, Status& status) {
        // set the group representation
        _decode<U, len>(start, end, std::move(setter), status);
        U groupSize = 1; // msg.getNumberOfParamGroups();
        std::vector<G> group(groupSize);
        for(int i = 0; i < groupSize; i++) {
            // assuming only default argume7nts only will be there, we just need to decode them, but can't see a way to create modularity.
            // should I do callback from one decode funtion to another
            // difference b/w calling, and callback sir.
            // get the paramGroupType, and call _decodeGroupMember only for those particular paramGroupTypes
            _decodeGroupMember(start, end, group[i], status);
        }
        groupSetter(group);
    }
    // LoginRequest msg;
    // _decode(start, end, msg);

    // msg -> {f1, f2, G1 = {f3, f4}}
    // messageLength, and messageType, 
    // 00 11 22 33

    // instead of manually setting the field, if we have a buffer of 10 bytes.

    // cout << msg << endl;
    void _decode(char*& start, char*& end, T msg, Status& status) {
        // fooling the compiler in thinking that we are calling different functions, it will still do the optimization at the function level, but not at the common level.
        // passing a value template argument, then exponential increase in search happens.
        // imagine only normal fields are available, then how to deal with
        // use sizeof to get the length, rather than passing the length.
        // is bind good or is lambda good, moving the bind, I believe moving the bind is good, or what is good.
        // std::move, what is really happening, let's assume that it moves the function pointer, but still the issue really is that , once entering the realm of function ptr, the inline won't happen
        // modifications post usage, move will cause troubles.
        // should not use function pointers, because it is high critical path, std::function is the issue, because it is not truly templated.
        // if we did the way balaji suggested, then it is truly templated.
        _decode<uint16_t, 4>(start, end, std::move(std::bind(&T::setStartOfMessage, &msg, std::placeholders::_1)), status);
        _decode<uint16_t, 4>(start, end, std::move(std::bind(&T::setMessageLength, &msg, std::placeholders::_1)), status);
        _decode<uint8_t, 2>(start, end, std::move(std::bind(&T::setMessageType, &msg, std::placeholders::_1)), status);
        _decode<uint8_t, 2>(start, end, std::move(std::bind(&T::setMatchingUnit, &msg, std::placeholders::_1)), status);
        _decode<uint32_t, 8>(start, end, std::move(std::bind(&T::setSequenceNumber, &msg, std::placeholders::_1)), status);
        _decode<8>(start, end, std::move(std::bind(&T::setSessionSubID, &msg, std::placeholders::_1)), status);
        _decode<8>(start, end, std::move(std::bind(&T::setUsername, &msg, std::placeholders::_1)), status);
        _decode<20>(start, end, std::move(std::bind(&T::setPassword, &msg, std::placeholders::_1)), status);

        _decode<uint8_t, 2>(start, end, std::move(std::bind(&T::setNumberOfParamGroups, &msg, std::placeholders::_1)), status);
        std::vector<TypeUnitSequences> typeUnitSequencesList;
        std::vector<TypeReturnBitfields> typeReturnBitfieldsList;
        TypeUnitSequences typeUnitSequences;
        TypeReturnBitfields typeReturnBitfields;
        // TODO manipulate the setter of the group to complete vector or pushing back a single element inside the vector.
        // the code is gonna get jumbeled because I'm using paramGroupType for some group, and won't use for someother group.
        // we should keep the _decodeGroup interface to be commonly used across multiple groups.
        for(int i = 0; i < msg.getNumberOfParamGroups(); i++) {
            char hexStr[3]; hexStr[2] = '\0';
            hexStr[0] = start[4];
            hexStr[1] = start[5];
            std::cout << hexStr[0] << hexStr[1] << std::endl;
            int typeValue = std::stoi(hexStr, nullptr);
            std::cout << typeValue << std::endl;
            if (typeValue == 80) {
                std::cout << "NoUnspecifiedUnitReplay" << std::endl;
                _decodeGroupMember(start, end, typeUnitSequences, status);
                typeUnitSequencesList.push_back(typeUnitSequences);
                break;
            } else if(typeValue == 81) {
                std::cout << "MessageType" << std::endl;
                // _decodeGroupMember(start, end, typeReturnBitfields, status);
                // typeReturnBitfieldsList.push_back(typeReturnBitfields);
            } else {
                std::cout << "Type not defined" << std::endl;
            }
        }
        msg.setTypeUnitSequences(std::move(typeUnitSequencesList));
        msg.setTypeReturnBitfields(std::move(typeReturnBitfieldsList));
        // approach-2 interface.
        // _decodeGroup<uint8_t, 2, TypeUnitSequences>(start, end, std::move(std::bind(&T::setNumberOfParamGroups, &msg, std::placeholders::_1)), std::move(std::bind(&T::setTypeUnitSequences, &msg, std::placeholders::_1)), status);
        
        // look at the below lines to understand how to deal with types, it is almost straight forward now.
        // setter for the vector<G> should be defined, and once that is done, it is all right.
        // _decodeGroup<uint8_t, 2, TypeReturnBitfields>(start, end, std::move(std::bind(&T::setNumberOfParamGroups, &msg, std::placeholders::_1)), std::move(std::bind(&T::setTypeReturnBitfields, &msg, std::placeholders::_1)), status);
        return;
    }

    // can we add msg as an argument to the template, then template<T msg>, then msg.setter can be called inside the codebase.
    template<typename U, int len>
    void _decode(char*& start, char*& end, std::function<void(U)> setter, Status& status) {
        //read value from buffer, call the setter, and then update the start pointer.
        char hexStr[len+1]; hexStr[len] = '\0';
        strncpy(hexStr, start, len);
        start += len;
        U value = static_cast<U>(std::stoi(hexStr, nullptr, 16));
        std::cout << static_cast<int>(value) << std::endl;
        setter(value);
    }

    template<int len>
    void _decode(char*& start, char*& end, std::function<void(const char*)> setter, Status& status) {
        // need to make the below 8 lines or something as seperate function, since they are used across at different places.
        char value[len/2];
        char hexStr[3]; hexStr[2] = '\0';
        for(int i = 0; i < len; i+=2) {
            hexStr[0] = *(start+i);
            hexStr[1] = *(start+i+1);
            value[i/2] = static_cast<char>(std::stoi(hexStr, nullptr, 16));
            std::cout << value[i/2];
        }
        std::cout << std::endl;
        setter(value);
        start += len;
    }

public:
    void decode(char*& start, char*& end, Status& status) {

        MessageEnum messageType = static_cast<MessageEnum>((start[8] << 8) | start[9]);

        LoginRequest loginRequest;
        _decode(start, end, loginRequest, status);

        return;
    }
};

int main(){

    char buffer[] = "baba3d00370000000000303030315445535454455354494e47000000030f00800102014abb0100020000000008008125030041050b00812c06004107004000000100002400ffffffff00007ffdf9d395ac00007ffdf9d395ad910000777fe4";

    char* start = buffer;
    char* end = buffer + strlen(buffer);
    // std::cout << strlen(buffer) << std::endl;
    std::string buffer_str(buffer);
    Status status;

    Decoder<LoginRequest> decoder;
    decoder.decode(start, end, status);
    // decoder.decode(string, status);
    return 0;
}