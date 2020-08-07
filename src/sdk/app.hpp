#pragma once

#include <cstdint>

#include "../include/json.hpp"
#include "../include/encode.hpp"
#define EXPORT_FN(TYPE) extern "C" TYPE __stdcall
using Json = nlohmann::json;
using string = std::string;
using text = const char *; //const char *; //避免写这么长的东西

// 方便区分C++原生类型和易语言类型
using ebyte = std::uint8_t;  // 易语言字节型
using eshort = std::int16_t;  // 易语言短整数型
using eint = std::int32_t;  // 易语言整数型
using elong = std::int64_t;  // 易语言长整数型
using efloat = float;  // 易语言小数型
using edouble = double;  // 易语言双精度小数型
using edate = std::uint64_t;  // 易语言日期时间型
using ebool = std::int32_t;  // 易语言逻辑型
using etext = const char*;  // 易语言文本型(GB2312)
using ebin = const std::uint8_t*;  // 易语言字节集
using esubptr = std::uint32_t;  // 易语言子程序指针

enum class MessageProcess  // 消息处理
{
    Block = 1,  // 拦截
    Ignore = 0  // 忽略
};

enum class messageType  // 消息类型
{
    temporary = 141,  // 临时会话
    temporary_Group = 0,  // 临时会话_群
    temporary_PublicAccount = 129,  // 临时会话_公众号
    temporary_WebQQConsultation = 201,  // 临时会话_网页QQ咨询
    friendUsualMessage = 166,  // 好友通常消息
    friendFile = 529,  // 好友文件
    friendAudio = 208,  // 好友语音
    groupRedEnvelope = 78,  // 群红包
    groupUsualMessage = 134  // 群聊通常消息
};

enum class groupEvent  // 群事件
{
    invited = 1,  // 我被邀请加入群
    memberJoined = 2,  // 某人加入了群
    memberVerifying = 3,  // 某人申请加群
    groupDissolved = 4,  // 群被解散
    memberQuit = 5,  // 某人退出了群
    memberKicked = 6,  // 某人被踢出群
    memberBanned = 7,  // 某人被禁言
    memberUndid = 8,  // 某人撤回事件
    administratorTook = 9,  // 某人被取消管理
    administratorGave = 10,  // 某人被赋予管理
    enableAllBanned = 11,  // 开启全员禁言
    disableAllBanned = 12,  // 关闭全员禁言
    enableAnonymous = 13,  // 开启匿名聊天
    disableAnonymous = 14,  // 关闭匿名聊天
    enableChatFrankly = 15,  // 开启坦白说
    disableChatFrankly = 16,  // 关闭坦白说
    allowGroupTemporary = 17,  // 允许群临时会话
    forbidGroupTemporary = 18,  // 禁止群临时会话
    allowCreateGroup = 19,  // 允许发起新的群聊
    forbidCreateGroup = 20,  // 禁止发起新的群聊
    allowUploadFile = 21,  // 允许上传群文件
    forbidUploadFile = 22,  // 禁止上传群文件
    allowUploadPicture = 23,  // 允许上传相册
    forbidUploadPicture = 24,  // 禁止上传相册
    memberInvited = 25,  // 某人被邀请入群
    showMemberTitle = 27,  // 展示成员群头衔
    hideMemberTitle = 28,  // 隐藏成员群头衔
    memberUnbanned = 29  // 某人被解除禁言
};

enum class QZoneEvent  // 空间事件
{
    related = 30  // 与我相关
};

enum class FriendEvent  // 好友事件
{
    removed = 15,  // 被好友删除
    signatureChanged = 16,  // 签名变更
    nameChanged = 17,  // 昵称改变
    userUndid = 18,  // 某人撤回事件
    newFriend = 19,  // 有新好友
    friendRequest = 20,  // 好友请求
    friendRequestAccepted = 21,  // 对方同意了您的好友请求
    friendRequestRefused = 22,  // 对方拒绝了您的好友请求
    informationLiked = 23,  // 资料卡点赞
    signatureLiked = 24,  // 签名点赞
    signatureReplied = 25,  // 签名回复
    tagLiked = 26,  // 个性标签点赞
    stickerLiked = 27,  // 随心贴回复
    stickerAdded = 28  // 随心贴增添
};

enum class Permission  // 权限
{
    outputLog = 0,  // 输出日志
    sendFriendMessage = 1,  // 发送好友消息
    sendGroupMessage = 2,  // 发送群消息
    sendGroupTemporaryMessage = 3,  // 发送群临时消息
    addFriend = 4,  // 添加好友
    addGroup = 5,  // 添加群
    removeFriend = 6,  // 删除好友
    setBlockFriend = 7,  // 设置屏蔽好友
    setSpecialFriend = 8,  // 设置特别关心好友
    sendFriendJSONMessage = 11,  // 发送好友json消息
    sendGroupJSONMessage = 12,  // 发送群json消息
    uploadFriendPicture = 13,  // 上传好友图片
    uploadGroupPicture = 14,  // 上传群图片
    uploadFriendAudio = 15,  // 上传好友语音
    uploadGroupAudio = 16,  // 上传群语音
    uploadAvatar = 17,  // 上传头像
    setGroupMemberNickname = 18,  // 设置群名片
    getNameFromCache = 19,  // 从缓存获取昵称
    getNameForce = 20,  // 强制获取昵称
    getSKey = 21,  // 获取skey
    getPSKey = 22,  // 获取pskey
    getClientKey = 23,  // 获取clientkey
    getThisQQ = 24,  // 获取框架QQ
    getFriendList = 25,  // 获取好友列表
    getGroupList = 26,  // 取群列表
    getGroupMemberList = 27,  // 取群成员列表
    setAdministrator = 28,  // 设置管理员
    getAdministratorList = 29,  // 取管理层列表
    getGroupMemberNickname = 30,  // 取群名片
    getSignature = 31,  // 取个性签名
    setName = 32,  // 修改昵称
    setSignature = 33,  // 修改个性签名
    kickGroupMember = 34,  // 删除群成员
    banGroupMember = 35,  // 禁言群成员
    quitGroup = 36,  //退群
    dissolveGroup = 37,  // 解散群
    uploadGroupAvatar = 38,  // 上传群头像
    banAll = 39,  // 全员禁言
    group_Create = 40,  // 群权限_发起新的群聊
    group_CreateTemporary = 41,  // 群权限_发起临时会话
    group_UploadFile = 42,  // 群权限_上传文件
    group_UploadPicture = 43,  // 群权限_上传相册
    group_InviteFriend = 44,  // 群权限_邀请好友加群
    group_Anonymous = 45,  // 群权限_匿名聊天
    group_ChatFrankly = 46,  // 群权限_坦白说
    group_AllowNewMemberReadHistory = 47,  // 群权限_新成员查看历史消息
    group_SetInviteMethod = 48,  // 群权限_邀请方式设置
    undid_Group = 49,  // 撤回消息_群聊
    undid_Private = 50,  // 撤回消息_私聊本身
    setLocationSharing = 51,  // 设置位置共享
    reportCurrentLocation = 52,  // 上报当前位置
    isBanned = 53,  // 是否被禁言
    handleFriendVerifyEvent = 54,  // 处理好友验证事件
    handleGroupVerifyEvent = 55,  // 处理群验证事件
    readForwardMessageContent = 56,  // 查看转发聊天记录内容
    uploadGroupFile = 57,  // 上传群文件
    createGroupFolder = 58,  // 创建群文件夹
    setStatus = 59,  // 设置在线状态
    likeQQ = 60,  // QQ点赞
    getPictureLink = 61,  // 取图片下载地址
    queryFriendInformation = 63, // 查询好友信息
    queryGroupInformation = 64,  // 查询群信息
    appReboot = 65,  // 框架重启
    forwardGroupFileToGroup = 66,  // 群文件转发至群
    forwardGroupFileToFriend = 67,  // 群文件转发至好友
    forwardFriendFileToFriend = 68,  // 好友文件转发至好友
    setGroupReceive = 69,  // 置群消息接收
    getDroupNameFromCache = 70,  // 取群名称_从缓存
    sendFreeGift = 71,  // 发送免费礼物
    getFriendStatus = 72,  // 取好友在线状态
     = 73,
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

template<typename FuncT>
FuncT _f(const Json& api, const string& name);

namespace HandlerBase
{
    struct private_msg_struct
    {
        INT64 senderQQ;           //8
        INT64 robotQQ;            //8
        INT32 msgReq;             //4
        INT64 msgSeq;             //8
        INT32 msgRecvTime;        //消息接收时间 4
        INT64 msgGroup;           //8 当为群临时会话时可取
        INT32 msgSendTime;        //4
        INT64 msgRandom;          //8 消息random
        INT32 msgPartNum;         //4 消息分片序列
        INT32 msgPartCount;       //4
        INT64 msgPartID;          //8
        text msgContent;          //消息内容
        INT32 bubbleId;           // 发送人气泡id
        INT32 msgType;            //消息type
        INT32 msgSubType;         //消息subtype
        INT32 msgSubTmpType;      // 0 群 1 讨论组 129 腾讯公众号 201 QQ咨询
        INT32 redPackType;        //整数型, , , 红包类型 : 2已转入余额 4点击收款 10红包
        void *sessionToen;        //会话Token
        INT64 fromEventQQ;        //来源事件QQ
        text fromEventQQNickName; //来源事件QQ昵称
        text fileID;              //文件Id
        void *fileMD5;            //文件Md5
        text fileName;            //文件名
        INT64 fileSize;           //文件大小  ?只有传文件才有。
    };
    int onPrivateMsg(void *private_msg);
    //int onPrivateMsg(void* sz);
    struct group_msg_struct
    {
        INT64 senderQQ; //8zijie ?
        INT64 robotQQ;
        INT32 msgReq;
        INT32 msgRecvTime;   //消息接收时间
        INT64 fromGroup;     //消息群号
        text fromGroupName;  //来源群名称, 文本型, , , 消息来源群名(貌似失效了)
        text fromQQCard;     //发送人群名片, 文本型, , , 没有名片则为空白
        INT32 msgSendTime;   //消息发送时间, 整数型, , , 消息发送时间
        INT64 msgRandom;     //消息Random, 长整数型, , , 消息random
        INT32 msgPartNum;    // 消息分片序列, 整数型
        INT32 msgPartCount;  //消息分片数量, 整数型
        INT64 msgPartID;     //消息分片标识, 长整数型
        INT32 msgType;       //消息类型, 整数型, , , 消息subtype
        text fromQQPosition; //发送人群头衔, 文本型, , , 发送者QQ群头衔
        text msgContent;     //消息内容, 文本型, , , 消息内容
        text replyContent;   //回复对象消息内容, 文本型, , , 如果是回复消息,这个变量保存回复的消息的信息
        INT32 bubbleId;      //气泡Id, 整数型, , , 发送者气泡id
        INT32 fromQQNS;      //发送人位置经度, 整数型
        INT32 fromQQSW;      //发送人位置纬度, 整数型
        text fileID;         //文件Id, 文本型
        void *fileMD5;       //文件Md5, 字节集
        text fileName;       //文件名, 文本型
        INT64 fileSize;      // 文件大小, 长整数型
        INT32 msgAppID;      //消息appid, 整数型, , , 消息appid
    };

    int onGroupMsg(void *group_msg);

    //我也不知道参数啥结构
    int onUninstall(void **);

    //我也不知道传入的是啥
    int onSettings(void *);
    
    //插件被启用事件
    int onEnabled(void*);
    //插件被禁用事件
    int onDisabled(void*);

    struct event_message_struct
    {

        INT64 robotQQ;             //, 长整数型
        INT64 fromGroup;           //来源群号, 长整数型
        INT64 operateQQ;           //操作QQ, 长整数型
        INT64 beOperatedQQ;        //, 长整数型
        INT64 msgSeq;              //消息Seq, 长整数型
        INT32 msgTimeStamp;        //消息时间戳, 整数型
        text fromGroupName;        // 来源群名, 文本型
        text operateQQNickName;    // 操作QQ昵称, 文本型
        text beOperatedQQNickName; // 触发QQ昵称, 文本型
        text msgContent;           //消息内容, 文本型
        INT32 msgType;             //消息类型, 整数型
        INT32 msgTmpType;          //消息子类型, 整数型
    };
    //事件消息
    int onEvent(void* em);
}; // namespace HandlerBase

class Application
{
public:
    Application(etext apidata, etext pluginkey);
    ~Application();

    std::string getJSON();

public: //Api
        //输出日志
    text addLog(text logContent, int textColor = 32768, int backColor = 16777215);
    //发送好友消息
    text sendFriendMsg(INT64 robotQQ,
                       INT64 friendQQ,
                       text content,
                       INT64 *Random = NULL,
                       INT32 *Req = NULL);
    //发送群消息
    text sendGroupMsg(
        INT64 robotQQ,
        INT64 GroupQQ,
        text content,
        int hideName = false);

protected:
    Json j;
    string api_key;
};

extern Application *app;