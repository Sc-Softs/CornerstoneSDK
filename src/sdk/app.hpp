#pragma once

#pragma pack(4)

#include <cstdint>

#include "../include/json.hpp"
#include "../include/encode.hpp"
#include <vector>

#define EXPORT_FN(TYPE) extern "C" TYPE __stdcall
using Json = nlohmann::json;
using string = std::string;
using text = const char *; //const char *; //避免写这么长的东西

using uint8_t = std::uint8_t;
using int8_t = std::int8_t;
using int16_t = std::int16_t;
using uint32_t = std::uint32_t;
using int32_t = std::int32_t;
using int64_t = std::int64_t;

// 方便区分C++原生类型和易语言类型
using ebyte = uint8_t;  // 易语言字节型
using eshort = int16_t;  // 易语言短整数型
using eint = int32_t;  // 易语言整数型
using elong = int64_t;  // 易语言长整数型
using efloat = float;  // 易语言小数型
using edouble = double;  // 易语言双精度小数型
using edate = uint64_t;  // 易语言日期时间型
using ebool = int32_t;  // 易语言逻辑型
using etext = const char*;  // 易语言文本型(GB2312)
using ebin = const uint8_t*;  // 易语言字节集
using esubptr = uint32_t;  // 易语言子程序指针

constexpr ebool etrue = 1;
constexpr ebool efalse = 0;

inline ebool bool2ebool(const bool& b)
{
    return b ? etrue : efalse;
}

inline bool ebool2bool(const ebool& eb)
{
    return eb == etrue;
}

inline ebool b2e(const bool &b){
    return bool2ebool(b);
}

inline bool e2b(const ebool &b){
    return ebool2bool(b);
}

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

template <typename FuncT>
inline FuncT* _f(Json api, const char* name);
#include "./app.util.hpp"

namespace HandlerBase
{
    using private_msg = volatile struct private_msg_struct
    {
        elong senderQQ;           //8
        elong robotQQ;            //8
        eint msgReq;             //4
        elong msgSeq;             //8
        eint msgRecvTime;        //消息接收时间 4
        elong msgGroup;           //8 当为群临时会话时可取
        eint msgSendTime;        //4
        elong msgRandom;          //8 消息random
        eint msgPartNum;         //4 消息分片序列
        eint msgPartCount;       //4
        elong msgPartID;          //8
        etext msgContent;          //消息内容
        eint bubbleId;           // 发送人气泡id
        eint msgType;            //消息type
        eint msgSubType;         //消息subtype
        eint msgSubTmpType;      // 0 群 1 讨论组 129 腾讯公众号 201 QQ咨询
        eint redPackType;        //整数型, , , 红包类型 : 2已转入余额 4点击收款 10红包
        void *sessionToen;        //会话Token
        elong fromEventQQ;        //来源事件QQ
        etext fromEventQQNickName; //来源事件QQ昵称
        etext fileID;              //文件Id
        void *fileMD5;            //文件Md5
        etext fileName;            //文件名
        elong fileSize;           //文件大小  ?只有传文件才有。
    };
    int OnPrivateMsg(private_msg *pm);
    //int onPrivateMsg(void* sz);
    using group_msg = volatile struct group_msg_struct
    {
        elong senderQQ; //8zijie ?
        elong robotQQ;
        eint msgReq;
        eint msgRecvTime;   //消息接收时间
        elong fromGroup;     //消息群号
        etext fromGroupName;  //来源群名称, 文本型, , , 消息来源群名(貌似失效了)
        etext fromQQCard;     //发送人群名片, 文本型, , , 没有名片则为空白
        eint msgSendTime;   //消息发送时间, 整数型, , , 消息发送时间
        elong msgRandom;     //消息Random, 长整数型, , , 消息random
        eint msgPartNum;    // 消息分片序列, 整数型
        eint msgPartCount;  //消息分片数量, 整数型
        elong msgPartID;     //消息分片标识, 长整数型
        eint msgType;       //消息类型, 整数型, , , 消息subtype
        etext fromQQPosition; //发送人群头衔, 文本型, , , 发送者QQ群头衔
        etext msgContent;     //消息内容, 文本型, , , 消息内容
        etext replyContent;   //回复对象消息内容, 文本型, , , 如果是回复消息,这个变量保存回复的消息的信息
        eint bubbleId;      //气泡Id, 整数型, , , 发送者气泡id
        eint fromQQNS;      //发送人位置经度, 整数型
        eint fromQQSW;      //发送人位置纬度, 整数型
        etext fileID;         //文件Id, 文本型
        void *fileMD5;       //文件Md5, 字节集
        etext fileName;       //文件名, 文本型
        elong fileSize;      // 文件大小, 长整数型
        eint msgAppID;      //消息appid, 整数型, , , 消息appid
    };

    int OnGroupMsg(group_msg *gm);

    //我也不知道参数啥结构
    int OnUninstall(void **);

    //我也不知道传入的是啥
    int OnSettings(void *);
    
    //插件被启用事件
    int OnEnabled(void*);
    //插件被禁用事件
    int OnDisabled(void*);

    using event_message = volatile struct event_message_struct
    {

        elong robotQQ;             //, 长整数型
        elong fromGroup;           //来源群号, 长整数型
        elong operateQQ;           //操作QQ, 长整数型
        elong beOperatedQQ;        //, 长整数型
        elong msgSeq;              //消息Seq, 长整数型
        eint msgTimeStamp;        //消息时间戳, 整数型
        etext fromGroupName;        // 来源群名, 文本型
        etext operateQQNickName;    // 操作QQ昵称, 文本型
        etext beOperatedQQNickName; // 触发QQ昵称, 文本型
        etext msgContent;           //消息内容, 文本型
        eint msgType;             //消息类型, 整数型
        eint msgTmpType;          //消息子类型, 整数型
    };
    //事件消息
    int OnEvent(event_message* em);
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
    text sendFriendMsg(elong robotQQ,
                       elong friendQQ,
                       text content,
                       elong *Random = NULL,
                       eint *Req = NULL);
    //发送群消息
    text sendGroupMsg(
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
    string OutputLog(const string& message, int32_t text_color = 32768,
        int32_t background_color = 16777215);

    /**
     * @brief 发送好友消息
     * @param thisQQ 框架QQ
     * @param friendQQ 好友QQ
     * @param content 发送内容
     * @param random 撤回消息用
     * @param req 撤回消息用
     * @return 成功返回的time用于撤回消息
     */
    string SendFriendMessage(int64_t thisQQ, int64_t friendQQ,
        const string& content, int64_t* random = nullptr, int32_t* req = nullptr);

    /**
     * @brief 发送群消息
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param content 发送内容
     * @param anonymous 匿名发送
     */
    string SendGroupMessage(int64_t thisQQ, int64_t groupQQ,
        const string& content, bool anonymous = false);

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
        int64_t otherQQ, const string& content,
        int64_t* random = nullptr, int32_t* req = nullptr);

    /**
     * @brief 添加好友
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @param verification 设置回答问题答案或是验证消息，多个问题答案用"|"分隔开
     */
    string AddFriend(int64_t thisQQ, int64_t otherQQ,
        const string& verification);

    /**
     * @brief 添加群（你在群内或需要付费入群也会直接发送验证消息）
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param verification 回答问题答案或是验证消息
     */
    string AddGroup(int64_t thisQQ, int64_t groupQQ,
        const string& verification);

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
     * @param friendQQ 好友QQ
     * @param json_content json发送内容
     * @param random 撤回消息用
     * @param req 撤回消息用
     * @return 成功返回的time用于撤回消息
     */
    string SendFriendJSONMessage(int64_t thisQQ, int64_t friendQQ,
        const string& json_content,
        int64_t* random = nullptr, int32_t* req = nullptr);

    /**
     * @brief 发送群JSON消息
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param json_content json发送内容
     * @param anonymous 匿名发送
     */
    string SendGroupJSONMessage(int64_t thisQQ, int64_t groupQQ,
        const string& json_content, bool anonymous = false);

    /**
     * @brief 上传好友图片
     * @param thisQQ 框架QQ
     * @param friendQQ 好友QQ
     * @param picture 图片数据
     * @param size 数据大小
     * @param is_flash 是否闪照
     * @return 成功返回图片代码
     */
    string UploadFriendImage(int64_t thisQQ, int64_t friendQQ,
        const uint8_t* picture, size_t size, bool is_flash);

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
        const uint8_t* picture, size_t size, bool is_flash = false);

    /**
     * @brief 上传好友语音
     * @param thisQQ 框架QQ
     * @param friendQQ 好友QQ
     * @param audio 语音数据
     * @param size 数据大小
     * @param audio_type 语音类型 0：普通语音，1：变声语音，2：文字语音，3：红包匹配语音
     * @param audio_text 语音文字 文字语音填附加文字(貌似会自动替换为语音对应的文本),匹配语音填a、b、s、ss、sss，注意是小写
     * @return 成功返回语音代码
     */
    string UploadFriendAudio(int64_t thisQQ, int64_t friendQQ,
        const uint8_t* audio, size_t size,
        int32_t audio_type = 0, const string& audio_text = "");

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
        const uint8_t* audio, size_t size,
        int32_t audio_type = 0, const string& audio_text = "");

    /**
     * @brief 上传头像
     * @param thisQQ 框架QQ
     * @param picture 图片数据
     * @param size 数据大小
     */
    string UploadAvatar(int64_t thisQQ,
        const uint8_t* picture, size_t size);
    

protected:
    Json j;
    string api_key;
};

extern Application *app;