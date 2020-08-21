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

#pragma once

#include "../sdk.h"

#include <string>

/*
std::string GBKtoUTF8(const char* src_str);
std::string UTF8toGBK(const std::string& src_str);
*/

std::wstring UTF8ToWideChar(const std::string& utf8);
std::string WideCharToUTF8(const std::wstring& wstr);
std::wstring ANSIToWideChar(const std::string& ansi);
std::string WideCharToANSI(const std::wstring& wstr);
std::wstring ANSIWithUCS2ToWideChar(const std::string& ansi_with_ucs2);
std::string WideCharToANSIWithUCS2(const std::wstring& wstr, const std::wstring& force_escape_wchars = L"[\\]");
#define e2s_s(ansi_with_ucs2) WideCharToUTF8(ANSIWithUCS2ToWideChar(ansi_with_ucs2))
#define s2e_s(utf8) WideCharToANSIWithUCS2(UTF8ToWideChar(utf8))
#define e2s(ansi_with_ucs2) e2s_s(ansi_with_ucs2).c_str()
#define s2e(utf8) s2e_s(utf8).c_str()
