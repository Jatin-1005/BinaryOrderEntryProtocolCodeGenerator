#include <iostream>
#include <bitset>
#include <vector>
#include <memory>
#include <variant>

class LoginRequest {
private:
    uint16_t startOfMessage_;
    uint16_t messageLength_;
    uint8_t messageType_;
    uint8_t matchingUnit_;
    uint32_t sequenceNumber_;
    uint32_t sessionSubID_;
    uint32_t username_;
    std::bitset<80> password_;

    struct G_NumberOfUnits {
        uint8_t numberOfUnits_;
        struct Member {
            uint8_t unitNumber_;
            uint32_t unitSequence_;
        };
        std::unique_ptr<std::vector<Member>> members_;
    };

    struct G_NumberOfReturnBitfields {
        uint8_t numberOfReturnBitfields_;
        struct Member {
            uint8_t returnBitfield_;
        };
        std::unique_ptr<std::vector<Member>> members_;
    };

    // Define Type-1 and Type-2 inside the class
    struct T_NoUnspecifiedUnitReplay {
        uint8_t noUnspecifiedUnitReplay_;
        G_NumberOfUnits numberOfUnits_;
    };
    


    struct T_MessageType {
        uint8_t messageType_;
        G_NumberOfReturnBitfields numberOfReturnBitfields_;
    };

    // G_NumberOfParamGroups with variant for Type-1 and Type-2
    struct G_NumberOfParamGroups {
        uint8_t numberOfParamGroups_;
        struct Member {
            uint16_t paramGroupLength_;
            uint8_t paramGroupType_;
            // Use std::variant to store either Type-1 or Type-2
            std::variant<T_NoUnspecifiedUnitReplay, T_MessageType> type_;
        };
        // Capture the members of the param groups (either Type-1 or Type-2)
        std::unique_ptr<std::vector<Member>> members_;
    };

    G_NumberOfParamGroups paramGroups_;
};

int main() {
    LoginRequest loginRequest;
    return 0;
}
