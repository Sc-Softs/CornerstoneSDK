/*
Cornerstone SDK
-- Corn SDK for Modern C++

Licensed under the MIT License
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

#include "../third_party/json.hpp"
// 万能的json for modern c++
using Json = nlohmann::json;

#include <string>
// 标准库字符串类
using string = std::string;

#include <vector>
// 标准库向量类
template <class T>
using vector = std::vector<T>;

// 标准库各种数据类型
using uint8_t = std::uint8_t;
using int8_t = std::int8_t;
using int16_t = std::int16_t;
using uint32_t = std::uint32_t;
using int32_t = std::int32_t;
using int64_t = std::int64_t;

// 易语言类型
using ebyte = uint8_t;        // 易语言字节型
using eshort = int16_t;       // 易语言短整数型
using eint = int32_t;         // 易语言整数型
using elong = int64_t;        // 易语言长整数型
using efloat = float;         // 易语言小数型
using edouble = double;       // 易语言双精度小数型
using edate = uint64_t;       // 易语言日期时间型
using ebool = int32_t;        // 易语言逻辑型
using etext = const char*;    // 易语言文本型(GBK)
using ebin = const void*;  // 易语言字节集
using esubptr = uintptr_t;     // 易语言子程序指针

using earray = void*;      // 易语言数组

class earray1D;

// 易语言常量
constexpr ebool etrue = 1;
constexpr ebool efalse = 0;

// 易语言类型转换
constexpr  ebool bool2ebool(const bool& b)
{
    return b ? etrue : efalse;
}

constexpr bool ebool2bool(const ebool& e)
{
    return e == etrue;
}

constexpr ebool b2e(const bool& b)
{
    return bool2ebool(b);
}

constexpr bool e2b(const ebool& e)
{
    return ebool2bool(e);
}

string GBKtoUTF8(const char* gbk);
string UTF8toGBK(const std::string& utf8);
#define e2s_s(src_str) GBKtoUTF8(src_str)
#define s2e_s(src_str) UTF8toGBK(src_str)
#define e2s(src_str) e2s_s(src_str).c_str()
#define s2e(src_str) s2e_s(src_str).c_str()

// 枚举常量

// 事件处理
enum class EventProcess : eint
{
    // 阻止其他插件继续处理
    Block = 1,
    // 允许其他插件继续处理
    Ignore = 0
};

// 消息类型
enum class MessageType : eint
{
    // 临时会话
    Temporary = 141,
    // 临时会话_群
    Temporary_Group = 0,
    // 临时会话_公众号
    Temporary_PublicAccount = 129,
    // 临时会话_网页QQ咨询
    Temporary_WebQQConsultation = 201,
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

// 事件类型
enum class EventType : eint
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


#pragma pack(4)
// 数据结构

// 私聊消息数据
using PrivateMessageData = volatile struct PrivateMessageData_
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
    etext MessageContent;
    // 发送人气泡ID
    eint BubbleID;
    // 消息类型
    MessageType MessageType;
    // 消息子类型
    eint MessageSubType;
    // 消息子临时类型 0: 群, 1: 讨论组, 129: 腾讯公众号, 201: QQ咨询
    eint MessageSubTemporaryType;
    // 红包类型 2: 已转入余额, 4: 点击收款, 10: 红包
    eint RedEnvelopeType;
    // 会话Token
    ebin SessionToken;
    // 来源事件QQ
    elong SourceEventQQ;
    // 来源事件QQ昵称
    etext SourceEventQQName;
    // 文件ID
    etext FileID;
    // 文件Md5
    ebin FileMD5;
    // 文件名
    etext FileName;
    // 文件大小
    elong FileSize;
};

// 服务信息
using ServiceInformation = volatile struct ServiceInformation_
{
    // 服务代号 1: SVIP, 4: 视频会员, 6: 音乐包, 105: star, 102: 黄钻, 103: 绿钻, 101: 红钻, 104:yellowlove, 107: SVIP&视频会员, 109: SVIP&绿钻, 110: SVIP&音乐包
    eint ServiceCodename;
    // 服务等级
    eint ServiceLevel;
};

// 好友信息
using FriendInformation = volatile struct FriendInformation_
{
    // 邮箱
    etext Email;
    // 账号
    elong QQNumber;
    // 昵称
    etext Name;
    // 备注
    etext Note;
    // 在线状态 只能使用[取好友列表]获取
    etext Status;
    // 赞数量 只能使用[查询好友信息]获取
    eint Likes;
    // 签名 只能使用[查询好友信息]获取
    etext Signature;
    // 性别 255: 隐藏, 0: 男, 1: 女
    eint Gender;
    // Q等级 只能使用[查询好友信息]获取
    eint Level;
    // 年龄 只能使用[查询好友信息]获取
    eint Age;
    // 国家 只能使用[查询好友信息]获取
    etext Nation;
    // 省份 只能使用[查询好友信息]获取
    etext Province;
    // 城市 只能使用[查询好友信息]获取
    etext City;
    // 服务列表 只能使用[查询好友信息]获取
    ServiceInformation ServiceList;
    // 连续在线天数 只能使用[查询好友信息]获取
    eint ContinuousOnlineTime;
    // QQ达人 只能使用[查询好友信息]获取
    etext QQTalent;
    // 今日已赞 只能使用[查询好友信息]获取
    eint LikesToday;
    // 今日可赞数 只能使用[查询好友信息]获取
    eint LikesAvailableToday;
};

// 群信息
using GroupInformation = volatile struct GroupInformation_
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
    etext GroupName;
    // strGroupMemo
    etext GroupMemo;
};

// 群成员信息
using GroupMemberInformation = volatile struct GroupMemberInformation_
{
    // 账号
    etext QQNumber;
    // 年龄
    eint Age;
    // 性别
    eint Gender;
    // 昵称
    etext Name;
    // 邮箱
    etext Email;
    // 名片
    etext Nickname;
    // 备注
    etext Note;
    // 头衔
    etext Title;
    // 手机号
    etext Phone;
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

// 群消息数据
using GroupMessageData = volatile struct GroupMessageData_
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
    etext SourceGroupName;
    // 发送人群名片 没有名片则为空白
    etext SenderNickname;
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
    MessageType MessageType;
    // 发送人群头衔
    etext SenderTitle;
    // 消息内容
    etext MessageContent;
    // 回复对象消息内容 如果是回复消息
    etext ReplyMessageContent;
    // 发送者气泡ID
    eint BubbleID;
    // 发送人位置经度
    eint SenderLongitude;
    // 发送人位置纬度
    eint SenderLatitude;
    // 文件Id
    etext FileID;
    // 文件Md5
    ebin FileMD5;
    // 文件名
    etext FileName;
    // 文件大小
    elong FileSize;
    // 消息AppID
    eint MessageAppID;
};

// 事件数据
using EventData = volatile struct EventData_
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
    etext SourceGroupName;
    // 操作QQ昵称
    etext OperateQQName;
    // 触发QQ昵称
    etext TriggerQQName;
    // 事件内容
    etext MessageContent;
    // 事件类型
    EventType EventType;
    // 事件子类型
    eint EventSubType;
};

// 群卡片信息
using GroupCardInformation = volatile struct GroupCardInformation_
{
    // 群名称
    etext GroupName;
    // 群地点
    etext GroupLocation;
    // 群分类
    etext GroupClassification;
    // 群标签 以|分割
    etext GroupTags;
    // 群介绍
    etext GroupDescription;
};

// 银行卡信息
using CardInformation = volatile struct CardInformation_
{
    // 序列
    eint Serial;
    // 尾号
    etext TailNumber;
    // 银行
    etext Bank;
    // 绑定手机
    etext BindPhone;
    // bind_serial
    etext BindSerial;
    // bank_type
    etext BankType;
};

// QQ钱包信息
using QQWalletInformation = volatile struct QQWalletInformation_
{
    // 余额
    etext Balance;
    // 身份证号
    etext ID;
    // 实名
    etext RealName;
    // 银行卡列表
    CardInformation* CardList;
};

// 订单详情
using OrderDetail = volatile struct
{
    // 订单时间
    etext OrderTime;
    // 订单说明
    etext OrderDescription;
    // 订单类名
    etext OrderClassification;
    // 订单类型
    etext OrderType;
    // 订单手续费
    etext OrderCommission;
    // 操作人QQ
    etext OperatorQQ;
    // 操作人昵称
    etext OperatorName;
    // 接收人QQ
    etext ReceiverQQ;
    // 接收人昵称
    etext ReceiverName;
    // 操作金额
    etext OperateAmount;
};

// 验证码信息
using CaptchaInformation = volatile struct CaptchaInformation_
{
    // token_id
    etext TokenID;
    // skey
    etext SKey;
    // bank_type
    etext BankType;
    // mobile
    etext Mobile;
    // business_type
    etext BusinessType;
    // random
    eint Random;
    // transaction_id
    etext TransactionID;
    // purchaser_id
    etext PurchaserID;
    // token
    etext Token;
    // auth_params
    etext AuthParams;
};

#pragma pack()

#endif  // CORNERSTONE_HEADER_TYPES_H_
