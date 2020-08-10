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

#ifndef CORNERSTONE_HEADER_API_H_
#define CORNERSTONE_HEADER_API_H_

#include "../sdk.h"

class API
{
public:
    /**
     * @brief 载入插件关键字和系统回调函数指针
     * @param apidata 系统回调函数指针JSON
     * @param pluginkey 插件关键字
     */
    API(etext apidata, etext pluginkey);

    ~API();

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
     * @param otherQQ 对方QQ
     * @param content 发送内容
     * @param random 撤回消息用
     * @param req 撤回消息用
     * @return 成功返回的time用于撤回消息
     */
    string SendFriendMessage(int64_t thisQQ, int64_t otherQQ,
                             const string &content,
                             int64_t *random = nullptr, int32_t *req = nullptr);

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
     * @param otherQQ 对方QQ
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
     * @param friendQQ 好友QQ
     * @param picture 图片数据
     * @param is_flash 是否闪照
     * @return 成功返回图片代码
     */
    string UploadFriendImage(int64_t thisQQ, int64_t friendQQ,
                             const uint8_t *picture, size_t length, bool is_flash);

    /**
     * @brief 上传群图片
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param picture 图片数据
     * @param is_flash 是否闪照
     * @return 成功返回图片代码
     */
    string UploadGroupImage(int64_t thisQQ, int64_t groupQQ,
                            const uint8_t *picture, size_t size, bool is_flash);

    /**
     * @brief 上传好友语音
     * @param thisQQ 框架QQ
     * @param friendQQ 好友QQ
     * @param audio 语音数据
     * @param audio_type 语音类型 0：普通语音，1：变声语音，2：文字语音，3：红包匹配语音
     * @param audio_text 语音文字 文字语音填附加文字(貌似会自动替换为语音对应的文本),匹配语音填a、b、s、ss、sss，注意是小写
     * @return 成功返回语音代码
     */
    string UploadFriendAudio(int64_t thisQQ, int64_t friendQQ,
                             const uint8_t *audio, size_t size,
                             int32_t audio_type, const string &audio_text);

    /*
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
     * @param friendList 好友信息列表
     * @return 成功返回好友数量，失败或无权限返回0
     */
    size_t GetFriendList(int64_t thisQQ, vector<FriendInformation> &friendList);

    /**
     * @brief 获取群列表
     * @param thisQQ 框架QQ
     * @param friendList 群信息列表
     * @return 成功返回群数量，失败或无权限返回0
     */
    size_t GetGroupList(int64_t thisQQ, vector<GroupInformation> &groupList);

    /**
     * @brief 取群成员列表
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param group_member_list 数据
     * @return 失败或无权限返回数量0
     */
    int32_t GetGroupMemberList(int64_t thisQQ, int64_t groupQQ, vector<GroupMemberInformation>& group_member_list);

    /**
     * @brief 设置管理员
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param otherQQ 群成员QQ
     * @param is_administrator 取消管理 取消或设置
     * @return 失败或无权限返回假
     */
    bool SetAdministrator(int64_t thisQQ, int64_t groupQQ, int64_t otherQQ, bool is_administrator);

    /**
     * @brief 取管理层列表
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @return 包括群主
     */
    string GetAdministratorList(int64_t thisQQ, int64_t groupQQ);

    /**
     * @brief 取群名片
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param otherQQ 群成员QQ
     * @return 成功返回群名片，注意，如果群成员的群名片未设置或群名片为空白，返回结果均为空
     */
    string GetGroupNickname(int64_t thisQQ, int64_t groupQQ, int64_t otherQQ);

    /**
     * @brief 取个性签名
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ 可以填框架QQ本身
     * @return 成功返回个性签名
     */
    string GetSignature(int64_t thisQQ, int64_t otherQQ);

    /**
     * @brief 修改昵称
     * @param thisQQ 框架QQ
     * @param name 昵称
     * @return 失败或无权限返回假
     */
    bool SetName(int64_t thisQQ, string name);

    /**
     * @brief 修改个性签名
     * @param thisQQ 框架QQ
     * @param signature 签名
     * @return 失败或无权限返回假
     */
    bool SetSignature(int64_t thisQQ, string signature);
    
    /**
     * @brief 删除群成员
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param otherQQ 群成员QQ
     * @param is_verification_refused 拒绝加群申请
     * @return 失败或无权限返回假
     */
    bool RemoveGroupMember(int64_t thisQQ, int64_t groupQQ, int64_t otherQQ, bool is_verification_refused);

    /**
     * @brief 禁言群成员
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param otherQQ 群成员QQ
     * @param time 禁言时长 单位：秒
     * @return 失败或无权限返回假
     */
    bool ShutUpGroupMember(int64_t thisQQ, int64_t groupQQ, int64_t otherQQ, int32_t time);

    /**
     * @brief 退群
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @return 失败或无权限返回假
     */
    bool QuitGroup(int64_t thisQQ, int64_t groupQQ);
    
    /**
     * @brief 解散群
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @return 失败或无权限返回假
     */
    bool DissolveGroup(int64_t thisQQ, int64_t groupQQ);
   
    /**
     * @brief 上传群头像
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param picture pic
     * @return 失败或无权限返回假
     */
    bool UploadGroupAvatar(int64_t thisQQ, int64_t groupQQ, const uint8_t *picture);

    /**
     * @brief 全员禁言
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_shut_up_all 是否开启
     * @return 失败或无权限返回假
     */
    bool ShutUpAll(int64_t thisQQ, int64_t groupQQ, bool is_shut_up_all);

    /**
     * @brief 群权限_发起新的群聊
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_allowed 是否允许
     * @return 失败或无权限返回假
     */
    bool GroupPermission_CreateGroup(int64_t thisQQ, int64_t groupQQ, bool is_allowed);
    
    /**
     * @brief 群权限_发起临时会话
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_allowed 是否允许
     * @return 失败或无权限返回假
     */
    bool GroupPermission_CreateTemporaryConversation(int64_t thisQQ, int64_t groupQQ, bool is_allowed);

    /**
     * @brief 群权限_上传文件
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_allowed 是否允许
     * @return 失败或无权限返回假
     */
    bool GroupPermission_UploadFile(int64_t thisQQ, int64_t groupQQ, bool is_allowed);
    
    
    /**
     * @brief 群权限_上传相册
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_allowed 是否允许
     * @return 失败或无权限返回假
     */
    bool GroupPermission_UploadPicture(int64_t thisQQ, int64_t groupQQ, bool is_allowed);
    
    /**
     * @brief 群权限_邀请好友加群
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_allowed 是否允许
     * @return 失败或无权限返回假
     */
    bool GroupPermission_InviteFriend(int64_t thisQQ, int64_t groupQQ, bool is_allowed);
    
    /**
     * @brief 群权限_匿名聊天
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_allowed 是否允许
     * @return 失败或无权限返回假
     */
    bool GroupPermission_Anonymous(int64_t thisQQ, int64_t groupQQ, bool is_allowed);
    
    /**
     * @brief 群权限_坦白说
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_allowed 是否允许
     * @return 失败或无权限返回假
     */
    bool GroupPermission_ChatFrankly(int64_t thisQQ, int64_t groupQQ, bool is_allowed);

    /**
     * @brief 群权限_新成员查看历史消息
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param is_allowed 是否允许
     * @return 失败或无权限返回假
     */
    bool GroupPermission_NewMemberReadChatHistory(int64_t thisQQ, int64_t groupQQ, bool is_allowed);
    
    /**
     * @brief 群权限_邀请方式设置
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param method 方式 1 无需审核;2 需要管理员审核;3 100人以内无需审核
     * @return 失败或无权限返回假
     */
    bool GroupPermission_SetInviteMethod(int64_t thisQQ, int64_t groupQQ, int32_t method);
    
    /**
     * @brief 撤回消息_群聊
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param fromRandom fromRandom
     * @param fromReq fromReq
     * @return 在群消息事件中使用，能收到并撤回自己发的消息，失败或无权限返回假
     */
    bool Undid_Group(int64_t thisQQ, int64_t groupQQ, int64_t from_random, int32_t from_req);
    
    /**
     * @brief 撤回消息_私聊本身
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @param from_random fromRandom
     * @param from_req fromReq
     * @param time time
     * @return 用于撤回自己发的消息，其他设备的个人消息通知也可以撤回
     */
    bool Undid_Private(int64_t thisQQ, int64_t otherQQ, int64_t from_random, int32_t from_req, int32_t time);

    /**
     * @brief 设置位置共享（开启后需要上报位置，大约3s上报一次，否则会自动关闭）
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param Longitude 经度 如：121.711540
     * @param Latitude 纬度 如：31.403343
     * @param is_enabled 是否开启
     * @return 失败或无权限返回假
     */ 
    bool SetLocationShare(int64_t thisQQ, int64_t groupQQ, double Longitude, double Latitude, bool is_enabled);

    /**
     * @brief 上报当前位置（大约3s上报一次，不得过快）
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param Longitude 经度 如：121.711540
     * @param Latitude 纬度 如：31.403343
     * @return 失败或无权限返回假
     */
    bool ReportCurrent(int64_t thisQQ, int64_t groupQQ, double Longitude, double Latitude);
    
    /**
     * @brief 是否被禁言
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @return 返回禁言时长，单位秒，失败、无权限或未被禁言返回0
     */
    int64_t IsShuttedUp(int64_t thisQQ, int64_t groupQQ);

    /**
     * @brief 处理群验证事件 在群验证事件下使用，无权限时不执行
     * @param thisQQ 框架QQ
     * @param source_groupQQ 来源群号
     * @param triggerQQ 触发QQ
     * @param message_seq 消息Seq
     * @param operate_type 操作类型 11: 同意, 12: 拒绝, 14: 忽略
     * @param event_type 事件类型 群事件_某人申请加群(Group_MemberVerifying)或群事件_我被邀请加入群(Group_Invited)
     */
    void ProcessGroupVerificationEvent(int64_t thisQQ, int64_t source_groupQQ, int64_t triggerQQ, int64_t message_seq, int32_t operate_type, int32_t event_type);

    /**
     * @brief 处理好友验证事件 在好友验证事件下使用，无权限时不执行
     * @param thisQQ 框架QQ
     * @param triggerQQ 触发QQ
     * @param message_seq 消息Seq
     * @param operate_type 操作类型 1: 同意, 2: 拒绝
     */
    void ProcessFriendVerificationEvent(int64_t thisQQ, int64_t triggerQQ, int64_t message_seq, int32_t operate_type);

    /**
     * @brief 查看转发聊天记录内容 私聊消息也可以使用此命令解析，无权限时不执行
     * @param thisQQ 框架QQ
     * @param resID resID 可在xml消息代码中取到
     * @param message_content 消息内容 私聊消息也可从该结构取信息
     */
    void ReadForwardedChatHistory(int64_t thisQQ, string resID, vector<GroupMessageData>& message_content)

    /**
     * @brief 上传群文件 本命令为耗时操作，请另开线程执行，本命令不支持上百mb的文件，无权限时不执行
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param path 文件路径 本地文件路径
     * @param directory 文件夹 该空保留，暂时无效
     */
    void ProcessFriendVerificationEvent(int64_t thisQQ, int64_t groupQQ, string path, string directory);

    /**
     * @brief 创建群文件夹
     * @param thisQQ 框架QQ
     * @param groupQQ 群号
     * @param directory 文件夹名
     * @return 失败或无权限返回假
     */
    bool CreateGroupDirectory(int64_t thisQQ, int64_t groupQQ, string directory);

    /**
    * @brief 设置在线状态
    * @param thisQQ 框架QQ
    * @param main main 11: 在线, 31: 离开, 41: 隐身, 50: 忙碌, 60: Q我吧, 70: 请勿打扰
    * @param sun sun 当main=11时，可进一步设置 0: 普通在线, 1000: 我的电量, 1011: 信号弱, 1016: 睡觉中, 1017: 游戏中, 1018: 学习中, 1019: 吃饭中, 1021: 煲剧中, 1022: 度假中, 1024: 在线学习, 1025: 在家旅游, 1027: TiMi中, 1028: 我在听歌, 1032: 熬夜中, 1050: 打球中, 1051: 恋爱中, 1052: 我没事
    * @param battery 电量 sun=1000时，可以设置上报电量，取值1到100
    * @return 失败或无权限返回假
    */
    bool SetStatus(int64_t thisQQ, int32_t main, int32_t sun = 0, int32_t battery = 0);

    /**
     * @brief api是否有权限
     * @param permission 权限 #权限_
     * @return 判断某api是否有权限
     */
    bool CheckPermission(int32_t permission);

    /**
     * @brief 取插件数据目录
     * @param new_file_path 新文件路径 若要更新插件，可将插件文件下载后在此填写新文件路径
     * @return 没有权限限制，建议将设置文件之类的都写这里面，结果结尾带\
     */
    string GetPluginDataDirectory(可空 string new_file_path);

    /**
     * @brief QQ点赞
     * @param thisQQ 框架QQ
     * @param otherQQ 对方QQ
     * @return 注意，非好友情况下进行点赞时返回成功，但不一定真正点上了
     */
    string QQLike(int64_t thisQQ, int64_t otherQQ);

    /**
     * @brief 取图片下载地址
     * @param image_code 图片代码 支持群聊、私聊的图片、闪照代码，注意是图片代码
     * @param thisQQ 框架QQ 群聊图片必填，私聊图片必空
     * @param groupQQ 群号 群聊图片必填，私聊图片必空
     */
    string GetImageDownloadLink(string image_code, 可空 int64_t thisQQ, 可空 int64_t groupQQ);

protected:
    Json j;
    string api_key;
};

#endif // CORNERSTONE_HEADER_API_H_
