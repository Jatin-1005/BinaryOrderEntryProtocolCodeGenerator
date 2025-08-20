#pragma once
#include "BOE_Msgs.h"
#include <iostream>
#include <iomanip>
#include <ostream>
#include <array>
#include <vector>

template <size_t length>
std::ostream &operator<<(std::ostream &os, const std::array<char, length> &arr)
{

        for (size_t idx = 0; idx < arr.size(); ++idx)
        {
                os << std::setw(2) << std::setfill('0') << static_cast<int>(arr[idx]);
        }
        return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<GroupNumberOfNewOrderCrossBitfields> &groupNumberOfNewOrderCrossBitfields)
{

        for (size_t idx = 0; idx < groupNumberOfNewOrderCrossBitfields.size(); ++idx)
        {

                os << "\n   NewOrderCrossBitfield" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupNumberOfNewOrderCrossBitfields[idx].getNewOrderCrossBitfield());
        }
        return os;
}
std::ostream &operator<<(std::ostream &os, const std::vector<GroupRepeatingGroupsOfNewOrderCross> &groupRepeatingGroupsOfNewOrderCross)
{

        for (size_t idx = 0; idx < groupRepeatingGroupsOfNewOrderCross.size(); ++idx)
        {

                os << "\n   Side" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupRepeatingGroupsOfNewOrderCross[idx].getSide());

                os << "\n   AllocQty" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupRepeatingGroupsOfNewOrderCross[idx].getAllocQty());

                os << "\n   ClOrdID" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << groupRepeatingGroupsOfNewOrderCross[idx].getClOrdID();

                os << "\n   Capacity" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupRepeatingGroupsOfNewOrderCross[idx].getCapacity());

                os << "\n   OpenClose" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupRepeatingGroupsOfNewOrderCross[idx].getOpenClose());

                os << "\n   GiveUpFirmID" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << groupRepeatingGroupsOfNewOrderCross[idx].getGiveUpFirmID();

                os << "\n   Account" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << groupRepeatingGroupsOfNewOrderCross[idx].getAccount();

                os << "\n   CMTANumber" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << groupRepeatingGroupsOfNewOrderCross[idx].getCMTANumber();

                os << "\n   ClearingAccount" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << groupRepeatingGroupsOfNewOrderCross[idx].getClearingAccount();

                os << "\n   ClearingOptionalData" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << groupRepeatingGroupsOfNewOrderCross[idx].getClearingOptionalData();
        }
        return os;
}
std::ostream &operator<<(std::ostream &os, const std::vector<GroupNumberOfUnits> &groupNumberOfUnits)
{

        for (size_t idx = 0; idx < groupNumberOfUnits.size(); ++idx)
        {

                os << "\n   UnitNumber" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupNumberOfUnits[idx].getUnitNumber());

                os << "\n   UnitSequence" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupNumberOfUnits[idx].getUnitSequence());
        }
        return os;
}
std::ostream &operator<<(std::ostream &os, const std::vector<GroupUnitSequences> &groupUnitSequences)
{

        for (size_t idx = 0; idx < groupUnitSequences.size(); ++idx)
        {

                os << "\n ParamGroupLength" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupUnitSequences[idx].getParamGroupLength());

                os << "\n ParamGroupType" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupUnitSequences[idx].getParamGroupType());

                os << "\n NoUnspecifiedUnitReplay" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupUnitSequences[idx].getNoUnspecifiedUnitReplay());

                os << "\n NumberOfUnits" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupUnitSequences[idx].getNumberOfUnits());

                os << groupUnitSequences[idx].getGroupNumberOfUnits();
        }
        return os;
}
std::ostream &operator<<(std::ostream &os, const std::vector<GroupNumberOfReturnBitfields> &groupNumberOfReturnBitfields)
{

        for (size_t idx = 0; idx < groupNumberOfReturnBitfields.size(); ++idx)
        {

                os << "\n   ReturnBitfield" << (idx + 1) << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupNumberOfReturnBitfields[idx].getReturnBitfield());
        }
        return os;
}
std::ostream &operator<<(std::ostream &os, const std::vector<GroupReturnBitfields> &groupReturnBitfields)
{

        for (size_t idx = 0; idx < groupReturnBitfields.size(); ++idx)
        {

                os << "\n ParamGroupLength" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupReturnBitfields[idx].getParamGroupLength());

                os << "\n ParamGroupType" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupReturnBitfields[idx].getParamGroupType());

                os << "\n MessageType" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupReturnBitfields[idx].getMessageType());

                os << "\n NumberOfReturnBitfields" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(groupReturnBitfields[idx].getNumberOfReturnBitfields());

                os << groupReturnBitfields[idx].getGroupNumberOfReturnBitfields();
        }
        return os;
}

std::ostream &operator<<(std::ostream &os, const LoginRequest &loginRequest)
{

        os << "\n StartOfMessage" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(loginRequest.getStartOfMessage());

        os << "\n MessageLength" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(loginRequest.getMessageLength());

        os << "\n MessageType" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(loginRequest.getMessageType());

        os << "\n MatchingUnit" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(loginRequest.getMatchingUnit());

        os << "\n SequenceNumber" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(loginRequest.getSequenceNumber());

        os << "\n SessionSubID" << ": " << std::setw(2) << std::setfill('0') << loginRequest.getSessionSubID();

        os << "\n Username" << ": " << std::setw(2) << std::setfill('0') << loginRequest.getUsername();

        os << "\n Password" << ": " << std::setw(2) << std::setfill('0') << loginRequest.getPassword();

        os << "\n NumberOfParamGroups" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(loginRequest.getNumberOfParamGroups());

        os << loginRequest.getGroupUnitSequences();

        os << loginRequest.getGroupReturnBitfields();

        return os;
}
std::ostream &operator<<(std::ostream &os, const NewOrderCross &newOrderCross)
{

        os << "\n StartOfMessage" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getStartOfMessage());

        os << "\n MessageLength" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getMessageLength());

        os << "\n MessageType" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getMessageType());

        os << "\n MatchingUnit" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getMatchingUnit());

        os << "\n SequenceNumber" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getSequenceNumber());

        os << "\n CrossID" << ": " << std::setw(2) << std::setfill('0') << newOrderCross.getCrossID();

        os << "\n CrossType" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getCrossType());

        os << "\n CrossPrioritization" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getCrossPrioritization());

        os << "\n Price" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getPrice());

        os << "\n OrderQty" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getOrderQty());

        os << "\n NumberOfNewOrderCrossBitfields" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getNumberOfNewOrderCrossBitfields());

        os << newOrderCross.getGroupNumberOfNewOrderCrossBitfields();

        os << "\n GroupCnt" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getGroupCnt());

        os << newOrderCross.getGroupRepeatingGroupsOfNewOrderCross();

        os << "\n Symbol" << ": " << std::setw(2) << std::setfill('0') << newOrderCross.getSymbol();

        os << "\n MaturityDate" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getMaturityDate());

        os << "\n StrikePrice" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getStrikePrice());

        os << "\n PutOrCall" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getPutOrCall());

        os << "\n ExecInst" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getExecInst());

        os << "\n AttributedQuote" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getAttributedQuote());

        os << "\n TargetPartyID" << ": " << std::setw(2) << std::setfill('0') << newOrderCross.getTargetPartyID();

        os << "\n PreventMatch" << ": " << std::setw(2) << std::setfill('0') << newOrderCross.getPreventMatch();

        os << "\n AutoMatch" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getAutoMatch());

        os << "\n AutoMatchPrice" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getAutoMatchPrice());

        os << "\n LastPriority" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(newOrderCross.getLastPriority());

        os << "\n RoutingFirmID" << ": " << std::setw(2) << std::setfill('0') << newOrderCross.getRoutingFirmID();

        return os;
}
