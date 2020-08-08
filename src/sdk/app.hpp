#pragma once

#pragma pack(4)

#include <cstdint>
#include <vector>

#include "../include/json.hpp"
#include "../include/encode.hpp"

#define EXPORT_FN(TYPE) extern "C" TYPE __stdcall
using Json = nlohmann::json;
using string = std::string;
using text = const char *; //const char *; //避免写这么长的东西
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
using eint = int32_t;// 易语言整数型
using elong = int64_t;        // 易语言长整数型
using efloat = float;// 易语言小数型
using edouble = double;       // 易语言双精度小数型
using edate = uint64_t;       // 易语言日期时间型
using ebool = int32_t;        // 易语言逻辑型
using etext = const char *;   // 易语言文本型(GB2312)
using ebin = const uint8_t *; // 易语言字节集
using esubptr = uint32_t;     // 易语言子程序指针

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

enum class MessageProcess // 消息处理
{
    Block = 1, // 拦截
    Ignore = 0 // 忽略
};

enum class MessageType // 消息类型
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

enum class GroupEvent // 群事件
{
    // 我被邀请加入群  
    Invited = 1,      
    // 某人加入了群 
    MemberJoined = 2, 
    // 某人申请加群
    MemberVerifying = 3,       
    // 群被解散  
    GroupDissolved = 4,        
    // 某人退出了群       
    MemberQuit = 5,   
    // 某人被踢出群
    MemberKicked = 6, 
    // 某人被禁言 
    MemberBanned = 7, 
    // 某人撤回事件        
    MemberUndid = 8,  
    // 某人被取消管理        
    AdministratorTook = 9,     
    // 某人被赋予管理
    AdministratorGave = 10,    
    // 开启全员禁言 
    EnableAllBanned = 11,      
    // 关闭全员禁言
    DisableAllBanned = 12,     
    // 开启匿名聊天
    EnableAnonymous = 13,      
    // 关闭匿名聊天
    DisableAnonymous = 14,     
    // 开启坦白说 
    EnableChatFrankly = 15,    
    // 关闭坦白说
    DisableChatFrankly = 16,   
    // 允许群临时会话       
    AllowGroupTemporary = 17,  
    // 禁止群临时会话
    ForbidGroupTemporary = 18, 
    // 允许发起新的群聊        
    AllowCreateGroup = 19,     
    // 禁止发起新的群聊
    ForbidCreateGroup = 20,    
    // 允许上传群文件 
    AllowUploadFile = 21,      
    // 禁止上传群文件
    ForbidUploadFile = 22,     
    // 允许上传相册 
    AllowUploadPicture = 23,   
    // 禁止上传相册
    ForbidUploadPicture = 24,  
    // 某人被邀请入群        
    MemberInvited = 25,        
    // 展示成员群头衔
    ShowMemberTitle = 27,      
    // 隐藏成员群头衔
    HideMemberTitle = 28,      
    // 某人被解除禁言
    MemberUnbanned = 29      
};

enum class QZoneEvent // 空间事件
{
    // 与我相关
    Related = 30 
};

enum class FriendEvent // 好友事件
{
    // 被好友删除 
    Removed = 15,
    // 签名变更           
    SignatureChanged = 16,      
    // 昵称改变          
    NameChanged = 17,           
    // 某人撤回事件        
    UserUndid = 18,             
     // 有新好友           
    NewFriend = 19,            
     // 好友请求           
    FriendRequest = 20,        
     // 对方同意了您的好友请求         
    FriendRequestAccepted = 21,
     // 对方拒绝了您的好友请求
    FriendRequestRefused = 22, 
    // 资料卡点赞 
    InformationLiked = 23,      
    // 签名点赞           
    SignatureLiked = 24,        
    // 签名回复          
    SignatureReplied = 25,      
    // 个性标签点赞        
    TagLiked = 26,              
    // 随心贴回复           
    StickerLiked = 27,          
     // 随心贴增添         
    StickerAdded = 28      
};

// 私聊消息数据
using PrivateMessageData = volatile struct pmd
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
    eint MessageType;
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
using ServiceInformation = volatile struct si
{
    // 服务代号 1: SVIP, 4: 视频会员, 6: 音乐包, 105: star, 102: 黄钻, 103: 绿钻, 101: 红钻, 104:yellowlove, 107: SVIP&视频会员, 109: SVIP&绿钻, 110: SVIP&音乐包
    eint ServiceCodename;
    // 服务等级
    eint ServiceLevel;
};

// 好友信息
using FriendInformation = volatile struct fi
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
using GroupInformation = volatile struct gif
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
    // dwShutupTimestamp
    elong ShutupTimestamp;
    // dwMyShutupTimestamp
    elong MyShutupTimestamp;
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
using GroupMemberInformation = volatile struct gmi
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
    elong ShutupTimestamp;
    // 加群时间
    elong JoinTime;
    // 发言时间
    elong ChatTime;
    // 群等级
    elong Level;
};

// 群消息数据
using GroupMessageData = volatile struct gmd
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
    eint MessageType;
    // 发送人群头衔
    etext SenderTitle;
    // 消息内容 消息内容
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

/*
using GroupMessageData = volatile struct
{
    //发送人QQ
    elong SenderQQ;
    //框架QQ
    elong RobotQQ;
    //消息req
    eint MessageReq;
    //消息接收时间
    eint MessageRecviveTime;
    //消息群号
    elong FromGroup;
    //来源群名称, 文本型, 消息来源群名(貌似失效了)
    etext FromGroupName;
    //发送人群名片, 文本型 , ,, , 没有名片则为空白
    etext FromQQCard;
    //消息发送时间, 整数型  ,
    eint MessageSendTime;
    //消息Random, , 长整数型,
    elong MessageRandom;
    // 消息分片序列, , ,
    eint MessagePartNum;
    //消息分片数量, 整数型型
    eint MessagePartCount;
    //消息分片标识, 长整数型
    elong MessagePartID;
    //消息类型, 整数型, , , 消息subtype
    eint MessageType;
    //发送人群头衔, 文本型, , , 发送者QQ群头衔
    etext FromQQPosition;
    //消息内容, 文本型, , , 消息内容
    etext MessageContent;
    //回复对象消息内容, 文本型, , , 如果是回复消息,这个变量保存回复的消息的信息
    etext replyContent;
    //气泡Id, 整数型, , , 发送者气泡id
    eint BubbleID;
    //发送人位置经度, 整数型
    eint FromQQNS;
    //发送人位置纬度, 整数型
    eint FromQQSW;
    //文件Id, 文本型
    etext FileID;
    //文件Md5, 字节集
    ebin FileMD5;
    //文件名, 文本型
    etext FileName;
    // 文件大小, 长整数型
    elong FileSize;
    //消息appid, 整数型, , , 消息appid
    eint MessageAppID;
};
*/

using EventData = volatile struct ed
{

    //框架QQ, 长整数型
    elong RobotQQ;
    //来源群号, 长整数型
    elong FromGroup;
    //操作QQ, 长整数型
    elong OperateQQ;
    //, 长整数型
    elong BeOperatedQQ;
    //消息Seq, 长整数型
    elong MessageSeq;
    //消息时间戳, 整数型
    eint MessageTimeStamp;
    // 来源群名, 文本型
    etext FromGroupName;
    // 操作QQ昵称, 文本型
    etext OperateQQNickName;
    // 触发QQ昵称, 文本型
    etext BeOperatedQQNickName;
    //消息内容, 文本型
    etext MessageContent;
    //消息类型, 整数型
    eint MessageType;
    //消息子类型, 整数型
    eint MessageTmpType;
};

/*

.数据类型 群成员信息, 公开, 
    .成员 账号, 文本型, , , 
    .成员 年龄, 整数型, , , 
    .成员 性别, 整数型, , , 
    .成员 昵称, 文本型, , , 
    .成员 邮箱, 文本型, , , 
    .成员 名片, 文本型, , , 
    .成员 备注, 文本型, , , 
    .成员 头衔, 文本型, , , 
    .成员 手机号, 文本型, , , 
    .成员 头衔到期时间, 长整数型, , , 
    .成员 禁言时间戳, 长整数型, , , 
    .成员 加群时间, 长整数型, , , 
    .成员 发言时间, 长整数型, , , 
    .成员 群等级, 长整数型, , , leve

.数据类型 群消息数据, 公开, 
    .成员 发送人QQ, 长整数型, , , 
    .成员 框架QQ, 长整数型, , , 
    .成员 消息Req, 整数型, , , 
    .成员 消息接收时间, 整数型, , , 
    .成员 消息群号, 长整数型, , , 
    .成员 来源群名称, 文本型, , , 消息来源群名(貌似失效了)
    .成员 发送人群名片, 文本型, , , 没有名片则为空白
    .成员 消息发送时间, 整数型, , , 消息发送时间
    .成员 消息Random, 长整数型, , , 消息random
    .成员 消息分片序列, 整数型, , , 
    .成员 消息分片数量, 整数型, , , 
    .成员 消息分片标识, 长整数型, , , 
    .成员 消息类型, 整数型, , , 消息subtype
    .成员 发送人群头衔, 文本型, , , 发送者QQ群头衔
    .成员 消息内容, 文本型, , , 消息内容
    .成员 回复对象消息内容, 文本型, , , 如果是回复消息,这个变量保存回复的消息的信息
    .成员 气泡Id, 整数型, , , 发送者气泡id
    .成员 发送人位置经度, 整数型, , , 
    .成员 发送人位置纬度, 整数型, , , 
    .成员 文件Id, 文本型, , , 
    .成员 文件Md5, 字节集, , , 
    .成员 文件名, 文本型, , , 
    .成员 文件大小, 长整数型, , , 
    .成员 消息appid, 整数型, , , 消息appid

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

.数据类型 事件消息数据, 公开, 
    .成员 框架QQ, 长整数型, , , 
    .成员 来源群号, 长整数型, , , 
    .成员 操作QQ, 长整数型, , , 
    .成员 触发QQ, 长整数型, , , 
    .成员 消息Seq, 长整数型, , , 
    .成员 消息时间戳, 整数型, , , 
    .成员 来源群名, 文本型, , , 
    .成员 操作QQ昵称, 文本型, , , 
    .成员 触发QQ昵称, 文本型, , , 
    .成员 消息内容, 文本型, , , 
    .成员 消息类型, 整数型, , , 
    .成员 消息子类型, 整数型, , , 

*/

template <typename FuncT>
inline FuncT *_f(Json api, const char *name);
#include "./app.util.hpp"

namespace HandlerBase
{
    // 好友消息事件
    int OnPrivateMessage(PrivateMessageData *pm);
    // 群消息事件
    int OnGroupMessage(GroupMessageData *gm);
    // 插件卸载事件（未知参数）
    int OnUninstall(void **);
    // 插件设置事件（未知参数）
    int OnSettings(void *);
    // 插件被启用事件（未知参数）
    int OnEnabled(void *);
    // 插件被禁用事件（未知参数）
    int OnDisabled(void *);
    // 事件事件
    int OnEvent(EventData *em);
}; // namespace HandlerBase

class Application
{
public:
    /**
     * @brief 载入插件关键字和系统回调函数指针
     * @param apidata 系统回调函数指针JSON
     * @param pluginkey 插件关键字
     */
    Application(etext apidata, etext pluginkey);
    ~Application();

    string getJSON();

public: //Api
        /*        //输出日志
    text addLog(text logContent, int textColor = 32768, int backColor = 16777215);
    //发送好友消息
    text sendFriendMessage(elong robotQQ,
 elong FriendQQ,
 text content,
 elong *Random = NULL,
 eint *Req = NULL);
    //发送群消息
    text sendGroupMessage(
        elong robotQQ,
        elong GroupQQ,
        text content,
        int hideName = false);
 */

    /**
     * @brief 输出日志
     * @param message 日志
     * @param text_color 文字颜色
     * @param background_color 背景颜色
     */
    string OutputLog(const string &message, int32_t text_color = 32768,
     int32_t background_color = 16777215);

    /**
     * @brief 发送好友消息
     * @param thisQQ 框架QQ
     * @param FriendQQ 好友QQ
     * @param content 发送内容
     * @param random 撤回消息用
     * @param req 撤回消息用
     * @return 成功返回的time用于撤回消息
     */
    string SendFriendMessage(int64_t thisQQ, int64_t FriendQQ,
  const string &content, int64_t *random = nullptr, int32_t *req = nullptr);

    /**
     * @brief 发送群消息
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param content 发送内容
     * @param anonymous 匿名发送
     */
    string SendGroupMessage(int64_t thisQQ, int64_t groupQQ,
 const string &content, bool anonymous = false);

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
    string SendGroupTemporaryMessage(int64_t thisQQ, int64_t groupQQ,
     int64_t otherQQ, const string &content,
     int64_t *random = nullptr, int32_t *req = nullptr);

    /**
     * @brief 添加好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @param verification 设置回答问题答案或是验证消息，多个问题答案用"|"分隔开
     */
    string AddFriend(int64_t thisQQ, int64_t otherQQ,
     const string &verification);

    /**
     * @brief 添加群（你在群内或需要付费入群也会直接发送验证消息）
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param verification 回答问题答案或是验证消息
     */
    string AddGroup(int64_t thisQQ, int64_t groupQQ,
    const string &verification);

    /**
     * @brief 删除好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     */
    string RemoveFriend(int64_t thisQQ, int64_t otherQQ);

    /**
     * @brief 设置屏蔽好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @param is_blocked 是否屏蔽
     */
    string SetBlockFriend(int64_t thisQQ, int64_t otherQQ,
 bool is_blocked);

    /**
     * @brief 设置特别关心好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @param is_special 是否屏蔽
     */
    string SetSpecialFriend(int64_t thisQQ, int64_t otherQQ,
 bool is_special);

    /**
     * @brief 发送好友JSON消息
     * @param thisQQ 框架QQ
     * @param FriendQQ 好友QQ
     * @param json_content json发送内容
     * @param random 撤回消息用
     * @param req 撤回消息用
     * @return 成功返回的time用于撤回消息
     */
    string SendFriendJSONMessage(int64_t thisQQ, int64_t FriendQQ,
 const string &json_content,
 int64_t *random = nullptr, int32_t *req = nullptr);

    /**
     * @brief 发送群JSON消息
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param json_content json发送内容
     * @param anonymous 匿名发送
     */
    string SendGroupJSONMessage(int64_t thisQQ, int64_t groupQQ,
const string &json_content, bool anonymous = false);

    /**
     * @brief 上传好友图片
     * @param thisQQ 框架QQ
     * @param FriendQQ 好友QQ
     * @param picture 图片数据
     * @param size 数据大小
     * @param is_flash 是否闪照
     * @return 成功返回图片代码
     */
    string UploadFriendImage(int64_t thisQQ, int64_t FriendQQ,
  const uint8_t *picture, size_t size, bool is_flash);

    /**
     * @brief 上传群图片
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param picture 图片数据
     * @param size 数据大小
     * @param is_flash 是否闪照
     * @return 成功返回图片代码
     */
    string UploadGroupImage(int64_t thisQQ, int64_t groupQQ,
 const uint8_t *picture, size_t size, bool is_flash = false);

    /**
     * @brief 上传好友语音
     * @param thisQQ 框架QQ
     * @param FriendQQ 好友QQ
     * @param audio 语音数据
     * @param size 数据大小
     * @param audio_type 语音类型 0：普通语音，1：变声语音，2：文字语音，3：红包匹配语音
     * @param audio_text 语音文字 文字语音填附加文字(貌似会自动替换为语音对应的文本),匹配语音填a、b、s、ss、sss，注意是小写
     * @return 成功返回语音代码
     */
    string UploadFriendAudio(int64_t thisQQ, int64_t FriendQQ,
  const uint8_t *audio, size_t size,
  int32_t audio_type = 0, const string &audio_text = "");

    /**
     * @brief 上传群语音
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param audio 语音数据
     * @param size 数据大小
     * @param audio_type 语音类型 0：普通语音，1：变声语音，2：文字语音，3：红包匹配语音
     * @param audio_text 语音文字 文字语音填附加文字(貌似会自动替换为语音对应的文本),匹配语音填a、b、s、ss、sss，注意是小写
     * @return 成功返回语音代码
     */
    string UploadGroupAudio(int64_t thisQQ, int64_t groupQQ,
 const uint8_t *audio, size_t size,
 int32_t audio_type = 0, const string &audio_text = "");

    /**
     * @brief 上传头像
     * @param thisQQ 框架QQ
     * @param picture 图片数据
     * @param size 数据大小
     */
    string UploadAvatar(int64_t thisQQ,
        const uint8_t *picture, size_t size);

    /**
     * @brief 设置群名片
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param otherQQ 群成员QQ
     * @param nickname 新名片
     */
    string SetGroupNickname(int64_t thisQQ,
 int64_t groupQQ, int64_t otherQQ, const string &nickname);

    /**
     * @brief 从缓存取昵称
     * @param otherQQ 对方QQ
     * @return 成功返回昵称
     */
    string GetNameFromCache(int64_t otherQQ);

    /**
     * @brief 从缓存取昵称
     * @param otherQQ 对方QQ
     * @return 成功返回昵称
     */
    string GetNameForce(int64_t otherQQ);

    /**
     * @brief 从缓存取群名（如果是框架QQ没加的群，[查询群信息]后也会记录缓存）
     * @param groupQQ 群号
     * @return 成功返回群名称
     */
    string GetGroupNameFromCache(int64_t groupQQ);

    /**
     * @brief 获取SKey
     * @param thisQQ 框架QQ
     * @return 成功返回SKey
     */
    string GetSKey(int64_t thisQQ);

    /**
     * @brief 获取PSKey
     * @param thisQQ 框架QQ
     * @param domain 域: tenpay.com;openmobile.qq.com;docs.qq.com;connect.qq.com;qzone.qq.com;vip.qq.com;gamecenter.qq.com;qun.qq.com;game.qq.com;qqweb.qq.com;ti.qq.com;office.qq.com;mail.qq.com;mma.qq.com
     * @return 成功返回PSKey
     */
    string GetPSKey(int64_t thisQQ, const string &domain);

    /**
     * @brief 获取ClientKey
     * @param thisQQ 框架QQ
     * @return 成功返回ClientKey
     */
    string GetClientKey(int64_t thisQQ);

    /**
     * @brief 获取框架QQ
     */
    string GetThisQQ();

    /**
     * @brief 获取好友列表
     * @param thisQQ 框架QQ
     * @return 成功返回好友数量，失败或无权限返回0
     */
    // int GetFriendList(uint64_t thisQQ,vector<FriendInformation> &array);

    /*


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
.参数 框架QQ, 长整数型, , 
.参数 来源群号, 长整数型, , 
.参数 触发QQ, 长整数型, , 
.参数 消息Seq, 长整数型, , 
.参数 操作类型, 整数型, , 11同意 12拒绝  14忽略
.参数 事件类型, 整数型, , #群事件_某人申请加群/#群事件_我被邀请加入群

调用子程序 (到整数 (j.取长整数 (“处理群验证事件”)), , , pluginkey, 框架QQ, 来源群号, 触发QQ, 消息Seq, 操作类型, 事件类型)

.子程序 处理好友验证事件, , 公开, 在好友验证事件下使用，无权限时不执行
.参数 框架QQ, 长整数型, , 
.参数 触发QQ, 长整数型, , 
.参数 消息Seq, 长整数型, , 
.参数 操作类型, 整数型, , 1同意 2拒绝

调用子程序 (到整数 (j.取长整数 (“处理好友验证事件”)), , , pluginkey, 框架QQ, 触发QQ, 消息Seq, 操作类型)


.子程序 查看转发聊天记录内容, , 公开, 私聊消息也可以使用此命令解析，无权限时不执行
.参数 框架QQ, 长整数型, , 
.参数 resId, 文本型, , 可在xml消息代码中取到
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
.参数 sun, 整数型, 可空, 当main=11时，可进一步设置 0普通在线 1000我的电量 1011信号弱 1024在线学习 1025在家旅游 1027TiMi中 1016睡觉中 1017游戏中 1018学习中 1019吃饭中 1021煲剧中 1022度假中 1032熬夜中 1050打球中 1051恋爱中 1052我没事 1028我在听歌
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
.参数 FileId, 文本型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (“群文件转发至群”)), , ret, pluginkey, 框架QQ, 来源群号, 目标群号, FileId)
返回 (ret)

.子程序 群文件转发至好友, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 来源群号, 长整数型, , 
.参数 目标QQ, 长整数型, , 
.参数 FileId, 文本型, , 
.参数 Filename, 文本型, , 
.参数 Req, 整数型, 参考 可空, 撤回消息用
.参数 Random, 长整数型, 参考 可空, 撤回消息用
.参数 time, 整数型, 参考 可空, 撤回消息用

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (“群文件转发至好友”)), , ret, pluginkey, 框架QQ, 来源群号, 目标QQ, FileId, Filename, Req, Random, time)
返回 (ret)

.子程序 好友文件转发至好友, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 来源QQ, 长整数型, , 
.参数 目标QQ, 长整数型, , 
.参数 FileId, 文本型, , 
.参数 Filename, 文本型, , 
.参数 Req, 整数型, 参考 可空, 撤回消息用
.参数 Random, 整数型, 参考 可空, 撤回消息用
.参数 time, 整数型, 参考 可空, 撤回消息用

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (“好友文件转发至好友”)), , ret, pluginkey, 框架QQ, 来源QQ, 目标QQ, FileId, Filename, Req, Random, time)
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

protected:
    Json j;
    string api_key;
};

//这就是传说中的全局api对象。你的api都是从这里调用的
extern Application *app;