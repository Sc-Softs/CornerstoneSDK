#include "sdk/app.hpp"
#include <fstream>
#include <iostream>
#include <windows.h>
#include "include/encode.hpp"
#include <stdio.h>
#include "include/unpack.hpp"

using string = std::string; //省写std

//收到私聊消息，使用 unpack::private_msg读取数据
int   HandlerBase::onPrivateMsg(void *pm)
{
    private_msg_struct pms;
    unpack::private_msg(pms,pm);
    if(string(pms.msgContent) == code::UTF8Decode("测试") ){
        app->sendFriendMsg(pms.robotQQ,pms.senderQQ,R"(
            愿你在我看不到的地方安然无恙，
            愿你的冬天永远不缺暖阳。
            愿你的明天不再经历雨打风霜，
            愿你的未来永远热泪盈眶。
        )");
    }
    return 0;
}

//收到群消息 使用unpack里面的东西读取数据
int  HandlerBase::onGroupMsg(void *group_msg){
    return 0;    
}

//插件卸载事件，这里清除app对象避免内存泄漏
int HandlerBase::onUninstall(void **){
    delete app;
    return 0;
}

//设置按钮被点击事件，这里可以DlgBox弹出对话框
int HandlerBase::onSettings(void*){
    return 0;
}

//事件消息事件，使用unpack对应的方法读数据
int HandlerBase::onEvent(void* em){
return 0;
}

//插件被启用的事件
int HandlerBase::onEnabled(void*){
    return 0;
}
//插件被禁用事件
int HandlerBase::onDisabled(void*){
    return 0;
}