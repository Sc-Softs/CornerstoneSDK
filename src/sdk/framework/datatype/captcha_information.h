#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的CaptchaInformation
struct _EType_CaptchaInformation
{
    // token_id
    etext TokenID = nullptr;
    // skey
    etext SKey = nullptr;
    // bank_type
    etext BankType = nullptr;
    // mobile
    etext Mobile = nullptr;
    // business_type
    etext BusinessType = nullptr;
    // random
    eint Random;
    // transaction_id
    etext TransactionID = nullptr;
    // purchaser_id
    etext PurchaserID = nullptr;
    // token
    etext Token = nullptr;
    // auth_params
    etext AuthParams = nullptr;
};
#pragma pack()

// 验证码信息
struct CaptchaInformation
{
    // token_id
    ::std::string TokenID;
    // skey
    ::std::string SKey;
    // bank_type
    ::std::string BankType;
    // mobile
    ::std::string Mobile;
    // business_type
    ::std::string BusinessType;
    // random
    eint Random;
    // transaction_id
    ::std::string TransactionID;
    // purchaser_id
    ::std::string PurchaserID;
    // token
    ::std::string Token;
    // auth_params
    ::std::string AuthParams;

    CaptchaInformation(const _EType_CaptchaInformation &info)
    {
        string_e2std(this->TokenID, info.TokenID);
        string_e2std(this->SKey, info.SKey);
        string_e2std(this->BankType, info.BankType);
        string_e2std(this->Mobile, info.Mobile);
        string_e2std(this->BusinessType, info.BusinessType);
        string_e2std(this->TransactionID, info.TransactionID);
        string_e2std(this->PurchaserID, info.PurchaserID);
        string_e2std(this->Token, info.Token);
        string_e2std(this->AuthParams, info.AuthParams);
    }

    operator _EType_CaptchaInformation() const
    {
        _EType_CaptchaInformation ret;
        ret.TokenID = this->TokenID.c_str();
        ret.SKey = this->SKey.c_str();
        ret.BankType = this->BankType.c_str();
        ret.Mobile = this->Mobile.c_str();
        ret.BusinessType = this->BusinessType.c_str();
        ret.Random = this->Random;
        ret.TransactionID = this->TransactionID.c_str();
        ret.PurchaserID = this->PurchaserID.c_str();
        ret.Token = this->Token.c_str();
        ret.AuthParams = this->AuthParams.c_str();
        return ret;
    }
};
