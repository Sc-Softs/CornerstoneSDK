#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的GroupMemberInformation
struct _EType_GroupMemberInformation
{
    // 账号
    etext QQNumber = nullptr;
    // 年龄
    eint Age;
    // 性别
    eint Gender;
    // 昵称
    etext Name = nullptr;
    // 邮箱
    etext Email = nullptr;
    // 名片
    etext Nickname = nullptr;
    // 备注
    etext Note = nullptr;
    // 头衔
    etext Title = nullptr;
    // 手机号
    etext Phone = nullptr;
    // 头衔到期时间
    elong TitleTimeout;
    // 禁言时间戳
    elong ShutUpTimestamp;
    // 加群时间
    elong JoinTime;
    // 发言时间
    elong ChatTime;
    // 群等级
    elong Level;
};
#pragma pack()

// 群成员信息
struct GroupMemberInformation
{
    // 账号
    ::std::string QQNumber;
    // 年龄
    eint Age;
    // 性别
    eint Gender;
    // 昵称
    ::std::string Name;
    // 邮箱
    ::std::string Email;
    // 名片
    ::std::string Nickname;
    // 备注
    ::std::string Note;
    // 头衔
    ::std::string Title;
    // 手机号
    ::std::string Phone;
    // 头衔到期时间
    elong TitleTimeout;
    // 禁言时间戳
    elong ShutUpTimestamp;
    // 加群时间
    elong JoinTime;
    // 发言时间
    elong ChatTime;
    // 群等级
    elong Level;

    GroupMemberInformation(const _EType_GroupMemberInformation &info) : Age{info.Age},
                                                                        Gender{info.Gender},
                                                                        TitleTimeout{info.TitleTimeout},
                                                                        ShutUpTimestamp{info.ShutUpTimestamp},
                                                                        JoinTime{info.JoinTime},
                                                                        ChatTime{info.ChatTime},
                                                                        Level{info.Level}
    {
        string_e2std(this->QQNumber, info.QQNumber);
        string_e2std(this->Name, info.Name);
        string_e2std(this->Email, info.Email);
        string_e2std(this->Nickname, info.Nickname);
        string_e2std(this->Note, info.Note);
        string_e2std(this->Title, info.Title);
        string_e2std(this->Phone, info.Phone);
    }
};
