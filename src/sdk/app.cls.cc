#define USE_E
#include "app.hpp"
#include "../config.h"


/**
 * @brief 载入插件关键字和系统回调函数指针
 * @param apidata 系统回调函数指针JSON
 * @param pluginkey 插件关键字
 */
Application::Application(etext apidata, etext pluginkey)
    : api_key(code::UTF8Encode(pluginkey)), j(Json::parse(code::UTF8Encode(apidata)))
{ }

Application::~Application()
{
}

const char* Application::getJSON()
{
    Json json_info = Json::parse(JSON_PART);

#ifdef ENABLE_PRIVATE_MSG
    json_info["friendmsaddres"] = (unsigned long)&HandlerBase::onPrivateMsg;
#endif

#ifdef ENABLE_GROUP_MSG
    json_info["groupmsaddres"] = (unsigned long)&HandlerBase::onGroupMsg;
#endif

#ifdef  ENABLE_PLUGIN_SETTINGS
    json_info["setproaddres"] = (unsigned long)&HandlerBase::onSettings;
#endif

#ifdef ENABLE_PLUGIN_ENABLED
    json_info["useproaddres"] = (unsigned long)&HandlerBase::onEnabled;
#endif

#ifdef ENABLE_PLUGIN_DISABLED
    json_info["banproaddres"] = (unsigned long)&HandlerBase::onDisabled;
#endif

    //自动生成的API列表
    for (auto i : authList)
    {
        json_info["data"]["needapilist"][i] = Json({{"state", "1"},
                                                    {"safe", "1"},
                                                    {"desc", "需要此权限运行插件"}});
    }
    
    return json_info.dump().c_str();
}

/*
text Application::sendFriendMsg(INT64 robotQQ,
                                INT64 friendQQ,
                                text content,
                                INT64 *Random,
                                INT32 *Req)
{

    using send_friend_fun = text(
        text api_key,
        INT64 robotQQ,
        INT64 friendQQ,
        text content,
        INT64 *,
        INT32 *);
    INT64 a = 0;
    INT32 b = 0;
    //判断是否为NULL的简写
    if (Random && Req)
    {
        a = *Random;
        b = *Req;
    }
    send_friend_fun *fn = (send_friend_fun *)((unsigned long)(j["发送好友消息"]));
    return fn(this->api_key.c_str(), robotQQ, friendQQ, code::UTF8Decode(content).c_str(), &a, &b);
}

text Application::sendGroupMsg(
    INT64 robotQQ,
    INT64 GroupQQ,
    text content,
    int hideName)
{
    using send_group_fun = text(
        text api_key,
        INT64 robotQQ,
        INT64 GroupQQ,
        text content,
        bool hideName);
    send_group_fun *fn = (send_group_fun *)((unsigned long)(j["发送群消息"]));
    std::string s = code::UTF8Decode(content);
    return fn(this->api_key.c_str(), robotQQ, GroupQQ, s.c_str(), hideName);
}
*/

/**
 * @brief 输出日志
 * @param message 日志
 * @param text_color 文字颜色
 * @param background_color 背景颜色
 */
string Application::OutputLog(const string& message, int32_t text_color,
    int32_t background_color)
{
    return e2s(_f
        <etext(etext, etext, eint, eint)>
        (this->j, "输出日志")
        (s2e(this->api_key), s2e(message.c_str()), text_color, background_color));
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
string Application::SendFriendMessage(int64_t thisQQ, int64_t friendQQ,
    const string& content, int64_t* random, int32_t* req)
{
    return e2s(_f
        <etext(etext, elong, elong, etext,
            elong, eint)>
        (this->j, "发送好友消息")
        (s2e(this->api_key), thisQQ, friendQQ, s2e(content.c_str()),
            random ? *random : 0, req ? *req : 0));
}

/**
 * @brief 发送群消息
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param content 发送内容
 * @param anonymous 匿名发送
 */
string Application::SendGroupMessage(int64_t thisQQ, int64_t groupQQ,
    const string& content, bool anonymous)
{
    return e2s(_f
        <etext(etext, elong, elong, etext, bool)>
        (this->j, "发送群消息")
        (s2e(this->api_key), thisQQ, groupQQ, s2e(content.c_str()),
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
string Application::SendGroupTemporaryMessage(int64_t thisQQ, int64_t groupQQ,
    int64_t otherQQ, const string& content,
    int64_t* random, int32_t* req)
{
    return e2s(_f
        <etext(etext, elong, elong, elong, etext,
            elong**, eint**)>
        (this->j, "发送群临时消息")
        (s2e(this->api_key), thisQQ, groupQQ, otherQQ, s2e(content.c_str()),
            &random, &req));
}

/**
 * @brief 添加好友
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 * @param verification 设置回答问题答案或是验证消息，多个问题答案用"|"分隔开
 */
string Application::AddFriend(int64_t thisQQ, int64_t otherQQ,
    const string& verification)
{
    return e2s(_f
        <etext(etext, elong, elong, etext)>
        (this->j, "添加好友")
        (s2e(this->api_key), thisQQ, otherQQ, s2e(verification.c_str())));
}

/**
 * @brief 添加群（你在群内或需要付费入群也会直接发送验证消息）
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param verification 回答问题答案或是验证消息
 */
string Application::AddGroup(int64_t thisQQ, int64_t groupQQ,
    const string& verification)
{
    return e2s(_f
        <etext(etext, elong, elong, etext)>
        (this->j, "添加群")
        (s2e(this->api_key), thisQQ, groupQQ, s2e(verification.c_str())));
}

/**
 * @brief 删除好友
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 */
string Application::RemoveFriend(int64_t thisQQ, int64_t otherQQ)
{
    return e2s(_f
        <etext(etext, elong, elong)>
        (this->j, "添加群")
        (s2e(this->api_key), thisQQ, otherQQ));
}

/**
 * @brief 设置屏蔽好友
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 * @param is_blocked 是否屏蔽
 */
string Application::SetBlockFriend(int64_t thisQQ, int64_t otherQQ,
    bool is_blocked)
{
    return e2s(_f
        <etext(etext, elong, elong, ebool)>
        (this->j, "置屏蔽好友")
        (s2e(this->api_key), thisQQ, otherQQ,
            b2e(is_blocked)));
}

/**
 * @brief 设置特别关心好友
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 * @param is_special 是否屏蔽
 */
string Application::SetSpecialFriend(int64_t thisQQ, int64_t otherQQ,
    bool is_special)
{
    return e2s(_f
        <etext(etext, elong, elong, ebool)>
        (this->j, "置特别关心好友")
        (s2e(this->api_key), thisQQ, otherQQ,
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
string Application::SendFriendJSONMessage(int64_t thisQQ, int64_t friendQQ,
    const string& json_content,
    int64_t* random, int32_t* req)
{
    return e2s(_f
        <etext(etext, elong, elong, etext,
            elong**, eint**)>
        (this->j, "发送好友json消息")
        (s2e(this->api_key), thisQQ, friendQQ, s2e(json_content),
            &random, &req));
}

/**
 * @brief 发送群JSON消息
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param json_content json发送内容
 * @param anonymous 匿名发送
 */
string Application::SendGroupJSONMessage(int64_t thisQQ, int64_t groupQQ,
    const string& json_content, bool anonymous)
{
    return e2s(_f
        <etext(etext, elong, elong, etext, bool)>
        (this->j, "发送群json消息")
        (s2e(this->api_key), thisQQ, groupQQ,
            s2e(json_content), anonymous));
}

/**
 * @brief 上传好友图片
 * @param thisQQ 框架QQ
 * @param friendQQ 好友QQ
 * @param picture 图片数据
 * @param is_flash 是否闪照
 * @return 成功返回图片代码
 */
string Application::UploadFriendImage(int64_t thisQQ, int64_t friendQQ,
    const uint8_t* picture, size_t length, bool is_flash)
{
    return e2s(_f
        <etext(etext, elong, elong, ebool, ebin, eint)>
        (this->j, "上传好友图片")
        (s2e(this->api_key), thisQQ, friendQQ, b2e(is_flash),
            picture, static_cast<eint>(length)));
}

/**
 * @brief 上传群图片
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param picture 图片数据
 * @param is_flash 是否闪照
 * @return 成功返回图片代码
 */
string Application::UploadGroupImage(int64_t thisQQ, int64_t groupQQ,
    const uint8_t* picture, size_t size, bool is_flash)
{
    return e2s(_f
        <etext(etext, elong, elong, ebool, ebin, eint)>
        (this->j, "上传群图片")
        (s2e(this->api_key), thisQQ, groupQQ, b2e(is_flash),
            picture, static_cast<eint>(size)));
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
string Application::UploadFriendAudio(int64_t thisQQ, int64_t friendQQ,
    const uint8_t* audio, size_t size,
    int32_t audio_type, const string& audio_text)
{
    return e2s(_f
        <etext(etext, elong, elong, eint, etext, ebin, eint)>
        (this->j, "上传好友语言")
        (s2e(this->api_key), thisQQ, friendQQ, audio_type, s2e(audio_text),
            audio, static_cast<eint>(size)));
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
string Application::UploadGroupAudio(int64_t thisQQ, int64_t groupQQ,
    const uint8_t* audio, size_t size,
    int32_t audio_type, const string& audio_text)
{
    return e2s(_f
        <etext(etext, elong, elong, eint, etext, ebin, eint)>
        (this->j, "上传群语音")
        (s2e(this->api_key), thisQQ, groupQQ, audio_type, s2e(audio_text),
            audio, static_cast<eint>(size)));
}

/**
 * @brief 上传头像
 * @param thisQQ 框架QQ
 * @param picture 图片数据
 * @param size 图片大小534
 */
string Application::UploadAvatar(int64_t thisQQ, const uint8_t* picture, size_t size)
{
    return e2s(_f
        <etext(etext, elong, ebin, eint)>
        (this->j, "上传头像")
        (s2e(this->api_key), thisQQ, picture, static_cast<eint>(size)));
}
