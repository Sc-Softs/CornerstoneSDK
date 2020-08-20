/*
Cornerstone SDK v0.2.0
-- 面向现代 C++ 的 Corn SDK
兼容 Corn SDK v2.6.5
https://github.com/Sc-Softs/CornerstoneSDK

使用 MIT License 进行许可
SPDX-License-Identifier: MIT
Copyright © 2020 Contributors of Cornerstone SDK

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef CORNERSTONE_HEADER_TYPES_H_
#define CORNERSTONE_HEADER_TYPES_H_

#include "../sdk.h"
#include "utils-inl.h"

#include <string>
#include <unordered_map>

// 易语言类型
using ebyte = std::uint8_t;        // 易语言字节型
using eshort = std::int16_t;       // 易语言短整数型
using eint = std::int32_t;         // 易语言整数型
using elong = std::int64_t;        // 易语言长整数型
using efloat = float;              // 易语言小数型
using edouble = double;            // 易语言双精度小数型
using edate = std::uint64_t;       // 易语言日期时间型
using ebool = std::int32_t;        // 易语言逻辑型
using etext = const char *;        // 易语言文本型(GBK)
using ebin = const std::uint8_t *; // 易语言字节集
using esubptr = std::uintptr_t;    // 易语言子程序指针

class earray // 易语言数组
{
public:
    earray() noexcept;
    ~earray() noexcept;
    size_t GetDimension() const noexcept;

    void *data;

private:
    HANDLE heap;
};

template <class EType, class CType>
class earray1D // 易语言一维数组
    : public earray
{
public:
    size_t GetSize() const noexcept
    {
        return ((eint *)this->data)[1];
    }

    size_t Unpack(std::vector<CType> &array) const noexcept
    {
        if (this->GetDimension() != 1)
        {
            return -1;
        }
        auto size = this->GetSize();
        if constexpr (std::is_compound_v<EType>)
        {
            volatile EType **data = (volatile EType **)(((eint *)this->data) + 2);
            array.clear();
            for (decltype(size) i = 0; i < size; i++)
            {
                array.push_back((CType)*(const_cast<EType *>(*data)));  
                data++;
            }
        }
        else
        {
            EType *data = (EType *)(((eint *)this->data) + 2);
            array.clear();
            for (auto i = 0; i < size; i++)
            {
                array.push_back(*data);
                data++;
            }
        }
        return size;
    }
};

// 易语言常量
constexpr ebool etrue = 1;
constexpr ebool efalse = 0;

// 易语言类型转换
constexpr ebool bool2ebool(const bool &b)
{
    return b ? etrue : efalse;
}

constexpr bool ebool2bool(const ebool &e)
{
    return e == etrue;
}

constexpr ebool b2e(const bool &b)
{
    return bool2ebool(b);
}

constexpr bool e2b(const ebool &e)
{
    return ebool2bool(e);
}

std::string GBKtoUTF8(const char *gbk);
std::string UTF8toGBK(const std::string &utf8);
#define e2s_s(src_str) GBKtoUTF8(src_str)
#define s2e_s(src_str) UTF8toGBK(src_str)
#define e2s(src_str) e2s_s(src_str).c_str()
#define s2e(src_str) s2e_s(src_str).c_str()

// WARNING: 使用完后请自行delete字符串指针，否则将造成内存泄露
inline const char* new_and_copy_str(const char* str)
{
    size_t size = std::strlen(str);
    char* newStr = new char[size + 1];
    std::strcpy(newStr, str);
    newStr[size] = '\0';
    return newStr;
}

//region 枚举常量
//=============

// 事件处理
enum class EventProcessEnum : eint
{
    // 阻止其他插件继续处理此事件
    Block = 1,
    // 允许其他插件继续处理此事件
    Ignore = 0
};

// 消息类型
enum class MessageTypeEnum : eint
{
    // 临时会话
    Temporary = 141,
    // 好友通常消息
    FriendUsualMessage = 166,
    // 好友文件
    FriendFile = 529,
    // 好友语音
    FriendAudio = 208,
    // 群红包
    GroupRedEnvelope = 78,
    // 群聊通常消息
    GroupUsualMessage = 134
};
// 消息子类型
enum class MessageSubTypeEnum : eint
{
    // 临时会话_群
    Temporary_Group = 0,
    // 临时会话_公众号
    Temporary_PublicAccount = 129,
    // 临时会话_网页QQ咨询
    Temporary_WebQQConsultation = 201,
};

// 事件类型
enum class EventTypeEnum : eint
{
    // 好友事件_被好友删除
    Friend_Removed = 15,
    // 好友事件_签名变更
    Friend_SignatureChanged = 16,
    // 好友事件_昵称改变
    Friend_NameChanged = 17,
    // 好友事件_某人撤回事件
    Friend_UserUndid = 18,
    // 好友事件_有新好友
    Friend_NewFriend = 19,
    // 好友事件_好友请求
    Friend_FriendRequest = 20,
    // 好友事件_对方同意了您的好友请求
    Friend_FriendRequestAccepted = 21,
    // 好友事件_对方拒绝了您的好友请求
    Friend_FriendRequestRefused = 22,
    // 好友事件_资料卡点赞
    Friend_InformationLiked = 23,
    // 好友事件_签名点赞
    Friend_SignatureLiked = 24,
    // 好友事件_签名回复
    Friend_SignatureReplied = 25,
    // 好友事件_个性标签点赞
    Friend_TagLiked = 26,
    // 好友事件_随心贴回复
    Friend_StickerLiked = 27,
    // 好友事件_随心贴增添
    Friend_StickerAdded = 28,

    // 空间事件_与我相关
    QZone_Related = 30,

    // 框架事件_登录成功
    This_SignInSuccess = 32,

    // 群事件_我被邀请加入群
    Group_Invited = 1,
    // 群事件_某人加入了群
    Group_MemberJoined = 2,
    // 群事件_某人申请加群
    Group_MemberVerifying = 3,
    // 群事件_群被解散
    Group_GroupDissolved = 4,
    // 群事件_某人退出了群
    Group_MemberQuit = 5,
    // 群事件_某人被踢出群
    Group_MemberKicked = 6,
    // 群事件_某人被禁言
    Group_MemberShutUp = 7,
    // 群事件_某人撤回事件
    Group_MemberUndid = 8,
    // 群事件_某人被取消管理
    Group_AdministratorTook = 9,
    // 群事件_某人被赋予管理
    Group_AdministratorGave = 10,
    // 群事件_开启全员禁言
    Group_EnableAllShutUp = 11,
    // 群事件_关闭全员禁言
    Group_DisableAllShutUp = 12,
    // 群事件_开启匿名聊天
    Group_EnableAnonymous = 13,
    // 群事件_关闭匿名聊天
    Group_DisableAnonymous = 14,
    // 群事件_开启坦白说
    Group_EnableChatFrankly = 15,
    // 群事件_关闭坦白说
    Group_DisableChatFrankly = 16,
    // 群事件_允许群临时会话
    Group_AllowGroupTemporary = 17,
    // 群事件_禁止群临时会话
    Group_ForbidGroupTemporary = 18,
    // 群事件_允许发起新的群聊
    Group_AllowCreateGroup = 19,
    // 群事件_禁止发起新的群聊
    Group_ForbidCreateGroup = 20,
    // 群事件_允许上传群文件
    Group_AllowUploadFile = 21,
    // 群事件_禁止上传群文件
    Group_ForbidUploadFile = 22,
    // 群事件_允许上传相册
    Group_AllowUploadPicture = 23,
    // 群事件_禁止上传相册
    Group_ForbidUploadPicture = 24,
    // 群事件_某人被邀请入群
    Group_MemberInvited = 25,
    // 群事件_展示成员群头衔
    Group_ShowMemberTitle = 27,
    // 群事件_隐藏成员群头衔
    Group_HideMemberTitle = 28,
    // 群事件_某人被解除禁言
    Group_MemberNotShutUp = 29
};

// 语音类型
enum class AudioTypeEnum : eint
{
    // 普通语音
    Normal = 0,
    // 变声语音
    Change = 1,
    // 文字语音
    Text = 2,
    // (红包)匹配语音
    Match = 3,
};

// 群验证信息操作类型
enum class GroupVerificationOperateEnum : eint
{
    Agree = 11,
    Deny = 12,
    Ignore = 14
};

// 好友验证信息操作类型
enum class FriendVerificationOperateEnum : eint
{
    Agree = 1,
    Deny = 2
};

// 主要在线状态
enum class StatusTypeEnum : eint
{
    // 在线
    Online = 11,
    // 离开
    Away = 31,
    // 隐身
    Invisibility = 41,
    // 忙碌
    Busy = 50,
    // Q我吧
    TalkToMe = 60,
    // 请勿打扰
    DoNotDisturb = 70
};

// 详细在线状态
enum class StatusOnlineTypeEnum : eint
{
    // 普通在线
    Normal = 0,
    // 我的电量
    ShowBattery = 1000,
    // 信号弱
    WeakSignal = 1011,
    // 睡觉中
    Sleeping = 1016,
    // 游戏中
    InGame = 1017,
    // 学习中
    Learning = 1018,
    // 吃饭中
    Eating = 1019,
    // 煲剧中
    WatchingTeleplay = 1021,
    // 度假中
    OnVacation = 1022,
    // 在线学习
    OnlineLearning = 1024,
    // 在家旅游
    TravelAtHome = 1025,
    // TiMi中
    InTiMi = 1027,
    // 我在听歌
    ListeningSong = 1028,
    // 熬夜中
    StayingUpLate = 1032,
    // 打球中
    PlayingBall = 1050,
    // 恋爱中
    InLove = 1051,
    // 我没事(实际上有事)
    IAmOK = 1052
};

// TODO 优化使用体验
// 免费礼物
enum class FreeGiftEnum : eint
{
    // 告白话筒
    Gift_367 = 367,
    // 卡布奇诺
    Gift_299 = 299,
    // 猫咪手表
    Gift_302 = 302,
    // 牵你的手
    Gift_280 = 280,
    // 可爱猫咪
    Gift_281 = 281,
    // 神秘面具
    Gift_284 = 284,
    // 甜wink
    Gift_285 = 285,
    // 我超忙的
    Gift_286 = 286,
    // 快乐肥宅水
    Gift_289 = 289,
    // 幸运手链
    Gift_290 = 290,
    // 坚强
    Gift_313 = 313,
    // 绒绒手套
    Gift_307 = 307,
    // 爱心口罩
    Gift_312 = 312,
    // 彩虹糖果
    Gift_308 = 308
};
//const std::unordered_map<std::string, eint> FreeGiftMap =
//        {
// 367: 告白话筒, 299: 卡布奇诺, 302: 猫咪手表, 280: 牵你的手, 281: 可爱猫咪, 284: 神秘面具, 285: 甜wink, 286: 我超忙的, 289: 快乐肥宅水, 290: 幸运手链, 313: 坚强, 307: 绒绒手套, 312: 爱心口罩, 308: 彩虹糖果
//        };


// 某些API中可能会用
// 权限（有感叹号的是危险权限！）
enum class PermissionEnum : eint
{
    // 输出日志
    OutputLog = 0,
    // 发送好友消息
    SendFriendMessage = 1,
    // 发送群消息
    SendGroupMessage = 2,
    // 发送群临时消息
    SendGroupTemporaryMessage = 3,
    // 添加好友
    AddFriend = 4,
    // 添加群
    AddGroup = 5,
    // 删除好友！
    RemoveFriend = 6,
    // 置屏蔽好友！
    SetBlockFriend = 7,
    // 置特别关心好友
    SetSpecialFriend = 8,
    // 发送好友json消息
    SendFriendJSONMessage = 11,
    // 发送群json消息
    SendGroupJSONMessage = 12,
    // 上传好友图片
    UploadFriendPicture = 13,
    // 上传群图片
    UploadGroupPicture = 14,
    // 上传好友语音
    UploadFriendAudio = 15,
    // 上传群语音
    UploadGroupAudio = 16,
    // 上传头像！
    UploadAvatar = 17,
    // 设置群名片
    SetGroupMemberNickname = 18,
    // 取昵称_从缓存
    GetNameFromCache = 19,
    // 强制取昵称
    GetNameForce = 20,
    // 获取skey！
    GetSKey = 21,
    // 获取pskey！
    GetPSKey = 22,
    // 获取clientkey！
    GetClientKey = 23,
    // 取框架QQ
    GetThisQQ = 24,
    // 取好友列表
    GetFriendList = 25,
    // 取群列表
    GetGroupList = 26,
    // 取群成员列表
    GetGroupMemberList = 27,
    // 设置管理员
    SetAdministrator = 28,
    // 取管理层列表
    GetAdministratorList = 29,
    // 取群名片
    GetGroupMemberNickname = 30,
    // 取个性签名
    GetSignature = 31,
    // 修改昵称！
    SetName = 32,
    // 修改个性签名！
    SetSignature = 33,
    // 删除群成员
    KickGroupMember = 34,
    // 禁言群成员
    BanGroupMember = 35,
    // 退群！
    QuitGroup = 36,
    // 解散群！
    DissolveGroup = 37,
    // 上传群头像
    UploadGroupAvatar = 38,
    // 全员禁言
    BanAll = 39,
    // 群权限_发起新的群聊
    Group_Create = 40,
    // 群权限_发起临时会话
    Group_CreateTemporary = 41,
    // 群权限_上传文件
    Group_UploadFile = 42,
    // 群权限_上传相册
    Group_UploadPicture = 43,
    // 群权限_邀请好友加群
    Group_InviteFriend = 44,
    // 群权限_匿名聊天
    Group_Anonymous = 45,
    // 群权限_坦白说
    Group_ChatFrankly = 46,
    // 群权限_新成员查看历史消息
    Group_NewMemberReadChatHistory = 47,
    // 群权限_邀请方式设置
    Group_SetInviteMethod = 48,
    // 撤回消息_群聊
    Undo_Group = 49,
    // 撤回消息_私聊本身
    Undo_Private = 50,
    // 设置位置共享
    SetLocationShare = 51,
    // 上报当前位置
    ReportCurrentLocation = 52,
    // 是否被禁言
    IsShutUp = 53,
    // 处理好友验证事件
    ProcessFriendVerification = 54,
    // 处理群验证事件
    ProcessGroupVerification = 55,
    // 查看转发聊天记录内容
    ReadForwardedChatHistory = 56,
    // 上传群文件
    UploadGroupFile = 57,
    // 创建群文件夹
    CreateGroupFolder = 58,
    // 设置在线状态
    SetStatus = 59,
    // QQ点赞！
    QQLike = 60,
    // 取图片下载地址
    GetImageDownloadLink = 61,
    // 查询好友信息
    QueryFriendInformation = 63,
    // 查询群信息
    QueryGroupInformation = 64,
    // 框架重启！
    Reboot = 65,
    // 群文件转发至群
    GroupFileForwardToGroup = 66,
    // 群文件转发至好友
    GroupFileForwardToFriend = 67,
    // 好友文件转发至好友
    FriendFileForwardToFriend = 68,
    // 置群消息接收
    SetGroupMessageReceive = 69,
    // 取群名称_从缓存
    GetGroupNameFromCache = 70,
    // 发送免费礼物
    SendFreeGift = 71,
    // 取好友在线状态
    GetFriendStatus = 72,
    // 取QQ钱包个人信息！
    GetQQWalletPersonalInformation = 73,
    // 获取订单详情
    GetOrderDetail = 74,
    // 提交支付验证码
    SubmitPaymentCaptcha = 75,
    // 分享音乐
    ShareMusic = 77,
    // 更改群聊消息内容！
    ModifyGroupMessageContent = 78,
    // 更改私聊消息内容！
    ModifyPrivateMessageContent = 79,
    // 群聊口令红包
    GroupPasswordRedEnvelope = 80,
    // 群聊拼手气红包
    GroupRandomRedEnvelope = 81,
    // 群聊普通红包
    GroupNormalRedEnvelope = 82,
    // 群聊画图红包
    GroupDrawRedEnvelope = 83,
    // 群聊语音红包
    GroupAudioRedEnvelope = 84,
    // 群聊接龙红包
    GroupFollowRedEnvelope = 85,
    // 群聊专属红包
    GroupExclusiveRedEnvelope = 86,
    // 好友口令红包
    FriendPasswordRedEnvelope = 87,
    // 好友普通红包
    FriendNormalRedEnvelope = 88,
    // 好友画图红包
    FriendDrawRedEnvelope = 89,
    // 好友语音红包
    FriendAudioRedEnvelope = 90,
    // 好友接龙红包
    FriendFollowRedEnvelope = 91,
};

const std::unordered_map<PermissionEnum, std::string> PermissionMap =
    {{PermissionEnum::OutputLog, "输出日志"},
     {PermissionEnum::SendFriendMessage, "发送好友消息"},
     {PermissionEnum::SendGroupMessage, "发送群消息"},
     {PermissionEnum::SendGroupTemporaryMessage, "发送群临时消息"},
     {PermissionEnum::AddFriend, "添加好友"},
     {PermissionEnum::AddGroup, "添加群"},
     {PermissionEnum::RemoveFriend, "删除好友"},
     {PermissionEnum::SetBlockFriend, "置屏蔽好友"},
     {PermissionEnum::SetSpecialFriend, "置特别关心好友"},
     {PermissionEnum::SendFriendJSONMessage, "发送好友json消息"},
     {PermissionEnum::SendGroupJSONMessage, "发送群json消息"},
     {PermissionEnum::UploadFriendPicture, "上传好友图片"},
     {PermissionEnum::UploadGroupPicture, "上传群图片"},
     {PermissionEnum::UploadFriendAudio, "上传好友语音"},
     {PermissionEnum::UploadGroupAudio, "上传群语音"},
     {PermissionEnum::UploadAvatar, "上传头像"},
     {PermissionEnum::SetGroupMemberNickname, "设置群名片"},
     {PermissionEnum::GetNameFromCache, "取昵称_从缓存"},
     {PermissionEnum::GetNameForce, "强制取昵称"},
     {PermissionEnum::GetSKey, "获取skey"},
     {PermissionEnum::GetPSKey, "获取pskey"},
     {PermissionEnum::GetClientKey, "获取clientkey"},
     {PermissionEnum::GetThisQQ, "取框架QQ"},
     {PermissionEnum::GetFriendList, "取好友列表"},
     {PermissionEnum::GetGroupList, "取群列表"},
     {PermissionEnum::GetGroupMemberList, "取群成员列表"},
     {PermissionEnum::SetAdministrator, "设置管理员"},
     {PermissionEnum::GetAdministratorList, "取管理层列表"},
     {PermissionEnum::GetGroupMemberNickname, "取群名片"},
     {PermissionEnum::GetSignature, "取个性签名"},
     {PermissionEnum::SetName, "修改昵称"},
     {PermissionEnum::SetSignature, "修改个性签名"},
     {PermissionEnum::KickGroupMember, "删除群成员"},
     {PermissionEnum::BanGroupMember, "禁言群成员"},
     {PermissionEnum::QuitGroup, "退群"},
     {PermissionEnum::DissolveGroup, "解散群"},
     {PermissionEnum::UploadGroupAvatar, "上传群头像"},
     {PermissionEnum::BanAll, "全员禁言"},
     {PermissionEnum::Group_Create, "群权限_发起新的群聊"},
     {PermissionEnum::Group_CreateTemporary, "群权限_发起临时会话"},
     {PermissionEnum::Group_UploadFile, "群权限_上传文件"},
     {PermissionEnum::Group_UploadPicture, "群权限_上传相册"},
     {PermissionEnum::Group_InviteFriend, "群权限_邀请好友加群"},
     {PermissionEnum::Group_Anonymous, "群权限_匿名聊天"},
     {PermissionEnum::Group_ChatFrankly, "群权限_坦白说"},
     {PermissionEnum::Group_NewMemberReadChatHistory, "群权限_新成员查看历史消息"},
     {PermissionEnum::Group_SetInviteMethod, "群权限_邀请方式设置"},
     {PermissionEnum::Undo_Group, "撤回消息_群聊"},
     {PermissionEnum::Undo_Private, "撤回消息_私聊本身"},
     {PermissionEnum::SetLocationShare, "设置位置共享"},
     {PermissionEnum::ReportCurrentLocation, "上报当前位置"},
     {PermissionEnum::IsShutUp, "是否被禁言"},
     {PermissionEnum::ProcessFriendVerification, "处理好友验证事件"},
     {PermissionEnum::ProcessGroupVerification, "处理群验证事件"},
     {PermissionEnum::ReadForwardedChatHistory, "查看转发聊天记录内容"},
     {PermissionEnum::UploadGroupFile, "上传群文件"},
     {PermissionEnum::CreateGroupFolder, "创建群文件夹"},
     {PermissionEnum::SetStatus, "设置在线状态"},
     {PermissionEnum::QQLike, "QQ点赞"},
     {PermissionEnum::GetImageDownloadLink, "取图片下载地址"},
     {PermissionEnum::QueryFriendInformation, "查询好友信息"},
     {PermissionEnum::QueryGroupInformation, "查询群信息"},
     {PermissionEnum::Reboot, "框架重启"},
     {PermissionEnum::GroupFileForwardToGroup, "群文件转发至群"},
     {PermissionEnum::GroupFileForwardToFriend, "群文件转发至好友"},
     {PermissionEnum::FriendFileForwardToFriend, "好友文件转发至好友"},
     {PermissionEnum::SetGroupMessageReceive, "置群消息接收"},
     {PermissionEnum::GetGroupNameFromCache, "取群名称_从缓存"},
     {PermissionEnum::SendFreeGift, "发送免费礼物"},
     {PermissionEnum::GetFriendStatus, "取好友在线状态"},
     {PermissionEnum::GetQQWalletPersonalInformation, "取QQ钱包个人信息"},
     {PermissionEnum::GetOrderDetail, "获取订单详情"},
     {PermissionEnum::SubmitPaymentCaptcha, "提交支付验证码"},
     {PermissionEnum::ShareMusic, "分享音乐"},
     {PermissionEnum::ModifyGroupMessageContent, "更改群聊消息内容"},
     {PermissionEnum::ModifyPrivateMessageContent, "更改私聊消息内容"},
     {PermissionEnum::GroupPasswordRedEnvelope, "群聊口令红包"},
     {PermissionEnum::GroupRandomRedEnvelope, "群聊拼手气红包"},
     {PermissionEnum::GroupNormalRedEnvelope, "群聊普通红包"},
     {PermissionEnum::GroupDrawRedEnvelope, "群聊画图红包"},
     {PermissionEnum::GroupAudioRedEnvelope, "群聊语音红包"},
     {PermissionEnum::GroupFollowRedEnvelope, "群聊接龙红包"},
     {PermissionEnum::GroupExclusiveRedEnvelope, "群聊专属红包"},
     {PermissionEnum::FriendPasswordRedEnvelope, "好友口令红包"},
     {PermissionEnum::FriendNormalRedEnvelope, "好友普通红包"},
     {PermissionEnum::FriendDrawRedEnvelope, "好友画图红包"},
     {PermissionEnum::FriendAudioRedEnvelope, "好友语音红包"},
     {PermissionEnum::FriendFollowRedEnvelope, "好友接龙红包"}};

//=============
//endregion

#pragma pack(4)
// 数据结构


#define etext_copy_new(dst, src) if ((src) != nullptr) {(dst) = new_and_copy_str((src));} else {(dst) = nullptr;}
#define delete_str_copy(str) if ((str) != nullptr) { delete[] (str); (str) = nullptr;}

// Note: _EType_开头的是内部转换用的类型，请使用普通的PrivateMessageData
struct _EType_PrivateMessageData
{
    // 发送人QQ
    elong SenderQQ;
    // 框架QQ
    elong ThisQQ;
    // 消息Req
    eint MessageReq;
    // 消息Seq
    elong MessageSeq;
    // 消息接收时间
    eint MessageReceiveTime;
    // 消息群号 当为群临时会话时可取
    elong MessageGroupQQ;
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
    // 消息内容
    etext MessageContent = nullptr;
    // 发送人气泡ID
    eint BubbleID;
    // 消息类型
    MessageTypeEnum MessageType;
    // 消息子类型
    MessageSubTypeEnum MessageSubType;
    // 消息子临时类型 0: 群, 1: 讨论组, 129: 腾讯公众号, 201: QQ咨询
    MessageSubTypeEnum MessageSubTemporaryType;
    // 红包类型 0: 非红包的普通消息, 2: 已转入余额, 4: 点击收款, 10: 红包
    eint RedEnvelopeType;
    // 会话Token
    ebin SessionToken = nullptr;
    // 来源事件QQ
    elong SourceEventQQ;
    // 来源事件QQ昵称
    etext SourceEventQQName = nullptr;
    // 文件ID
    etext FileID = nullptr;
    // 文件Md5
    ebin FileMD5 = nullptr;
    // 文件名
    etext FileName = nullptr;
    // 文件大小
    elong FileSize;
};
// 私聊消息数据
struct PrivateMessageData : _EType_PrivateMessageData
{
    PrivateMessageData(const PrivateMessageData& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->MessageContent, info.MessageContent);
        etext_copy_new(this->SourceEventQQName, info.SourceEventQQName);
        etext_copy_new(this->FileID, info.FileID);
        etext_copy_new(this->FileName, info.FileName);
    }
    PrivateMessageData(const _EType_PrivateMessageData& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->MessageContent, e2s(info.MessageContent));
        etext_copy_new(this->SourceEventQQName, e2s(info.SourceEventQQName));
        etext_copy_new(this->FileID, e2s(info.FileID));
        etext_copy_new(this->FileName, e2s(info.FileName));
    }
    ~PrivateMessageData()
    {
        delete_str_copy(this->MessageContent);
        delete_str_copy(this->SourceEventQQName);
        delete_str_copy(this->FileID);
        delete_str_copy(this->FileName);
    }
};

// Note: _EType_开头的是内部转换用的类型，请使用普通的ServiceInformation
struct _EType_ServiceInformation
{
    // 服务代号 1: SVIP, 4: 视频会员, 6: 音乐包, 105: star, 102: 黄钻, 103: 绿钻, 101: 红钻, 104:yellowlove, 107: SVIP&视频会员, 109: SVIP&绿钻, 110: SVIP&音乐包
    eint ServiceCodename;
    // 服务等级
    eint ServiceLevel;
};
// 服务信息
struct ServiceInformation : _EType_ServiceInformation
{
    ServiceInformation()
    {}
    ServiceInformation(const ServiceInformation& info)
    {
        memcpy(this, &info, sizeof(info));
    }
    ServiceInformation(const _EType_ServiceInformation& info)
    {
        memcpy(this, &info, sizeof(info));
    }
};

// Note: _EType_开头的是内部转换用的类型，请使用普通的FriendInformation
struct _EType_FriendInformation
{
    // 邮箱
    etext Email = nullptr;
    // 账号
    elong QQNumber;
    // 昵称
    etext Name = nullptr;
    // 备注
    etext Note = nullptr;
    // 在线状态 只能使用[取好友列表]获取
    etext Status = nullptr;
    // 赞数量 只能使用[查询好友信息]获取
    eint Likes;
    // 签名 只能使用[查询好友信息]获取
    etext Signature = nullptr;
    // 性别 255: 隐藏, 0: 男, 1: 女
    eint Gender;
    // Q等级 只能使用[查询好友信息]获取
    eint Level;
    // 年龄 只能使用[查询好友信息]获取
    eint Age;
    // 国家 只能使用[查询好友信息]获取
    etext Nation = nullptr;
    // 省份 只能使用[查询好友信息]获取
    etext Province = nullptr;
    // 城市 只能使用[查询好友信息]获取
    etext City = nullptr;
    // 服务列表 只能使用[查询好友信息]获取
    ServiceInformation *ServiceList = nullptr;
    // 连续在线天数 只能使用[查询好友信息]获取
    eint ContinuousOnlineTime;
    // QQ达人 只能使用[查询好友信息]获取
    etext QQTalent = nullptr;
    // 今日已赞 只能使用[查询好友信息]获取
    eint LikesToday;
    // 今日可赞数 只能使用[查询好友信息]获取
    eint LikesAvailableToday;
};
// 好友信息
struct FriendInformation : _EType_FriendInformation
{
    FriendInformation(const FriendInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->Email, info.Email);
        etext_copy_new(this->Name, info.Name);
        etext_copy_new(this->Note, info.Note);
        etext_copy_new(this->Status, info.Status);
        etext_copy_new(this->Signature, info.Signature);
        etext_copy_new(this->Nation, info.Nation);
        etext_copy_new(this->Province, info.Province);
        etext_copy_new(this->City, info.City);
        etext_copy_new(this->QQTalent, info.QQTalent);
    }
    FriendInformation(const _EType_FriendInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->Email, e2s(info.Email));
        etext_copy_new(this->Name, e2s(info.Name));
        etext_copy_new(this->Note, e2s(info.Note));
        etext_copy_new(this->Status, e2s(info.Status));
        etext_copy_new(this->Signature, e2s(info.Signature));
        etext_copy_new(this->Nation, e2s(info.Nation));
        etext_copy_new(this->Province, e2s(info.Province));
        etext_copy_new(this->City, e2s(info.City));
        etext_copy_new(this->QQTalent, e2s(info.QQTalent));

        if (this->ServiceList != nullptr)
        {
            earray1D<_EType_ServiceInformation, ServiceInformation> array;
            std::vector<ServiceInformation> info_list;
            array.data = this->ServiceList;
            size_t size = array.Unpack(info_list);
            if (size > 0) {
                this->ServiceList = new ServiceInformation[size];
                for (size_t i = 0; i < info_list.size(); i++)
                {
                    memcpy(this->ServiceList + i, &info_list[i], sizeof(ServiceInformation));
                }
            }
        }
    }
    ~FriendInformation()
    {
        delete_str_copy(this->Email);
        delete_str_copy(this->Name);
        delete_str_copy(this->Note);
        delete_str_copy(this->Status);
        delete_str_copy(this->Signature);
        delete_str_copy(this->Nation);
        delete_str_copy(this->Province);
        delete_str_copy(this->City);
        delete_str_copy(this->QQTalent);

        if (this->ServiceList != nullptr)
        {
            delete this->ServiceList;
            this->ServiceList = nullptr;
        }

    }
};

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
// 群信息
struct GroupInformation : _EType_GroupInformation
{
    GroupInformation(const GroupInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->GroupName, info.GroupName);
        etext_copy_new(this->GroupMemo, info.GroupMemo);
    }
    GroupInformation(const _EType_GroupInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->GroupName, e2s(info.GroupName));
        etext_copy_new(this->GroupMemo, e2s(info.GroupMemo));
    }
    ~GroupInformation()
    {
        delete_str_copy(this->GroupName);
        delete_str_copy(this->GroupMemo);
    }
};

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
// 群成员信息
struct GroupMemberInformation : _EType_GroupMemberInformation
{
    GroupMemberInformation(const GroupMemberInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->QQNumber, info.QQNumber);
        etext_copy_new(this->Name, info.Name);
        etext_copy_new(this->Email, info.Email);
        etext_copy_new(this->Nickname, info.Nickname);
        etext_copy_new(this->Note, info.Note);
        etext_copy_new(this->Title, info.Title);
        etext_copy_new(this->Phone, info.Phone);
    }
    GroupMemberInformation(const _EType_GroupMemberInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->QQNumber, e2s(info.QQNumber));
        etext_copy_new(this->Name, e2s(info.Name));
        etext_copy_new(this->Email, e2s(info.Email));
        etext_copy_new(this->Nickname, e2s(info.Nickname));
        etext_copy_new(this->Note, e2s(info.Note));
        etext_copy_new(this->Title, e2s(info.Title));
        etext_copy_new(this->Phone, e2s(info.Phone));
    }
    ~GroupMemberInformation()
    {
        delete_str_copy(this->QQNumber);
        delete_str_copy(this->Name);
        delete_str_copy(this->Email);
        delete_str_copy(this->Nickname);
        delete_str_copy(this->Note);
        delete_str_copy(this->Title);
        delete_str_copy(this->Phone);
    }
};

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
// 群消息数据
struct GroupMessageData : _EType_GroupMessageData
{
    GroupMessageData(const GroupMessageData& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->SourceGroupName, info.SourceGroupName);
        etext_copy_new(this->SenderNickname, info.SenderNickname);
        etext_copy_new(this->SenderTitle, info.SenderTitle);
        etext_copy_new(this->MessageContent, info.MessageContent);
        etext_copy_new(this->ReplyMessageContent, info.ReplyMessageContent);
        etext_copy_new(this->FileID, info.FileID);
        etext_copy_new(this->FileName, info.FileName);
    }
    GroupMessageData(const _EType_GroupMessageData& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->SourceGroupName, e2s(info.SourceGroupName));
        etext_copy_new(this->SenderNickname, e2s(info.SenderNickname));
        etext_copy_new(this->SenderTitle, e2s(info.SenderTitle));
        etext_copy_new(this->MessageContent, e2s(info.MessageContent));
        etext_copy_new(this->ReplyMessageContent, e2s(info.ReplyMessageContent));
        etext_copy_new(this->FileID, e2s(info.FileID));
        etext_copy_new(this->FileName, e2s(info.FileName));
    }
    ~GroupMessageData()
    {
        delete_str_copy(this->SourceGroupName);
        delete_str_copy(this->SenderNickname);
        delete_str_copy(this->SenderTitle);
        delete_str_copy(this->MessageContent);
        delete_str_copy(this->ReplyMessageContent);
        delete_str_copy(this->FileID);
        delete_str_copy(this->FileName);
    }
};

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
// 事件数据
struct EventData : _EType_EventData
{
    EventData(const EventData& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->SourceGroupName, info.SourceGroupName);
        etext_copy_new(this->OperateQQName, info.OperateQQName);
        etext_copy_new(this->TriggerQQName, info.TriggerQQName);
        etext_copy_new(this->MessageContent, info.MessageContent);
    }
    EventData(const _EType_EventData& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->SourceGroupName, e2s(info.SourceGroupName));
        etext_copy_new(this->OperateQQName, e2s(info.OperateQQName));
        etext_copy_new(this->TriggerQQName, e2s(info.TriggerQQName));
        etext_copy_new(this->MessageContent, e2s(info.MessageContent));
    }
    ~EventData()
    {
        delete_str_copy(this->SourceGroupName);
        delete_str_copy(this->OperateQQName);
        delete_str_copy(this->TriggerQQName);
        delete_str_copy(this->MessageContent);
    }
};

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
// 群卡片信息
struct GroupCardInformation : _EType_GroupCardInformation
{
    GroupCardInformation(const GroupCardInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->GroupName, info.GroupName);
        etext_copy_new(this->GroupLocation, info.GroupLocation);
        etext_copy_new(this->GroupClassification, info.GroupClassification);
        etext_copy_new(this->GroupTags, info.GroupTags);
        etext_copy_new(this->GroupDescription, info.GroupDescription);
    }
    GroupCardInformation(const _EType_GroupCardInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->GroupName, e2s(info.GroupName));
        etext_copy_new(this->GroupLocation, e2s(info.GroupLocation));
        etext_copy_new(this->GroupClassification, e2s(info.GroupClassification));
        etext_copy_new(this->GroupTags, e2s(info.GroupTags));
        etext_copy_new(this->GroupDescription, e2s(info.GroupDescription));
    }
    ~GroupCardInformation()
    {
        delete_str_copy(this->GroupName);
        delete_str_copy(this->GroupLocation);
        delete_str_copy(this->GroupClassification);
        delete_str_copy(this->GroupTags);
        delete_str_copy(this->GroupDescription);
    }
};

// Note: _EType_开头的是内部转换用的类型，请使用普通的GroupFileInformation
struct _EType_GroupFileInformation
{
    // 文件夹fileid或者文件fileid
    etext FileID = nullptr;
    // 文件夹名或文件名
    etext FileName = nullptr;
    // 文件大小，文件夹时表示有多少个文件
    elong FileSize;
    // 文件md5，文件夹时为空，部分文件类型也可能是空
    ebin FileMd5 = nullptr;
    // 创建文件夹或上传文件的QQ
    elong FileFromUin;
    // 创建文件夹或上传文件的QQ
    etext FileFromNick = nullptr;
    // 文件类型  1: 文件, 2: 文件夹
    eint FileType;
};
// 群文件信息
struct GroupFileInformation : _EType_GroupFileInformation
{
    GroupFileInformation(const GroupFileInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->FileID, info.FileID);
        etext_copy_new(this->FileName, info.FileName);
        etext_copy_new(this->FileFromNick, info.FileFromNick);
    }
    GroupFileInformation(const _EType_GroupFileInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->FileID, e2s(info.FileID));
        etext_copy_new(this->FileName, e2s(info.FileName));
        etext_copy_new(this->FileFromNick, e2s(info.FileFromNick));
    }
    ~GroupFileInformation()
    {
        delete_str_copy(this->FileID);
        delete_str_copy(this->FileName);
        delete_str_copy(this->FileFromNick);
    }
};

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
// 银行卡信息
struct CardInformation : _EType_CardInformation
{
    CardInformation()
    {}
    CardInformation(const CardInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->TailNumber, info.TailNumber);
        etext_copy_new(this->Bank, info.Bank);
        etext_copy_new(this->BindPhone, info.BindPhone);
        etext_copy_new(this->BindSerial, info.BindSerial);
        etext_copy_new(this->BankType, info.BankType);
    }
    CardInformation(const _EType_CardInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->TailNumber, e2s(info.TailNumber));
        etext_copy_new(this->Bank, e2s(info.Bank));
        etext_copy_new(this->BindPhone, e2s(info.BindPhone));
        etext_copy_new(this->BindSerial, e2s(info.BindSerial));
        etext_copy_new(this->BankType, e2s(info.BankType));
    }
    ~CardInformation()
    {
        delete_str_copy(this->TailNumber);
        delete_str_copy(this->Bank);
        delete_str_copy(this->BindPhone);
        delete_str_copy(this->BindSerial);
        delete_str_copy(this->BankType);
    }
};

// Note: _EType_开头的是内部转换用的类型，请使用普通的QQWalletInformation
struct _EType_QQWalletInformation
{
    // 余额
    etext Balance = nullptr;
    // 身份证号
    etext ID = nullptr;
    // 实名
    etext RealName = nullptr;
    // 银行卡列表
    CardInformation *CardList = nullptr;
};
// QQ钱包信息
struct QQWalletInformation : _EType_QQWalletInformation
{
    QQWalletInformation(const QQWalletInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->Balance, info.Balance);
        etext_copy_new(this->ID, info.ID);
        etext_copy_new(this->RealName, info.RealName);
    }
    QQWalletInformation(const _EType_QQWalletInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->Balance, e2s(info.Balance));
        etext_copy_new(this->ID, e2s(info.ID));
        etext_copy_new(this->RealName, e2s(info.RealName));

        if (this->CardList != nullptr)
        {
            earray1D<_EType_CardInformation, CardInformation> array;
            std::vector<CardInformation> info_list;
            array.data = this->CardList;
            size_t size = array.Unpack(info_list);
            if (size > 0) {
                this->CardList = new CardInformation[size];
                for (size_t i = 0; i < info_list.size(); i++)
                {
                    memcpy(this->CardList + i, &info_list[i], sizeof(CardInformation));
                }
            }
        }
    }
    ~QQWalletInformation()
    {
        delete_str_copy(this->Balance);
        delete_str_copy(this->ID);
        delete_str_copy(this->RealName);

        if (this->CardList != nullptr)
        {
            delete this->CardList;
            this->CardList = nullptr;
        }
    }
};

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
// 订单详情
struct OrderDetail : _EType_OrderDetail
{
    OrderDetail(const OrderDetail& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->OrderTime, info.OrderTime);
        etext_copy_new(this->OrderDescription, info.OrderDescription);
        etext_copy_new(this->OrderClassification, info.OrderClassification);
        etext_copy_new(this->OrderType, info.OrderType);
        etext_copy_new(this->OrderCommission, info.OrderCommission);
        etext_copy_new(this->OperatorQQ, info.OperatorQQ);
        etext_copy_new(this->OperatorName, info.OperatorName);
        etext_copy_new(this->ReceiverQQ, info.ReceiverQQ);
        etext_copy_new(this->ReceiverName, info.ReceiverName);
        etext_copy_new(this->OperateAmount, info.OperateAmount);
    }
    OrderDetail(const _EType_OrderDetail& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->OrderTime, e2s(info.OrderTime));
        etext_copy_new(this->OrderDescription, e2s(info.OrderDescription));
        etext_copy_new(this->OrderClassification, e2s(info.OrderClassification));
        etext_copy_new(this->OrderType, e2s(info.OrderType));
        etext_copy_new(this->OrderCommission, e2s(info.OrderCommission));
        etext_copy_new(this->OperatorQQ, e2s(info.OperatorQQ));
        etext_copy_new(this->OperatorName, e2s(info.OperatorName));
        etext_copy_new(this->ReceiverQQ, e2s(info.ReceiverQQ));
        etext_copy_new(this->ReceiverName, e2s(info.ReceiverName));
        etext_copy_new(this->OperateAmount, e2s(info.OperateAmount));
    }
    ~OrderDetail()
    {
        delete_str_copy(this->OrderTime);
        delete_str_copy(this->OrderDescription);
        delete_str_copy(this->OrderClassification);
        delete_str_copy(this->OrderType);
        delete_str_copy(this->OrderCommission);
        delete_str_copy(this->OperatorQQ);
        delete_str_copy(this->OperatorName);
        delete_str_copy(this->ReceiverQQ);
        delete_str_copy(this->ReceiverName);
        delete_str_copy(this->OperateAmount);
    }
};

// Note: _EType_开头的是内部转换用的类型，请使用普通的CaptchaInformation
struct _EType_CaptchaInformation
{
    _EType_CaptchaInformation() {}
    // FIXME 需要限定类型只能为CaptchaInformation
    // TODO 增加字符串指针为null的判断
    template<typename T>
    _EType_CaptchaInformation(const T& info) {
        memcpy(this, &info, sizeof(_EType_CaptchaInformation));
        this->TokenID = s2e(this->TokenID);
        this->SKey = s2e(this->SKey);
        this->BankType = s2e(this->BankType);
        this->Mobile = s2e(this->Mobile);
        this->BusinessType = s2e(this->BusinessType);
        this->TransactionID = s2e(this->TransactionID);
        this->PurchaserID = s2e(this->PurchaserID);
        this->Token = s2e(this->Token);
        this->AuthParams = s2e(this->AuthParams);
    }
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
// 验证码信息
struct CaptchaInformation : _EType_CaptchaInformation
{
    CaptchaInformation() {};
    CaptchaInformation(const CaptchaInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->TokenID, info.TokenID);
        etext_copy_new(this->SKey, info.SKey);
        etext_copy_new(this->BankType, info.BankType);
        etext_copy_new(this->Mobile, info.Mobile);
        etext_copy_new(this->BusinessType, info.BusinessType);
        etext_copy_new(this->TransactionID, info.TransactionID);
        etext_copy_new(this->PurchaserID, info.PurchaserID);
        etext_copy_new(this->Token, info.Token);
        etext_copy_new(this->AuthParams, info.AuthParams);
    }
    CaptchaInformation(const _EType_CaptchaInformation& info)
    {
        memcpy(this, &info, sizeof(info));
        etext_copy_new(this->TokenID, e2s(info.TokenID));
        etext_copy_new(this->SKey, e2s(info.SKey));
        etext_copy_new(this->BankType, e2s(info.BankType));
        etext_copy_new(this->Mobile, e2s(info.Mobile));
        etext_copy_new(this->BusinessType, e2s(info.BusinessType));
        etext_copy_new(this->TransactionID, e2s(info.TransactionID));
        etext_copy_new(this->PurchaserID, e2s(info.PurchaserID));
        etext_copy_new(this->Token, e2s(info.Token));
        etext_copy_new(this->AuthParams, e2s(info.AuthParams));
    }
    ~CaptchaInformation()
    {
        delete_str_copy(this->TokenID);
        delete_str_copy(this->SKey);
        delete_str_copy(this->BankType);
        delete_str_copy(this->Mobile);
        delete_str_copy(this->BusinessType);
        delete_str_copy(this->TransactionID);
        delete_str_copy(this->PurchaserID);
        delete_str_copy(this->Token);
        delete_str_copy(this->AuthParams);
    }
};

#undef etext_copy_new
#undef delete_str_copy

#pragma pack()
#endif // CORNERSTONE_HEADER_TYPES_H_