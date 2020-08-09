/*
Corn SDK for Modern C++

MIT License

Copyright © 2020 Contributors of Corn SDK for Modern C++

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

#pragma once

#pragma pack(4)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

#include "json.hpp"

using Json = nlohmann::json;
using string = std::string;

template <class T>
using vector = std::vector<T>;

using uint8_t = std::uint8_t;
using int8_t = std::int8_t;
using int16_t = std::int16_t;
using uint32_t = std::uint32_t;
using int32_t = std::int32_t;
using int64_t = std::int64_t;

// 方便区分C++原生类型和易语言类型
using ebyte = uint8_t;        // 易语言字节型
using eshort = int16_t;       // 易语言短整数型
using eint = int32_t;         // 易语言整数型
using elong = int64_t;        // 易语言长整数型
using efloat = float;         // 易语言小数型
using edouble = double;       // 易语言双精度小数型
using edate = uint64_t;       // 易语言日期时间型
using ebool = int32_t;        // 易语言逻辑型
using etext = const char*;    // 易语言文本型(GBK)
using ebin = const uint8_t*;  // 易语言字节集
using esubptr = uintptr_t;     // 易语言子程序指针

using earray = void*;      // 易语言子程序指针

/*
//解包工具类
namespace package
{
    class UnPack
    {
    public:
        UnPack(void *pALL) : your_pointer((char *)pALL) {}

        template <class WHAT>
        WHAT &getData()
        {
            WHAT &ret = *(WHAT *)(your_pointer + nowOffset);
            nowOffset += sizeof(WHAT);
            return ret;
        }

    protected:
        char *your_pointer = nullptr;
        long nowOffset = 0;
    };
}; // namespace package

template <class T>
class earray1 : public vector<T>
{
public:
    earray1()
};
*/

constexpr ebool etrue = 1;
constexpr ebool efalse = 0;

inline ebool bool2ebool(const bool &b)
{
    return b ? etrue : efalse;
}

inline bool ebool2bool(const ebool &eb)
{
    return eb == etrue;
}

inline ebool b2e(const bool &b)
{
    return bool2ebool(b);
}

inline bool e2b(const ebool &b)
{
    return ebool2bool(b);
}

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


/*
.数据类型 群卡片信息, 公开,
    .成员 群名称, 文本型, , ,
    .成员 群地点, 文本型, , ,
    .成员 群分类, 文本型, , ,
    .成员 群标签, 文本型, , , 以|分割
    .成员 群介绍, 文本型, , ,

.数据类型 QQ钱包信息, 公开,
    .成员 余额, 文本型, , ,
    .成员 身份证号, 文本型, , ,
    .成员 实名, 文本型, , ,
    .成员 银行卡列表, 银行卡信息, , "1",

.数据类型 银行卡信息, 公开,
    .成员 序列, 整数型, , ,
    .成员 尾号, 文本型, , ,
    .成员 银行, 文本型, , ,
    .成员 绑定手机, 文本型, , ,
    .成员 bind_serial, 文本型, , ,
    .成员 bank_type, 文本型, , ,

.数据类型 订单详情, 公开,
    .成员 订单时间, 文本型, , ,
    .成员 订单说明, 文本型, , ,
    .成员 订单类名, 文本型, , ,
    .成员 订单类型, 文本型, , ,
    .成员 订单手续费, 文本型, , ,
    .成员 操作人QQ, 文本型, , ,
    .成员 操作人昵称, 文本型, , ,
    .成员 接收人QQ, 文本型, , ,
    .成员 接收人昵称, 文本型, , ,
    .成员 操作金额, 文本型, , ,

.数据类型 验证码信息, 公开,
    .成员 token_id, 文本型, , ,
    .成员 skey, 文本型, , ,
    .成员 bank_type, 文本型, , ,
    .成员 mobile, 文本型, , ,
    .成员 business_type, 文本型, , ,
    .成员 random, 整数型, , ,
    .成员 transaction_id, 文本型, , ,
    .成员 purchaser_id, 文本型, , ,
    .成员 token, 文本型, , ,
    .成员 auth_params, 文本型, , ,
*/





// 好友消息事件
EventProcess OnPrivateMessage(PrivateMessageData* data);
// 群消息事件
EventProcess OnGroupMessage(GroupMessageData* data);
// 插件卸载事件（未知参数）
EventProcess OnUninstall(void*);
// 插件设置事件（未知参数）
EventProcess OnSettings(void*);
// 插件被启用事件（未知参数）
EventProcess OnEnabled(void*);
// 插件被禁用事件（未知参数）
EventProcess OnDisabled(void*);
// 事件事件
EventProcess OnEvent(EventData* data);
