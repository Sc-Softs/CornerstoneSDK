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

class UnPack{
public:
    UnPack(void *data){
        this->data = (uint8_t *)data;
    }
    template <class RetT>
    RetT& get(){
        RetT& tmp = *(RetT*)(data + offset);
        offset += sizeof(RetT);
        return tmp;
    }
private:
    uint8_t *data;
    int offset = 0;
};

template <class FuncT>
inline FuncT* _f(Json api, const char* name)
{
    return (FuncT*)((uintptr_t)api[name]);
}

#endif  // CORNERSTONE_HEADER_UNTILS_INL_H_