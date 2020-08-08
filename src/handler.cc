#include "sdk/app.hpp"
#include <fstream>
#include <iostream>
#include <windows.h>
#include "include/encode.hpp"
#include <stdio.h>

using string = std::string; // 省写std::

// 好友消息事件
int HandlerBase::OnPrivateMessage(PrivateMessageData *pm)
{
    string msg = code::UTF8Encode(pm->MessageContent);
    if(msg == "测试")
    {
        app->OutputLog("日志测试");
        app->OutputLog("好友消息测试");
        app->SendFriendMessage(pm->ThisQQ, pm->SenderQQ, R"(
            愿你在我看不到的地方安然无恙，
            愿你的冬天永远不缺暖阳。
            愿你的明天不再经历雨打风霜，
            愿你的未来永远热泪盈眶。
        )");
        app->OutputLog("好友消息测试成功");
    }
    return 0;
}

// 群消息事件
int HandlerBase::OnGroupMessage(GroupMessageData *gm){
    if(string(gm->MessageContent) == code::UTF8Decode("测试")){
        
    }
    return 0;    
}

// 插件卸载事件（未知参数）
int HandlerBase::OnUninstall(void **){
    // 清除app对象避免内存泄漏
    delete app;
    return 0;
}

// 插件设置事件（未知参数），这里可以弹出对话框
int HandlerBase::OnSettings(void*){
    return 0;
}

// 插件被启用事件（未知参数）
int HandlerBase::OnEnabled(void*){
    return 0;
}

// 插件被禁用事件（未知参数）
int HandlerBase::OnDisabled(void*){
    return 0;
}

// 事件消息
int HandlerBase::OnEvent(EventData* em){
    return 0;
}
