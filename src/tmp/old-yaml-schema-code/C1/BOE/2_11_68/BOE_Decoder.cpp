template <typename HandlerType>
class Decoder
{
    GroupNumberOfReturnBitfields groupNumberOfReturnBitfields;
    GroupNumberOfUnits groupNumberOfUnits;
    TypeUnitSequences typeUnitSequences;
    TypeReturnBitfields typeReturnBitfields;
    LoginRequest loginRequest;
    LoginResponse loginResponse;
    inline uint8_t _getType(char *&start, char *&end)
    {
        uint8_t type;
        memcpy(&type, start + 2, 1);
        return type;
    }

    template <typename FieldType>
    inline FieldType _getField(char *&start, char *&end)
    {
        FieldType field;
        std::memcpy(&field, start, sizeof(FieldType));
        start += sizeof(FieldType);
        return field;
    }
    void _decodeGroupNumberOfReturnBitfields(char *&start, char *&end, Status &status)
    {
        groupNumberOfReturnBitfields.setReturnBitfield(_getField<uint8_t>(start, end));
        return;
    }
    void _decodeGroupNumberOfUnits(char *&start, char *&end, Status &status)
    {
        groupNumberOfUnits.setUnitNumber(_getField<uint8_t>(start, end));
        groupNumberOfUnits.setUnitSequence(_getField<uint32_t>(start, end));
        return;
    }
    void _decodeTypeUnitSequences(char *&start, char *&end, Status &status)
    {
        typeUnitSequences.setParamGroupLengthUnitSequences(_getField<uint16_t>(start, end));
        typeUnitSequences.setParamGroupTypeUnitSequences(_getField<uint8_t>(start, end));
        typeUnitSequences.setNoUnspecifiedUnitReplay(_getField<uint8_t>(start, end));
        typeUnitSequences.setNumberOfUnits(_getField<uint8_t>(start, end));
        for (uint8_t i = 0; i < typeUnitSequences.getNumberOfUnits(); i++)
        {
            _decodeGroupNumberOfUnits(start, end, status);
            typeUnitSequences.setGroupNumberOfUnits(std::move(groupNumberOfUnits));
        }
        return;
    }
    void _decodeTypeReturnBitfields(char *&start, char *&end, Status &status)
    {
        typeReturnBitfields.setParamGroupLengthReturnBitfields(_getField<uint16_t>(start, end));
        typeReturnBitfields.setParamGroupTypeReturnBitfields(_getField<uint8_t>(start, end));
        typeReturnBitfields.setMessageType(_getField<uint8_t>(start, end));
        typeReturnBitfields.setNumberOfReturnBitfields(_getField<uint8_t>(start, end));
        for (uint8_t i = 0; i < typeReturnBitfields.getNumberOfReturnBitfields(); i++)
        {
            _decodeGroupNumberOfReturnBitfields(start, end, status);
            typeReturnBitfields.setGroupNumberOfReturnBitfields(std::move(groupNumberOfReturnBitfields));
        }
        return;
    }
    void _decodeLoginRequest(char *&start, char *&end, Status &status)
    {
        loginRequest.setStartOfMessage(_getField<uint16_t>(start, end));
        loginRequest.setMessageLength(_getField<uint16_t>(start, end));
        loginRequest.setMessageType(_getField<uint8_t>(start, end));
        loginRequest.setMatchingUnit(_getField<uint8_t>(start, end));
        loginRequest.setSequenceNumber(_getField<uint32_t>(start, end));
        loginRequest.setSessionSubID(start);
        start += 4;
        loginRequest.setUsername(start);
        start += 4;
        loginRequest.setPassword(start);
        start += 10;
        loginRequest.setNumberOfParamGroups(_getField<uint8_t>(start, end));
        for (uint8_t i = 0; i < loginRequest.getNumberOfParamGroups(); i++)
        {
            TypeEnum type = static_cast<TypeEnum>(_getType(start, end));
            if (type == TypeEnum::UNITSEQUENCES)
            {
                _decodeTypeUnitSequences(start, end, status);
                loginRequest.setTypeUnitSequences(std::move(typeUnitSequences));
            }
            else if (type == TypeEnum::RETURNBITFIELDS)
            {
                _decodeTypeReturnBitfields(start, end, status);
                loginRequest.setTypeReturnBitfields(std::move(typeReturnBitfields));
            }
            else
            {
                std::cout << "Type Not Found" << std::endl;
            }
        }
        return;
    }
    void _decodeLoginResponse(char *&start, char *&end, Status &status)
    {
        loginResponse.setStartOfMessage(_getField<uint16_t>(start, end));
        loginResponse.setMessageLength(_getField<uint16_t>(start, end));
        loginResponse.setMessageType(_getField<uint8_t>(start, end));
        loginResponse.setMatchingUnit(_getField<uint8_t>(start, end));
        loginResponse.setSequenceNumber(_getField<uint32_t>(start, end));
        loginResponse.setLoginResponseStatus(start);
        start += 1;
        loginResponse.setLoginResponseText(start);
        start += 60;
        loginResponse.setNoUnspecifiedUnitReplay(_getField<uint8_t>(start, end));
        loginResponse.setLastReceivedSequenceNumber(_getField<uint32_t>(start, end));
        loginResponse.setNumberOfUnits(_getField<uint8_t>(start, end));
        for (uint8_t i = 0; i < loginResponse.getNumberOfUnits(); i++)
        {
            _decodeGroupNumberOfUnits(start, end, status);
            loginResponse.setGroupNumberOfUnits(std::move(groupNumberOfUnits));
        }
        return;
    }

public:
    void decode(char *&start, char *&end, HandlerType &customHandler, Status &status)
    {
        _decodeLoginRequest(start, end, status);
        customHandler(loginRequest);
    }
};