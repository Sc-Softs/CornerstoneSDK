#pragma once

#include "../../eport/etypes.h"
#include "../constants.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的ServiceInformation
struct _EType_ServiceInformation
{
    // 服务代号 1: SVIP, 4: 视频会员, 6: 音乐包, 105: star, 102: 黄钻, 103: 绿钻, 101: 红钻, 104:yellowlove, 107: SVIP&视频会员, 109: SVIP&绿钻, 110: SVIP&音乐包
    eint ServiceCodename;
    // 服务等级
    eint ServiceLevel;
};
#pragma pack()

// 服务信息
struct ServiceInformation
{
    enum ServiceCode : eint
    {
        SVIP = 1,              //SVIP
        VIDEO_VIP = 4,         //视频会员
        MUSIC_PACK = 6,        //音乐包
        STAR = 105,            //star
        YELLOW_DIAMOND = 102,  //黄钻
        GREEN_DIAMOND = 103,   //绿钻
        RED_DIAMOND = 101,     //红钻
        YELLOWLOVE = 104,      //yellowlove
        SVIP_WITH_VIDEO = 107, //SVIP&视频会员
        SVIP_WITH_GREEN = 109, //SVIP&绿钻
        SVIP_WITH_MUSIC = 110  //SVIP&音乐包
    } ServiceCodename;
    eint ServiceLevel;

    ServiceInformation(const _EType_ServiceInformation &info) : ServiceCodename{info.ServiceCodename}, ServiceLevel{info.ServiceLevel}
    {
    }
};
