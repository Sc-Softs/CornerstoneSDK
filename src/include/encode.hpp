#pragma once
#include <windows.h>
#include <string>

namespace code
{
    inline std::string UTF8Encode(const char *src_str)
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

    inline const char* UTF8Decode(const std::string& src_str)
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
        return strTemp.c_str();
    }
}; // namespace code
//#ifndef USE_E_TYPES
inline std::string e2s(const char* src_str)
{
    return code::UTF8Encode(src_str);
}
inline const char* s2e(const std::string& src_str)
{
    return code::UTF8Decode(src_str);
}
//#else

//#endif