
#pragma once
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <cstring>

enum StringLengthsEnum : size_t
{
    SESSIONSUBID = 4,
    USERNAME = 4,
    PASSWORD = 10,
    CROSSID = 20,
    CLORDID = 20,
    GIVEUPFIRMID = 4,
    SYMBOL = 8,
    TARGETPARTYID = 4,
    PREVENTMATCH = 3,
    ACCOUNT = 16,
    CMTANUMBER = 4,
    CLEARINGACCOUNT = 4,
    ROUTINGFIRMID = 4,
    CLEARINGOPTIONALDATA = 16,
};
enum class NewOrderCrossBitfieldIdx : uint8_t
{
    // Bitfield group with index 0
    SYMBOL = 0,
    MATURITYDATE = 0,
    STRIKEPRICE = 0,
    PUTORCALL = 0,
    EXECINST = 0,
    ATTRIBUTEDQUOTE = 0,
    TARGETPARTYID = 0,
    PREVENTMATCH = 0,

    // Bitfield group with index 1
    AUTOMATCH = 1,
    AUTOMATCHPRICE = 1,
    LASTPRIORITY = 1,
    ACCOUNT = 1,
    CMTANUMBER = 1,
    CLEARINGACCOUNT = 1,
    ROUTINGFIRMID = 1,
    CLEARINGOPTIONALDATA = 1,

};
enum class NewOrderCrossBitIdx : uint8_t
{ // Bitfield group with index 0
    SYMBOL = 0,
    MATURITYDATE = 1,
    STRIKEPRICE = 2,
    PUTORCALL = 3,
    EXECINST = 4,
    ATTRIBUTEDQUOTE = 5,
    TARGETPARTYID = 6,
    PREVENTMATCH = 7,

    // Bitfield group with index 1
    AUTOMATCH = 0,
    AUTOMATCHPRICE = 1,
    LASTPRIORITY = 2,
    ACCOUNT = 3,
    CMTANUMBER = 4,
    CLEARINGACCOUNT = 5,
    ROUTINGFIRMID = 6,
    CLEARINGOPTIONALDATA = 7,

};
enum MessagesEnum : uint8_t
{
    LOGINREQUEST = 55,
    LOGINRESPONSE = 36,
    NEWORDERCROSS = 65
};

static const std::unordered_map<uint8_t, MessagesEnum> messagesEnumOptions = {{55, MessagesEnum::LOGINREQUEST}, {36, MessagesEnum::LOGINRESPONSE}, {65, MessagesEnum::NEWORDERCROSS}};
enum ParamGroupTypesEnum : uint8_t
{
    RETURNBITFIELDS = 129,
    UNITSEQUENCES = 128
};

static const std::unordered_map<uint8_t, ParamGroupTypesEnum> paramGroupTypesEnumOptions = {{129, ParamGroupTypesEnum::RETURNBITFIELDS}, {128, ParamGroupTypesEnum::UNITSEQUENCES}};
enum StartOfMessageEnum : uint16_t
{
    STARTOFMESSAGE = 47802
};

static const std::unordered_map<uint16_t, StartOfMessageEnum> startOfMessageEnumOptions = {{47802, StartOfMessageEnum::STARTOFMESSAGE}};
enum MatchingUnitEnum : uint8_t
{
    MATCHINGUNIT = 0
};

static const std::unordered_map<uint8_t, MatchingUnitEnum> matchingUnitEnumOptions = {{0, MatchingUnitEnum::MATCHINGUNIT}};
enum SequenceNumberEnum : uint32_t
{
    SEQUENCENUMBER = 0
};

static const std::unordered_map<uint32_t, SequenceNumberEnum> sequenceNumberEnumOptions = {{0, SequenceNumberEnum::SEQUENCENUMBER}};
class GroupNumberOfNewOrderCrossBitfields
{
    uint8_t newOrderCrossBitfield_;

public:
    GroupNumberOfNewOrderCrossBitfields() : newOrderCrossBitfield_(0)
    {
    }
    GroupNumberOfNewOrderCrossBitfields(uint8_t newOrderCrossBitfield) : newOrderCrossBitfield_(newOrderCrossBitfield)
    {
    }

    void reset() { newOrderCrossBitfield_ = 0; }

    inline const uint8_t &getNewOrderCrossBitfield() const noexcept { return newOrderCrossBitfield_; }
    inline uint8_t &getNewOrderCrossBitfieldRef() noexcept { return newOrderCrossBitfield_; }
    inline uint8_t getNewOrderCrossBitfieldCopy() const noexcept { return newOrderCrossBitfield_; }
    inline void setNewOrderCrossBitfield(uint8_t newOrderCrossBitfield) noexcept { newOrderCrossBitfield_ = newOrderCrossBitfield; }
};
class GroupRepeatingGroupsOfNewOrderCross
{

public:
    enum class SideEnum : char
    {
        BUY = '1',
        SELL = '2',
        UNKNOWN = '0'
    };
    static const std::unordered_map<char, SideEnum> sideEnumOptions;

private:
    SideEnum side_;
    uint32_t allocQty_;
    std::array<char, StringLengthsEnum::CLORDID> clOrdID_;

public:
    enum class CapacityEnum : char
    {
        UNKNOWN = 'Z',
        CUSTOMER = 'C',
        MARKET_MAKER = 'M',
        FIRM = 'F',
        PROFESSIONAL_CUSTOMER = 'U',
        AWAY_MARKET_MAKER = 'N',
        BROKER_DEALER = 'B',
        JOINT_BACK_OFFICE = 'J'
    };
    static const std::unordered_map<char, CapacityEnum> capacityEnumOptions;

private:
    CapacityEnum capacity_;

public:
    enum class OpenCloseEnum : char
    {
        UNKNOWN = 'Z',
        OPEN = 'O',
        CLOSE = 'C',
        NONE = 'N'
    };
    static const std::unordered_map<char, OpenCloseEnum> openCloseEnumOptions;

private:
    OpenCloseEnum openClose_;
    std::array<char, StringLengthsEnum::GIVEUPFIRMID> giveUpFirmID_;
    std::array<char, StringLengthsEnum::ACCOUNT> account_;
    std::array<char, StringLengthsEnum::CMTANUMBER> cMTANumber_;
    std::array<char, StringLengthsEnum::CLEARINGACCOUNT> clearingAccount_;
    std::array<char, StringLengthsEnum::CLEARINGOPTIONALDATA> clearingOptionalData_;

public:
    GroupRepeatingGroupsOfNewOrderCross() : side_(SideEnum::UNKNOWN), allocQty_(0), clOrdID_{}, capacity_(CapacityEnum::UNKNOWN), openClose_(OpenCloseEnum::UNKNOWN), giveUpFirmID_{}, account_{}, cMTANumber_{}, clearingAccount_{}, clearingOptionalData_{}
    {
    }
    GroupRepeatingGroupsOfNewOrderCross(SideEnum side, uint32_t allocQty, const char *clOrdID, CapacityEnum capacity, OpenCloseEnum openClose, const char *giveUpFirmID, const char *account, const char *cMTANumber, const char *clearingAccount, const char *clearingOptionalData) : side_(side), allocQty_(allocQty), clOrdID_(), capacity_(capacity), openClose_(openClose), giveUpFirmID_(), account_(), cMTANumber_(), clearingAccount_(), clearingOptionalData_()
    {
        std::memcpy(clOrdID_.data(), clOrdID, StringLengthsEnum::CLORDID);
        std::memcpy(giveUpFirmID_.data(), giveUpFirmID, StringLengthsEnum::GIVEUPFIRMID);
        std::memcpy(account_.data(), account, StringLengthsEnum::ACCOUNT);
        std::memcpy(cMTANumber_.data(), cMTANumber, StringLengthsEnum::CMTANUMBER);
        std::memcpy(clearingAccount_.data(), clearingAccount, StringLengthsEnum::CLEARINGACCOUNT);
        std::memcpy(clearingOptionalData_.data(), clearingOptionalData, StringLengthsEnum::CLEARINGOPTIONALDATA);
    }

    void reset()
    {
        side_ = SideEnum::UNKNOWN;
        allocQty_ = 0;
        clOrdID_.fill('0');
        capacity_ = CapacityEnum::UNKNOWN;
        openClose_ = OpenCloseEnum::UNKNOWN;
        giveUpFirmID_.fill('0');
        account_.fill('0');
        cMTANumber_.fill('0');
        clearingAccount_.fill('0');
        clearingOptionalData_.fill('0');
    }

    inline const SideEnum &getSide() const noexcept { return side_; }
    inline SideEnum &getSideRef() noexcept { return side_; }
    inline SideEnum getSideCopy() const noexcept { return side_; }
    inline void setSide(SideEnum side) noexcept { side_ = side; }

    inline const uint32_t &getAllocQty() const noexcept { return allocQty_; }
    inline uint32_t &getAllocQtyRef() noexcept { return allocQty_; }
    inline uint32_t getAllocQtyCopy() const noexcept { return allocQty_; }
    inline void setAllocQty(uint32_t allocQty) noexcept { allocQty_ = allocQty; }

    inline const std::array<char, StringLengthsEnum::CLORDID> &getClOrdID() const noexcept { return clOrdID_; }
    inline std::array<char, StringLengthsEnum::CLORDID> &getClOrdIDRef() noexcept { return clOrdID_; }
    inline std::array<char, StringLengthsEnum::CLORDID> getClOrdIDCopy() const noexcept { return clOrdID_; }
    inline void setClOrdID(const char *clOrdID) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::CLORDID, std::strlen(clOrdID));
        std::memcpy(clOrdID_.data(), clOrdID, length);
        for (size_t i = length; i < StringLengthsEnum::CLORDID; ++i)
        {
            clOrdID_[i] = 0;
        }
    }

    inline const CapacityEnum &getCapacity() const noexcept { return capacity_; }
    inline CapacityEnum &getCapacityRef() noexcept { return capacity_; }
    inline CapacityEnum getCapacityCopy() const noexcept { return capacity_; }
    inline void setCapacity(CapacityEnum capacity) noexcept { capacity_ = capacity; }

    inline const OpenCloseEnum &getOpenClose() const noexcept { return openClose_; }
    inline OpenCloseEnum &getOpenCloseRef() noexcept { return openClose_; }
    inline OpenCloseEnum getOpenCloseCopy() const noexcept { return openClose_; }
    inline void setOpenClose(OpenCloseEnum openClose) noexcept { openClose_ = openClose; }

    inline const std::array<char, StringLengthsEnum::GIVEUPFIRMID> &getGiveUpFirmID() const noexcept { return giveUpFirmID_; }
    inline std::array<char, StringLengthsEnum::GIVEUPFIRMID> &getGiveUpFirmIDRef() noexcept { return giveUpFirmID_; }
    inline std::array<char, StringLengthsEnum::GIVEUPFIRMID> getGiveUpFirmIDCopy() const noexcept { return giveUpFirmID_; }
    inline void setGiveUpFirmID(const char *giveUpFirmID) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::GIVEUPFIRMID, std::strlen(giveUpFirmID));
        std::memcpy(giveUpFirmID_.data(), giveUpFirmID, length);
        for (size_t i = length; i < StringLengthsEnum::GIVEUPFIRMID; ++i)
        {
            giveUpFirmID_[i] = 0;
        }
    }

    inline const std::array<char, StringLengthsEnum::ACCOUNT> &getAccount() const noexcept { return account_; }
    inline std::array<char, StringLengthsEnum::ACCOUNT> &getAccountRef() noexcept { return account_; }
    inline std::array<char, StringLengthsEnum::ACCOUNT> getAccountCopy() const noexcept { return account_; }
    inline void setAccount(const char *account) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::ACCOUNT, std::strlen(account));
        std::memcpy(account_.data(), account, length);
        for (size_t i = length; i < StringLengthsEnum::ACCOUNT; ++i)
        {
            account_[i] = 0;
        }
    }

    inline const std::array<char, StringLengthsEnum::CMTANUMBER> &getCMTANumber() const noexcept { return cMTANumber_; }
    inline std::array<char, StringLengthsEnum::CMTANUMBER> &getCMTANumberRef() noexcept { return cMTANumber_; }
    inline std::array<char, StringLengthsEnum::CMTANUMBER> getCMTANumberCopy() const noexcept { return cMTANumber_; }
    inline void setCMTANumber(const char *cMTANumber) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::CMTANUMBER, std::strlen(cMTANumber));
        std::memcpy(cMTANumber_.data(), cMTANumber, length);
        for (size_t i = length; i < StringLengthsEnum::CMTANUMBER; ++i)
        {
            cMTANumber_[i] = 0;
        }
    }

    inline const std::array<char, StringLengthsEnum::CLEARINGACCOUNT> &getClearingAccount() const noexcept { return clearingAccount_; }
    inline std::array<char, StringLengthsEnum::CLEARINGACCOUNT> &getClearingAccountRef() noexcept { return clearingAccount_; }
    inline std::array<char, StringLengthsEnum::CLEARINGACCOUNT> getClearingAccountCopy() const noexcept { return clearingAccount_; }
    inline void setClearingAccount(const char *clearingAccount) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::CLEARINGACCOUNT, std::strlen(clearingAccount));
        std::memcpy(clearingAccount_.data(), clearingAccount, length);
        for (size_t i = length; i < StringLengthsEnum::CLEARINGACCOUNT; ++i)
        {
            clearingAccount_[i] = 0;
        }
    }

    inline const std::array<char, StringLengthsEnum::CLEARINGOPTIONALDATA> &getClearingOptionalData() const noexcept { return clearingOptionalData_; }
    inline std::array<char, StringLengthsEnum::CLEARINGOPTIONALDATA> &getClearingOptionalDataRef() noexcept { return clearingOptionalData_; }
    inline std::array<char, StringLengthsEnum::CLEARINGOPTIONALDATA> getClearingOptionalDataCopy() const noexcept { return clearingOptionalData_; }
    inline void setClearingOptionalData(const char *clearingOptionalData) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::CLEARINGOPTIONALDATA, std::strlen(clearingOptionalData));
        std::memcpy(clearingOptionalData_.data(), clearingOptionalData, length);
        for (size_t i = length; i < StringLengthsEnum::CLEARINGOPTIONALDATA; ++i)
        {
            clearingOptionalData_[i] = 0;
        }
    }
};

const std::unordered_map<char, GroupRepeatingGroupsOfNewOrderCross::SideEnum> sideEnumOptions = {{'1', GroupRepeatingGroupsOfNewOrderCross::SideEnum::BUY}, {'2', GroupRepeatingGroupsOfNewOrderCross::SideEnum::SELL}, {'0', GroupRepeatingGroupsOfNewOrderCross::SideEnum::UNKNOWN}};
const std::unordered_map<char, GroupRepeatingGroupsOfNewOrderCross::CapacityEnum> capacityEnumOptions = {{'Z', GroupRepeatingGroupsOfNewOrderCross::CapacityEnum::UNKNOWN}, {'C', GroupRepeatingGroupsOfNewOrderCross::CapacityEnum::CUSTOMER}, {'M', GroupRepeatingGroupsOfNewOrderCross::CapacityEnum::MARKET_MAKER}, {'F', GroupRepeatingGroupsOfNewOrderCross::CapacityEnum::FIRM}, {'U', GroupRepeatingGroupsOfNewOrderCross::CapacityEnum::PROFESSIONAL_CUSTOMER}, {'N', GroupRepeatingGroupsOfNewOrderCross::CapacityEnum::AWAY_MARKET_MAKER}, {'B', GroupRepeatingGroupsOfNewOrderCross::CapacityEnum::BROKER_DEALER}, {'J', GroupRepeatingGroupsOfNewOrderCross::CapacityEnum::JOINT_BACK_OFFICE}};
const std::unordered_map<char, GroupRepeatingGroupsOfNewOrderCross::OpenCloseEnum> openCloseEnumOptions = {{'Z', GroupRepeatingGroupsOfNewOrderCross::OpenCloseEnum::UNKNOWN}, {'O', GroupRepeatingGroupsOfNewOrderCross::OpenCloseEnum::OPEN}, {'C', GroupRepeatingGroupsOfNewOrderCross::OpenCloseEnum::CLOSE}, {'N', GroupRepeatingGroupsOfNewOrderCross::OpenCloseEnum::NONE}};
class GroupNumberOfUnits
{
    uint8_t unitNumber_;
    uint32_t unitSequence_;

public:
    GroupNumberOfUnits() : unitNumber_(0), unitSequence_(0)
    {
    }
    GroupNumberOfUnits(uint8_t unitNumber, uint32_t unitSequence) : unitNumber_(unitNumber), unitSequence_(unitSequence)
    {
    }

    void reset()
    {
        unitNumber_ = 0;
        unitSequence_ = 0;
    }

    inline const uint8_t &getUnitNumber() const noexcept { return unitNumber_; }
    inline uint8_t &getUnitNumberRef() noexcept { return unitNumber_; }
    inline uint8_t getUnitNumberCopy() const noexcept { return unitNumber_; }
    inline void setUnitNumber(uint8_t unitNumber) noexcept { unitNumber_ = unitNumber; }

    inline const uint32_t &getUnitSequence() const noexcept { return unitSequence_; }
    inline uint32_t &getUnitSequenceRef() noexcept { return unitSequence_; }
    inline uint32_t getUnitSequenceCopy() const noexcept { return unitSequence_; }
    inline void setUnitSequence(uint32_t unitSequence) noexcept { unitSequence_ = unitSequence; }
};
class GroupUnitSequences
{
    uint16_t paramGroupLength_;
    static constexpr uint8_t paramGroupType_ = ParamGroupTypesEnum::UNITSEQUENCES;

public:
    enum class NoUnspecifiedUnitReplayEnum : uint8_t
    {
        TRUE = 1,
        FALSE = 0,
        UNKNOWN = 2
    };
    static const std::unordered_map<uint8_t, NoUnspecifiedUnitReplayEnum> noUnspecifiedUnitReplayEnumOptions;

private:
    NoUnspecifiedUnitReplayEnum noUnspecifiedUnitReplay_;
    uint8_t numberOfUnits_;
    std::vector<GroupNumberOfUnits> groupNumberOfUnitsList_;

public:
    GroupUnitSequences() : paramGroupLength_(0), noUnspecifiedUnitReplay_(NoUnspecifiedUnitReplayEnum::UNKNOWN), numberOfUnits_(0), groupNumberOfUnitsList_()
    {
    }
    GroupUnitSequences(uint16_t paramGroupLength, NoUnspecifiedUnitReplayEnum noUnspecifiedUnitReplay, std::vector<GroupNumberOfUnits> &&groupNumberOfUnitsList) : paramGroupLength_(paramGroupLength), noUnspecifiedUnitReplay_(noUnspecifiedUnitReplay), numberOfUnits_(groupNumberOfUnitsList.size()), groupNumberOfUnitsList_(groupNumberOfUnitsList)
    {
    }

    void reset()
    {
        paramGroupLength_ = 0;
        noUnspecifiedUnitReplay_ = NoUnspecifiedUnitReplayEnum::UNKNOWN;
        numberOfUnits_ = 0;
        groupNumberOfUnitsList_.clear();
    }

    inline const uint16_t &getParamGroupLength() const noexcept { return paramGroupLength_; }
    inline uint16_t &getParamGroupLengthRef() noexcept { return paramGroupLength_; }
    inline uint16_t getParamGroupLengthCopy() const noexcept { return paramGroupLength_; }
    inline void setParamGroupLength(uint16_t paramGroupLength) noexcept { paramGroupLength_ = paramGroupLength; }

    inline constexpr const uint8_t &getParamGroupType() const noexcept { return paramGroupType_; }
    inline uint8_t getParamGroupTypeCopy() const noexcept { return paramGroupType_; }

    inline const NoUnspecifiedUnitReplayEnum &getNoUnspecifiedUnitReplay() const noexcept { return noUnspecifiedUnitReplay_; }
    inline NoUnspecifiedUnitReplayEnum &getNoUnspecifiedUnitReplayRef() noexcept { return noUnspecifiedUnitReplay_; }
    inline NoUnspecifiedUnitReplayEnum getNoUnspecifiedUnitReplayCopy() const noexcept { return noUnspecifiedUnitReplay_; }
    inline void setNoUnspecifiedUnitReplay(NoUnspecifiedUnitReplayEnum noUnspecifiedUnitReplay) noexcept { noUnspecifiedUnitReplay_ = noUnspecifiedUnitReplay; }

    inline const uint8_t &getNumberOfUnits() const noexcept { return numberOfUnits_; }
    inline uint8_t getNumberOfUnitsCopy() const noexcept { return numberOfUnits_; }
    inline const std::vector<GroupNumberOfUnits> &getGroupNumberOfUnits() const noexcept
    {
        return groupNumberOfUnitsList_;
    }
    inline std::vector<GroupNumberOfUnits> &getGroupNumberOfUnitsRef() noexcept
    {
        return groupNumberOfUnitsList_;
    }
    inline std::vector<GroupNumberOfUnits> getGroupNumberOfUnitsCopy() const noexcept
    {
        return groupNumberOfUnitsList_;
    }
    inline void setGroupNumberOfUnits(GroupNumberOfUnits &&groupNumberOfUnits) noexcept
    {
        groupNumberOfUnitsList_.emplace_back(groupNumberOfUnits);

        ++numberOfUnits_;
        return;
    }
};

const std::unordered_map<uint8_t, GroupUnitSequences::NoUnspecifiedUnitReplayEnum> noUnspecifiedUnitReplayEnumOptions = {{1, GroupUnitSequences::NoUnspecifiedUnitReplayEnum::TRUE}, {0, GroupUnitSequences::NoUnspecifiedUnitReplayEnum::FALSE}, {2, GroupUnitSequences::NoUnspecifiedUnitReplayEnum::UNKNOWN}};
class GroupNumberOfReturnBitfields
{
    uint8_t returnBitfield_;

public:
    GroupNumberOfReturnBitfields() : returnBitfield_(0)
    {
    }
    GroupNumberOfReturnBitfields(uint8_t returnBitfield) : returnBitfield_(returnBitfield)
    {
    }

    void reset() { returnBitfield_ = 0; }

    inline const uint8_t &getReturnBitfield() const noexcept { return returnBitfield_; }
    inline uint8_t &getReturnBitfieldRef() noexcept { return returnBitfield_; }
    inline uint8_t getReturnBitfieldCopy() const noexcept { return returnBitfield_; }
    inline void setReturnBitfield(uint8_t returnBitfield) noexcept { returnBitfield_ = returnBitfield; }
};
class GroupReturnBitfields
{
    uint16_t paramGroupLength_;
    static constexpr uint8_t paramGroupType_ = ParamGroupTypesEnum::RETURNBITFIELDS;
    uint8_t messageType_;
    uint8_t numberOfReturnBitfields_;
    std::vector<GroupNumberOfReturnBitfields> groupNumberOfReturnBitfieldsList_;

public:
    GroupReturnBitfields() : paramGroupLength_(0), messageType_(0), numberOfReturnBitfields_(0), groupNumberOfReturnBitfieldsList_()
    {
    }
    GroupReturnBitfields(uint16_t paramGroupLength, uint8_t messageType, std::vector<GroupNumberOfReturnBitfields> &&groupNumberOfReturnBitfieldsList) : paramGroupLength_(paramGroupLength), messageType_(messageType), numberOfReturnBitfields_(groupNumberOfReturnBitfieldsList.size()), groupNumberOfReturnBitfieldsList_(groupNumberOfReturnBitfieldsList)
    {
    }

    void reset()
    {
        paramGroupLength_ = 0;
        messageType_ = 0;
        numberOfReturnBitfields_ = 0;
        groupNumberOfReturnBitfieldsList_.clear();
    }

    inline const uint16_t &getParamGroupLength() const noexcept { return paramGroupLength_; }
    inline uint16_t &getParamGroupLengthRef() noexcept { return paramGroupLength_; }
    inline uint16_t getParamGroupLengthCopy() const noexcept { return paramGroupLength_; }
    inline void setParamGroupLength(uint16_t paramGroupLength) noexcept { paramGroupLength_ = paramGroupLength; }

    inline constexpr const uint8_t &getParamGroupType() const noexcept { return paramGroupType_; }
    inline uint8_t getParamGroupTypeCopy() const noexcept { return paramGroupType_; }

    inline const uint8_t &getMessageType() const noexcept { return messageType_; }
    inline uint8_t &getMessageTypeRef() noexcept { return messageType_; }
    inline uint8_t getMessageTypeCopy() const noexcept { return messageType_; }
    inline void setMessageType(uint8_t messageType) noexcept { messageType_ = messageType; }

    inline const uint8_t &getNumberOfReturnBitfields() const noexcept { return numberOfReturnBitfields_; }
    inline uint8_t getNumberOfReturnBitfieldsCopy() const noexcept { return numberOfReturnBitfields_; }
    inline const std::vector<GroupNumberOfReturnBitfields> &getGroupNumberOfReturnBitfields() const noexcept
    {
        return groupNumberOfReturnBitfieldsList_;
    }
    inline std::vector<GroupNumberOfReturnBitfields> &getGroupNumberOfReturnBitfieldsRef() noexcept
    {
        return groupNumberOfReturnBitfieldsList_;
    }
    inline std::vector<GroupNumberOfReturnBitfields> getGroupNumberOfReturnBitfieldsCopy() const noexcept
    {
        return groupNumberOfReturnBitfieldsList_;
    }
    inline void setGroupNumberOfReturnBitfields(GroupNumberOfReturnBitfields &&groupNumberOfReturnBitfields) noexcept
    {
        groupNumberOfReturnBitfieldsList_.emplace_back(groupNumberOfReturnBitfields);

        ++numberOfReturnBitfields_;
        return;
    }
};

class LoginRequest
{

    static constexpr uint16_t startOfMessage_ = StartOfMessageEnum::STARTOFMESSAGE;
    uint16_t messageLength_;
    static constexpr uint8_t messageType_ = MessagesEnum::LOGINREQUEST;
    static constexpr uint8_t matchingUnit_ = MatchingUnitEnum::MATCHINGUNIT;
    static constexpr uint32_t sequenceNumber_ = SequenceNumberEnum::SEQUENCENUMBER;
    std::array<char, StringLengthsEnum::SESSIONSUBID> sessionSubID_;
    std::array<char, StringLengthsEnum::USERNAME> username_;
    std::array<char, StringLengthsEnum::PASSWORD> password_;
    uint8_t numberOfParamGroups_;
    std::vector<GroupUnitSequences> groupUnitSequencesList_;
    std::vector<GroupReturnBitfields> groupReturnBitfieldsList_;

public:
    LoginRequest() : messageLength_(0), sessionSubID_{}, username_{}, password_{}, numberOfParamGroups_(0), groupUnitSequencesList_(), groupReturnBitfieldsList_()
    {
    }
    LoginRequest(uint16_t messageLength, const char *sessionSubID, const char *username, const char *password, std::vector<GroupUnitSequences> &&groupUnitSequencesList, std::vector<GroupReturnBitfields> &&groupReturnBitfieldsList) : messageLength_(messageLength), sessionSubID_(), username_(), password_(), numberOfParamGroups_(groupUnitSequencesList.size() + groupReturnBitfieldsList.size()), groupUnitSequencesList_(groupUnitSequencesList), groupReturnBitfieldsList_(groupReturnBitfieldsList)
    {
        std::memcpy(sessionSubID_.data(), sessionSubID, StringLengthsEnum::SESSIONSUBID);
        std::memcpy(username_.data(), username, StringLengthsEnum::USERNAME);
        std::memcpy(password_.data(), password, StringLengthsEnum::PASSWORD);
    }

    void reset()
    {
        messageLength_ = 0;
        sessionSubID_.fill('0');
        username_.fill('0');
        password_.fill('0');
        numberOfParamGroups_ = 0;
        groupUnitSequencesList_.clear();
        groupReturnBitfieldsList_.clear();
    }

    inline constexpr const uint16_t &getStartOfMessage() const noexcept { return startOfMessage_; }
    inline uint16_t getStartOfMessageCopy() const noexcept { return startOfMessage_; }

    inline const uint16_t &getMessageLength() const noexcept { return messageLength_; }
    inline uint16_t &getMessageLengthRef() noexcept { return messageLength_; }
    inline uint16_t getMessageLengthCopy() const noexcept { return messageLength_; }
    inline void setMessageLength(uint16_t messageLength) noexcept { messageLength_ = messageLength; }

    inline constexpr const uint8_t &getMessageType() const noexcept { return messageType_; }
    inline uint8_t getMessageTypeCopy() const noexcept { return messageType_; }

    inline constexpr const uint8_t &getMatchingUnit() const noexcept { return matchingUnit_; }
    inline uint8_t getMatchingUnitCopy() const noexcept { return matchingUnit_; }

    inline constexpr const uint32_t &getSequenceNumber() const noexcept { return sequenceNumber_; }
    inline uint32_t getSequenceNumberCopy() const noexcept { return sequenceNumber_; }

    inline const std::array<char, StringLengthsEnum::SESSIONSUBID> &getSessionSubID() const noexcept { return sessionSubID_; }
    inline std::array<char, StringLengthsEnum::SESSIONSUBID> &getSessionSubIDRef() noexcept { return sessionSubID_; }
    inline std::array<char, StringLengthsEnum::SESSIONSUBID> getSessionSubIDCopy() const noexcept { return sessionSubID_; }
    inline void setSessionSubID(const char *sessionSubID) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::SESSIONSUBID, std::strlen(sessionSubID));
        std::memcpy(sessionSubID_.data(), sessionSubID, length);
        for (size_t i = length; i < StringLengthsEnum::SESSIONSUBID; ++i)
        {
            sessionSubID_[i] = 0;
        }
    }

    inline const std::array<char, StringLengthsEnum::USERNAME> &getUsername() const noexcept { return username_; }
    inline std::array<char, StringLengthsEnum::USERNAME> &getUsernameRef() noexcept { return username_; }
    inline std::array<char, StringLengthsEnum::USERNAME> getUsernameCopy() const noexcept { return username_; }
    inline void setUsername(const char *username) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::USERNAME, std::strlen(username));
        std::memcpy(username_.data(), username, length);
        for (size_t i = length; i < StringLengthsEnum::USERNAME; ++i)
        {
            username_[i] = 0;
        }
    }

    inline const std::array<char, StringLengthsEnum::PASSWORD> &getPassword() const noexcept { return password_; }
    inline std::array<char, StringLengthsEnum::PASSWORD> &getPasswordRef() noexcept { return password_; }
    inline std::array<char, StringLengthsEnum::PASSWORD> getPasswordCopy() const noexcept { return password_; }
    inline void setPassword(const char *password) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::PASSWORD, std::strlen(password));
        std::memcpy(password_.data(), password, length);
        for (size_t i = length; i < StringLengthsEnum::PASSWORD; ++i)
        {
            password_[i] = 0;
        }
    }

    inline const uint8_t &getNumberOfParamGroups() const noexcept { return numberOfParamGroups_; }
    inline uint8_t getNumberOfParamGroupsCopy() const noexcept { return numberOfParamGroups_; }
    inline const std::vector<GroupUnitSequences> &getGroupUnitSequences() const noexcept
    {
        return groupUnitSequencesList_;
    }
    inline std::vector<GroupUnitSequences> &getGroupUnitSequencesRef() noexcept
    {
        return groupUnitSequencesList_;
    }
    inline std::vector<GroupUnitSequences> getGroupUnitSequencesCopy() const noexcept
    {
        return groupUnitSequencesList_;
    }
    inline void setGroupUnitSequences(GroupUnitSequences &&groupUnitSequences) noexcept
    {
        groupUnitSequencesList_.emplace_back(groupUnitSequences);

        ++numberOfParamGroups_;
        return;
    }
    inline const std::vector<GroupReturnBitfields> &getGroupReturnBitfields() const noexcept
    {
        return groupReturnBitfieldsList_;
    }
    inline std::vector<GroupReturnBitfields> &getGroupReturnBitfieldsRef() noexcept
    {
        return groupReturnBitfieldsList_;
    }
    inline std::vector<GroupReturnBitfields> getGroupReturnBitfieldsCopy() const noexcept
    {
        return groupReturnBitfieldsList_;
    }
    inline void setGroupReturnBitfields(GroupReturnBitfields &&groupReturnBitfields) noexcept
    {
        groupReturnBitfieldsList_.emplace_back(groupReturnBitfields);

        ++numberOfParamGroups_;
        return;
    }
};
class NewOrderCross
{

    static constexpr uint16_t startOfMessage_ = StartOfMessageEnum::STARTOFMESSAGE;
    uint16_t messageLength_;
    static constexpr uint8_t messageType_ = MessagesEnum::NEWORDERCROSS;
    static constexpr uint8_t matchingUnit_ = MatchingUnitEnum::MATCHINGUNIT;
    uint32_t sequenceNumber_;
    std::array<char, StringLengthsEnum::CROSSID> crossID_;

public:
    enum class CrossTypeEnum : char
    {
        UNKNOWN = '0',
        AIM = '1',
        QCC = '2',
        SAM = '3',
        PCC = '4'
    };
    static const std::unordered_map<char, CrossTypeEnum> crossTypeEnumOptions;

private:
    CrossTypeEnum crossType_;

public:
    enum class CrossPrioritizationEnum : char
    {
        BUY = '1',
        SELL = '2',
        UNKNOWN = '0'
    };
    static const std::unordered_map<char, CrossPrioritizationEnum> crossPrioritizationEnumOptions;

private:
    CrossPrioritizationEnum crossPrioritization_;
    uint64_t price_;
    uint32_t orderQty_;
    uint8_t numberOfNewOrderCrossBitfields_;
    std::vector<GroupNumberOfNewOrderCrossBitfields> groupNumberOfNewOrderCrossBitfieldsList_;
    uint16_t groupCnt_;
    std::vector<GroupRepeatingGroupsOfNewOrderCross> groupRepeatingGroupsOfNewOrderCrossList_;
    std::array<char, StringLengthsEnum::SYMBOL> symbol_;
    uint32_t maturityDate_;
    uint64_t strikePrice_;
    char putOrCall_;
    char execInst_;
    char attributedQuote_;
    std::array<char, StringLengthsEnum::TARGETPARTYID> targetPartyID_;
    std::array<char, StringLengthsEnum::PREVENTMATCH> preventMatch_;
    char autoMatch_;
    uint64_t autoMatchPrice_;
    char lastPriority_;
    std::array<char, StringLengthsEnum::ROUTINGFIRMID> routingFirmID_;

public:
    NewOrderCross() : messageLength_(0), sequenceNumber_(0), crossID_{}, crossType_(CrossTypeEnum::UNKNOWN), crossPrioritization_(CrossPrioritizationEnum::UNKNOWN), price_(0), orderQty_(0), numberOfNewOrderCrossBitfields_(0), groupNumberOfNewOrderCrossBitfieldsList_(), groupCnt_(0), groupRepeatingGroupsOfNewOrderCrossList_(), symbol_{}, maturityDate_(0), strikePrice_(0), putOrCall_(0), execInst_(0), attributedQuote_(0), targetPartyID_{}, preventMatch_{}, autoMatch_(0), autoMatchPrice_(0), lastPriority_(0), routingFirmID_{}
    {
    }
    NewOrderCross(uint16_t messageLength, uint32_t sequenceNumber, const char *crossID, CrossTypeEnum crossType, CrossPrioritizationEnum crossPrioritization, uint64_t price, uint32_t orderQty, std::vector<GroupNumberOfNewOrderCrossBitfields> &&groupNumberOfNewOrderCrossBitfieldsList, std::vector<GroupRepeatingGroupsOfNewOrderCross> &&groupRepeatingGroupsOfNewOrderCrossList, const char *symbol, uint32_t maturityDate, uint64_t strikePrice, char putOrCall, char execInst, char attributedQuote, const char *targetPartyID, const char *preventMatch, char autoMatch, uint64_t autoMatchPrice, char lastPriority, const char *routingFirmID) : messageLength_(messageLength), sequenceNumber_(sequenceNumber), crossID_(), crossType_(crossType), crossPrioritization_(crossPrioritization), price_(price), orderQty_(orderQty), numberOfNewOrderCrossBitfields_(groupNumberOfNewOrderCrossBitfieldsList.size()), groupNumberOfNewOrderCrossBitfieldsList_(groupNumberOfNewOrderCrossBitfieldsList), groupCnt_(groupRepeatingGroupsOfNewOrderCrossList.size()), groupRepeatingGroupsOfNewOrderCrossList_(groupRepeatingGroupsOfNewOrderCrossList), symbol_(), maturityDate_(maturityDate), strikePrice_(strikePrice), putOrCall_(putOrCall), execInst_(execInst), attributedQuote_(attributedQuote), targetPartyID_(), preventMatch_(), autoMatch_(autoMatch), autoMatchPrice_(autoMatchPrice), lastPriority_(lastPriority), routingFirmID_()
    {
        std::memcpy(crossID_.data(), crossID, StringLengthsEnum::CROSSID);
        std::memcpy(symbol_.data(), symbol, StringLengthsEnum::SYMBOL);
        std::memcpy(targetPartyID_.data(), targetPartyID, StringLengthsEnum::TARGETPARTYID);
        std::memcpy(preventMatch_.data(), preventMatch, StringLengthsEnum::PREVENTMATCH);
        std::memcpy(routingFirmID_.data(), routingFirmID, StringLengthsEnum::ROUTINGFIRMID);
    }

    void reset()
    {
        messageLength_ = 0;
        sequenceNumber_ = 0;
        crossID_.fill('0');
        crossType_ = CrossTypeEnum::UNKNOWN;
        crossPrioritization_ = CrossPrioritizationEnum::UNKNOWN;
        price_ = 0;
        orderQty_ = 0;
        numberOfNewOrderCrossBitfields_ = 0;
        groupNumberOfNewOrderCrossBitfieldsList_.clear();
        groupCnt_ = 0;
        groupRepeatingGroupsOfNewOrderCrossList_.clear();
        symbol_.fill('0');
        maturityDate_ = 0;
        strikePrice_ = 0;
        putOrCall_ = 0;
        execInst_ = 0;
        attributedQuote_ = 0;
        targetPartyID_.fill('0');
        preventMatch_.fill('0');
        autoMatch_ = 0;
        autoMatchPrice_ = 0;
        lastPriority_ = 0;
        routingFirmID_.fill('0');
    }

    inline constexpr const uint16_t &getStartOfMessage() const noexcept { return startOfMessage_; }
    inline uint16_t getStartOfMessageCopy() const noexcept { return startOfMessage_; }

    inline const uint16_t &getMessageLength() const noexcept { return messageLength_; }
    inline uint16_t &getMessageLengthRef() noexcept { return messageLength_; }
    inline uint16_t getMessageLengthCopy() const noexcept { return messageLength_; }
    inline void setMessageLength(uint16_t messageLength) noexcept { messageLength_ = messageLength; }

    inline constexpr const uint8_t &getMessageType() const noexcept { return messageType_; }
    inline uint8_t getMessageTypeCopy() const noexcept { return messageType_; }

    inline constexpr const uint8_t &getMatchingUnit() const noexcept { return matchingUnit_; }
    inline uint8_t getMatchingUnitCopy() const noexcept { return matchingUnit_; }

    inline const uint32_t &getSequenceNumber() const noexcept { return sequenceNumber_; }
    inline uint32_t &getSequenceNumberRef() noexcept { return sequenceNumber_; }
    inline uint32_t getSequenceNumberCopy() const noexcept { return sequenceNumber_; }
    inline void setSequenceNumber(uint32_t sequenceNumber) noexcept { sequenceNumber_ = sequenceNumber; }

    inline const std::array<char, StringLengthsEnum::CROSSID> &getCrossID() const noexcept { return crossID_; }
    inline std::array<char, StringLengthsEnum::CROSSID> &getCrossIDRef() noexcept { return crossID_; }
    inline std::array<char, StringLengthsEnum::CROSSID> getCrossIDCopy() const noexcept { return crossID_; }
    inline void setCrossID(const char *crossID) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::CROSSID, std::strlen(crossID));
        std::memcpy(crossID_.data(), crossID, length);
        for (size_t i = length; i < StringLengthsEnum::CROSSID; ++i)
        {
            crossID_[i] = 0;
        }
    }

    inline const CrossTypeEnum &getCrossType() const noexcept { return crossType_; }
    inline CrossTypeEnum &getCrossTypeRef() noexcept { return crossType_; }
    inline CrossTypeEnum getCrossTypeCopy() const noexcept { return crossType_; }
    inline void setCrossType(CrossTypeEnum crossType) noexcept { crossType_ = crossType; }

    inline const CrossPrioritizationEnum &getCrossPrioritization() const noexcept { return crossPrioritization_; }
    inline CrossPrioritizationEnum &getCrossPrioritizationRef() noexcept { return crossPrioritization_; }
    inline CrossPrioritizationEnum getCrossPrioritizationCopy() const noexcept { return crossPrioritization_; }
    inline void setCrossPrioritization(CrossPrioritizationEnum crossPrioritization) noexcept { crossPrioritization_ = crossPrioritization; }

    inline const uint64_t &getPrice() const noexcept { return price_; }
    inline uint64_t &getPriceRef() noexcept { return price_; }
    inline uint64_t getPriceCopy() const noexcept { return price_; }
    inline void setPrice(uint64_t price) noexcept { price_ = price; }

    inline const uint32_t &getOrderQty() const noexcept { return orderQty_; }
    inline uint32_t &getOrderQtyRef() noexcept { return orderQty_; }
    inline uint32_t getOrderQtyCopy() const noexcept { return orderQty_; }
    inline void setOrderQty(uint32_t orderQty) noexcept { orderQty_ = orderQty; }

    inline const uint8_t &getNumberOfNewOrderCrossBitfields() const noexcept { return numberOfNewOrderCrossBitfields_; }
    inline uint8_t getNumberOfNewOrderCrossBitfieldsCopy() const noexcept { return numberOfNewOrderCrossBitfields_; }
    inline const std::vector<GroupNumberOfNewOrderCrossBitfields> &getGroupNumberOfNewOrderCrossBitfields() const noexcept
    {
        return groupNumberOfNewOrderCrossBitfieldsList_;
    }
    inline std::vector<GroupNumberOfNewOrderCrossBitfields> &getGroupNumberOfNewOrderCrossBitfieldsRef() noexcept
    {
        return groupNumberOfNewOrderCrossBitfieldsList_;
    }
    inline std::vector<GroupNumberOfNewOrderCrossBitfields> getGroupNumberOfNewOrderCrossBitfieldsCopy() const noexcept
    {
        return groupNumberOfNewOrderCrossBitfieldsList_;
    }
    inline void setGroupNumberOfNewOrderCrossBitfields(GroupNumberOfNewOrderCrossBitfields &&groupNumberOfNewOrderCrossBitfields) noexcept
    {
        groupNumberOfNewOrderCrossBitfieldsList_.emplace_back(groupNumberOfNewOrderCrossBitfields);

        ++numberOfNewOrderCrossBitfields_;
        return;
    }

    inline const uint16_t &getGroupCnt() const noexcept { return groupCnt_; }
    inline uint16_t getGroupCntCopy() const noexcept { return groupCnt_; }
    inline const std::vector<GroupRepeatingGroupsOfNewOrderCross> &getGroupRepeatingGroupsOfNewOrderCross() const noexcept
    {
        return groupRepeatingGroupsOfNewOrderCrossList_;
    }
    inline std::vector<GroupRepeatingGroupsOfNewOrderCross> &getGroupRepeatingGroupsOfNewOrderCrossRef() noexcept
    {
        return groupRepeatingGroupsOfNewOrderCrossList_;
    }
    inline std::vector<GroupRepeatingGroupsOfNewOrderCross> getGroupRepeatingGroupsOfNewOrderCrossCopy() const noexcept
    {
        return groupRepeatingGroupsOfNewOrderCrossList_;
    }
    inline void setGroupRepeatingGroupsOfNewOrderCross(GroupRepeatingGroupsOfNewOrderCross &&groupRepeatingGroupsOfNewOrderCross) noexcept
    {
        groupRepeatingGroupsOfNewOrderCrossList_.emplace_back(groupRepeatingGroupsOfNewOrderCross);

        ++groupCnt_;
        return;
    }

    inline const std::array<char, StringLengthsEnum::SYMBOL> &getSymbol() const noexcept { return symbol_; }
    inline std::array<char, StringLengthsEnum::SYMBOL> &getSymbolRef() noexcept { return symbol_; }
    inline std::array<char, StringLengthsEnum::SYMBOL> getSymbolCopy() const noexcept { return symbol_; }
    inline void setSymbol(const char *symbol) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::SYMBOL, std::strlen(symbol));
        std::memcpy(symbol_.data(), symbol, length);
        for (size_t i = length; i < StringLengthsEnum::SYMBOL; ++i)
        {
            symbol_[i] = 0;
        }
    }

    inline const uint32_t &getMaturityDate() const noexcept { return maturityDate_; }
    inline uint32_t &getMaturityDateRef() noexcept { return maturityDate_; }
    inline uint32_t getMaturityDateCopy() const noexcept { return maturityDate_; }
    inline void setMaturityDate(uint32_t maturityDate) noexcept { maturityDate_ = maturityDate; }

    inline const uint64_t &getStrikePrice() const noexcept { return strikePrice_; }
    inline uint64_t &getStrikePriceRef() noexcept { return strikePrice_; }
    inline uint64_t getStrikePriceCopy() const noexcept { return strikePrice_; }
    inline void setStrikePrice(uint64_t strikePrice) noexcept { strikePrice_ = strikePrice; }

    inline const char &getPutOrCall() const noexcept { return putOrCall_; }
    inline char &getPutOrCallRef() noexcept { return putOrCall_; }
    inline char getPutOrCallCopy() const noexcept { return putOrCall_; }
    inline void setPutOrCall(char putOrCall) noexcept { putOrCall_ = putOrCall; }

    inline const char &getExecInst() const noexcept { return execInst_; }
    inline char &getExecInstRef() noexcept { return execInst_; }
    inline char getExecInstCopy() const noexcept { return execInst_; }
    inline void setExecInst(char execInst) noexcept { execInst_ = execInst; }

    inline const char &getAttributedQuote() const noexcept { return attributedQuote_; }
    inline char &getAttributedQuoteRef() noexcept { return attributedQuote_; }
    inline char getAttributedQuoteCopy() const noexcept { return attributedQuote_; }
    inline void setAttributedQuote(char attributedQuote) noexcept { attributedQuote_ = attributedQuote; }

    inline const std::array<char, StringLengthsEnum::TARGETPARTYID> &getTargetPartyID() const noexcept { return targetPartyID_; }
    inline std::array<char, StringLengthsEnum::TARGETPARTYID> &getTargetPartyIDRef() noexcept { return targetPartyID_; }
    inline std::array<char, StringLengthsEnum::TARGETPARTYID> getTargetPartyIDCopy() const noexcept { return targetPartyID_; }
    inline void setTargetPartyID(const char *targetPartyID) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::TARGETPARTYID, std::strlen(targetPartyID));
        std::memcpy(targetPartyID_.data(), targetPartyID, length);
        for (size_t i = length; i < StringLengthsEnum::TARGETPARTYID; ++i)
        {
            targetPartyID_[i] = 0;
        }
    }

    inline const std::array<char, StringLengthsEnum::PREVENTMATCH> &getPreventMatch() const noexcept { return preventMatch_; }
    inline std::array<char, StringLengthsEnum::PREVENTMATCH> &getPreventMatchRef() noexcept { return preventMatch_; }
    inline std::array<char, StringLengthsEnum::PREVENTMATCH> getPreventMatchCopy() const noexcept { return preventMatch_; }
    inline void setPreventMatch(const char *preventMatch) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::PREVENTMATCH, std::strlen(preventMatch));
        std::memcpy(preventMatch_.data(), preventMatch, length);
        for (size_t i = length; i < StringLengthsEnum::PREVENTMATCH; ++i)
        {
            preventMatch_[i] = 0;
        }
    }

    inline const char &getAutoMatch() const noexcept { return autoMatch_; }
    inline char &getAutoMatchRef() noexcept { return autoMatch_; }
    inline char getAutoMatchCopy() const noexcept { return autoMatch_; }
    inline void setAutoMatch(char autoMatch) noexcept { autoMatch_ = autoMatch; }

    inline const uint64_t &getAutoMatchPrice() const noexcept { return autoMatchPrice_; }
    inline uint64_t &getAutoMatchPriceRef() noexcept { return autoMatchPrice_; }
    inline uint64_t getAutoMatchPriceCopy() const noexcept { return autoMatchPrice_; }
    inline void setAutoMatchPrice(uint64_t autoMatchPrice) noexcept { autoMatchPrice_ = autoMatchPrice; }

    inline const char &getLastPriority() const noexcept { return lastPriority_; }
    inline char &getLastPriorityRef() noexcept { return lastPriority_; }
    inline char getLastPriorityCopy() const noexcept { return lastPriority_; }
    inline void setLastPriority(char lastPriority) noexcept { lastPriority_ = lastPriority; }

    inline const std::array<char, StringLengthsEnum::ROUTINGFIRMID> &getRoutingFirmID() const noexcept { return routingFirmID_; }
    inline std::array<char, StringLengthsEnum::ROUTINGFIRMID> &getRoutingFirmIDRef() noexcept { return routingFirmID_; }
    inline std::array<char, StringLengthsEnum::ROUTINGFIRMID> getRoutingFirmIDCopy() const noexcept { return routingFirmID_; }
    inline void setRoutingFirmID(const char *routingFirmID) noexcept
    {

        std::size_t length = std::min<std::size_t>(StringLengthsEnum::ROUTINGFIRMID, std::strlen(routingFirmID));
        std::memcpy(routingFirmID_.data(), routingFirmID, length);
        for (size_t i = length; i < StringLengthsEnum::ROUTINGFIRMID; ++i)
        {
            routingFirmID_[i] = 0;
        }
    }
};

const std::unordered_map<char, NewOrderCross::CrossTypeEnum> crossTypeEnumOptions = {{'0', NewOrderCross::CrossTypeEnum::UNKNOWN}, {'1', NewOrderCross::CrossTypeEnum::AIM}, {'2', NewOrderCross::CrossTypeEnum::QCC}, {'3', NewOrderCross::CrossTypeEnum::SAM}, {'4', NewOrderCross::CrossTypeEnum::PCC}};
const std::unordered_map<char, NewOrderCross::CrossPrioritizationEnum> crossPrioritizationEnumOptions = {{'1', NewOrderCross::CrossPrioritizationEnum::BUY}, {'2', NewOrderCross::CrossPrioritizationEnum::SELL}, {'0', NewOrderCross::CrossPrioritizationEnum::UNKNOWN}};