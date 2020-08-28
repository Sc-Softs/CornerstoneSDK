#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的OrderDetail
struct _EType_OrderDetail
{
    // 订单时间
    etext OrderTime = nullptr;
    // 订单说明
    etext OrderDescription = nullptr;
    // 订单类名
    etext OrderClassification = nullptr;
    // 订单类型
    etext OrderType = nullptr;
    // 订单手续费
    etext OrderCommission = nullptr;
    // 操作人QQ
    etext OperatorQQ = nullptr;
    // 操作人昵称
    etext OperatorName = nullptr;
    // 接收人QQ
    etext ReceiverQQ = nullptr;
    // 接收人昵称
    etext ReceiverName = nullptr;
    // 操作金额
    etext OperateAmount = nullptr;
};
#pragma pack()

// 订单详情
struct OrderDetail
{
    // 订单时间
    ::std::string OrderTime;
    // 订单说明
    ::std::string OrderDescription;
    // 订单类名
    ::std::string OrderClassification;
    // 订单类型
    ::std::string OrderType;
    // 订单手续费
    ::std::string OrderCommission;
    // 操作人QQ
    ::std::string OperatorQQ;
    // 操作人昵称
    ::std::string OperatorName;
    // 接收人QQ
    ::std::string ReceiverQQ;
    // 接收人昵称
    ::std::string ReceiverName;
    // 操作金额
    ::std::string OperateAmount;

    OrderDetail(const _EType_OrderDetail &info)
    {
        string_e2std(this->OrderTime, info.OrderTime);
        string_e2std(this->OrderDescription, info.OrderDescription);
        string_e2std(this->OrderClassification, info.OrderClassification);
        string_e2std(this->OrderType, info.OrderType);
        string_e2std(this->OrderCommission, info.OrderCommission);
        string_e2std(this->OperatorQQ, info.OperatorQQ);
        string_e2std(this->OperatorName, info.OperatorName);
        string_e2std(this->ReceiverQQ, info.ReceiverQQ);
        string_e2std(this->ReceiverName, info.ReceiverName);
        string_e2std(this->OperateAmount, info.OperateAmount);
    }
};
