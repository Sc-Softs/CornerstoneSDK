/*
小栗子机器人非官方C++SDK xsdk v0.1.1 (C) NKID00 2020

部分改编自小栗子机器人官方易语言SDK cornsdk v2.5.9

zlib License

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef XSDK_INCLUDE_XSDK_HPP_
#define XSDK_INCLUDE_XSDK_HPP_

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <string>
#include <array>

#include "json.hpp"
using json = nlohmann::json;

using namespace std;

#define ECALL __stdcall  // 易语言调用约定

using ebyte = uint8_t;  // 易语言字节型
using eshort = int16_t;  // 易语言短整数型
using eint = int32_t;  // 易语言整数型
using elong = int64_t;  // 易语言长整数型
using efloat = float;  // 易语言小数型
using edouble = double;  // 易语言双精度小数型
using edate = uint64_t;  // 易语言日期时间型

using ebool = int32_t;  // 易语言逻辑型
constexpr ebool etrue = 1;
constexpr ebool efalse = 0;

constexpr ebool bool2ebool(const bool& b)
{
    return b ? etrue : efalse;
}

constexpr bool ebool2bool(const ebool& eb)
{
    return eb == etrue;
}

auto& b2e = bool2ebool;
auto& e2b = ebool2bool;

using etext = const char*;  // 易语言文本型(GB2312)

etext wstring2etext(const wstring& ws)  // Unicode -> GB2312
{
    // 取得长度
    auto es_len = WideCharToMultiByte(CP_ACP, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
    auto es_c_str = new char[es_len + 1];
    memset(es_c_str, 0, sizeof(char) * (es_len + 1));
    // 转换
    WideCharToMultiByte(CP_ACP, 0, ws.c_str(), -1, es_c_str, es_len, nullptr, nullptr);
    string es(es_c_str);
    delete[] es_c_str;
    return es.c_str();
}

wstring etext2wstring(etext es)  // GB2312 -> Unicode
{
    // 取得长度
    auto ws_len = MultiByteToWideChar(CP_ACP, 0, es, -1, nullptr, 0);
    auto ws_c_str = new wchar_t[ws_len + 1];
    memset(ws_c_str, 0, sizeof(wchar_t) * (ws_len + 1));
    // 转换
    MultiByteToWideChar(CP_ACP, 0, es, -1, ws_c_str, ws_len);
    wstring ws(ws_c_str);
    delete[] ws_c_str;
    return ws;
}

auto& w2e = wstring2etext;  // Unicode -> GB2312
auto& e2w = etext2wstring;  // GB2312 -> Unicode

using ebin = const uint8_t*;  // 易语言字节集
using esubptr = uint32_t;  // 易语言子程序指针

enum class MessageProcess  // 消息处理
{
    Block = 1,  // 拦截
    Ignore = 0  // 忽略
};

enum class MessageType  // 消息类型
{
    Temporary = 141,  // 临时会话
    Temporary_Group = 0,  // 临时会话_群
    Temporary_PublicAccount = 129,  // 临时会话_公众号
    Temporary_WebQQConsultation = 201,  // 临时会话_网页QQ咨询
    FriendUsualMessage = 166,  // 好友通常消息
    FriendFile = 529,  // 好友文件
    FriendAudio = 208,  // 好友语音
    GroupRedEnvelope = 78,  // 群红包
    GroupUsualMessage = 134  // 群聊通常消息
};

enum class GroupEvent  // 群事件
{
    Invited = 1,  // 我被邀请加入群
    MemberJoined = 2,  // 某人加入了群
    MemberVerifying = 3,  // 某人申请加群
    GroupDissolved = 4,  // 群被解散
    MemberQuit = 5,  // 某人退出了群
    MemberKicked = 6,  // 某人被踢出群
    MemberBanned = 7,  // 某人被禁言
    MemberUndid = 8,  // 某人撤回事件
    AdministratorTook = 9,  // 某人被取消管理
    AdministratorGave = 10,  // 某人被赋予管理
    EnableAllBanned = 11,  // 开启全员禁言
    DisableAllBanned = 12,  // 关闭全员禁言
    EnableAnonymous = 13,  // 开启匿名聊天
    DisableAnonymous = 14,  // 关闭匿名聊天
    EnableChatFrankly = 15,  // 开启坦白说
    DisableChatFrankly = 16,  // 关闭坦白说
    AllowGroupTemporary = 17,  // 允许群临时会话
    ForbidGroupTemporary = 18,  // 禁止群临时会话
    AllowCreateGroup = 19,  // 允许发起新的群聊
    ForbidCreateGroup = 20,  // 禁止发起新的群聊
    AllowUploadFile = 21,  // 允许上传群文件
    ForbidUploadFile = 22,  // 禁止上传群文件
    AllowUploadPicture = 23,  // 允许上传相册
    ForbidUploadPicture = 24,  // 禁止上传相册
    MemberInvited = 25,  // 某人被邀请入群
    ShowMemberTitle = 27,  // 展示成员群头衔
    HideMemberTitle = 28,  // 隐藏成员群头衔
    MemberUnbanned = 29  // 某人被解除禁言
};

enum class QZoneEvent  // 空间事件
{
    Related = 30  // 与我相关
};

enum class FriendEvent  // 好友事件
{
    Removed = 15,  // 被好友删除
    SignatureChanged = 16,  // 签名变更
    NameChanged = 17,  // 昵称改变
    UserUndid = 18,  // 某人撤回事件
    NewFriend = 19,  // 有新好友
    FriendRequest = 20,  // 好友请求
    FriendRequestAccepted = 21,  // 对方同意了您的好友请求
    FriendRequestRefused = 22,  // 对方拒绝了您的好友请求
    InformationLiked = 23,  // 资料卡点赞
    SignatureLiked = 24,  // 签名点赞
    SignatureReplied = 25,  // 签名回复
    TagLiked = 26,  // 个性标签点赞
    StickerLiked = 27,  // 随心贴回复
    StickerAdded = 28  // 随心贴增添
};

enum class Permission  // 权限
{
    OutputLog = 0,  // 输出日志
    SendFriendMessage = 1,  // 发送好友消息
    SendGroupMessage = 2,  // 发送群消息
    SendGroupTemporaryMessage = 3,  // 发送群临时消息
    AddFriend = 4,  // 添加好友
    AddGroup = 5,  // 添加群
    RemoveFriend = 6,  // 删除好友
    SetBlockFriend = 7,  // 设置屏蔽好友
    SetSpecialFriend = 8,  // 设置特别关心好友
    SendFriendJSONMessage = 11,  // 发送好友json消息
    SendGroupJSONMessage = 12,  // 发送群json消息
    UploadFriendPicture = 13,  // 上传好友图片
    UploadGroupPicture = 14,  // 上传群图片
    UploadFriendAudio = 15,  // 上传好友语音
    UploadGroupAudio = 16,  // 上传群语音
    UploadAvatar = 17,  // 上传头像
    SetGroupMemberNickname = 18,  // 设置群名片
    GetNameFromCache = 19,  // 从缓存获取昵称
    GetNameForce = 20,  // 强制获取昵称
    GetSKey = 21,  // 获取skey
    GetPSKey = 22,  // 获取pskey
    GetClientKey = 23,  // 获取clientkey
    GetThisQQ = 24,  // 获取框架QQ
    GetFriendList = 25,  // 获取好友列表
    GetGroupList = 26,  // 取群列表
    GetGroupMemberList = 27,  // 取群成员列表
    SetAdministrator = 28,  // 设置管理员
    GetAdministratorList = 29,  // 取管理层列表
    GetGroupMemberNickname = 30,  // 取群名片
    GetSignature = 31,  // 取个性签名
    SetName = 32,  // 修改昵称
    SetSignature = 33,  // 修改个性签名
    KickGroupMember = 34,  // 删除群成员
    BanGroupMember = 35,  // 禁言群成员
    QuitGroup = 36,  //退群
    DissolveGroup = 37,  // 解散群
    UploadGroupAvatar = 38,  // 上传群头像
    BanAll = 39,  // 全员禁言
    Group_Create = 40,  // 群权限_发起新的群聊
    Group_CreateTemporary = 41,  // 群权限_发起临时会话
    Group_UploadFile = 42,  // 群权限_上传文件
    Group_UploadPicture = 43,  // 群权限_上传相册
    Group_InviteFriend = 44,  // 群权限_邀请好友加群
    Group_Anonymous = 45,  // 群权限_匿名聊天
    群权限_坦白说 = 46,
    群权限_新成员查看历史消息 = 47,
    群权限_邀请方式设置 = 48,
    撤回消息_群聊 = 49,
    撤回消息_私聊本身 = 50,
    设置位置共享 = 51,
    上报当前位置 = 52,
    是否被禁言 = 53,
    处理好友验证事件 = 54,
    处理群验证事件 = 55,
    查看转发聊天记录内容 = 56,
    上传群文件 = 57,
    创建群文件夹 = 58,
    设置在线状态 = 59,
    QQ点赞 = 60,
    取图片下载地址 = 61,
    查询好友信息 = 63,
    查询群信息 = 64,
    框架重启 = 65,
    群文件转发至群 = 66,
    群文件转发至好友 = 67,
    好友文件转发至好友 = 68,
    置群消息接收 = 69,
    取群名称_从缓存 = 70,
    发送免费礼物 = 71,
    取好友在线状态 = 72,
    取QQ钱包个人信息 = 73,
    获取订单详情 = 74,
    提交支付验证码 = 75,
    分享音乐 = 77,
    更改群聊消息内容 = 78,
    更改私聊消息内容 = 79,
    群聊口令红包 = 80,
    群聊拼手气红包 = 81,
    群聊普通红包 = 82,
    群聊画图红包 = 83,
    群聊语音红包 = 84,
    群聊接龙红包 = 85,
    群聊专属红包 = 86,
    好友口令红包 = 87,
    好友普通红包 = 88,
    好友画图红包 = 89,
    好友语音红包 = 90,
    好友接龙红包 = 91,
};

struct 私聊消息数据
{
    elong 发送人QQ;
    elong 框架QQ;
    eint 消息Req;
    elong 消息Seq;
    eint 消息接收时间;
    elong 消息群号;  // 当为群临时会话时可取
    eint 消息发送时间;
    elong 消息Random;  // 消息random
    eint 消息分片序列;
    eint 消息分片数量;
    elong 消息分片标识;
    etext 消息内容;  // 消息内容
    eint 气泡Id;  // 发送人气泡id
    eint 消息类型;  // 消息type
    eint 消息子类型;  // 消息subtype
    eint 消息子临时类型;  // 0 群 1 讨论组 129 腾讯公众号 201 QQ咨询
    eint 红包类型;  // 红包类型:  2已转入余额 4点击收款 10红包
    ebin 会话token;  // 会话Token
    elong 来源事件QQ;
    etext 来源事件QQ昵称;
    etext 文件Id;
    ebin 文件Md5;
    etext 文件名;
    elong 文件大小;
};

struct 服务信息
{
    eint 服务代号;
    eint 服务等级;
};

struct 好友信息
{
    etext 邮箱;
    elong 账号;
    etext 昵称;
    etext 备注;
    etext 在线状态;  // 只能使用[取好友列表]获取
    eint 赞数量;  // 只能使用[查询好友信息]获取
    etext 签名;  // 只能使用[查询好友信息]获取
    eint 性别;  // 255：隐藏，0：男，1：女，只能使用[查询好友信息]获取
    eint Q等级;  // 只能使用[查询好友信息]获取
    eint 年龄;  // 只能使用[查询好友信息]获取
    etext 国家;  // 只能使用[查询好友信息]获取
    etext 省份;  // 只能使用[查询好友信息]获取
    etext 城市;  // 只能使用[查询好友信息]获取
    服务信息* 服务列表;  // 只能使用[查询好友信息]获取
    eint 连续在线天数;  // 只能使用[查询好友信息]获取
    etext QQ达人;  // 只能使用[查询好友信息]获取
    eint 今日已赞;  // 只能使用[查询好友信息]获取
    eint 今日可赞数;  // 只能使用[查询好友信息]获取
};

struct 群信息
{
    elong 群ID;
    elong 群号;
    elong cFlag;
    elong dwGroupInfoSeq;
    elong dwGroupFlagExt;
    elong dwGroupRankSeq;
    elong dwCertificationType;
    elong dwShutupTimestamp;
    elong dwMyShutupTimestamp;
    elong dwCmdUinUinFlag;
    elong dwAdditionalFlag;
    elong dwGroupTypeFlag;
    elong dwGroupSecType;
    elong dwGroupSecTypeInfo;
    elong dwGroupClassExt;
    elong dwAppPrivilegeFlag;
    elong dwSubscriptionUin;
    elong 群成员数量;
    elong dwMemberNumSeq;
    elong dwMemberCardSeq;
    elong dwGroupFlagExt3;
    elong dwGroupOwnerUin;
    elong cIsConfGroup;
    elong cIsModifyConfGroupFace;
    elong cIsModifyConfGroupName;
    elong dwCmduinJoinTime;
    etext 群名称;
    etext strGroupMemo;
};

struct 群成员信息
{
    etext 账号;
    eint 年龄;
    eint 性别;
    etext 昵称;
    etext 邮箱;
    etext 名片;
    etext 备注;
    etext 头衔;
    etext 手机号;
    elong 头衔到期时间;
    elong 禁言时间戳;
    elong 加群时间;
    elong 发言时间;
    elong 群等级;
};

struct 群消息数据
{
    elong 发送人QQ;
    elong 框架QQ;
    eint 消息Req;
    eint 消息接收时间;
    elong 消息群号;
    etext 来源群名称;
    etext 发送人群名片;
    eint 消息发送时间;
    elong 消息Random;
    eint 消息分片序列;
    eint 消息分片数量;
    elong 消息分片标识;
    eint 消息类型;
    etext 发送人群头衔;
    etext 消息内容;
    etext 回复对象消息内容;
    eint 气泡Id;
    eint 发送人位置经度;
    eint 发送人位置纬度;
    etext 文件Id;
    ebin 文件Md5;
    etext 文件名;
    elong 文件大小;
    eint 消息appid;
};

struct 群卡片信息
{
    etext 群名称;
    etext 群地点;
    etext 群分类;
    etext 群标签;
    etext 群介绍;
};

struct 银行卡信息
{
    eint 序列;
    etext 尾号;
    etext 银行;
    etext 绑定手机;
    etext bind_serial;
    etext bank_type;
};

struct QQ钱包信息
{
    etext 余额;
    etext 身份证号;
    etext 实名;
    银行卡信息* 银行卡列表;
};

struct 订单详情
{
    etext 订单时间;
    etext 订单说明;
    etext 订单类名;
    etext 订单类型;
    etext 订单手续费;
    etext 操作人QQ;
    etext 操作人昵称;
    etext 接收人QQ;
    etext 接收人昵称;
    etext 操作金额;
};

struct 验证码信息
{
    etext token_id;
    etext skey;
    etext bank_type;
    etext mobile;
    etext business_type;
    eint random;
    etext transaction_id;
    etext purchaser_id;
    etext token;
    etext auth_params;
};

struct 事件消息数据
{
    elong 框架QQ;
    elong 来源群号;
    elong 操作QQ;
    elong 触发QQ;
    elong 消息Seq;
    eint 消息时间戳;
    etext 来源群名;
    etext 操作QQ昵称;
    etext 触发QQ昵称;
    etext 消息内容;
    eint 消息类型;
    eint 消息子类型;
};

template<typename FuncT>
FuncT _f(const json& api, const wstring& name)
{
    return (FuncT)((intptr_t)api[name]);
}

class API
{
public:
    /**
     * @brief 载入插件关键字和系统回调函数指针
     * @param _plugin_key 插件关键字
     * @param _apidata 系统回调函数指针JSON
     */
    void init(const etext& _plugin_key, const etext& _apidata)
    {
        this->plugin_key = e2w(_plugin_key);
        this->api = json::parse(e2w(_apidata));
    }

    /**
     * @brief 输出日志
     * @param message 日志
     * @param text_color 文字颜色
     * @param background_color 背景颜色
     */
    wstring OutputLog(const wstring& message, int32_t text_color = 32768,
        int32_t background_color = 16777215)
    {
        return e2w(_f
            <etext(*)(etext, etext, eint, eint)>
            (this->api, L"输出日志")
            (w2e(this->plugin_key), w2e(message), text_color, background_color));
    }

    /**
     * @brief 发送好友消息
     * @param thisQQ 框架QQ
     * @param friendQQ 好友QQ
     * @param content 发送内容
     * @param random 撤回消息用
     * @param req 撤回消息用
     * @return 成功返回的time用于撤回消息
     */
    wstring SendFriendMessage(int64_t thisQQ, int64_t friendQQ,
        const wstring& content, int64_t* random = nullptr, int32_t* req = nullptr)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, etext,
                elong, eint)>
            (this->api, L"发送好友消息")
            (w2e(this->plugin_key), thisQQ, friendQQ, w2e(content),
                random ? *random : 0, req ? *req : 0));
    }

    /**
     * @brief 发送群消息
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param content 发送内容
     * @param anonymous 匿名发送
     */
    wstring SendGroupMessage(int64_t thisQQ, int64_t groupQQ,
        const wstring& content, bool anonymous = false)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, etext, bool)>
            (this->api, L"发送群消息")
            (w2e(this->plugin_key), thisQQ, groupQQ, w2e(content),
                anonymous));
    }

    /**
     * @brief 发送群临时消息
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param otherQQ 对方QQ
     * @param content 发送内容
     * @param random 撤回消息用
     * @param req 撤回消息用
     * @return 成功返回的time用于撤回消息
     */
    wstring SendGroupTemporaryMessage(int64_t thisQQ, int64_t groupQQ,
        int64_t otherQQ, const wstring& content,
        int64_t* random = nullptr, int32_t* req = nullptr)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, elong, etext,
                elong**, eint**)>
            (this->api, L"发送群临时消息")
            (w2e(this->plugin_key), thisQQ, groupQQ, otherQQ, w2e(content),
                &random, &req));
    }

    /**
     * @brief 添加好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @param verification 设置回答问题答案或是验证消息，多个问题答案用"|"分隔开
     */
    wstring AddFriend(int64_t thisQQ, int64_t otherQQ,
        const wstring& verification)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, etext)>
            (this->api, L"添加好友")
            (w2e(this->plugin_key), thisQQ, otherQQ, w2e(verification)));
    }

    /**
     * @brief 添加群（你在群内或需要付费入群也会直接发送验证消息）
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param verification 回答问题答案或是验证消息
     */
    wstring AddFriend(int64_t thisQQ, int64_t groupQQ,
        const wstring& verification)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, etext)>
            (this->api, L"添加群")
            (w2e(this->plugin_key), thisQQ, groupQQ, w2e(verification)));
    }

    /**
     * @brief 删除好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     */
    wstring RemoveFriend(int64_t thisQQ, int64_t otherQQ)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong)>
            (this->api, L"添加群")
            (w2e(this->plugin_key), thisQQ, otherQQ));
    }

    /**
     * @brief 设置屏蔽好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @param is_blocked 是否屏蔽
     */
    wstring SetBlockFriend(int64_t thisQQ, int64_t otherQQ,
        bool is_blocked)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, ebool)>
            (this->api, L"置屏蔽好友")
            (w2e(this->plugin_key), thisQQ, otherQQ,
                b2e(is_blocked)));
    }

    /**
     * @brief 设置特别关心好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @param is_special 是否屏蔽
     */
    wstring SetSpecialFriend(int64_t thisQQ, int64_t otherQQ,
        bool is_special)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, ebool)>
            (this->api, L"置特别关心好友")
            (w2e(this->plugin_key), thisQQ, otherQQ,
                b2e(is_special)));
    }

    /**
     * @brief 发送好友JSON消息
     * @param thisQQ 框架QQ
     * @param friendQQ 好友QQ
     * @param json_content json发送内容
     * @param random 撤回消息用
     * @param req 撤回消息用
     * @return 成功返回的time用于撤回消息
     */
    wstring SendFriendJSONMessage(int64_t thisQQ, int64_t friendQQ,
        const wstring& json_content,
        int64_t* random = nullptr, int32_t* req = nullptr)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, etext,
                elong**, eint**)>
            (this->api, L"发送好友json消息")
            (w2e(this->plugin_key), thisQQ, friendQQ, w2e(json_content),
                &random, &req));
    }

    /**
     * @brief 发送群JSON消息
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param json_content json发送内容
     * @param anonymous 匿名发送
     */
    wstring SendGroupJSONMessage(int64_t thisQQ, int64_t groupQQ,
        const wstring& json_content, bool anonymous = false)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, etext, bool)>
            (this->api, L"发送群json消息")
            (w2e(this->plugin_key), thisQQ, groupQQ,
                w2e(json_content), anonymous));
    }

    /**
     * @brief 上传好友图片
     * @param thisQQ 框架QQ
     * @param friendQQ 好友QQ
     * @param picture 图片数据
     * @param is_flash 是否闪照
     * @return 成功返回图片代码
     */
    wstring UploadFriendImage(int64_t thisQQ, int64_t friendQQ,
        const vector<uint8_t>& picture, bool is_flash = false)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, ebool, ebin, eint)>
            (this->api, L"上传好友图片")
            (w2e(this->plugin_key), thisQQ, friendQQ, b2e(is_flash),
                picture.data(), static_cast<eint>(picture.size())));
    }

    /**
     * @brief 上传群图片
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param picture 图片数据
     * @param is_flash 是否闪照
     * @return 成功返回图片代码
     */
    wstring UploadGroupImage(int64_t thisQQ, int64_t groupQQ,
        const vector<uint8_t>& picture, bool is_flash = false)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, ebool, ebin, eint)>
            (this->api, L"上传群图片")
            (w2e(this->plugin_key), thisQQ, groupQQ, b2e(is_flash),
                picture.data(), static_cast<eint>(picture.size())));
    }

    /**
     * @brief 上传好友语音
     * @param thisQQ 框架QQ
     * @param friendQQ 好友QQ
     * @param audio 语音数据
     * @param audio_type 语音类型 0：普通语音，1：变声语音，2：文字语音，3：红包匹配语音
     * @param audio_text 语音文字 文字语音填附加文字(貌似会自动替换为语音对应的文本),匹配语音填a、b、s、ss、sss，注意是小写
     * @return 成功返回语音代码
     */
    wstring UploadFriendAudio(int64_t thisQQ, int64_t friendQQ, const vector<uint8_t>& audio,
        int32_t audio_type = 0, const wstring& audio_text = L"")
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, eint, etext, ebin, eint)>
            (this->api, L"上传好友语言")
            (w2e(this->plugin_key), thisQQ, friendQQ, audio_type, w2e(audio_text),
                audio.data(), static_cast<eint>(audio.size())));
    }

    /**
     * @brief 上传群语音
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param audio 语音数据
     * @param audio_type 语音类型 0：普通语音，1：变声语音，2：文字语音，3：红包匹配语音
     * @param audio_text 语音文字 文字语音填附加文字(貌似会自动替换为语音对应的文本),匹配语音填a、b、s、ss、sss，注意是小写
     * @return 成功返回语音代码
     */
    wstring UploadGroupAudio(int64_t thisQQ, int64_t groupQQ, const vector<uint8_t>& audio,
        int32_t audio_type = 0, const wstring& audio_text = L"")
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, eint, etext, ebin, eint)>
            (this->api, L"上传群语音")
            (w2e(this->plugin_key), thisQQ, groupQQ, audio_type, w2e(audio_text),
                audio.data(), static_cast<eint>(audio.size())));
    }

    /**
     * @brief 上传头像
     * @param thisQQ 框架QQ
     * @param picture 图片数据
     */
    wstring UploadAvatar(int64_t thisQQ, const vector<uint8_t>& picture)
    {
        return e2w(_f
            <etext(*)(etext, elong, ebin, eint)>
            (this->api, L"上传头像")
            (w2e(this->plugin_key), thisQQ, picture.data(),
                static_cast<eint>(picture.size())));
    }

    /* TODO

    .子程序 silk解码, 字节集, 公开, 无权限要求
    .参数 音频文件路径, 文本型, , 注意文件后缀必须和文件格式相对应

    .局部变量 name, 文本型, , ,
    .局部变量 bin, 字节集, , ,

    .判断开始 (并且 (文件是否存在 (相加 (取运行目录 (), “\main\corn\ffmpeg.exe”)), 文件是否存在 (相加 (取运行目录 (), “\main\corn\silkdecode.exe”)), 文件是否存在 (相加 (取运行目录 (), “\main\corn\silkencode.exe”))))
        .判断开始 (文件是否存在 (音频文件路径))
            赋值 (name, 相加 (到文本 (取随机数 (1000, 999999)), 取文本右边 (音频文件路径, 相减 (取文本长度 (音频文件路径), 倒找文本 (音频文件路径, “\”, , 假)))))
            .如果真 (取反 (文件是否存在 (相加 (取运行目录 (), “\main\data\voice”))))
                创建目录 (相加 (取运行目录 (), “\main\data\voice”))
            .如果真结束
            赋值 (name, 相加 (取运行目录 (), “\main\data\voice\”, name))
            赋值 (name, 取文本左边 (name, 相减 (倒找文本 (name, “.”, , 假), 1)))
            赋值 (bin, 读入文件 (音频文件路径))
            .判断开始 (等于 (取字节集左边 (bin, 5), 到字节集 (“#!AMR”)))
                运行 (相加 (“main\corn\ffmpeg -i ”, #引号, 音频文件路径, #引号, “ ”, #引号, name, “.mp3”, #引号), 真, #隐藏窗口)
            .默认
                运行 (相加 (“main\corn\silkdecode ”, #引号, 音频文件路径, #引号, “ ”, #引号, name, “.pcm”, #引号), 真, #隐藏窗口)
                运行 (相加 (“main\corn\ffmpeg -f s16le -ar 24000 -ac 1 -i ”, #引号, name, “.pcm”, #引号, “ ”, #引号, name, “.mp3”, #引号), 真, )
            .判断结束
            赋值 (bin, 读入文件 (相加 (name, “.mp3”)))
            删除文件 (相加 (name, “.mp3”))
            删除文件 (相加 (name, “.pcm”))
            输出日志 (“silk解码->解码完成”)
            返回 (bin)
        .默认
            输出日志 (“silk解码->音频文件不存在”)
            返回 ({  })
        .判断结束

    .默认
        输出日志 (“silk解码->corn文件夹缺少语音转码库，请自行到官网或交流群下载”)
        返回 ({  })
    .判断结束


    .子程序 silk编码, 字节集, 公开, 无权限要求
    .参数 音频文件路径, 文本型, , 注意文件后缀必须和文件格式相对应

    .局部变量 name, 文本型, , ,
    .局部变量 ret, 字节集, , ,

    .判断开始 (并且 (文件是否存在 (相加 (取运行目录 (), “\main\corn\ffmpeg.exe”)), 文件是否存在 (相加 (取运行目录 (), “\main\corn\silkdecode.exe”)), 文件是否存在 (相加 (取运行目录 (), “\main\corn\silkencode.exe”))))
        .判断开始 (文件是否存在 (音频文件路径))
            赋值 (name, 相加 (到文本 (取随机数 (1000, 999999)), 取文本右边 (音频文件路径, 相减 (取文本长度 (音频文件路径), 倒找文本 (音频文件路径, “\”, , 假)))))
            .如果真 (取反 (文件是否存在 (相加 (取运行目录 (), “\main\data\voice\”))))
                创建目录 (相加 (取运行目录 (), “\main\data\voice\”))
            .如果真结束
            赋值 (name, 相加 (取运行目录 (), “\main\data\voice\”, name))
            赋值 (name, 取文本左边 (name, 相减 (倒找文本 (name, “.”, , 假), 1)))
            运行 (相加 (“main\corn\ffmpeg -y -i ”, #引号, 音频文件路径, #引号, “ -f s16le -ar 24000 -ac 1 ”, #引号, name, “.pcm”, #引号), 真, #隐藏窗口)
            运行 (相加 (“main\corn\silkencode ”, #引号, name, “.pcm”, #引号, “ ”, #引号, name, “.silk”, #引号, “ -tencent”), 真, #隐藏窗口)
            赋值 (ret, 读入文件 (相加 (name, “.silk”)))
            删除文件 (相加 (name, “.pcm”))
            删除文件 (相加 (name, “.silk”))
            输出日志 (“silk编码->编码完成”)
            返回 (ret)
        .默认
            输出日志 (“silk解码->音频文件不存在”)
            返回 ({  })
        .判断结束

    .默认
        输出日志 (“silk解码->corn文件夹缺少语音转码库，请自行到官网或交流群下载”)
        返回 ({  })
    .判断结束

    */

    /**
     * @brief 设置群名片
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param otherQQ 对方QQ
     * @param nickname 群名片
     */
    wstring SetGroupMemberNickname(int64_t thisQQ, int64_t groupQQ,
        int64_t otherQQ, const wstring& nickname)
    {
        return e2w(_f
            <etext(*)(etext, elong, elong, elong, etext)>
            (this->api, L"设置群名片")
            (w2e(this->plugin_key), thisQQ, groupQQ, otherQQ,
                w2e(nickname)));
    }

    /**
     * @brief 从缓存获取昵称
     * @param otherQQ 对方QQ
     * @return 成功返回昵称
     */
    wstring GetNameFromCache(int64_t otherQQ)
    {
        return e2w(_f
            <etext(*)(etext, elong)>
            (this->api, L"取昵称_从缓存")
            (w2e(this->plugin_key), otherQQ));
    }

    /**
     * @brief 强制获取昵称
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @return 成功返回昵称
     */
    wstring GetNameForce(int64_t thisQQ, const wstring& otherQQ)
    {
        return e2w(_f
            <etext(*)(etext, elong, etext)>
            (this->api, L"取群名称_从缓存")
            (w2e(this->plugin_key), thisQQ, w2e(otherQQ)));
    }

    /**
     * @brief 从缓存获取群名称（即使是框架QQ没加的群，调用[查询群信息]后也会记录缓存）
     * @param groupQQ 群号
     * @return 成功返回群名称
     */
    wstring GetGroupNameFromCache(int64_t groupQQ)
    {
        return e2w(_f
            <etext(*)(etext, elong)>
            (this->api, L"取昵称_从缓存")
            (w2e(this->plugin_key), groupQQ));
    }

    /**
     * @brief 获取skey
     * @param thisQQ 框架QQ
     * @return 成功返回skey
     */
    wstring GetSKey(int64_t thisQQ)
    {
        return e2w(_f
            <etext(*)(etext, elong)>
            (this->api, L"获取skey")
            (w2e(this->plugin_key), thisQQ));
    }

    /**
     * @brief 获取pskey
     * @param thisQQ 框架QQ
     * @param domain 域 tenpay.com;openmobile.qq.com;docs.qq.com;connect.qq.com;qzone.qq.com;vip.qq.com;gamecenter.qq.com;qun.qq.com;game.qq.com;qqweb.qq.com;ti.qq.com;office.qq.com;mail.qq.com;mma.qq.com
     * @return 成功返回pskey
     */
    wstring GetPSKey(int64_t thisQQ, const wstring& domain)
    {
        return e2w(_f
            <etext(*)(etext, elong, etext)>
            (this->api, L"获取pskey")
            (w2e(this->plugin_key), thisQQ, w2e(domain)));
    }

    /**
     * @brief 获取clientkey
     * @param thisQQ 框架QQ
     * @return 成功返回clientkey
     */
    wstring GetClientKey(int64_t thisQQ)
    {
        return e2w(_f
            <etext(*)(etext, elong)>
            (this->api, L"获取clientkey")
            (w2e(this->plugin_key), thisQQ));
    }

    /**
     * @brief 获取框架QQ
     */
    wstring GetClientKey()
    {
        return e2w(_f
            <etext(*)(etext)>
            (this->api, L"取框架QQ")
            (w2e(this->plugin_key)));
    }

private:
    wstring plugin_key;
    json api;
};

/* TODO

.子程序 取好友列表, 整数型, 公开, 失败或无权限返回数量0
.参数 框架QQ, 长整数型, ,
.参数 数据, 好友信息, 参考 数组,

.局部变量 ret, 整数型, , ,

清除数组 (数据)
调用子程序 (到整数 (j.取长整数 (“取好友列表”)), , ret, pluginkey, 框架QQ, 取变量地址 (数据))
返回 (ret)

.子程序 取群列表, 整数型, 公开, 失败或无权限返回数量0
.参数 框架QQ, 长整数型, ,
.参数 数据, 群信息, 参考 数组,

.局部变量 ret, 整数型, , ,

清除数组 (数据)
调用子程序 (到整数 (j.取长整数 (“取群列表”)), , ret, pluginkey, 框架QQ, 取变量地址 (数据))
返回 (ret)

.子程序 取群成员列表, 整数型, 公开, 失败或无权限返回数量0
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 数据, 群成员信息, 参考 数组,

.局部变量 ret, 整数型, , ,

清除数组 (数据)
调用子程序 (到整数 (j.取长整数 (“取群成员列表”)), , ret, pluginkey, 框架QQ, 群号, 取变量地址 (数据))
返回 (ret)

.子程序 设置管理员, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 群成员QQ, 长整数型, ,
.参数 取消管理, 逻辑型, , 取消或设置

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“设置管理员”)), , ret, pluginkey, 框架QQ, 群号, 群成员QQ, 取消管理)
返回 (ret)


.子程序 取管理层列表, 文本型, 公开, 包括群主
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“取管理层列表”)), , ret, pluginkey, 框架QQ, 群号)
返回 (ret)

.子程序 取群名片, 文本型, 公开, 成功返回群名片，注意，如果群成员的群名片未设置或群名片为空白，返回结果均为空
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 群成员QQ, 长整数型, ,

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“取群名片”)), , ret, pluginkey, 框架QQ, 群号, 群成员QQ)
返回 (ret)

.子程序 取个性签名, 文本型, 公开, 成功返回个性签名
.参数 框架QQ, 长整数型, ,
.参数 对方QQ, 长整数型, , 可以填框架QQ本身

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“取个性签名”)), , ret, pluginkey, 框架QQ, 对方QQ)
返回 (ret)


.子程序 修改昵称, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 昵称, 文本型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“修改昵称”)), , ret, pluginkey, 框架QQ, 昵称)
返回 (ret)


.子程序 修改个性签名, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 签名, 文本型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“修改个性签名”)), , ret, pluginkey, 框架QQ, 签名)
返回 (ret)


.子程序 删除群成员, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 群成员QQ, 长整数型, ,
.参数 拒绝加群申请, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“删除群成员”)), , ret, pluginkey, 框架QQ, 群号, 群成员QQ, 拒绝加群申请)
返回 (ret)


.子程序 禁言群成员, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 群成员QQ, 长整数型, ,
.参数 禁言时长, 整数型, , 单位：秒

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“禁言群成员”)), , ret, pluginkey, 框架QQ, 群号, 群成员QQ, 禁言时长)
返回 (ret)


.子程序 退群, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“退群”)), , ret, pluginkey, 框架QQ, 群号)
返回 (ret)

.子程序 解散群, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“解散群”)), , ret, pluginkey, 框架QQ, 群号)
返回 (ret)

.子程序 上传群头像, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 pic, 字节集, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“上传群头像”)), , ret, pluginkey, 框架QQ, 群号, 取变量数据地址 (pic), 取字节集长度 (pic))
返回 (ret)


.子程序 全员禁言, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否开启, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“全员禁言”)), , ret, pluginkey, 框架QQ, 群号, 是否开启)
返回 (ret)


.子程序 群权限_发起新的群聊, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否允许, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_发起新的群聊”)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_发起临时会话, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否允许, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_发起临时会话”)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_上传文件, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否允许, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_上传文件”)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_上传相册, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否允许, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_上传相册”)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_邀请好友加群, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否允许, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_邀请好友加群”)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_匿名聊天, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否允许, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_匿名聊天”)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_坦白说, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否允许, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_坦白说”)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_新成员查看历史消息, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 是否允许, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_新成员查看历史消息”)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_邀请方式设置, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 方式, 整数型, , 1 无需审核;2 需要管理员审核;3 100人以内无需审核

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群权限_邀请方式设置”)), , ret, pluginkey, 框架QQ, 群号, 方式)
返回 (ret)


.子程序 撤回消息_群聊, 逻辑型, 公开, 在群消息事件中使用，能收到并撤回自己发的消息，失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 fromRandom, 长整数型, ,
.参数 fromReq, 整数型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“撤回消息_群聊”)), , ret, pluginkey, 框架QQ, 群号, fromRandom, fromReq)
返回 (ret)

.子程序 撤回消息_私聊本身, 逻辑型, 公开, 用于撤回自己发的消息，其他设备的个人消息通知也可以撤回
.参数 框架QQ, 长整数型, ,
.参数 对方QQ, 长整数型, ,
.参数 fromRandom, 长整数型, ,
.参数 fromReq, 整数型, ,
.参数 time, 整数型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“撤回消息_私聊本身”)), , ret, pluginkey, 框架QQ, 对方QQ, fromRandom, fromReq, time)
返回 (ret)

.子程序 设置位置共享, 逻辑型, 公开, 开启后需要上报位置，大约3s上报一次，否则会自动关闭，失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 经度, 双精度小数型, , 如：121.711540
.参数 纬度, 双精度小数型, , 如：31.403343
.参数 是否开启, 逻辑型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“设置位置共享”)), , ret, pluginkey, 框架QQ, 群号, 经度, 纬度, 是否开启)
返回 (ret)

.子程序 上报当前位置, 逻辑型, 公开, 大约3s上报一次，不得过快，失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 经度, 双精度小数型, , 如：121.711540
.参数 纬度, 双精度小数型, , 如：31.403343

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“上报当前位置”)), , ret, pluginkey, 框架QQ, 群号, 经度, 纬度)
返回 (ret)

.子程序 是否被禁言, 长整数型, 公开, 返回禁言时长，单位秒，[失败/无权限/未被禁言]返回0
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,

.局部变量 ret, 长整数型, , ,

调用子程序 (到整数 (j.取长整数 (“是否被禁言”)), , ret, pluginkey, 框架QQ, 群号)
返回 (ret)

.子程序 处理群验证事件, , 公开, 在群验证事件下使用，无权限时不执行
.参数 my_uin, 长整数型, ,
.参数 fromGroup, 长整数型, ,
.参数 fromUin, 长整数型, ,
.参数 fromSeq, 长整数型, ,
.参数 op, 整数型, , 11同意 12拒绝  14忽略
.参数 fromType, 整数型, , #群事件_某人申请加群/#群事件_我被邀请加入群

调用子程序 (到整数 (j.取长整数 (“处理群验证事件”)), , , pluginkey, my_uin, fromGroup, fromUin, fromSeq, op, fromType)

.子程序 处理好友验证事件, , 公开, 在好友验证事件下使用，无权限时不执行
.参数 my_uin, 长整数型, ,
.参数 fromUin, 长整数型, ,
.参数 fromSeq, 长整数型, ,
.参数 op, 整数型, , 1同意 2拒绝

调用子程序 (到整数 (j.取长整数 (“处理好友验证事件”)), , , pluginkey, my_uin, fromUin, fromSeq, op)


.子程序 查看转发聊天记录内容, , 公开, 私聊消息也可以使用此命令解析，无权限时不执行
.参数 框架QQ, 长整数型, ,
.参数 resId, 长整数型, , 可在xml消息代码中取到
.参数 消息内容, 群消息数据, 参考 数组, 私聊消息也可从该结构取信息

调用子程序 (到整数 (j.取长整数 (“查看转发聊天记录内容”)), , , pluginkey, 框架QQ, resId, 取变量地址 (消息内容))

.子程序 上传群文件, , 公开, 本命令为耗时操作，请另开线程执行，本命令不支持上百mb的文件，无权限时不执行
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 文件路径, 文本型, , 本地文件路径
.参数 文件夹, 文本型, 可空, 该空保留，暂时无效

调用子程序 (到整数 (j.取长整数 (“上传群文件”)), , , pluginkey, 框架QQ, 群号, 文件路径, 文件夹)

.子程序 创建群文件夹, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 文件夹名, 文本型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“创建群文件夹”)), , ret, pluginkey, 框架QQ, 群号, 文件夹名)
返回 (ret)

.子程序 设置在线状态, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 main, 整数型, , 11在线 31离开 41隐身 50忙碌 60Q我吧 70请勿打扰
.参数 sun, 整数型, 可空, 当main=11时，可进一步设置 0普通在线 1000我的电量 1011信号弱 1024在线学习 1025在家旅游 1027TiMi中 1016睡觉中 1017游戏中 1018学习中 1019吃饭中 1021煲剧中 1022度假中 1032熬夜中
.参数 电量, 整数型, 可空, sun=1000时，可以设置上报电量，取值1到100

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“设置在线状态”)), , ret, pluginkey, 框架QQ, main, sun, 电量)
返回 (ret)


.子程序 api是否有权限, 逻辑型, 公开, 判断某api是否有权限
.参数 权限, 整数型, , #权限_

.局部变量 ret, 逻辑型, , ,
.局部变量 name, 文本型, , ,

.判断开始 (apilist.是否存在 (相加 (“API[”, 到文本 (权限), “]”)))
    赋值 (name, apilist.取文本 (相加 (“API[”, 到文本 (权限), “]”)))
    调用子程序 (到整数 (j.取长整数 (“api是否有权限”)), , ret, pluginkey, name)
.默认
    赋值 (ret, 假)
.判断结束
返回 (ret)

.子程序 重载自身, , 公开, 没有权限限制，请勿将新的插件文件下载至plugin文件夹，请确保新旧文件appname一致
.参数 新文件路径, 文本型, 可空, 若要更新插件，可将插件文件下载后在此填写新文件路径

调用子程序 (到整数 (j.取长整数 (“重载自身”)), , , pluginkey, 新文件路径)

.子程序 取插件数据目录, 文本型, 公开, 没有权限限制，建议将设置文件之类的都写这里面，结果结尾带\
.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“取插件数据目录”)), , ret, pluginkey)
返回 (ret)

.子程序 QQ点赞, 文本型, 公开, 注意，非好友情况下进行点赞时返回成功，但不一定真正点上了
.参数 框架QQ, 长整数型, ,
.参数 对方QQ, 长整数型, ,

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“QQ点赞”)), , ret, pluginkey, 框架QQ, 对方QQ)
返回 (ret)

.子程序 取图片下载地址, 文本型, 公开,
.参数 图片代码, 文本型, , 支持群聊、私聊的图片、闪照代码，注意是图片代码
.参数 框架QQ, 长整数型, 可空, 群聊图片必填，私聊图片必空
.参数 群号, 长整数型, 可空, 群聊图片必填，私聊图片必空

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“取图片下载地址”)), , ret, pluginkey, 图片代码, 框架QQ, 群号)
返回 (ret)

.子程序 查询好友信息, 逻辑型, 公开, 支持陌生人查询
.参数 框架QQ, 长整数型, ,
.参数 对方QQ, 长整数型, ,
.参数 数据, 好友信息, 参考,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“查询好友信息”)), , ret, pluginkey, 框架QQ, 对方QQ, 取变量地址 (数据))
返回 (ret)

.子程序 查询群信息, 逻辑型, 公开,
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 数据, 群卡片信息, 参考,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“查询群信息”)), , ret, pluginkey, 框架QQ, 群号, 取变量地址 (数据))
返回 (ret)

.子程序 框架重启, , 公开, 有权限限制，建议使用前检查是否具有权限
调用子程序 (到整数 (j.取长整数 (“框架重启”)), , , pluginkey)

.子程序 群文件转发至群, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 来源群号, 长整数型, ,
.参数 目标群号, 长整数型, ,
.参数 fileId, 文本型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群文件转发至群”)), , ret, pluginkey, 框架QQ, 来源群号, 目标群号, fileId)
返回 (ret)

.子程序 群文件转发至好友, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 来源群号, 长整数型, ,
.参数 目标QQ, 长整数型, ,
.参数 fileId, 文本型, ,
.参数 filename, 文本型, ,
.参数 Req, 整数型, 参考 可空, 撤回消息用
.参数 Random, 长整数型, 参考 可空, 撤回消息用
.参数 time, 整数型, 参考 可空, 撤回消息用

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“群文件转发至好友”)), , ret, pluginkey, 框架QQ, 来源群号, 目标QQ, fileId, filename, Req, Random, time)
返回 (ret)

.子程序 好友文件转发至好友, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 来源QQ, 长整数型, ,
.参数 目标QQ, 长整数型, ,
.参数 fileId, 文本型, ,
.参数 filename, 文本型, ,
.参数 Req, 整数型, 参考 可空, 撤回消息用
.参数 Random, 整数型, 参考 可空, 撤回消息用
.参数 time, 整数型, 参考 可空, 撤回消息用

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“好友文件转发至好友”)), , ret, pluginkey, 框架QQ, 来源QQ, 目标QQ, fileId, filename, Req, Random, time)
返回 (ret)

.子程序 置群消息接收, 逻辑型, 公开, 失败或无权限返回假，此API未对返回结果进行分析，返回真不一定成功
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 设置类型, 整数型, , 1接收并提醒 2收进群助手 3屏蔽群消息 4接收不提醒

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“置群消息接收”)), , ret, pluginkey, 框架QQ, 群号, 设置类型)
返回 (ret)

.子程序 发送免费礼物, 文本型, 公开, 绕过广告发送免费礼物
.参数 框架QQ, 长整数型, ,
.参数 群号, 长整数型, ,
.参数 对方QQ, 长整数型, ,
.参数 packageID, 整数型, , 299卡布奇诺;302猫咪手表;280牵你的手;281可爱猫咪;284神秘面具;285甜wink;286我超忙的;289快乐肥宅水;290幸运手链;313坚强;307绒绒手套; 312爱心口罩;308彩虹糖果

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“发送免费礼物”)), , ret, pluginkey, 框架QQ, 群号, 对方QQ, packageID)
返回 (ret)

.子程序 取好友在线状态, 文本型, 公开, 失败或无权限返回空，支持查询陌生人
.参数 框架QQ, 长整数型, ,
.参数 对方QQ, 长整数型, ,

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“取好友在线状态”)), , ret, pluginkey, 框架QQ, 对方QQ)
返回 (ret)

.子程序 取QQ钱包个人信息, 文本型, 公开, 包括余额、名字、银行卡等
.参数 框架QQ, 长整数型, ,
.参数 数据, QQ钱包信息, 参考, 取银行卡信息时注意不要数组越界

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“取QQ钱包个人信息”)), , ret, pluginkey, 框架QQ, 取变量地址 (数据))
返回 (ret)

.子程序 获取订单详情, 文本型, 公开, 可以查订单，比如别人给你转账，你可以查询转账的详情
.参数 框架QQ, 长整数型, ,
.参数 订单号, 文本型, , 或者称之为listid
.参数 数据, 订单详情, 参考,

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“获取订单详情”)), , ret, pluginkey, 框架QQ, 订单号, 取变量地址 (数据))
返回 (ret)


.子程序 提交支付验证码, 文本型, 公开, 用银行卡支付时需要验证，只需要验证一次
.参数 框架QQ, 长整数型, ,
.参数 验证码信息, 验证码信息, , 银行卡发红包时传回的
.参数 验证码, 文本型, , 手机收到的短信验证码
.参数 支付密码, 文本型, , 用于验证并支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“提交支付验证码”)), , ret, pluginkey, 框架QQ, 取变量地址 (验证码信息), 验证码, 支付密码)
返回 (ret)

.子程序 分享音乐, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, ,
.参数 分享对象, 长整数型, , 分享的群或分享的好友QQ
.参数 歌曲名, 文本型, ,
.参数 歌手名, 文本型, ,
.参数 跳转地址, 文本型, , 点击音乐json后跳转的地址
.参数 封面地址, 文本型, , 音乐的封面图片地址
.参数 文件地址, 文本型, , 音乐源文件地址，如https://xxx.com/xxx.mp3
.参数 应用类型, 整数型, 可空, 0QQ音乐 1虾米音乐 2酷我音乐 3酷狗音乐 4网易云音乐  默认0
.参数 分享类型, 整数型, 可空, 0私聊 1群聊  默认0

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“分享音乐”)), , ret, pluginkey, 框架QQ, 分享对象, 歌曲名, 歌手名, 跳转地址, 封面地址, 文件地址, 应用类型, 分享类型)
返回 (ret)

.子程序 更改群聊消息内容, 逻辑型, 公开, 使用此命令可以更改当前群聊消息内容，并使更改后的内容投递给之后的插件，无权限返回假
.参数 数据指针, 整数型, ,
.参数 新消息内容, 文本型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“更改群聊消息内容”)), , ret, pluginkey, 数据指针, 新消息内容)
返回 (ret)

.子程序 更改私聊消息内容, 逻辑型, 公开, 使用此命令可以更改当前私聊消息内容，并使更改后的内容投递给之后的插件，无权限返回假
.参数 数据指针, 整数型, ,
.参数 新消息内容, 文本型, ,

.局部变量 ret, 逻辑型, , ,

调用子程序 (到整数 (j.取长整数 (“更改私聊消息内容”)), , ret, pluginkey, 数据指针, 新消息内容)
返回 (ret)

.子程序 群聊口令红包, 文本型, 公开,
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 群号, 长整数型, ,
.参数 口令, 文本型, ,
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“群聊口令红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 口令, 支付密码, 银行卡序列)
返回 (ret)

.子程序 群聊拼手气红包, 文本型, 公开,
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 群号, 长整数型, ,
.参数 祝福语, 文本型, ,
.参数 红包皮肤Id, 整数型, 可空, 1522光与夜之恋,1527代号:三国(打了一辈子仗),1525街霸:对决,1518代号:三国(俺送红包来了),1476天涯明月刀,1512一人之下。其他皮肤id自己找
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“群聊拼手气红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 祝福语, 红包皮肤Id, 支付密码, 银行卡序列)
返回 (ret)

.子程序 群聊普通红包, 文本型, 公开,
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 群号, 长整数型, ,
.参数 祝福语, 文本型, ,
.参数 红包皮肤Id, 整数型, 可空, 1522光与夜之恋,1527代号:三国(打了一辈子仗),1525街霸:对决,1518代号:三国(俺送红包来了),1476天涯明月刀,1512一人之下。其他皮肤id自己找
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“群聊普通红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 祝福语, 红包皮肤Id, 支付密码, 银行卡序列)
返回 (ret)


.子程序 群聊画图红包, 文本型, 公开,
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 群号, 长整数型, ,
.参数 题目名, 文本型, , 只能填手Q有的，如：庄周
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“群聊画图红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 题目名, 支付密码, 银行卡序列)
返回 (ret)


.子程序 群聊语音红包, 文本型, 公开,
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 群号, 长整数型, ,
.参数 语音口令, 文本型, ,
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“群聊语音红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 语音口令, 支付密码, 银行卡序列)
返回 (ret)


.子程序 群聊接龙红包, 文本型, 公开,
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 群号, 长整数型, ,
.参数 接龙内容, 文本型, ,
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“群聊接龙红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 接龙内容, 支付密码, 银行卡序列)
返回 (ret)


.子程序 群聊专属红包, 文本型, 公开,
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 群号, 长整数型, ,
.参数 领取人, 文本型, , 多个领取人QQ用|分隔
.参数 祝福语, 文本型, ,
.参数 是否均分, 逻辑型, 可空, 默认不均分(拼手气),均分时每个领取人领取金额相同
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“群聊专属红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 领取人, 祝福语, 是否均分, 支付密码, 银行卡序列)
返回 (ret)


.子程序 好友口令红包, 文本型, 公开, 不支持非好友！
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 对方QQ, 长整数型, ,
.参数 口令, 文本型, ,
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“好友口令红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 口令, 支付密码, 银行卡序列)
返回 (ret)


.子程序 好友普通红包, 文本型, 公开, 不支持非好友！
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 对方QQ, 长整数型, ,
.参数 祝福语, 文本型, ,
.参数 红包皮肤Id, 整数型, 可空, 1522光与夜之恋,1527代号:三国(打了一辈子仗),1525街霸:对决,1518代号:三国(俺送红包来了),1476天涯明月刀,1512一人之下。其他皮肤id自己找
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“好友普通红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 祝福语, 红包皮肤Id, 支付密码, 银行卡序列)
返回 (ret)


.子程序 好友画图红包, 文本型, 公开, 不支持非好友！
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 对方QQ, 长整数型, ,
.参数 题目名, 文本型, , 只能填手Q有的，如：庄周
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“好友画图红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 题目名, 支付密码, 银行卡序列)
返回 (ret)


.子程序 好友语音红包, 文本型, 公开, 不支持非好友！
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 对方QQ, 长整数型, ,
.参数 语音口令, 文本型, ,
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“好友语音红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 语音口令, 支付密码, 银行卡序列)
返回 (ret)


.子程序 好友接龙红包, 文本型, 公开, 不支持非好友！
.参数 框架QQ, 长整数型, ,
.参数 总数量, 整数型, ,
.参数 总金额, 整数型, , 单位分
.参数 对方QQ, 长整数型, ,
.参数 接龙内容, 文本型, ,
.参数 支付密码, 文本型, ,
.参数 银行卡序列, 整数型, 可空, 大于0时使用银行卡支付

.局部变量 ret, 文本型, , ,

调用子程序 (到整数 (j.取长整数 (“好友接龙红包”)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 接龙内容, 支付密码, 银行卡序列)
返回 (ret)

*/

#endif  // XSDK_INCLUDE_XSDK_HPP_
