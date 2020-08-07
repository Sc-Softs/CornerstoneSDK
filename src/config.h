#define ENABLE_PRIVATE_MSG //启用私聊处理。不需要直接去掉
#define ENABLE_GROUP_MSG
#define ENABLE_PLUGIN_SETTINGS
#define ENABLE_PLUGIN_ENABLED//插件启用事件
#define ENABLE_PLUGIN_DISABLED//插件被禁用事件
const auto JSON_PART =   R"J(
        {
            "appname":    "C++样例应用",
            "author":     "这是作者",
            "appv":       "1.0.0",
            "describe":   "应用的说明",
            "sdkv":       "2.5.9"
        }
)J";

//在这里改动你的权限
const auto apiList = {"输出日志","发送好友消息"};



//所有的权限。希望大家看得懂
/*
.版本 2

apilist.创建 (, )
apilist.置文本 (“API[0]”, “输出日志”)
apilist.置文本 (“API[1]”, “发送好友消息”)
apilist.置文本 (“API[2]”, “发送群消息”)
apilist.置文本 (“API[3]”, “发送群临时消息”)
apilist.置文本 (“API[4]”, “添加好友”)
apilist.置文本 (“API[5]”, “添加群”)
apilist.置文本 (“API[6]”, “删除好友”)
apilist.置文本 (“API[7]”, “置屏蔽好友”)
apilist.置文本 (“API[8]”, “置特别关心好友”)
apilist.置文本 (“API[9]”, “发送好友xml消息”)
apilist.置文本 (“API[10]”, “发送群xml消息”)
apilist.置文本 (“API[11]”, “发送好友json消息”)
apilist.置文本 (“API[12]”, “发送群json消息”)
apilist.置文本 (“API[13]”, “上传好友图片”)
apilist.置文本 (“API[14]”, “上传群图片”)
apilist.置文本 (“API[15]”, “上传好友语音”)
apilist.置文本 (“API[16]”, “上传群语音”)
apilist.置文本 (“API[17]”, “上传头像”)
apilist.置文本 (“API[18]”, “设置群名片”)
apilist.置文本 (“API[19]”, “取昵称_从缓存”)
apilist.置文本 (“API[20]”, “强制取昵称”)
apilist.置文本 (“API[21]”, “获取skey”)
apilist.置文本 (“API[22]”, “获取pskey”)
apilist.置文本 (“API[23]”, “获取clientkey”)
apilist.置文本 (“API[24]”, “取框架QQ”)
apilist.置文本 (“API[25]”, “取好友列表”)
apilist.置文本 (“API[26]”, “取群列表”)
apilist.置文本 (“API[27]”, “取群成员列表”)
apilist.置文本 (“API[28]”, “设置管理员”)
apilist.置文本 (“API[29]”, “取管理层列表”)
apilist.置文本 (“API[30]”, “取群名片”)
apilist.置文本 (“API[31]”, “取个性签名”)
apilist.置文本 (“API[32]”, “修改昵称”)
apilist.置文本 (“API[33]”, “修改个性签名”)
apilist.置文本 (“API[34]”, “删除群成员”)
apilist.置文本 (“API[35]”, “禁言群成员”)
apilist.置文本 (“API[36]”, “退群”)
apilist.置文本 (“API[37]”, “解散群”)
apilist.置文本 (“API[38]”, “上传群头像”)
apilist.置文本 (“API[39]”, “全员禁言”)
apilist.置文本 (“API[40]”, “群权限_发起新的群聊”)
apilist.置文本 (“API[41]”, “群权限_发起临时会话”)
apilist.置文本 (“API[42]”, “群权限_上传文件”)
apilist.置文本 (“API[43]”, “群权限_上传相册”)
apilist.置文本 (“API[44]”, “群权限_邀请好友加群”)
apilist.置文本 (“API[45]”, “群权限_匿名聊天”)
apilist.置文本 (“API[46]”, “群权限_坦白说”)
apilist.置文本 (“API[47]”, “群权限_新成员查看历史消息”)
apilist.置文本 (“API[48]”, “群权限_邀请方式设置”)
apilist.置文本 (“API[49]”, “撤回消息_群聊”)
apilist.置文本 (“API[50]”, “撤回消息_私聊本身”)
apilist.置文本 (“API[51]”, “设置位置共享”)
apilist.置文本 (“API[52]”, “上报当前位置”)
apilist.置文本 (“API[53]”, “是否被禁言”)
apilist.置文本 (“API[54]”, “处理好友验证事件”)
apilist.置文本 (“API[55]”, “处理群验证事件”)
apilist.置文本 (“API[56]”, “查看转发聊天记录内容”)
apilist.置文本 (“API[57]”, “上传群文件”)
apilist.置文本 (“API[58]”, “创建群文件夹”)
apilist.置文本 (“API[59]”, “设置在线状态”)
apilist.置文本 (“API[60]”, “QQ点赞”)
apilist.置文本 (“API[61]”, “取图片下载地址”)
apilist.置文本 (“API[62]”, “记录致命错误”)
apilist.置文本 (“API[63]”, “查询好友信息”)
apilist.置文本 (“API[64]”, “查询群信息”)
apilist.置文本 (“API[65]”, “框架重启”)
apilist.置文本 (“API[66]”, “群文件转发至群”)
apilist.置文本 (“API[67]”, “群文件转发至好友”)
apilist.置文本 (“API[68]”, “好友文件转发至好友”)
apilist.置文本 (“API[69]”, “置群消息接收”)
apilist.置文本 (“API[70]”, “取群名称_从缓存”)
apilist.置文本 (“API[71]”, “发送免费礼物”)
apilist.置文本 (“API[72]”, “取好友在线状态”)
apilist.置文本 (“API[73]”, “取QQ钱包个人信息”)
apilist.置文本 (“API[74]”, “获取订单详情”)
apilist.置文本 (“API[75]”, “提交支付验证码”)
apilist.置文本 (“API[76]”, “领取红包”)
apilist.置文本 (“API[77]”, “分享音乐”)
apilist.置文本 (“API[78]”, “更改群聊消息内容”)
apilist.置文本 (“API[79]”, “更改私聊消息内容”)
apilist.置文本 (“API[80]”, “群聊口令红包”)
apilist.置文本 (“API[81]”, “群聊拼手气红包”)
apilist.置文本 (“API[82]”, “群聊普通红包”)
apilist.置文本 (“API[83]”, “群聊画图红包”)
apilist.置文本 (“API[84]”, “群聊语音红包”)
apilist.置文本 (“API[85]”, “群聊接龙红包”)
apilist.置文本 (“API[86]”, “群聊专属红包”)
apilist.置文本 (“API[87]”, “好友口令红包”)
apilist.置文本 (“API[88]”, “好友普通红包”)
apilist.置文本 (“API[89]”, “好友画图红包”)
apilist.置文本 (“API[90]”, “好友语音红包”)
apilist.置文本 (“API[91]”, “好友接龙红包”)

*/