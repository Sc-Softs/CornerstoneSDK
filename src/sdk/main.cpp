#include <string>
#include "app.hpp"

Application *app = nullptr;

EXPORT_FN(text) apprun(text apidata, text pluginkey)
{
    // 初始化API，请勿删除
    app = new Application(apidata, pluginkey);
    // 将插件信息提交给框架
    auto tmp = app->getJSON();
    tmp = code::UTF8Decode(tmp.c_str());//转码给E语言。
    auto cstr = new char[tmp.size() + 1];//如果直接返回c_str()，有时会崩溃。
    cstr[tmp.size()] = '\0';//确保没事。
    strcpy(cstr, tmp.c_str());
    return cstr;//不知道E语言会不会回收这个内存？
}