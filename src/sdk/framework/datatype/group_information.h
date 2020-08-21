#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的GroupInformation
struct _EType_GroupInformation
{
    // 群ID
    elong GroupID;
    // 群号
    elong GroupQQ;
    // cFlag
    elong CFlag;
    // dwGroupInfoSeq
    elong GroupInfoSeq;
    // dwGroupFlagExt
    elong GroupFlagExt;
    // dwGroupRankSeq
    elong GroupRankSeq;
    // dwCertificationType
    elong CertificationType;
    // 禁言时间戳
    elong ShutUpTimestamp;
    // 框架QQ禁言时间戳
    elong ThisShutUpTimestamp;
    // dwCmdUinUinFlag
    elong CmdUinUinFlag;
    // dwAdditionalFlag
    elong AdditionalFlag;
    // dwGroupTypeFlag
    elong GroupTypeFlag;
    // dwGroupSecType
    elong GroupSecType;
    // dwGroupSecTypeInfo
    elong GroupSecTypeInfo;
    // dwGroupClassExt
    elong GroupClassExt;
    // dwAppPrivilegeFlag
    elong AppPrivilegeFlag;
    // dwSubscriptionUin
    elong SubscriptionUin;
    // 群成员数量
    elong GroupMemberCount;
    // dwMemberNumSeq
    elong MemberNumSeq;
    // dwMemberCardSeq
    elong MemberCardSeq;
    // dwGroupFlagExt3
    elong GroupFlagExt3;
    // dwGroupOwnerUin
    elong GroupOwnerUin;
    // cIsConfGroup
    elong IsConfGroup;
    // cIsModifyConfGroupFace
    elong IsModifyConfGroupFace;
    // cIsModifyConfGroupName
    elong IsModifyConfGroupName;
    // dwCmduinJoinTime
    elong CmduinJoinTime;
    // 群名称
    etext GroupName = nullptr;
    // strGroupMemo
    etext GroupMemo = nullptr;
};
#pragma pack()

// 群信息
struct GroupInformation
{
    // 群ID
    elong GroupID;
    // 群号
    elong GroupQQ;
    // cFlag
    elong CFlag;
    // dwGroupInfoSeq
    elong GroupInfoSeq;
    // dwGroupFlagExt
    elong GroupFlagExt;
    // dwGroupRankSeq
    elong GroupRankSeq;
    // dwCertificationType
    elong CertificationType;
    // 禁言时间戳
    elong ShutUpTimestamp;
    // 框架QQ禁言时间戳
    elong ThisShutUpTimestamp;
    // dwCmdUinUinFlag
    elong CmdUinUinFlag;
    // dwAdditionalFlag
    elong AdditionalFlag;
    // dwGroupTypeFlag
    elong GroupTypeFlag;
    // dwGroupSecType
    elong GroupSecType;
    // dwGroupSecTypeInfo
    elong GroupSecTypeInfo;
    // dwGroupClassExt
    elong GroupClassExt;
    // dwAppPrivilegeFlag
    elong AppPrivilegeFlag;
    // dwSubscriptionUin
    elong SubscriptionUin;
    // 群成员数量
    elong GroupMemberCount;
    // dwMemberNumSeq
    elong MemberNumSeq;
    // dwMemberCardSeq
    elong MemberCardSeq;
    // dwGroupFlagExt3
    elong GroupFlagExt3;
    // dwGroupOwnerUin
    elong GroupOwnerUin;
    // cIsConfGroup
    elong IsConfGroup;
    // cIsModifyConfGroupFace
    elong IsModifyConfGroupFace;
    // cIsModifyConfGroupName
    elong IsModifyConfGroupName;
    // dwCmduinJoinTime
    elong CmduinJoinTime;
    // 群名称
    ::std::string GroupName;
    // strGroupMemo
    ::std::string GroupMemo;

    GroupInformation(const _EType_GroupInformation& info):
        GroupID{info.GroupID},
        GroupQQ{info.GroupQQ},
        CFlag{info.CFlag},
        GroupInfoSeq{info.GroupInfoSeq},
        GroupFlagExt{info.GroupFlagExt},
        GroupRankSeq{info.GroupRankSeq},
        CertificationType{info.CertificationType},
        ShutUpTimestamp{info.ShutUpTimestamp},
        ThisShutUpTimestamp{info.ThisShutUpTimestamp},
        CmdUinUinFlag{info.CmdUinUinFlag},
        AdditionalFlag{info.AdditionalFlag},
        GroupTypeFlag{info.GroupTypeFlag},
        GroupSecType{info.GroupSecType},
        GroupSecTypeInfo{info.GroupSecTypeInfo},
        GroupClassExt{info.GroupClassExt},
        AppPrivilegeFlag{info.AppPrivilegeFlag},
        SubscriptionUin{info.SubscriptionUin},
        GroupMemberCount{info.GroupMemberCount},
        MemberNumSeq{info.MemberNumSeq},
        MemberCardSeq{info.MemberCardSeq},
        GroupFlagExt3{info.GroupFlagExt3},
        GroupOwnerUin{info.GroupOwnerUin},
        IsConfGroup{info.IsConfGroup},
        IsModifyConfGroupFace{info.IsModifyConfGroupFace},
        IsModifyConfGroupName{info.IsModifyConfGroupName},
        CmduinJoinTime{info.CmduinJoinTime}
    {
        string_e2std(this->GroupName,info.GroupName);
        string_e2std(this->GroupMemo,info.GroupMemo);
    }
};
