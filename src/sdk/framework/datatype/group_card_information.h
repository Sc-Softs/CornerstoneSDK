#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的GroupCardInformation
struct _EType_GroupCardInformation
{
    // 群名称
    etext GroupName = nullptr;
    // 群地点
    etext GroupLocation = nullptr;
    // 群分类
    etext GroupClassification = nullptr;
    // 群标签 以|分割
    etext GroupTags = nullptr;
    // 群介绍
    etext GroupDescription = nullptr;
};
#pragma pack()

// 群卡片信息
struct GroupCardInformation
{
    // 群名称
    ::std::string GroupName;
    // 群地点
    ::std::string GroupLocation;
    // 群分类
    ::std::string GroupClassification;
    // 群标签 以|分割
    ::std::string GroupTags;
    // 群介绍
    ::std::string GroupDescription;

    GroupCardInformation(const _EType_GroupCardInformation& info)
    {
        string_e2std(this->GroupName, info.GroupName);
        string_e2std(this->GroupLocation, info.GroupLocation);
        string_e2std(this->GroupClassification, info.GroupClassification);
        string_e2std(this->GroupTags, info.GroupTags);
        string_e2std(this->GroupDescription, info.GroupDescription);
    }
};
