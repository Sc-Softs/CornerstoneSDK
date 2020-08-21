#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的CardInformation
struct _EType_CardInformation
{
    // 序列
    eint Serial;
    // 尾号
    etext TailNumber = nullptr;
    // 银行
    etext Bank = nullptr;
    // 绑定手机
    etext BindPhone = nullptr;
    // bind_serial
    etext BindSerial = nullptr;
    // bank_type
    etext BankType = nullptr;
};
#pragma pack()

// 银行卡信息
struct CardInformation
{
    // 序列
    eint Serial;
    // 尾号
    ::std::string TailNumber;
    // 银行
    ::std::string Bank;
    // 绑定手机
    ::std::string BindPhone;
    // bind_serial
    ::std::string BindSerial;
    // bank_type
    ::std::string BankType;

    CardInformation(const _EType_CardInformation& info):
        Serial{info.Serial}
    {
        string_e2std(this->TailNumber, info.TailNumber);
        string_e2std(this->Bank, info.Bank);
        string_e2std(this->BindPhone, info.BindPhone);
        string_e2std(this->BindSerial, info.BindSerial);
        string_e2std(this->BankType, info.BankType);
    }
};
