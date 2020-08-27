/*
Cornerstone SDK v0.2.0
-- 面向现代 C++ 的 Corn SDK
兼容 Corn SDK v2.7.1
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

#include "../sdk.h"

#include <cstring>

earray::earray() noexcept
{
    // 分配一个空间专门给框架释放着玩
    this->heap = GetProcessHeap();
    this->data = HeapAlloc(heap, HEAP_ZERO_MEMORY, 1);
    *((std::uint8_t*)this->data) = 1;
}

earray::~earray() noexcept
{
    HeapFree(this->heap, 0, this->data);
}

size_t earray::GetDimension() const noexcept
{
    return ((eint *)this->data)[0];
}

// WARNING: 使用完后请自行delete字符串指针，否则将造成内存泄露
const char* new_and_copy_str(const char* str)
{
    size_t size = std::strlen(str);
    char* newStr = new char[size + 1];
    std::memcpy(newStr, str, size + 1);
    newStr[size] = '\0';
    return newStr;
}
