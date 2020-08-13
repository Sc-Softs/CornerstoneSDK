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

#ifndef CORNERSTONE_HEADER_UNTILS_INL_H_
#define CORNERSTONE_HEADER_UNTILS_INL_H_

#include "../sdk.h"

class Unpacker
{
public:
    Unpacker(const void *data)
    {
        this->data = (std::uint8_t *)data;
    }

    template <class RetT>
    RetT &get()
    {
        auto &ret = *((RetT *)data);
        data += sizeof(RetT);
        return ret;
    }

private:
    std::uint8_t *data;
};

class earray1D
{
public:
    /**
     * @brief 解包易语言数组（成员为简单类型）
     */
    template <class ESimpleT>
    static size_t Unpack(const void *data, std::vector<ESimpleT> &array)
    {
        auto unpacker = Unpacker(data);
        auto dimension = unpacker.get<eint>(); // 数组维度
        if (dimension != 1)                    // 只考虑1维的情况
        {
            return -1;
        }
        auto size = unpacker.get<eint>();
        array.clear();
        for (auto i = 0; i < size; i++)
        {
            array.push_back(unpacker.get<ESimpleT>());
        }
        return size;
    }

    /**
     * @brief 解包易语言数组（成员为自定义结构）
     */
    template <class EStructT>
    static size_t UnpackStruct(const void *data, std::vector<EStructT> &array)
    {
        auto unpacker = Unpacker(data);
        auto dimension = unpacker.get<eint>(); // 数组维度
        if (dimension != 1)                    // 只考虑1维的情况
        {
            return -1;
        }
        auto size = unpacker.get<eint>();
        array.clear();
        for (auto i = 0; i < size; i++)
        {
            volatile EStructT *pointer = unpacker.get<volatile EStructT *>();
            EStructT value = *(const_cast<EStructT *>(pointer)); // EStructT((const EStructT &)*pointer); // 强转是未定义行为
            array.push_back(value);
        }
        return size;
    }
};

template <class FuncT>
inline FuncT *_f(Json api, const char *name)
{
    return (FuncT *)((uintptr_t)api[name]);
}

#include <string>

/**
 * @brief 获取API返回的JSON文本中的返回码
 * @param retstr API返回的JSON文本
 * @return 返回码
 */
inline std::int32_t get_retcode(std::string retstr)
{
    return (std::int32_t)(Json::parse(retstr)["retcode"]);
}

inline std::string to_string(const char *value)
{
    return std::string(value);
}

inline std::string to_string(const std::string &value)
{
    return value;
}

template <class T>
inline std::string to_string(T value)
{
    return std::to_string(value);
}

/**
 * @brief 依次连接所有参数（无参数）
 * @return 空字符串
 */
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

constexpr std::uint32_t make_color(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    return r + g << 8 + b << 16;
}

constexpr void read_color(std::uint32_t color, std::uint8_t &r, std::uint8_t &g, std::uint8_t &b)
{
    b = color >> 16;
    g = color & 0x0000ff00 >> 8;
    r = color & 0x000000ff;
}

// 调试
#ifdef DEBUG
#define debug() MessageBoxA(nullptr, sum_string(__FUNCTION__, ":", __LINE__).c_str(), "DEBUG at", MB_OK | MB_ICONINFORMATION)
#else
#define debug()
#endif

#endif // CORNERSTONE_HEADER_UNTILS_INL_H_
