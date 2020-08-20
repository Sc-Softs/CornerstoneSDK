/*
Cornerstone SDK v0.2.0
-- 面向现代 C++ 的 Corn SDK
兼容 Corn SDK v2.6.5
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

#include <string>
#include <cstring>

/*
std::string GBKtoUTF8(const char* src_str)
{
    auto len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, nullptr, 0);
    auto wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    auto str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, nullptr, nullptr);
    std::string strTemp = str;
    if (wstr)
        delete[] wstr;
    if (str)
        delete[] str;
    return strTemp;
}

std::string UTF8toGBK(const std::string& src_str)
{
    auto len = MultiByteToWideChar(CP_UTF8, 0, src_str.c_str(), -1, nullptr, 0);
    auto wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, src_str.c_str(), -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, nullptr, 0, nullptr, nullptr);
    auto szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, nullptr, nullptr);
    std::string strTemp(szGBK);
    if (wszGBK)
        delete[] wszGBK;
    if (szGBK)
        delete[] szGBK;
    return strTemp;
}
*/

std::wstring ToWideChar(std::uint32_t code_page, const std::string &src_str)
{
    auto len = MultiByteToWideChar(code_page, 0, src_str.c_str(), -1, nullptr, 0);
    if (!len)
    {
        return L"";
    }
    auto wstr_c = new wchar_t[len + 1];
    if (!wstr_c)
    {
        return L"";
    }
    memset(wstr_c, 0, len + 1);
    MultiByteToWideChar(code_page, 0, src_str.c_str(), -1, wstr_c, len);
    std::wstring wstr(wstr_c);
    delete[] wstr_c;
    return wstr;
}

std::string FromWideChar(std::uint32_t code_page, const std::wstring& src_wstr)
{
    auto len = WideCharToMultiByte(code_page, 0, src_wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (!len)
    {
        return "";
    }
    auto str_c = new char[len + 1];
    if (!str_c)
    {
        return "";
    }
    memset(str_c, 0, len + 1);
    WideCharToMultiByte(code_page, 0, src_wstr.c_str(), -1, str_c, len, nullptr, nullptr);
    std::string str(str_c);
    delete[] str_c;
    return str;
}

std::wstring UTF8ToWideChar(const std::string& utf8)
{
    return ToWideChar(CP_UTF8, utf8);
}

std::string WideCharToUTF8(const std::wstring& wstr)
{
    return FromWideChar(CP_UTF8, wstr);
}

std::wstring ANSIToWideChar(const std::string &ansi)
{
    return ToWideChar(CP_ACP, ansi);
}

std::string WideCharToANSI(const std::wstring& wstr)
{
    return FromWideChar(CP_ACP, wstr);
}


inline bool IsWideCharHex(wchar_t wch)
{
    return (wch >= L'0' && wch <= L'9') || (wch >= L'a' && wch <= L'f') || (wch >= L'A' && wch <= L'F');
}

inline std::uint8_t WideCharToHex(wchar_t wch)
{
    if (wch >= L'0' && wch <= L'9')
    {
        return wch - L'0';
    }
    else if (wch >= L'a' && wch <= L'f')
    {
        return wch - L'a' + 10;
    }
    else  // wch >= L'A' && wch <= L'F'
    {
        return wch - L'A' + 10;
    }
}

wchar_t UCS2ToWideChar(const std::wstring& ucs2)
{
    auto it = ucs2.cbegin();
    it += 2;  // L'\\u'
    uint16_t wch_value = 0;
    for (auto i = 0; i < 4; i++)
    {
        wch_value <<= 4;
        wch_value += WideCharToHex(*it);
        it++;
    }
    auto wch = static_cast<wchar_t>(wch_value);
    return wch;
}

std::wstring ANSIWithUCS2ToWideChar(const std::string& ansi_with_ucs2)
{
    auto wstr_with_ucs2 = ANSIToWideChar(ansi_with_ucs2);
    std::wstring wstr;
    wstr.reserve(wstr_with_ucs2.size() + 1);  // 预留 L'\0'
    std::wstring ucs2_tmp;
    ucs2_tmp.reserve(7);  // 预留 L'\0'
    for (auto it = wstr_with_ucs2.cbegin(), cend = wstr_with_ucs2.cend(); it != cend; it++)
    {
        if (*it == L'\\')
        {
            ucs2_tmp = L"\\";
            it++;
            if (it != cend && *it == L'u')
            {
                ucs2_tmp += L'u';
                it++;
                if (it != cend && IsWideCharHex(*it))
                {
                    ucs2_tmp += *it;
                    it++;
                    if (it != cend && IsWideCharHex(*it))
                    {
                        ucs2_tmp += *it;
                        it++;
                        if (it != cend && IsWideCharHex(*it))
                        {
                            ucs2_tmp += *it;
                            it++;
                            if (it != cend && IsWideCharHex(*it))
                            {
                                ucs2_tmp += *it;
                                wstr += UCS2ToWideChar(ucs2_tmp);
                                continue;
                            }
                        }
                    }
                }
            }
            wstr += ucs2_tmp;
            if (it == cend)
            {
                break;
            }
        }
        wstr += *it;
    }
    return wstr;
}

char HexToChar(uint8_t hex)
{
    if (hex <= 9)
    {
        return '0' + hex;
    }
    else  // hex >= 10 && hex <= 15
    {
        return 'a' + hex - 10;
    }
}

std::string WideCharToUCS2(wchar_t wch)
{
    auto wch_value = static_cast<uint16_t>(wch);
    std::string ucs2;
    ucs2.reserve(7);  // 预留 '\0'
    ucs2 += "\\u";
    ucs2 += HexToChar(wch_value >> 12);
    ucs2 += HexToChar((wch_value >> 8) & 0xf);
    ucs2 += HexToChar((wch_value >> 4) & 0xf);
    ucs2 += HexToChar(wch_value & 0xf);
    return ucs2;
}

std::string WideCharToANSIWithUCS2(const std::wstring& wstr)
{
    BOOL is_default_char_used = FALSE;
    auto len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, &is_default_char_used);
    if (!len)
    {
        return "";
    }
    // 如果能够用ANSI编码
    if (!is_default_char_used)
    {
        auto ansi_c = new char[len + 1];
        if (!ansi_c)
        {
            return "";
        }
        memset(ansi_c, 0, len + 1);
        WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, ansi_c, len, nullptr, nullptr);
        std::string ansi(ansi_c);
        delete[] ansi_c;
        return ansi;
    }
    else
    {
        auto wstr_c_tmp = new wchar_t[2];
        if (!wstr_c_tmp)
        {
            return "";
        }
        wstr_c_tmp[1] = L'\0';
        auto ansi_c_tmp = new char[8];  // 3应该够用了但是保险点还是分配个8
        if (!ansi_c_tmp)
        {
            delete[] wstr_c_tmp;
            return "";
        }
        std::string ansi_with_ucs2;
        // 对每个WideChar尝试使用ANSI编码
        for (auto it = wstr.cbegin(), cend = wstr.cend(); it != cend; it++)
        {
            // 如果字符在基础平面上
            if ((uint16_t)(*it) >> 11 != 0b11011)
            {
                is_default_char_used = FALSE;
                wstr_c_tmp[0] = *it;
                auto len = WideCharToMultiByte(CP_ACP, 0, wstr_c_tmp, -1, nullptr, 0, nullptr, &is_default_char_used);
                if (!len)
                {
                    delete[] wstr_c_tmp;
                    delete[] ansi_c_tmp;
                    return "";
                }
                // 如果能够用ANSI编码
                if (!is_default_char_used)
                {
                    memset(ansi_c_tmp, 0, len + 1);
                    WideCharToMultiByte(CP_ACP, 0, wstr_c_tmp, -1, ansi_c_tmp, len, nullptr, nullptr);
                    ansi_with_ucs2 += ansi_c_tmp;
                    continue;
                }
            }
            // 字符不在基础平面上或者无法编码
            ansi_with_ucs2 += WideCharToUCS2(*it);
        }
        delete[] wstr_c_tmp;
        delete[] ansi_c_tmp;
        return ansi_with_ucs2;
    }
}
