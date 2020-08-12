<h1>
  <p align=center>
    Cornerstone SDK
  </p>
</h1>

> Corn SDK for Modern C++

<p align=center>
  <a href="./todo.txt">
    <img src="https://img.shields.io/badge/API-99%25-important.svg" />
  </a>
  <a href="https://zh.cppreference.com">
    <img src="https://img.shields.io/badge/language-C++-informational.svg" />
  </a>
  <a href="./LICENSE">
      <img src="https://img.shields.io/badge/license-MIT-success.svg" />
  </a>
</p>

## **目前此SDK可能还有一些API存在漏洞**

[下载地址](https://github.com/Sc-Softs/CornerstoneSDK/releases)

**此SDK在 <font size="4">[MIT](./LICENSE)</font> 许可证下发布**

Copyright &copy; 2020 Contributors of Cornerstone SDK

本SDK采用 **GN(Generate Ninja)** 和 **Ninja** 作为构建工具

GN 和 Ninja 已经编译好并附带在 `bin` 目录下，GN 和 Ninja 构建工具版权属于 &copy; Google Inc.

如果您有兴趣，可以尝试将开发环境迁移到 Visual Studio 2015 或更新的 MSVC 环境上

但是，最新的 MSVC 编译器已经不支持比XP老的系统并且要安装相关的运行库(大部分人也不知道需要设置 `/MT` 才能静态编译)

## 插件编写方法

1. 修改 `handler.cc` 和 `config.h`
   
2. 运行 `./build.cmd` 来编译和链接
   
   - 生成的插件文件在 `out` 目录下
  
   - 如果出现链接问题，请尝试运行 `./clean.cmd` 后再次编译

   - 如果觉得麻烦，此 SDK 附带 VSCode 运行配置,可以执行菜单 `终端->运行生成任务` 来编译，执行 `终端->运行任务->清理` 来删除临时文件 

## 提示

- 若要修改dll名称，请修改 `BUILD.gn`

- 如果你新加入了新的C++源文件(\*.cc,\*.cpp,\*.cxx,\*.c,\*.C)，你需要在 `BUILD.gn` 里声明它

  - 对于一般用户，请只修改 `handler.cc` 和 `config.h` ，**防止 SDK 损坏**

- 所有API均在在类 `app` 里面，调用例子参见 `handler.cc`

- 插件信息和所需权限请在 `config.h` 里面修改。

- 你可以直接在 `build.cmd` 里面加上复制dll到对应插件安装目录的命令

- **本SDK包含C++14标准特性**


- 如果你觉得编译慢，请执行 `g++ xxx.h` 命令，将头文件预编译成二进制

- C++源文件和头文件全部采用 **UTF8编码** ，易语言采用 **GBK编码** ，请使用 `GBKtoUTF8` 和 `UTF8toGBK` 函数来转换编码
   
## 推荐的C++插件开发环境

- Cornerstone SDK

- TDM-GCC

  - 注意安装时要选添加PATH

- [Visual Studio Code](https://code.visualstudio.com/) 和插件:

  - Chinese (Simplified) Language Pack for Visual Studio Code

  - cpptools

  - gn

  - Path Intellisense

  - Material Theme

  - Material Theme Icons

## 鸣谢

- Corn SDK

- [Visual Studio Code](https://code.visualstudio.com/)

- [JSON for modern C++](https://github.com/nlohmann/json)

- [TDM GCC](https://jmeubank.github.io/tdm-gcc/) 

- [GN/Ninja](http://www.ninja-build.org/)
