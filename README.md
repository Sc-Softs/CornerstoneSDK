<h1>
  <p align=center>
    <b>
      Cornerstone
    </b>
    SDK
  </p>
</h1>

> Corn SDK for Modern C++

<p align=center>
  <a href="./todo.txt">
    <img src="https://img.shields.io/badge/API-99%25-important.svg" />
  </a>
  <a href="https://zh.cppreference.com">
    <img src="https://img.shields.io/badge/language-C++14-informational.svg" />
  </a>
  <a href="./LICENSE">
      <img src="https://img.shields.io/badge/license-MIT-success.svg" />
  </a>
</p>

[**下载地址**](https://github.com/Sc-Softs/CornerstoneSDK/releases)

## **目前此SDK可能还存在一些漏洞**

## **欢迎提交 [Issue](https://github.com/Sc-Softs/CornerstoneSDK/issues) 和 [PR](https://github.com/Sc-Softs/CornerstoneSDK/pulls)，感谢您的贡献**

Copyright &copy; 2020 Contributors of Cornerstone SDK

此 SDK 采用 **GN(Generate Ninja)** 和 **Ninja** 作为构建工具

GN 和 Ninja 已经编译好并附带在 `bin` 目录下，GN 和 Ninja 构建工具版权属于 &copy; Google Inc.

## 如何编写插件

- 修改 `plugin.cc` 和 `config.h`

- 运行 `./clean.cmd` 来清理部分中间文件

  - 若只修改了头文件则必须在编译前运行

  - 遇到未知的编译错误时也可以尝试运行

  - 也可以在 VSCode 中执行 `终端->运行任务->清理`

- 运行 `./build.cmd` 来编译和链接

  - 生成的中间文件在 `build` 目录下

  - 生成的插件文件在 `out` 目录下

  - 也可以在 VSCode 中执行 `终端->运行生成任务`

## 提示

- `SilkDecode`（silk解码）和 `SilkEncode`（silk编码）两个 API 尚未实现

- 请勿删除事件处理函数的参数带有的 `volatile` 修饰符

  - 若处理易语言结构（自定义数据类型）时遇到错误，也可以考虑使用 `volatile` 修饰符来修饰相关指针

- 相关 API 可通过类 `API` 的全局对象 `api` 调用，调用例子参见 `plugin.cc`

- 插件信息和所需权限请在 `config.h` 里面修改

- 以 `e` 开头的类型均为易语言原生类型，如 `ebool` 和 `etext`

- C++源文件和头文件均采用 `UTF8` 编码，但易语言采用 `GBK` 编码，必要时请使用 `GBKtoUTF8` 和 `UTF8toGBK` 函数来转换编码

  - `GBKtoUTF8` 和 `UTF8toGBK` 函数分别可以使用简写 `e2s` 和 `s2e`

  - `etext` 对象均使用 `GBK` 编码，`string` 对象通常使用 `UTF8` 编码

  - 相关API调用使用的参数和返回值（不包括 `etext` 类型）均使用 `UTF8` 编码

- 需要支持 C++14 特性的编译器才能正常使用此 SDK

- 若要修改插件文件名称，请修改 `BUILD.gn`

- 如果新加入了新的 C++ 源文件(\*.cc,\*.cpp,\*.cxx,\*.c,\*.C)，你需要在 `BUILD.gn` 里声明它

  - 一般用户可以只修改 `plugin.cc` 和 `config.h`

- 可以直接在 `build.cmd` 里面加上复制编译后的插件到对应插件安装目录的命令

- 如果编译缓慢，请执行 `g++ xxx.h` 命令，将头文件预编译成二进制

## 推荐的开发环境

- TDM-GCC

  - 注意安装时要选添加 PATH

  - 如果您有兴趣，可以尝试将开发环境迁移到 Visual Studio 2015 或更新的 MSVC 环境下

- [Visual Studio Code](https://code.visualstudio.com/) 和插件:

  - [Chinese (Simplified) Language Pack](https://marketplace.visualstudio.com/items?itemName=MS-CEINTL.vscode-language-pack-zh-hans)

  - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

  - [GN](https://marketplace.visualstudio.com/items?itemName=npclaudiu.vscode-gn)（可选）

  - [Path Intellisense](https://marketplace.visualstudio.com/items?itemName=christian-kohler.path-intellisense)（可选）

  - [TODO Highlight](https://marketplace.visualstudio.com/items?itemName=wayou.vscode-todo-highlight)（可选）

## 致谢

- Corn SDK

- [Visual Studio Code](https://code.visualstudio.com/) 和插件

- [JSON for modern C++](https://github.com/nlohmann/json)

- [TDM GCC](https://jmeubank.github.io/tdm-gcc/)

- [GN/Ninja](http://www.ninja-build.org/)
