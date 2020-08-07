#include "app.hpp"
#include "../config.h"

Application::Application(etext apidata, etext pluginkey)
{
    this->api_key = pluginkey;
    this->j = Json::parse(code::UTF8Encode(apidata));
}
std::string Application::getJSON()
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
    for (auto i : apiList)
    {
        json_info["data"]["needapilist"][i] = Json({{"state", "1"},
                                                    {"safe", "1"},
                                                    {"desc", "需要此权限运行插件"}});
    }
    
    return json_info.dump();
}

text Application::addLog(text logContent, int textColor, int backColor)
{
    return code::UTF8Encode(_f
    <text(*)(etext, etext, eint, eint)>
    (j, "输出日志")
    (this->api_key, logContent, textColor, backColor));
    /*
    using add_log_fun = text(
        text api_key,
        text logContent,
        int textColor,
        int backColor);
    add_log_fun *fn = (add_log_fun *)((unsigned long)(j["输出日志"]));
    return fn(this->api_key.c_str(), logContent, textColor, backColor);
    */
}

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

Application::~Application()
{
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