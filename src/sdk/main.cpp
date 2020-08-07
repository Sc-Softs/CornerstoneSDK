#include <iostream>
#include <fstream>
#include "app.hpp"
Application *app = nullptr;
EXPORT_FN(text) apprun(text apidata, text pluginkey)
{
    // 初始化API，请勿删除
    app = new Application(apidata, pluginkey);
    // 将插件信息提交给框架
    return app->getJSON();
}