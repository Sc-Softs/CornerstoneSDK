#include "sdk/sdk.h"
#include <cstdint>
#include <string>
using namespace std;

// Cornerstone SDK 的部分 API 尚未经过测试，可能仍存在漏洞
// 欢迎前往 https://github.com/Sc-Softs/CornerstoneSDK 提交Issue和PR，感谢您的贡献

// 请勿在事件处理函数中执行上传文件等耗时操作，此类操作请另开线程执行

// 私聊消息事件
EventProcessEnum OnPrivateMessage(PrivateMessageData &data)
{
    // 序列从0开始，过滤腾讯长消息自动分片的片段内容，你也可以删除这里来获取分片片段内容
    if (data.MessageClipID > 0 && data.MessageClip + 1 != data.MessageClipCount)
    {
        return EventProcessEnum::Ignore;
    }
    // 不处理自己发送的消息
    if (data.ThisQQ == data.SenderQQ)
    {
        return EventProcessEnum::Ignore;
    }

    // 这部分判断消息类型，本例中只处理群临时消息和好友普通消息
    bool shouldHandle = false;
    if (data.MessageType == MessageTypeEnum::FriendUsualMessage)
    {
        // 消息子类型目前没有用到，判断是否为普通消息需要通过红包类型=0判断
        if (data.RedEnvelopeType == 0)
        {
            shouldHandle = true;
        }
    }
    else if (data.MessageType == MessageTypeEnum::Temporary)
    {
        if (data.MessageSubTemporaryType == MessageSubTypeEnum::Temporary_Group)
        {
            shouldHandle = true;
        }
    }
    if (!shouldHandle)
    {
        return EventProcessEnum::Ignore;
    }

    std::string content = data.MessageContent;
    std::string ret;
    if (content == "CornerstoneSDK测试")
    {
        api->OutputLog("好友消息测试");
        ret = "好友消息测试";
    }
    else if (content == "CornerstoneSDK测试好友列表")
    {
        vector<FriendInformation> friend_list;
        auto size = api->GetFriendList(data.ThisQQ, friend_list);
        if (size == 0)
        {
            api->OutputLog("好友列表获取失败: 返回的size为0");
            ret = "好友列表获取失败: 返回的size为0";
        }
        else
        {
            api->OutputLog(sum_string("好友列表获取成功: 返回的size为", size));
            string friends;
            for (auto friend_info : friend_list)
            {
                friends += sum_string(friend_info.QQNumber, ": ", friend_info.Name, "\n");
            }
            ret = friends;
        }
    }
    else if (content == "CornerstoneSDK测试群列表")
    {
        vector<GroupInformation> group_list;
        auto size = api->GetGroupList(data.ThisQQ, group_list);
        if (size == 0)
        {
            api->OutputLog("群列表获取失败: 返回的size为0");
            ret = "群列表获取失败: 返回的size为0";
        }
        else
        {
            api->OutputLog(sum_string("群列表获取成功: 返回的size为", size));
            string groups;
            for (auto group_info : group_list)
            {
                groups += sum_string(group_info.GroupQQ, ": ", group_info.GroupName, "\n");
            }
            ret = groups;
        }
    }

    // 根据不同的消息来源调用不同的发送信息api
    if (data.MessageType == MessageTypeEnum::FriendUsualMessage)
    {
        api->SendFriendMessage(data.ThisQQ, data.SenderQQ, ret);
    }
    else if (data.MessageType == MessageTypeEnum::Temporary && data.MessageSubTemporaryType == MessageSubTypeEnum::Temporary_Group)
    {
        api->SendGroupTemporaryMessage(data.ThisQQ, data.MessageGroupQQ, data.SenderQQ, ret);
    }

    // 已经处理过的消息返回Block阻止其他插件继续处理
    return EventProcessEnum::Block;
}

// 群消息事件
EventProcessEnum OnGroupMessage(GroupMessageData &data)
{
    // 序列从0开始，过滤腾讯长消息自动分片的片段内容，你也可以删除这里来获取分片片段内容
    if (data.MessageClipID > 0 && data.MessageClip + 1 != data.MessageClipCount)
    {
        return EventProcessEnum::Ignore;
    }
    // 不处理自己发送的消息
    if (data.ThisQQ == data.SenderQQ)
    {
        return EventProcessEnum::Ignore;
    }
    // 只处理普通群聊信息
    if (data.MessageType != MessageTypeEnum::GroupUsualMessage)
    {
        return EventProcessEnum::Ignore;
    }

    std::string content = data.MessageContent;
    if (content == "CornerstoneSDK测试")
    {
        api->OutputLog("群消息测试");
        api->SendGroupMessage(data.ThisQQ, data.MessageGroupQQ, "群消息测试");
        auto retcode = get_retcode(api->SendGroupTemporaryMessage(data.ThisQQ, data.MessageGroupQQ, data.SenderQQ, "临时消息测试"));
        if (retcode != 0)
        {
            api->OutputLog(sum_string("临时消息发送失败: ", retcode));
        }
    }
    else if (content == "CornerstoneSDK测试取群成员列表")
    {
        vector<GroupMemberInformation> member_list;
        auto size = api->GetGroupMemberList(data.ThisQQ, data.MessageGroupQQ, member_list);
        if (size == 0)
        {
            api->OutputLog("群成员列表获取失败: 返回的size为0");
            api->SendGroupMessage(data.ThisQQ, data.MessageGroupQQ, "群成员列表获取失败: 返回的size为0");
        }
        else
        {
            api->OutputLog(sum_string("群成员列表获取成功: 返回的size为", size));
            string members;
            // 最多只显示5个群成员
            int max = (int)member_list.size();
            if (max > 5) max = 5;
            for (int i = 0; i < max; i++)
            {
                auto member_info = member_list[i];
                members += sum_string(member_info.QQNumber, ": ", member_info.Name, "\n");
            }
            api->SendGroupMessage(data.ThisQQ, data.MessageGroupQQ, members);
        }
    }

    // 已经处理过的消息返回Block阻止其他插件继续处理
    return EventProcessEnum::Block;
}

// 插件卸载事件
EventProcessEnum OnUninstall()
{
    delete api; // 清除全局API对象避免内存泄漏
    return EventProcessEnum::Ignore;
}

// 插件设置事件 这里可以弹出对话框
EventProcessEnum OnSettings()
{
    return EventProcessEnum::Ignore;
}

// 插件被启用事件
EventProcessEnum OnEnabled()
{
    api->OutputLog(sum_string("插件数据目录：", api->GetPluginDataDirectory()));
    return EventProcessEnum::Ignore;
}

// 插件被禁用事件
EventProcessEnum OnDisabled()
{
    return EventProcessEnum::Ignore;
}

// 事件消息
EventProcessEnum OnEvent(EventData &data)
{
    if (data.SourceGroupQQ == 0) // 非群事件
    {
        switch (data.EventType)
        {
        // 好友事件_被好友删除
        case EventTypeEnum::Friend_Removed:
            break;
        // 好友事件_签名变更
        case EventTypeEnum::Friend_SignatureChanged:
            break;
        // 好友事件_昵称改变
        case EventTypeEnum::Friend_NameChanged:
            break;
        // 好友事件_某人撤回事件
        case EventTypeEnum::Friend_UserUndid:
            break;
        // 好友事件_有新好友
        case EventTypeEnum::Friend_NewFriend:
            break;
        // 好友事件_好友请求
        case EventTypeEnum::Friend_FriendRequest:
            break;
        // 好友事件_对方同意了您的好友请求
        case EventTypeEnum::Friend_FriendRequestAccepted:
            break;
        // 好友事件_对方拒绝了您的好友请求
        case EventTypeEnum::Friend_FriendRequestRefused:
            break;
        // 好友事件_资料卡点赞
        case EventTypeEnum::Friend_InformationLiked:
            break;
        // 好友事件_签名点赞
        case EventTypeEnum::Friend_SignatureLiked:
            break;
        // 好友事件_签名回复
        case EventTypeEnum::Friend_SignatureReplied:
            break;
        // 好友事件_个性标签点赞
        case EventTypeEnum::Friend_TagLiked:
            break;
        // 好友事件_随心贴回复
        case EventTypeEnum::Friend_StickerLiked:
            break;
        // 好友事件_随心贴增添
        case EventTypeEnum::Friend_StickerAdded:
            break;
        // 空间事件_与我相关
        case EventTypeEnum::QZone_Related:
            break;
        // 框架事件_登录成功
        case EventTypeEnum::This_SignInSuccess:
            break;
        // 其他事件
        default:
            break;
        }
    }
    else // 群事件
    {
        switch (data.EventType)
        {
        // 群事件_我被邀请加入群
        case EventTypeEnum::Group_Invited:
            break;
        // 群事件_某人加入了群
        case EventTypeEnum::Group_MemberJoined:
            break;
        // 群事件_某人申请加群
        case EventTypeEnum::Group_MemberVerifying:
            break;
        // 群事件_群被解散
        case EventTypeEnum::Group_GroupDissolved:
            break;
        // 群事件_某人退出了群
        case EventTypeEnum::Group_MemberQuit:
            break;
        // 群事件_某人被踢出群
        case EventTypeEnum::Group_MemberKicked:
            break;
        // 群事件_某人被禁言
        case EventTypeEnum::Group_MemberShutUp:
            break;
        // 群事件_某人撤回事件
        case EventTypeEnum::Group_MemberUndid:
            break;
        // 群事件_某人被取消管理
        case EventTypeEnum::Group_AdministratorTook:
            break;
        // 群事件_某人被赋予管理
        case EventTypeEnum::Group_AdministratorGave:
            break;
        // 群事件_开启全员禁言
        case EventTypeEnum::Group_EnableAllShutUp:
            break;
        // 群事件_关闭全员禁言
        case EventTypeEnum::Group_DisableAllShutUp:
            break;
        // 群事件_开启匿名聊天
        case EventTypeEnum::Group_EnableAnonymous:
            break;
        // 群事件_关闭匿名聊天
        case EventTypeEnum::Group_DisableAnonymous:
            break;
        // 群事件_开启坦白说
        case EventTypeEnum::Group_EnableChatFrankly:
            break;
        // 群事件_关闭坦白说
        case EventTypeEnum::Group_DisableChatFrankly:
            break;
        // 群事件_允许群临时会话
        case EventTypeEnum::Group_AllowGroupTemporary:
            break;
        // 群事件_禁止群临时会话
        case EventTypeEnum::Group_ForbidGroupTemporary:
            break;
        // 群事件_允许发起新的群聊
        case EventTypeEnum::Group_AllowCreateGroup:
            break;
        // 群事件_禁止发起新的群聊
        case EventTypeEnum::Group_ForbidCreateGroup:
            break;
        // 群事件_允许上传群文件
        case EventTypeEnum::Group_AllowUploadFile:
            break;
        // 群事件_禁止上传群文件
        case EventTypeEnum::Group_ForbidUploadFile:
            break;
        // 群事件_允许上传相册
        case EventTypeEnum::Group_AllowUploadPicture:
            break;
        // 群事件_禁止上传相册
        case EventTypeEnum::Group_ForbidUploadPicture:
            break;
        // 群事件_某人被邀请入群
        case EventTypeEnum::Group_MemberInvited:
            break;
        // 群事件_展示成员群头衔
        case EventTypeEnum::Group_ShowMemberTitle:
            break;
        // 群事件_隐藏成员群头衔
        case EventTypeEnum::Group_HideMemberTitle:
            break;
        // 群事件_某人被解除禁言
        case EventTypeEnum::Group_MemberNotShutUp:
            break;
        // 其他事件
        default:
            break;
        }
    }
    return EventProcessEnum::Ignore;
}
