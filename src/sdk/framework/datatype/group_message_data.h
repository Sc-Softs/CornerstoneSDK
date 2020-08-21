#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的GroupMessageData
struct _EType_GroupMessageData
{
    // 发送人QQ
    elong SenderQQ;
    // 框架QQ
    elong ThisQQ;
    // 消息Req
    eint MessageReq;
    // 消息接收时间
    eint MessageReceiveTime;
    // 消息群号
    elong MessageGroupQQ;
    // 消息来源群名（貌似失效了）
    etext SourceGroupName = nullptr;
    // 发送人群名片 没有名片则为空白
    etext SenderNickname = nullptr;
    // 消息发送时间
    eint MessageSendTime;
    // 消息Random
    elong MessageRandom;
    // 消息分片序列
    eint MessageClip;
    // 消息分片数量
    eint MessageClipCount;
    // 消息分片标识
    elong MessageClipID;
    // 消息类型
    MessageTypeEnum MessageType;
    // 发送人群头衔
    etext SenderTitle = nullptr;
    // 消息内容
    etext MessageContent = nullptr;
    // 回复对象消息内容 如果是回复消息
    etext ReplyMessageContent = nullptr;
    // 发送者气泡ID
    eint BubbleID;
    // 框架QQ匿名Id，用于区分别人和自己(当天从未使用过匿名则为0)
    eint ThisQQAnonymousID;
    // 保留参数，请勿使用
    eint reserved_;
    // 文件Id
    etext FileID = nullptr;
    // 文件Md5
    ebin FileMD5 = nullptr;
    // 文件名
    etext FileName = nullptr;
    // 文件大小
    elong FileSize;
    // 消息AppID
    eint MessageAppID;
};
#pragma pack()

// 群消息数据
struct GroupMessageData
{
    // 发送人QQ
    elong SenderQQ;
    // 框架QQ
    elong ThisQQ;
    // 消息Req
    eint MessageReq;
    // 消息接收时间
    eint MessageReceiveTime;
    // 消息群号
    elong MessageGroupQQ;
    // 消息来源群名（貌似失效了）
    ::std::string SourceGroupName;
    // 发送人群名片 没有名片则为空白
    ::std::string SenderNickname;
    // 消息发送时间
    eint MessageSendTime;
    // 消息Random
    elong MessageRandom;
    // 消息分片序列
    eint MessageClip;
    // 消息分片数量
    eint MessageClipCount;
    // 消息分片标识
    elong MessageClipID;
    // 消息类型
    MessageTypeEnum MessageType;
    // 发送人群头衔
    ::std::string SenderTitle;
    // 消息内容
    ::std::string MessageContent;
    // 回复对象消息内容 如果是回复消息
    ::std::string ReplyMessageContent;
    // 发送者气泡ID
    eint BubbleID;
    // 框架QQ匿名Id，用于区分别人和自己(当天从未使用过匿名则为0)
    eint ThisQQAnonymousID;
    // 保留参数，请勿使用
    eint reserved_;
    // 文件Id
    ::std::string FileID;
    // 文件Md5
    ebin FileMD5 = nullptr;
    // 文件名
    ::std::string FileName;
    // 文件大小
    elong FileSize;
    // 消息AppID
    eint MessageAppID;
    GroupMessageData(const _EType_GroupMessageData& info):
        SenderQQ{info.SenderQQ},
        ThisQQ{info.ThisQQ},
        MessageReq{info.MessageReq},
        MessageReceiveTime{info.MessageReceiveTime},
        MessageGroupQQ{info.MessageGroupQQ},
        MessageSendTime{info.MessageSendTime},
        MessageRandom{info.MessageRandom},
        MessageClip{info.MessageClip},
        MessageClipCount{info.MessageClipCount},
        MessageClipID{info.MessageClipID},
        MessageType{info.MessageType},
        BubbleID{info.BubbleID},
        ThisQQAnonymousID{info.ThisQQAnonymousID},
        FileSize{info.FileSize},
        MessageAppID{info.MessageAppID}
    {
        string_e2std(this->SourceGroupName, info.SourceGroupName);
        string_e2std(this->SenderNickname, info.SenderNickname);
        string_e2std(this->SenderTitle, info.SenderTitle);
        string_e2std(this->MessageContent, info.MessageContent);
        string_e2std(this->ReplyMessageContent, info.ReplyMessageContent);
        string_e2std(this->FileID, info.FileID);
        string_e2std(this->FileName, info.FileName);
    }
};
