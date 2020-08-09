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
{ }

API::~API()
{ }

/**
 * @brief 输出日志
 * @param message 日志
 * @param text_color 文字颜色
 * @param background_color 背景颜色
 */
string API::OutputLog(const string &message, int32_t text_color,
    int32_t background_color)
{
    return e2s(_f<etext(etext, etext, eint, eint)>
        (this->j, "输出日志")
        (s2e(this->api_key), s2e(message), text_color, background_color));
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
    const string &content, int64_t* random, int32_t* req)
{
    auto a = random ? *random : 0;
    auto b = req ? *req : 0;
    return e2s(_f<etext(etext, elong, elong, etext, elong*, eint*)>
        (this->j, "发送好友消息")(s2e(this->api_key), thisQQ, friendQQ,
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
    return e2s(_f<etext(etext, elong, elong, etext, bool)>
        (this->j, "发送群消息")
        (s2e(this->api_key), thisQQ, groupQQ, s2e(content), anonymous));
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
                                              int64_t* random, int32_t* req)
{
    auto a = random ? *random : 0;
    auto b = req ? *req : 0;
    return e2s(_f<etext(etext, elong, elong, elong, etext,
                        elong*, eint*)>(this->j, "发送群临时消息")(s2e(this->api_key), thisQQ, groupQQ, otherQQ, s2e(content.c_str()),
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
                                          int64_t* random, int32_t* req)
{
    auto a = random ? *random : 0;
    auto b = req ? *req : 0;
    return e2s(_f<etext(etext, elong, elong, etext,
                        elong*, eint*)>(this->j, "发送好友json消息")(s2e(this->api_key), thisQQ, friendQQ, s2e(json_content),
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
                                      const uint8_t* picture, size_t length, bool is_flash)
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
                                     const uint8_t* picture, size_t size, bool is_flash)
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
                                      const uint8_t* audio, size_t size,
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
                                     const uint8_t* audio, size_t size,
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
string API::UploadAvatar(int64_t thisQQ, const uint8_t* picture, size_t size)
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

#include <sstream>
/**
 * @brief 获取好友列表
 * @param thisQQ 框架QQ
 * @return 成功返回好友数量，失败或无权限返回0
*/
 size_t API::GetFriendList(int64_t thisQQ/*, vector<FriendInformation>& friendList*/)
{
    int number = 0;
    earray info;
    number = _f<eint(etext,elong,earray)>(this->j,"取好友列表")(s2e(this->api_key),thisQQ,&info);
    std::wstringstream wss;
    wss << (uintptr_t)info;
    MessageBox(nullptr, TEXT("API::GetFriendList"), wss.str().c_str(), MB_OK);
    return  number;
}


/**
 * @brief 获取群列表
 * @param thisQQ 框架QQ
 * @param friendList 群信息列表
 * @return 成功返回群数量，失败或无权限返回0
 */
size_t API::GetGroupList(int64_t thisQQ/*, vector<GroupInformation>& groupList*/)
{
    return 0;
}

/*

.子程序 取好友列表, 整数型, 公开, 失败或无权限返回数量0
.参数 框架QQ, 长整数型, , 
.参数 数据, 好友信息, 参考 数组, 

.局部变量 ret, 整数型, , , 

清除数组 (数据)
调用子程序 (到整数 (j.取长整数 (取好友列表)), , ret, pluginkey, 框架QQ, 取变量地址 (数据))
返回 (ret)

.子程序 取群列表, 整数型, 公开, 失败或无权限返回数量0
.参数 框架QQ, 长整数型, , 
.参数 数据, 群信息, 参考 数组, 

.局部变量 ret, 整数型, , , 

清除数组 (数据)
调用子程序 (到整数 (j.取长整数 (取群列表)), , ret, pluginkey, 框架QQ, 取变量地址 (数据))
返回 (ret)

.子程序 取群成员列表, 整数型, 公开, 失败或无权限返回数量0
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 数据, 群成员信息, 参考 数组, 

.局部变量 ret, 整数型, , , 

清除数组 (数据)
调用子程序 (到整数 (j.取长整数 (取群成员列表)), , ret, pluginkey, 框架QQ, 群号, 取变量地址 (数据))
返回 (ret)

.子程序 设置管理员, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 群成员QQ, 长整数型, , 
.参数 取消管理, 逻辑型, , 取消或设置

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (设置管理员)), , ret, pluginkey, 框架QQ, 群号, 群成员QQ, 取消管理)
返回 (ret)


.子程序 取管理层列表, 文本型, 公开, 包括群主
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (取管理层列表)), , ret, pluginkey, 框架QQ, 群号)
返回 (ret)

.子程序 取群名片, 文本型, 公开, 成功返回群名片，注意，如果群成员的群名片未设置或群名片为空白，返回结果均为空
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 群成员QQ, 长整数型, , 

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (取群名片)), , ret, pluginkey, 框架QQ, 群号, 群成员QQ)
返回 (ret)

.子程序 取个性签名, 文本型, 公开, 成功返回个性签名
.参数 框架QQ, 长整数型, , 
.参数 对方QQ, 长整数型, , 可以填框架QQ本身

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (取个性签名)), , ret, pluginkey, 框架QQ, 对方QQ)
返回 (ret)


.子程序 修改昵称, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 昵称, 文本型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (修改昵称)), , ret, pluginkey, 框架QQ, 昵称)
返回 (ret)


.子程序 修改个性签名, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 签名, 文本型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (修改个性签名)), , ret, pluginkey, 框架QQ, 签名)
返回 (ret)


.子程序 删除群成员, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 群成员QQ, 长整数型, , 
.参数 拒绝加群申请, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (删除群成员)), , ret, pluginkey, 框架QQ, 群号, 群成员QQ, 拒绝加群申请)
返回 (ret)


.子程序 禁言群成员, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 群成员QQ, 长整数型, , 
.参数 禁言时长, 整数型, , 单位：秒

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (禁言群成员)), , ret, pluginkey, 框架QQ, 群号, 群成员QQ, 禁言时长)
返回 (ret)


.子程序 退群, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (退群)), , ret, pluginkey, 框架QQ, 群号)
返回 (ret)

.子程序 解散群, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (解散群)), , ret, pluginkey, 框架QQ, 群号)
返回 (ret)

.子程序 上传群头像, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 pic, 字节集, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (上传群头像)), , ret, pluginkey, 框架QQ, 群号, 取变量数据地址 (pic), 取字节集长度 (pic))
返回 (ret)


.子程序 全员禁言, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否开启, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (全员禁言)), , ret, pluginkey, 框架QQ, 群号, 是否开启)
返回 (ret)


.子程序 群权限_发起新的群聊, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否允许, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_发起新的群聊)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_发起临时会话, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否允许, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_发起临时会话)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_上传文件, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否允许, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_上传文件)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_上传相册, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否允许, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_上传相册)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_邀请好友加群, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否允许, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_邀请好友加群)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_匿名聊天, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否允许, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_匿名聊天)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_坦白说, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否允许, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_坦白说)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_新成员查看历史消息, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 是否允许, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_新成员查看历史消息)), , ret, pluginkey, 框架QQ, 群号, 是否允许)
返回 (ret)


.子程序 群权限_邀请方式设置, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 方式, 整数型, , 1 无需审核;2 需要管理员审核;3 100人以内无需审核

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群权限_邀请方式设置)), , ret, pluginkey, 框架QQ, 群号, 方式)
返回 (ret)


.子程序 撤回消息_群聊, 逻辑型, 公开, 在群消息事件中使用，能收到并撤回自己发的消息，失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 fromRandom, 长整数型, , 
.参数 fromReq, 整数型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (撤回消息_群聊)), , ret, pluginkey, 框架QQ, 群号, fromRandom, fromReq)
返回 (ret)

.子程序 撤回消息_私聊本身, 逻辑型, 公开, 用于撤回自己发的消息，其他设备的个人消息通知也可以撤回
.参数 框架QQ, 长整数型, , 
.参数 对方QQ, 长整数型, , 
.参数 fromRandom, 长整数型, , 
.参数 fromReq, 整数型, , 
.参数 time, 整数型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (撤回消息_私聊本身)), , ret, pluginkey, 框架QQ, 对方QQ, fromRandom, fromReq, time)
返回 (ret)

.子程序 设置位置共享, 逻辑型, 公开, 开启后需要上报位置，大约3s上报一次，否则会自动关闭，失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 经度, 双精度小数型, , 如：121.711540
.参数 纬度, 双精度小数型, , 如：31.403343
.参数 是否开启, 逻辑型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (设置位置共享)), , ret, pluginkey, 框架QQ, 群号, 经度, 纬度, 是否开启)
返回 (ret)

.子程序 上报当前位置, 逻辑型, 公开, 大约3s上报一次，不得过快，失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 经度, 双精度小数型, , 如：121.711540
.参数 纬度, 双精度小数型, , 如：31.403343

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (上报当前位置)), , ret, pluginkey, 框架QQ, 群号, 经度, 纬度)
返回 (ret)

.子程序 是否被禁言, 长整数型, 公开, 返回禁言时长，单位秒，[失败/无权限/未被禁言]返回0
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 

.局部变量 ret, 长整数型, , , 

调用子程序 (到整数 (j.取长整数 (是否被禁言)), , ret, pluginkey, 框架QQ, 群号)
返回 (ret)

.子程序 处理群验证事件, , 公开, 在群验证事件下使用，无权限时不执行
.参数 框架QQ, 长整数型, , 
.参数 来源群号, 长整数型, , 
.参数 触发QQ, 长整数型, , 
.参数 消息Seq, 长整数型, , 
.参数 操作类型, 整数型, , 11同意 12拒绝  14忽略
.参数 事件类型, 整数型, , #群事件_某人申请加群/#群事件_我被邀请加入群

调用子程序 (到整数 (j.取长整数 (处理群验证事件)), , , pluginkey, 框架QQ, 来源群号, 触发QQ, 消息Seq, 操作类型, 事件类型)

.子程序 处理好友验证事件, , 公开, 在好友验证事件下使用，无权限时不执行
.参数 框架QQ, 长整数型, , 
.参数 触发QQ, 长整数型, , 
.参数 消息Seq, 长整数型, , 
.参数 操作类型, 整数型, , 1同意 2拒绝

调用子程序 (到整数 (j.取长整数 (处理好友验证事件)), , , pluginkey, 框架QQ, 触发QQ, 消息Seq, 操作类型)


.子程序 查看转发聊天记录内容, , 公开, 私聊消息也可以使用此命令解析，无权限时不执行
.参数 框架QQ, 长整数型, , 
.参数 resId, 文本型, , 可在xml消息代码中取到
.参数 消息内容, 群消息数据, 参考 数组, 私聊消息也可从该结构取信息

调用子程序 (到整数 (j.取长整数 (查看转发聊天记录内容)), , , pluginkey, 框架QQ, resId, 取变量地址 (消息内容))

.子程序 上传群文件, , 公开, 本命令为耗时操作，请另开线程执行，本命令不支持上百mb的文件，无权限时不执行
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 文件路径, 文本型, , 本地文件路径
.参数 文件夹, 文本型, 可空, 该空保留，暂时无效

调用子程序 (到整数 (j.取长整数 (上传群文件)), , , pluginkey, 框架QQ, 群号, 文件路径, 文件夹)

.子程序 创建群文件夹, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 文件夹名, 文本型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (创建群文件夹)), , ret, pluginkey, 框架QQ, 群号, 文件夹名)
返回 (ret)

.子程序 设置在线状态, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 main, 整数型, , 11在线 31离开 41隐身 50忙碌 60Q我吧 70请勿打扰
.参数 sun, 整数型, 可空, 当main=11时，可进一步设置 0普通在线 1000我的电量 1011信号弱 1024在线学习 1025在家旅游 1027TiMi中 1016睡觉中 1017游戏中 1018学习中 1019吃饭中 1021煲剧中 1022度假中 1032熬夜中 1050打球中 1051恋爱中 1052我没事 1028我在听歌
.参数 电量, 整数型, 可空, sun=1000时，可以设置上报电量，取值1到100

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (设置在线状态)), , ret, pluginkey, 框架QQ, main, sun, 电量)
返回 (ret)


.子程序 api是否有权限, 逻辑型, 公开, 判断某api是否有权限
.参数 权限, 整数型, , #权限_

.局部变量 ret, 逻辑型, , , 
.局部变量 name, 文本型, , , 

.判断开始 (apilist.是否存在 (相加 (API[, 到文本 (权限), ])))
    赋值 (name, apilist.取文本 (相加 (API[, 到文本 (权限), ])))
    调用子程序 (到整数 (j.取长整数 (api是否有权限)), , ret, pluginkey, name)
.默认
    赋值 (ret, 假)
.判断结束
返回 (ret)

.子程序 重载自身, , 公开, 没有权限限制，请勿将新的插件文件下载至plugin文件夹，请确保新旧文件appname一致
.参数 新文件路径, 文本型, 可空, 若要更新插件，可将插件文件下载后在此填写新文件路径

调用子程序 (到整数 (j.取长整数 (重载自身)), , , pluginkey, 新文件路径)

.子程序 取插件数据目录, 文本型, 公开, 没有权限限制，建议将设置文件之类的都写这里面，结果结尾带\
.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (取插件数据目录)), , ret, pluginkey)
返回 (ret)

.子程序 QQ点赞, 文本型, 公开, 注意，非好友情况下进行点赞时返回成功，但不一定真正点上了
.参数 框架QQ, 长整数型, , 
.参数 对方QQ, 长整数型, , 

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (QQ点赞)), , ret, pluginkey, 框架QQ, 对方QQ)
返回 (ret)

.子程序 取图片下载地址, 文本型, 公开, 
.参数 图片代码, 文本型, , 支持群聊、私聊的图片、闪照代码，注意是图片代码
.参数 框架QQ, 长整数型, 可空, 群聊图片必填，私聊图片必空
.参数 群号, 长整数型, 可空, 群聊图片必填，私聊图片必空

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (取图片下载地址)), , ret, pluginkey, 图片代码, 

.子程序 查询好友信息, 逻辑型, 公开, 支持陌生人查询
.参数 框架QQ, 长整数型, , 
.参数 对方QQ, 长整数型, , 
.参数 数据, 好友信息, 参考, 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (查询好友信息)), , ret, pluginkey, 框架QQ, 对方QQ, 取变量地址 (数据))
返回 (ret)

.子程序 查询群信息, 逻辑型, 公开, 
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 数据, 群卡片信息, 参考, 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (查询群信息)), , ret, pluginkey, 框架QQ, 群号, 取变量地址 (数据))
返回 (ret)

.子程序 框架重启, , 公开, 有权限限制，建议使用前检查是否具有权限
调用子程序 (到整数 (j.取长整数 (框架重启)), , , pluginkey)

.子程序 群文件转发至群, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 来源群号, 长整数型, , 
.参数 目标群号, 长整数型, , 
.参数 fileId, 文本型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群文件转发至群)), , ret, pluginkey, 框架QQ, 来源群号, 目标群号, fileId)
返回 (ret)

.子程序 群文件转发至好友, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 来源群号, 长整数型, , 
.参数 目标QQ, 长整数型, , 
.参数 fileId, 文本型, , 
.参数 filename, 文本型, , 
.参数 Req, 整数型, 参考 可空, 撤回消息用
.参数 Random, 长整数型, 参考 可空, 撤回消息用
.参数 time, 整数型, 参考 可空, 撤回消息用

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (群文件转发至好友)), , ret, pluginkey, 框架QQ, 来源群号, 目标QQ, fileId, filename, Req, Random, time)
返回 (ret)

.子程序 好友文件转发至好友, 逻辑型, 公开, 失败或无权限返回假
.参数 框架QQ, 长整数型, , 
.参数 来源QQ, 长整数型, , 
.参数 目标QQ, 长整数型, , 
.参数 fileId, 文本型, , 
.参数 filename, 文本型, , 
.参数 Req, 整数型, 参考 可空, 撤回消息用
.参数 Random, 整数型, 参考 可空, 撤回消息用
.参数 time, 整数型, 参考 可空, 撤回消息用

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (好友文件转发至好友)), , ret, pluginkey, 框架QQ, 来源QQ, 目标QQ, fileId, filename, Req, Random, time)
返回 (ret)

.子程序 置群消息接收, 逻辑型, 公开, 失败或无权限返回假，此API未对返回结果进行分析，返回真不一定成功
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 设置类型, 整数型, , 1接收并提醒 2收进群助手 3屏蔽群消息 4接收不提醒

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (置群消息接收)), , ret, pluginkey, 框架QQ, 群号, 设置类型)
返回 (ret)

.子程序 发送免费礼物, 文本型, 公开, 绕过广告发送免费礼物
.参数 框架QQ, 长整数型, , 
.参数 群号, 长整数型, , 
.参数 对方QQ, 长整数型, , 
.参数 packageID, 整数型, , 299卡布奇诺;302猫咪手表;280牵你的手;281可爱猫咪;284神秘面具;285甜wink;286我超忙的;289快乐肥宅水;290幸运手链;313坚强;307绒绒手套; 312爱心口罩;308彩虹糖果

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (发送免费礼物)), , ret, pluginkey, 框架QQ, 群号, 对方QQ, packageID)
返回 (ret)

.子程序 取好友在线状态, 文本型, 公开, 失败或无权限返回空，支持查询陌生人
.参数 框架QQ, 长整数型, , 
.参数 对方QQ, 长整数型, , 

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (取好友在线状态)), , ret, pluginkey, 框架QQ, 对方QQ)
返回 (ret)

.子程序 取QQ钱包个人信息, 文本型, 公开, 包括余额、名字、银行卡等
.参数 框架QQ, 长整数型, , 
.参数 数据, QQ钱包信息, 参考, 取银行卡信息时注意不要数组越界

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (取QQ钱包个人信息)), , ret, pluginkey, 框架QQ, 取变量地址 (数据))
返回 (ret)

.子程序 获取订单详情, 文本型, 公开, 可以查订单，比如别人给你转账，你可以查询转账的详情
.参数 框架QQ, 长整数型, , 
.参数 订单号, 文本型, , 或者称之为listid
.参数 数据, 订单详情, 参考, 

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (获取订单详情)), , ret, pluginkey, 框架QQ, 订单号, 取变量地址 (数据))
返回 (ret)


.子程序 提交支付验证码, 文本型, 公开, 用银行卡支付时需要验证，只需要验证一次
.参数 框架QQ, 长整数型, , 
.参数 验证码信息, 验证码信息, , 银行卡发红包时传回的
.参数 验证码, 文本型, , 手机收到的短信验证码
.参数 支付密码, 文本型, , 用于验证并支付

.局部变量 ret, 文本型, , , 

调用子程序 (到整数 (j.取长整数 (提交支付验证码)), , ret, pluginkey, 框架QQ, 取变量地址 (验证码信息), 验证码, 支付密码)
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

调用子程序 (到整数 (j.取长整数 (分享音乐)), , ret, pluginkey, 框架QQ, 分享对象, 歌曲名, 歌手名, 跳转地址, 封面地址, 文件地址, 应用类型, 分享类型)
返回 (ret)

.子程序 更改群聊消息内容, 逻辑型, 公开, 使用此命令可以更改当前群聊消息内容，并使更改后的内容投递给之后的插件，无权限返回假
.参数 数据指针, 整数型, , 
.参数 新消息内容, 文本型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (更改群聊消息内容)), , ret, pluginkey, 数据指针, 新消息内容)
返回 (ret)

.子程序 更改私聊消息内容, 逻辑型, 公开, 使用此命令可以更改当前私聊消息内容，并使更改后的内容投递给之后的插件，无权限返回假
.参数 数据指针, 整数型, , 
.参数 新消息内容, 文本型, , 

.局部变量 ret, 逻辑型, , , 

调用子程序 (到整数 (j.取长整数 (更改私聊消息内容)), , ret, pluginkey, 数据指针, 新消息内容)
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

调用子程序 (到整数 (j.取长整数 (群聊口令红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 口令, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (群聊拼手气红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 祝福语, 红包皮肤Id, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (群聊普通红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 祝福语, 红包皮肤Id, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (群聊画图红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 题目名, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (群聊语音红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 语音口令, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (群聊接龙红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 接龙内容, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (群聊专属红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 群号, 领取人, 祝福语, 是否均分, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (好友口令红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 口令, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (好友普通红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 祝福语, 红包皮肤Id, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (好友画图红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 题目名, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (好友语音红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 语音口令, 支付密码, 银行卡序列)
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

调用子程序 (到整数 (j.取长整数 (好友接龙红包)), , ret, pluginkey, 框架QQ, 总数量, 总金额, 对方QQ, 接龙内容, 支付密码, 银行卡序列)
返回 (ret)
*/
