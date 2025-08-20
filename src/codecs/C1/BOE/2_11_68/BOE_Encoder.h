#pragma once
#include "BOE_Msgs.h"
#include "/root/Subhash/src/common/status.h"
#include "/root/Subhash/src/common/utils.h"




template <typename HandlerType>
class Encoder {
    

    
    template <typename U>
    inline void _encode(char *&start, char *end, const U &field, Status &status) noexcept
    {
        
        if (status.getStatus() != StatusEnum::PARSING)
            return;  

        
        if (start + sizeof(field) > end)  
        {
            status.updateStatus(StatusEnum::BUFFER_OVERFLOW);
            return;
        }

        
        if constexpr (std::is_enum<U>::value)
        {
            if (field == U::UNKNOWN)
            {
                status.updateStatus(StatusEnum::INVALID_OBJECT);
                return;
            }
        }

        
        *reinterpret_cast<U *>(start) = field;
        start += sizeof(field);
        
        status.updateNextStart(start);  
    }

    
    template <typename U>
    void _encode(char *&start, char *end, const std::vector<U> &field, Status &status) noexcept {
        
        if (status.getStatus() != StatusEnum::PARSING)
            return;  
        
        for (const auto &element : field) {
            _encode(start, end, element, status);
            if (status.getStatus() != StatusEnum::PARSING) return;  // Exit loop on overflow
        }
    }


    // Specialization for encoding vectors of fields dependent on bitfields
    template <typename U, typename B>
    void _encode(char *&start, char *end, const std::vector<U> &field, const std::vector<B> &bitfields, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;  

        for (const auto &element : field)
        {
            _encode(start, end, element, bitfields, status);
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
        }
    }

    
    template <size_t len>
    void _encode(char *&start, char *end, const std::array<char, len> &field, Status &status) noexcept
    {
        
        if (status.getStatus() != StatusEnum::PARSING)
            return;  

        for (const auto &element : field)
        {
            _encode(start, end, element, status);
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
        }
    }
    // Specific encode function for GroupNumberOfNewOrderCrossBitfields class 

        inline void _encode(char*& start, char* end, const GroupNumberOfNewOrderCrossBitfields& groupNumberOfNewOrderCrossBitfields, Status& status) noexcept{
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
            
            _encode(start, end, groupNumberOfNewOrderCrossBitfields.getNewOrderCrossBitfield(), status);
        }// Specific encode function for GroupRepeatingGroupsOfNewOrderCross class 

        // Specific encode function for GroupRepeatingGroupsOfNewOrderCross class with optional fields

            inline void _encode(char*& start, char* end, const GroupRepeatingGroupsOfNewOrderCross& groupRepeatingGroupsOfNewOrderCross, const std::vector<GroupNumberOfNewOrderCrossBitfields>& groupNumberOfNewOrderCrossBitfields, Status& status) noexcept{
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
            
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getSide(), status);
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getAllocQty(), status);
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getClOrdID(), status);
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getCapacity(), status);
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getOpenClose(), status);
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getGiveUpFirmID(), status);
                if (groupNumberOfNewOrderCrossBitfields [static_cast<uint8_t>(NewOrderCrossBitfieldIdx::ACCOUNT)].getNewOrderCrossBitfield() & (1 << static_cast<uint8_t>(NewOrderCrossBitIdx::ACCOUNT)))
                {
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getAccount(), status);
            }
                if (groupNumberOfNewOrderCrossBitfields [static_cast<uint8_t>(NewOrderCrossBitfieldIdx::CMTANUMBER)].getNewOrderCrossBitfield() & (1 << static_cast<uint8_t>(NewOrderCrossBitIdx::CMTANUMBER)))
                {
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getCMTANumber(), status);
            }
                if (groupNumberOfNewOrderCrossBitfields [static_cast<uint8_t>(NewOrderCrossBitfieldIdx::CLEARINGACCOUNT)].getNewOrderCrossBitfield() & (1 << static_cast<uint8_t>(NewOrderCrossBitIdx::CLEARINGACCOUNT)))
                {
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getClearingAccount(), status);
            }
                if (groupNumberOfNewOrderCrossBitfields [static_cast<uint8_t>(NewOrderCrossBitfieldIdx::CLEARINGOPTIONALDATA)].getNewOrderCrossBitfield() & (1 << static_cast<uint8_t>(NewOrderCrossBitIdx::CLEARINGOPTIONALDATA)))
                {
            _encode(start, end, groupRepeatingGroupsOfNewOrderCross.getClearingOptionalData(), status);
            }
        }// Specific encode function for GroupNumberOfUnits class 

        inline void _encode(char*& start, char* end, const GroupNumberOfUnits& groupNumberOfUnits, Status& status) noexcept{
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
            
            _encode(start, end, groupNumberOfUnits.getUnitNumber(), status);
            _encode(start, end, groupNumberOfUnits.getUnitSequence(), status);
        }// Specific encode function for GroupUnitSequences class 

        inline void _encode(char*& start, char* end, const GroupUnitSequences& groupUnitSequences, Status& status) noexcept{
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
            
            _encode(start, end, groupUnitSequences.getParamGroupLength(), status);
            _encode(start, end, groupUnitSequences.getParamGroupType(), status);
            _encode(start, end, groupUnitSequences.getNoUnspecifiedUnitReplay(), status);
            _encode(start, end, groupUnitSequences.getNumberOfUnits(), status);
                        _encode(start, end, groupUnitSequences.getGroupNumberOfUnits(), status);
        }// Specific encode function for GroupNumberOfReturnBitfields class 

        inline void _encode(char*& start, char* end, const GroupNumberOfReturnBitfields& groupNumberOfReturnBitfields, Status& status) noexcept{
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
            
            _encode(start, end, groupNumberOfReturnBitfields.getReturnBitfield(), status);
        }// Specific encode function for GroupReturnBitfields class 

        inline void _encode(char*& start, char* end, const GroupReturnBitfields& groupReturnBitfields, Status& status) noexcept{
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
            
            _encode(start, end, groupReturnBitfields.getParamGroupLength(), status);
            _encode(start, end, groupReturnBitfields.getParamGroupType(), status);
            _encode(start, end, groupReturnBitfields.getMessageType(), status);
            _encode(start, end, groupReturnBitfields.getNumberOfReturnBitfields(), status);
                        _encode(start, end, groupReturnBitfields.getGroupNumberOfReturnBitfields(), status);
        }
    void _encode(char*& start, char* end, const LoginRequest& loginRequest, Status& status) noexcept
        {
            
            _encode(start, end, loginRequest.getStartOfMessage(), status);
            _encode(start, end, loginRequest.getMessageLength(), status);
            _encode(start, end, loginRequest.getMessageType(), status);
            _encode(start, end, loginRequest.getMatchingUnit(), status);
            _encode(start, end, loginRequest.getSequenceNumber(), status);
            _encode(start, end, loginRequest.getSessionSubID(), status);
            _encode(start, end, loginRequest.getUsername(), status);
            _encode(start, end, loginRequest.getPassword(), status);
            _encode(start, end, loginRequest.getNumberOfParamGroups(), status);
                        _encode(start, end, loginRequest.getGroupUnitSequences(), status);
                        _encode(start, end, loginRequest.getGroupReturnBitfields(), status);
        }void _encode(char*& start, char* end, const NewOrderCross& newOrderCross, Status& status) noexcept
        {
            
            _encode(start, end, newOrderCross.getStartOfMessage(), status);
            _encode(start, end, newOrderCross.getMessageLength(), status);
            _encode(start, end, newOrderCross.getMessageType(), status);
            _encode(start, end, newOrderCross.getMatchingUnit(), status);
            _encode(start, end, newOrderCross.getSequenceNumber(), status);
            _encode(start, end, newOrderCross.getCrossID(), status);
            _encode(start, end, newOrderCross.getCrossType(), status);
            _encode(start, end, newOrderCross.getCrossPrioritization(), status);
            _encode(start, end, newOrderCross.getPrice(), status);
            _encode(start, end, newOrderCross.getOrderQty(), status);
            _encode(start, end, newOrderCross.getNumberOfNewOrderCrossBitfields(), status);
                        _encode(start, end, newOrderCross.getGroupNumberOfNewOrderCrossBitfields(), status);
            _encode(start, end, newOrderCross.getGroupCnt(), status);
                        _encode(start, end, newOrderCross.getGroupRepeatingGroupsOfNewOrderCross(), newOrderCross.getGroupNumberOfNewOrderCrossBitfields(), status);auto bitfields = newOrderCross.getGroupNumberOfNewOrderCrossBitfields();
                    size_t bitfieldIdx = 0;
                    size_t bitIdx = 0;bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::SYMBOL);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::SYMBOL);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getSymbol(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::MATURITYDATE);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::MATURITYDATE);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getMaturityDate(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::STRIKEPRICE);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::STRIKEPRICE);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getStrikePrice(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::PUTORCALL);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::PUTORCALL);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getPutOrCall(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::EXECINST);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::EXECINST);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getExecInst(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::ATTRIBUTEDQUOTE);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::ATTRIBUTEDQUOTE);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getAttributedQuote(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::TARGETPARTYID);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::TARGETPARTYID);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getTargetPartyID(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::PREVENTMATCH);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::PREVENTMATCH);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getPreventMatch(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::AUTOMATCH);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::AUTOMATCH);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getAutoMatch(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::AUTOMATCHPRICE);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::AUTOMATCHPRICE);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getAutoMatchPrice(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::LASTPRIORITY);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::LASTPRIORITY);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getLastPriority(), status);
            }bitfieldIdx = static_cast<uint8_t>(NewOrderCrossBitfieldIdx::ROUTINGFIRMID);
                bitIdx = static_cast<uint8_t>(NewOrderCrossBitIdx::ROUTINGFIRMID);
                if (bitfields.size() > bitfieldIdx and bitfields[bitfieldIdx].getNewOrderCrossBitfield() & (1 << bitIdx))
                {
            _encode(start, end, newOrderCross.getRoutingFirmID(), status);
            }
        }
public:
    
    template <typename T>
    void encode(const std::vector<char> &buffer, const T &msg, Status &status)
    {
        char *start = const_cast<char *>(buffer.data());
        char *end = start + buffer.size();
        HandlerType handler;
        _encode(start, end, msg, status);

        
        if (status.getStatus() == StatusEnum::PARSING)
            status.updateStatus(StatusEnum::COMPLETE);
        handler(status);
    }
};


