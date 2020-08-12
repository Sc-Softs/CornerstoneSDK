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

#ifndef CORNERSTONE_HEADER_SDK_H_
#define CORNERSTONE_HEADER_SDK_H_

//系统
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// 第三方
#include "third_party/json.hpp"

// 工具
#include "utils/types.h"
#include "utils/utils-inl.h"

// API
#include "api/api.h"

// 好友消息事件
EventProcess OnPrivateMessage(volatile PrivateMessageData *data);
// 群消息事件
EventProcess OnGroupMessage(volatile GroupMessageData *data);
// 插件卸载事件（未知参数）
EventProcess OnUninstall(void *);
// 插件设置事件（未知参数），这里可以弹出对话框
EventProcess OnSettings(void *);
// 插件被启用事件（未知参数）
EventProcess OnEnabled(void *);
// 插件被禁用事件（未知参数）
EventProcess OnDisabled(void *);
// 事件消息
EventProcess OnEvent(volatile EventData *data);

// 插件入口点，extern "C" 防止命名重整
extern "C" etext __stdcall apprun(etext apidata, etext pluginkey);

// 调试
#ifdef DEBUG
#define debug() MessageBoxA(nullptr, (string(__FUNCTION__) + ":" + std::to_string(__LINE__)).c_str(), "DEBUG at", MB_OK | MB_ICONINFORMATION)
#else
#define debug()
#endif

// API对象
class API;
extern API *api;

// 其他
#include <string>

/**
 * @brief 获取API返回的JSON文本中的返回码
 * @param retstr API返回的JSON文本
 */
inline int32_t get_retcode(std::string retstr)
{
    return (int32_t)(Json::parse(retstr)["retcode"]);
}

inline std::string to_string(const char *value)
{
    return string(value);
}

inline std::string to_string(const string &value)
{
    return value;
}

template <class T>
inline std::string to_string(T value)
{
    return std::to_string(value);
}

inline std::string sum_string()
{
    return "";
}

/**
 * @brief 依次连接所有参数
 * @return 所有参数连接后的字符串
 */
template <class T, class... Types>
inline std::string sum_string(T first, Types... args)
{
    if (sizeof...(args) == 0)
    {
        return to_string(first);
    }
    else
    {
        return to_string(first) + sum_string(args...);
    }
}

#endif // CORNERSTONE_HEADER_SDK_H_
