#include <iostream>
#include <fstream>
#include "app.hpp"
Application *app = nullptr;
EXPORT_FN(text) apprun(text apidata, text pluginkey)
{
    app = new Application(apidata,pluginkey);
    auto tmp = app->getJSON();//这几步千万不能省略，否则会导致莫名其妙的无法加载
    auto t = code::UTF8Decode(tmp.c_str());
    return t.c_str();
}