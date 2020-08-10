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

#include "api.h"
/**
 * @brief 载入插件关键字和系统回调函数指针
 * @param apidata 系统回调函数指针JSON
 * @param pluginkey 插件关键字
 */
API::API(etext apidata, etext pluginkey)
    : api_key(GBKtoUTF8(pluginkey)), j(Json::parse(GBKtoUTF8(apidata)))
{
}

API::~API()
{
}

/**
 * @brief 输出日志
 * @param message 日志
 * @param text_color 文字颜色
 * @param background_color 背景颜色
 */
string API::OutputLog(const string &message, int32_t text_color,
                      int32_t background_color)
{
    return e2s(_f<etext(etext, etext, eint, eint)>(this->j, "输出日志")(s2e(this->api_key), s2e(message), text_color, background_color));
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
string API::SendFriendMessage(int64_t thisQQ, int64_t friendQQ,
                              const string &content, int64_t *random, int32_t *req)
{
    auto a = random ? *random : 0;
    auto b = req ? *req : 0;
    return e2s(_f<etext(etext, elong, elong, etext, elong *, eint *)>(this->j, "发送好友消息")(s2e(this->api_key), thisQQ, friendQQ,
                                                                                               s2e(content), &a, &b));
}

/**
 * @brief 发送群消息
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param content 发送内容
 * @param anonymous 匿名发送
 */
string API::SendGroupMessage(int64_t thisQQ, int64_t groupQQ,
                             const string &content, bool anonymous)
{
    return e2s(_f<etext(etext, elong, elong, etext, bool)>(this->j, "发送群消息")(s2e(this->api_key), thisQQ, groupQQ, s2e(content), anonymous));
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
string API::SendGroupTemporaryMessage(int64_t thisQQ, int64_t groupQQ,
                                      int64_t otherQQ, const string &content,
                                      int64_t *random, int32_t *req)
{
    auto a = random ? *random : 0;
    auto b = req ? *req : 0;
    return e2s(_f<etext(etext, elong, elong, elong, etext,
                        elong *, eint *)>(this->j, "发送群临时消息")(s2e(this->api_key), thisQQ, groupQQ, otherQQ, s2e(content.c_str()),
                                                                     &a, &b));
}

/**
 * @brief 添加好友
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 * @param verification 设置回答问题答案或是验证消息，多个问题答案用"|"分隔开
 */
string API::AddFriend(int64_t thisQQ, int64_t otherQQ,
                      const string &verification)
{
    return e2s(_f<etext(etext, elong, elong, etext)>(this->j, "添加好友")(s2e(this->api_key), thisQQ, otherQQ, s2e(verification.c_str())));
}

/**
 * @brief 添加群（你在群内或需要付费入群也会直接发送验证消息）
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param verification 回答问题答案或是验证消息
 */
string API::AddGroup(int64_t thisQQ, int64_t groupQQ,
                     const string &verification)
{
    return e2s(_f<etext(etext, elong, elong, etext)>(this->j, "添加群")(s2e(this->api_key), thisQQ, groupQQ, s2e(verification.c_str())));
}

/**
 * @brief 删除好友
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 */
string API::RemoveFriend(int64_t thisQQ, int64_t otherQQ)
{
    return e2s(_f<etext(etext, elong, elong)>(this->j, "删除好友")(s2e(this->api_key), thisQQ, otherQQ));
}

/**
 * @brief 设置屏蔽好友
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 * @param is_blocked 是否屏蔽
 */
string API::SetBlockFriend(int64_t thisQQ, int64_t otherQQ,
                           bool is_blocked)
{
    return e2s(_f<etext(etext, elong, elong, ebool)>(this->j, "置屏蔽好友")(s2e(this->api_key), thisQQ, otherQQ,
                                                                            b2e(is_blocked)));
}

/**
 * @brief 设置特别关心好友
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 * @param is_special 是否屏蔽
 */
string API::SetSpecialFriend(int64_t thisQQ, int64_t otherQQ,
                             bool is_special)
{
    return e2s(_f<etext(etext, elong, elong, ebool)>(this->j, "置特别关心好友")(s2e(this->api_key), thisQQ, otherQQ,
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
string API::SendFriendJSONMessage(int64_t thisQQ, int64_t friendQQ,
                                  const string &json_content,
                                  int64_t *random, int32_t *req)
{
    auto a = random ? *random : 0;
    auto b = req ? *req : 0;
    return e2s(_f<etext(etext, elong, elong, etext,
                        elong *, eint *)>(this->j, "发送好友json消息")(s2e(this->api_key), thisQQ, friendQQ, s2e(json_content),
                                                                       &a, &b));
}

/**
 * @brief 发送群JSON消息
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param json_content json发送内容
 * @param anonymous 匿名发送
 */
string API::SendGroupJSONMessage(int64_t thisQQ, int64_t groupQQ,
                                 const string &json_content, bool anonymous)
{
    return e2s(_f<etext(etext, elong, elong, etext, bool)>(this->j, "发送群json消息")(s2e(this->api_key), thisQQ, groupQQ,
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
string API::UploadFriendImage(int64_t thisQQ, int64_t friendQQ,
                              const uint8_t *picture, size_t length, bool is_flash)
{
    return e2s(_f<etext(etext, elong, elong, ebool, ebin, eint)>(this->j, "上传好友图片")(s2e(this->api_key), thisQQ, friendQQ, b2e(is_flash),
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
string API::UploadGroupImage(int64_t thisQQ, int64_t groupQQ,
                             const uint8_t *picture, size_t size, bool is_flash)
{
    return e2s(_f<etext(etext, elong, elong, ebool, ebin, eint)>(this->j, "上传群图片")(s2e(this->api_key), thisQQ, groupQQ, b2e(is_flash),
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
string API::UploadFriendAudio(int64_t thisQQ, int64_t friendQQ,
                              const uint8_t *audio, size_t size,
                              int32_t audio_type, const string &audio_text)
{
    return e2s(_f<etext(etext, elong, elong, eint, etext, ebin, eint)>(this->j, "上传好友语言")(s2e(this->api_key), thisQQ, friendQQ, audio_type, s2e(audio_text),
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
string API::UploadGroupAudio(int64_t thisQQ, int64_t groupQQ,
                             const uint8_t *audio, size_t size,
                             int32_t audio_type, const string &audio_text)
{
    return e2s(_f<etext(etext, elong, elong, eint, etext, ebin, eint)>(this->j, "上传群语音")(s2e(this->api_key), thisQQ, groupQQ, audio_type, s2e(audio_text),
                                                                                              audio, static_cast<eint>(size)));
}

/**
 * @brief 上传头像
 * @param thisQQ 框架QQ
 * @param picture 图片数据
 * @param size 图片大小534
 */
string API::UploadAvatar(int64_t thisQQ, const uint8_t *picture, size_t size)
{
    return e2s(_f<etext(etext, elong, ebin, eint)>(this->j, "上传头像")(s2e(this->api_key), thisQQ, picture, static_cast<eint>(size)));
}

/**
 * @brief 设置群名片
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param otherQQ 群成员QQ
 * @param nickname 新名片
 */
string API::SetGroupNickname(int64_t thisQQ, int64_t groupQQ,
                             int64_t otherQQ, const string &nickname)
{
    return e2s(_f<etext(etext, elong, elong, elong, etext)>(this->j, "设置群名片")(
        s2e(this->api_key), thisQQ, groupQQ, otherQQ, s2e(nickname)));
}

/**
 * @brief 从缓存取昵称
 * @param otherQQ 对方QQ
 * @return 成功返回昵称
 */
string API::GetNameFromCache(int64_t otherQQ)
{
    return e2s(
        _f<etext(etext, elong)>(this->j, "取昵称_从缓存")(s2e(this->api_key), otherQQ));
}

/**
 * @brief 从缓存取昵称
 * @param otherQQ 对方QQ
 * @return 成功返回昵称
 */
string API::GetNameForce(int64_t otherQQ)
{
    return e2s(
        _f<etext(etext, elong)>(this->j, "强制取昵称")(s2e(this->api_key), otherQQ));
}

/**
 * @brief 从缓存取群名（如果是框架QQ没加的群，[查询群信息]后也会记录缓存）
 * @param groupQQ 群号
 * @return 成功返回群名称
 */
string API::GetGroupNameFromCache(int64_t groupQQ)
{
    return e2s(
        _f<etext(etext, elong)>(this->j, "取群名称_从缓存")(s2e(this->api_key), groupQQ));
}

/**
     * @brief 获取SKey
     * @param thisQQ 框架QQ
     * @return 成功返回SKey
     */
string API::GetSKey(int64_t thisQQ)
{
    return e2s(
        _f<etext(etext, elong)>(this->j, "获取skey")(s2e(this->api_key), thisQQ));
}

/**
     * @brief 获取PSKey
     * @param thisQQ 框架QQ
     * @param domain 域: tenpay.com;openmobile.qq.com;docs.qq.com;connect.qq.com;qzone.qq.com;vip.qq.com;gamecenter.qq.com;qun.qq.com;game.qq.com;qqweb.qq.com;ti.qq.com;office.qq.com;mail.qq.com;mma.qq.com
     * @return 成功返回PSKey
     */
string API::GetPSKey(int64_t thisQQ, const string &domain)
{
    return e2s(
        _f<etext(etext, elong)>(this->j, "获取pskey")(s2e(this->api_key), thisQQ));
}

/**
 * @brief 获取ClientKey
 * @param thisQQ 框架QQ
 * @return 成功返回ClientKey
 */
string API::GetClientKey(int64_t thisQQ)
{
    return e2s(
        _f<etext(etext, elong)>(this->j, "获取clientkey")(s2e(this->api_key), thisQQ));
}

/**
 * @brief 获取框架QQ
 */
string API::GetThisQQ()
{
    return e2s(
        _f<etext(etext)>(this->j, "取框架QQ")(s2e(this->api_key)));
}

/**
 * @brief 获取好友列表
 * @param thisQQ 框架QQ
 * @return 成功返回好友数量，失败或无权限返回0
 */
size_t API::GetFriendList(int64_t thisQQ, vector<FriendInformation> &friendList)
{
    int number = 0;
    earray info;
    number = _f<eint(etext, elong, earray)>(this->j, "取好友列表")(s2e(this->api_key), thisQQ, &info);
    earray1D arrayUnpacker;
    arrayUnpacker.Unpack<FriendInformation>(info, friendList);
    return number;
}

/**
 * @brief 获取群列表
 * @param thisQQ 框架QQ
 * @param friendList 群信息列表
 * @return 成功返回群数量，失败或无权限返回0
 */
size_t API::GetGroupList(int64_t thisQQ, vector<GroupInformation> &groupList)
{
    int number = 0;
    earray info;
    number = _f<eint(etext, elong, earray)>(this->j, "取群列表")(s2e(this->api_key), thisQQ, &info);
    earray1D arrayUnpacker;
    arrayUnpacker.Unpack<GroupInformation>(info, groupList);
    return number;
}

  /**
 * @brief 取群成员列表
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param group_member_list 数据
 * @return 失败或无权限返回数量0
 */
int32_t API::GetGroupMemberList(int64_t thisQQ, int64_t groupQQ, vector<GroupMemberInformation>& group_member_list)
{
    int number = 0;
    earray info;
    number = _f<eint(etext,elong,elong,earray)>(this->j,"取群成员列表")(s2e(this->api_key),thisQQ,groupQQ,info);
    earray1D unpacker;
    unpacker.Unpack<GroupMemberInformation>(info,group_member_list);
    return 0;
}

/**
 * @brief 设置管理员
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param otherQQ 群成员QQ
 * @param is_administrator 取消管理 取消或设置
 * @return 失败或无权限返回假
 */
bool API::SetAdministrator(int64_t thisQQ, int64_t groupQQ, int64_t otherQQ, bool is_administrator)
{

}

/**
 * @brief 取群名片
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param otherQQ 群成员QQ
 * @return 成功返回群名片，注意，如果群成员的群名片未设置或群名片为空白，返回结果均为空
 */
string API::GetGroupNickname(int64_t thisQQ, int64_t groupQQ, int64_t otherQQ)
{

}

/**
 * @brief 取个性签名
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ 可以填框架QQ本身
 * @return 成功返回个性签名
 */
string API::GetSignature(int64_t thisQQ, int64_t otherQQ)
{

}

/**
 * @brief 修改昵称
 * @param thisQQ 框架QQ
 * @param name 昵称
 * @return 失败或无权限返回假
 */
bool API::SetName(int64_t thisQQ, string name)
{

}

/**
 * @brief 修改个性签名
 * @param thisQQ 框架QQ
 * @param signature 签名
 * @return 失败或无权限返回假
 */
bool API::SetSignature(int64_t thisQQ, string signature)
{

}

 
/**
 * @brief 删除群成员
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param otherQQ 群成员QQ
 * @param is_verification_refused 拒绝加群申请
 * @return 失败或无权限返回假
 */
bool API::RemoveGroupMember(int64_t thisQQ, int64_t groupQQ, int64_t otherQQ, bool is_verification_refused)
{

}

/**
 * @brief 禁言群成员
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param otherQQ 群成员QQ
 * @param time 禁言时长 单位：秒
 * @return 失败或无权限返回假
 */
bool API::ShutUpGroupMember(int64_t thisQQ, int64_t groupQQ, int64_t otherQQ, int32_t time)
{

}

/**
 * @brief 退群
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @return 失败或无权限返回假
 */
bool API::QuitGroup(int64_t thisQQ, int64_t groupQQ)
{

}

/**
 * @brief 解散群
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @return 失败或无权限返回假
 */
bool API::DissolveGroup(int64_t thisQQ, int64_t groupQQ)
{

}

/**
 * @brief 上传群头像
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param picture pic
 * @return 失败或无权限返回假
 */
bool API::UploadGroupAvatar(int64_t thisQQ, int64_t groupQQ, uint8_t *picture)
{

}

/**
 * @brief 全员禁言
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_shut_up_all 是否开启
 * @return 失败或无权限返回假
 */
bool API::ShutUpAll(int64_t thisQQ, int64_t groupQQ, bool is_shut_up_all)
{

}

/**
 * @brief 群权限_发起新的群聊
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_allowed 是否允许
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_CreateGroup(int64_t thisQQ, int64_t groupQQ, bool is_allowed)
{

}

/**
 * @brief 群权限_发起临时会话
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_allowed 是否允许
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_CreateTemporaryConversation(int64_t thisQQ, int64_t groupQQ, bool is_allowed)
{

}

/**
 * @brief 群权限_上传文件
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_allowed 是否允许
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_UploadFile(int64_t thisQQ, int64_t groupQQ, bool is_allowed)
{

}


/**
 * @brief 群权限_上传相册
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_allowed 是否允许
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_UploadPicture(int64_t thisQQ, int64_t groupQQ, bool is_allowed)
{

}

/**
 * @brief 群权限_邀请好友加群
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_allowed 是否允许
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_InviteFriend(int64_t thisQQ, int64_t groupQQ, bool is_allowed)
{

}

/**
 * @brief 群权限_匿名聊天
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_allowed 是否允许
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_Anonymous(int64_t thisQQ, int64_t groupQQ, bool is_allowed)
{

}

/**
 * @brief 群权限_坦白说
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_allowed 是否允许
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_ChatFrankly(int64_t thisQQ, int64_t groupQQ, bool is_allowed)
{

}

/**
 * @brief 群权限_新成员查看历史消息
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param is_allowed 是否允许
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_NewMemberReadHistory(int64_t thisQQ, int64_t groupQQ, bool is_allowed)
{

}

/**
 * @brief 群权限_邀请方式设置
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param method 方式 1 无需审核;2 需要管理员审核;3 100人以内无需审核
 * @return 失败或无权限返回假
 */
bool API::GroupPermission_SetInviteMethod(int64_t thisQQ, int64_t groupQQ, int32_t method)
{

}

/**
 * @brief 撤回消息_群聊
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param fromRandom fromRandom
 * @param fromReq fromReq
 * @return 在群消息事件中使用，能收到并撤回自己发的消息，失败或无权限返回假
 */
bool API::Undid_Group(int64_t thisQQ, int64_t groupQQ, int64_t from_random, int32_t from_req)
{

}

/**
 * @brief 撤回消息_私聊本身
 * @param thisQQ 框架QQ
 * @param otherQQ 对方QQ
 * @param from_random fromRandom
 * @param from_req fromReq
 * @param time time
 * @return 用于撤回自己发的消息，其他设备的个人消息通知也可以撤回
 */
bool API::Undid_Private(int64_t thisQQ, int64_t otherQQ, int64_t from_random, int32_t from_req, int32_t time)
{

}

/**
 * @brief 设置位置共享（开启后需要上报位置，大约3s上报一次，否则会自动关闭）
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param Longitude 经度 如：121.711540
 * @param Latitude 纬度 如：31.403343
 * @param is_enabled 是否开启
 * @return 失败或无权限返回假
 */ 
bool API::SetLocationShare(int64_t thisQQ, int64_t groupQQ, double Longitude, double Latitude, bool is_enabled)
{

}

/**
 * @brief 上报当前位置（大约3s上报一次，不得过快）
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @param Longitude 经度 如：121.711540
 * @param Latitude 纬度 如：31.403343
 * @return 失败或无权限返回假
 */
bool API::ReportCurrent(int64_t thisQQ, int64_t groupQQ, double Longitude, double Latitude)
{

}

/**
 * @brief 是否被禁言
 * @param thisQQ 框架QQ
 * @param groupQQ 群号
 * @return 返回禁言时长，单位秒，失败、无权限或未被禁言返回0
 */
int64_t API::IsShuttedUp(int64_t thisQQ, int64_t groupQQ)
{

}


 /**
 * @brief 处理群验证事件 在群验证事件下使用，无权限时不执行
 * @param thisQQ 框架QQ
 * @param source_groupQQ 来源群号
 * @param triggerQQ 触发QQ
 * @param message_seq 消息Seq
 * @param operate_type 操作类型 11: 同意, 12: 拒绝, 14: 忽略
 * @param event_type 事件类型 群事件_某人申请加群(Group_MemberVerifying)或群事件_我被邀请加入群(Group_Invited)
 */
void ProcessGroupVerificationEvent(int64_t thisQQ, int64_t source_groupQQ, int64_t triggerQQ, int64_t message_seq, int32_t operate_type, int32_t event_type)
{

}

/**
 * @brief 处理好友验证事件 在好友验证事件下使用，无权限时不执行
 * @param thisQQ 框架QQ
 * @param triggerQQ 触发QQ
 * @param message_seq 消息Seq
 * @param operate_type 操作类型 1: 同意, 2: 拒绝
 */
void ProcessFriendVerificationEvent(int64_t thisQQ, int64_t triggerQQ, int64_t message_seq, int32_t operate_type)
{

}
