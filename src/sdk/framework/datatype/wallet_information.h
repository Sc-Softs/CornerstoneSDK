#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"
#include "./card_information.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的QQWalletInformation
struct _EType_QQWalletInformation
{
    // 余额
    etext Balance = nullptr;
    // 身份证号
    etext ID = nullptr;
    // 实名
    etext RealName = nullptr;
    // 银行卡列表
    _EType_CardInformation *CardList = nullptr;
};
#pragma pack()

// QQ钱包信息
struct QQWalletInformation
{
    // 余额
    ::std::string Balance;
    // 身份证号
    ::std::string ID;
    // 实名
    ::std::string RealName;
    // 银行卡列表
    ::std::vector<CardInformation> CardList;

    QQWalletInformation(const _EType_QQWalletInformation& info)
    {
        string_e2std(this->Balance, info.Balance);
        string_e2std(this->ID, info.ID);
        string_e2std(this->RealName, info.RealName);

        if (info.CardList != nullptr)
        {
            auto size = reinterpret_cast<eint*>(info.CardList)[1];
            auto pptr = reinterpret_cast<_EType_CardInformation**>(
                reinterpret_cast<eint*>(info.CardList)+2);
            ::std::for_each(pptr,pptr+size,[this](const auto ptr){
                this->CardList.push_back(*ptr);
            });
        }
    }
};
