#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的EventData
struct _EType_EventData
{
    // 框架QQ
    elong ThisQQ;
    // 来源群号
    elong SourceGroupQQ;
    // 操作QQ
    elong OperateQQ;
    // 触发QQ
    elong TriggerQQ;
    // 消息Seq
    elong MessageSeq;
    // 消息时间戳
    eint MessageTimestamp;
    // 来源群名
    etext SourceGroupName = nullptr;
    // 操作QQ昵称
    etext OperateQQName = nullptr;
    // 触发QQ昵称
    etext TriggerQQName = nullptr;
    // 事件内容
    etext MessageContent = nullptr;
    // 事件类型
    EventTypeEnum EventType;
    // 事件子类型
    eint EventSubType;
};
#pragma pack()

// 事件数据
struct EventData
{
    // 框架QQ
    elong ThisQQ;
    // 来源群号
    elong SourceGroupQQ;
    // 操作QQ
    elong OperateQQ;
    // 触发QQ
    elong TriggerQQ;
    // 消息Seq
    elong MessageSeq;
    // 消息时间戳
    eint MessageTimestamp;
    // 来源群名
    ::std::string SourceGroupName;
    // 操作QQ昵称
    ::std::string OperateQQName;
    // 触发QQ昵称
    ::std::string TriggerQQName;
    // 事件内容
    ::std::string MessageContent;
    // 事件类型
    EventTypeEnum EventType;
    // 事件子类型
    eint EventSubType;
    
    EventData(const _EType_EventData& info):ThisQQ{info.ThisQQ},
        SourceGroupQQ{info.SourceGroupQQ},
        OperateQQ{info.OperateQQ},
        TriggerQQ{info.TriggerQQ},
        MessageSeq{info.MessageSeq},
        MessageTimestamp{info.MessageTimestamp},
        EventType{info.EventType},
        EventSubType{info.EventSubType}
    {
        string_e2std(this->SourceGroupName, info.SourceGroupName);
        string_e2std(this->OperateQQName, info.OperateQQName);
        string_e2std(this->TriggerQQName, info.TriggerQQName);
        string_e2std(this->MessageContent, info.MessageContent);
    }
};
