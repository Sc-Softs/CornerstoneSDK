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

#ifndef CORNERSTONE_SDK_HEADER_TYPES_H_
#define CORNERSTONE_SDK_HEADER_TYPES_H_

#include <cstring>
#include <unordered_map>
#include <type_traits>
#include <algorithm>


#include "../sdk.h"
#include "utils-inl.h"

#include "../eport/etypes.h"
#include "../framework/constants.h"


class earray // 易语言数组
{
public:
    earray() noexcept;
    ~earray() noexcept;
    size_t GetDimension() const noexcept;

    void *data;

private:
    HANDLE heap;
};

template <class EType, class CType>
class earray1D // 易语言一维数组
    : public earray
{
public:
    size_t GetSize() const noexcept
    {
        return ((eint *)this->data)[1];
    }

    size_t Unpack(std::vector<CType> &array) const noexcept
    {
        if (this->GetDimension() != 1)
        {
            return -1;
        }
        auto size = this->GetSize();
        if constexpr (std::is_compound_v<EType>)
        {
            volatile EType **data = (volatile EType **)(((eint *)this->data) + 2);
            array.clear();
            for (decltype(size) i = 0; i < size; i++)
            {
                array.push_back((CType)*(const_cast<EType *>(*data)));
                data++;
            }
        }
        else
        {
            EType *data = (EType *)(((eint *)this->data) + 2);
            array.clear();
            for (auto i = 0; i < size; i++)
            {
                array.push_back(*data);
                data++;
            }
        }
        return size;
    }
};

// 易语言常量
constexpr ebool etrue = 1;
constexpr ebool efalse = 0;

// 易语言类型转换
constexpr ebool bool2ebool(const bool &b)
{
    return b ? etrue : efalse;
}

constexpr bool ebool2bool(const ebool &e)
{
    return e == etrue;
}

constexpr ebool b2e(const bool &b)
{
    return bool2ebool(b);
}

constexpr bool e2b(const ebool &e)
{
    return ebool2bool(e);
}

// WARNING: 使用完后请自行delete字符串指针，否则将造成内存泄露
const char* new_and_copy_str(const char* str);

//=============
//endregion

#pragma pack(4)
// 数据结构

#pragma pack()
#endif // CORNERSTONE_SDK_HEADER_TYPES_H_