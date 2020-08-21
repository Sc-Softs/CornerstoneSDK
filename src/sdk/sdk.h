/*
Cornerstone SDK v0.2.0
-- 面向现代 C++ 的 Corn SDK
兼容 Corn SDK v2.6.9
https://github.com/Sc-Softs/CornerstoneSDK

使用 MIT License 进行许可
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

#ifndef CORNERSTONE_SDK_HEADER_SDK_H_
#define CORNERSTONE_SDK_HEADER_SDK_H_

// 系统
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// 第三方
#include "third_party/json.hpp"
using Json = nlohmann::json;

// 工具
#include "encoding/encoding.h"
#include "utils/types.h"
#include "utils/utils-inl.h"

// API
#include "api/api.h"

// 好友消息事件
EventProcessEnum OnPrivateMessage(PrivateMessageData &data);
// 群消息事件
EventProcessEnum OnGroupMessage(GroupMessageData &data);
// 插件卸载事件
EventProcessEnum OnUninstall();
// 插件设置事件 这里可以弹出对话框
EventProcessEnum OnSettings();
// 插件被启用事件
EventProcessEnum OnEnabled();
// 插件被禁用事件
EventProcessEnum OnDisabled();
// 其他事件
EventProcessEnum OnEvent(EventData &data);

// 私聊消息事件回调包装
EventProcessEnum ECallBack_OnPrivateMessage(volatile _EType_PrivateMessageData* eData);
// 群消息事件回调包装
EventProcessEnum ECallBack_OnGroupMessage(volatile _EType_GroupMessageData* eData);
// 插件卸载事件回调包装（未知参数）
EventProcessEnum ECallBack_OnUninstall(void*);
// 插件设置事件回调包装（未知参数）
EventProcessEnum ECallBack_OnSettings(void*);
// 插件被启用事件回调包装（未知参数）
EventProcessEnum ECallBack_OnEnabled(void*);
// 插件被禁用事件回调包装（未知参数）
EventProcessEnum ECallBack_OnDisabled(void*);
// 其他事件回调包装
EventProcessEnum ECallBack_OnEvent(volatile _EType_EventData* eData);

// API对象
class API;
extern API *api;

#endif // CORNERSTONE_SDK_HEADER_SDK_H_
