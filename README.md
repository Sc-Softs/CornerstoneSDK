<h1>
  <p align=center>
    <b>
      Cornerstone SDK
    </b>
  </p>
</h1>

<h3>
  <p align="center">
    面向现代 C++ 的 Corn SDK
  </p>

  <p align="center">
    <a href="https://github.com/Sc-Softs/CornerstoneSDK/releases">
      <img src="https://img.shields.io/badge/release-v0.2.1-important.svg" />
    </a>
    <a href="https://zh.cppreference.com/w/cpp/17">
      <img src="https://img.shields.io/badge/language-C++17-informational.svg" />
    </a>
    <a href="./LICENSE">
        <img src="https://img.shields.io/badge/license-MIT-success.svg" />
    </a>
  </p>
  <p align="center">
    兼容 Corn SDK v2.6.9
  </p>
  <p align="center">
    <a href="https://github.com/Sc-Softs/CornerstoneSDK/releases">
      下载地址
    </a>
  </p>
</h3>

---

## **此 SDK 的部分 API 尚未经过测试，可能存在漏洞**

## **欢迎提交 [Issue](https://github.com/Sc-Softs/CornerstoneSDK/issues) 和 [PR](https://github.com/Sc-Softs/CornerstoneSDK/pulls)，感谢您的贡献**

---

## 编写插件

- 在 [Releases页面](https://github.com/Sc-Softs/CornerstoneSDK/releases) 下载 SDK 的最新版本下方 `Assets` 中的 `Source code (zip)` 并解压

- 在 `src/config.h` 里设置插件信息和所需权限

- 在 `src/plugin.cc` 里编写事件处理函数

  - 相关 API 可通过类 `API` 的全局对象 `api` 调用

    - `SilkDecode`（silk解码）和 `SilkEncode`（silk编码）两个 API 尚未实现

## 构建插件（使用 Visual Studio + MSVC）
- 需要支持部分 C++17 特性的编译器

  - `MSVC 19.12+`（即 `VS 2017 15.5+` 或 `VS 2019`）

- 推荐使用的开发环境

  - [Visual Studio 2019](https://visualstudio.microsoft.com/vs/) 

    - `使用 C++ 的桌面开发` 工作负载

- 使用 VS 打开 `CornerstoneSDK.sln` 来打开SDK

- 执行 `生成->清理 CornerstoneSDK` 来清理中间文件

  - 无需手动运行

- 执行 `生成->生成 CornerstoneSDK（Ctrl+B）` 来构建插件

  - 生成的中间文件在 `build/` 目录下

  - 生成的插件文件在 `out/` 目录下

    - 若要修改插件文件名，请在 `CornerstoneSDK 属性页->配置属性->常规` 中修改 `目标文件名`（注意选择 `配置->所有配置`）

- 如果需要使用其他 C++ 源文件，请 `右键单击 Plugin 筛选器->添加->新建项/现有项`

- 可以在 `CornerstoneSDK 属性页->配置属性->生成事件->生成后事件` 中加上复制编译后的插件到插件安装目录的命令（注意选择 `配置->所有配置`）

## 构建插件（使用 Visual Studio Code + GN + Ninja）
- GN 和 Ninja 已经编译好并附带在 `bin/` 目录下，GN 和 Ninja 的版权属于 &copy; Google Inc.

- 需要支持部分 C++17 特性的编译器

  - `GCC 7+` 或 `Clang 3.9+`

- 推荐使用的开发环境

  - [tdm-gcc 9.2.0](https://jmeubank.github.io/tdm-gcc/)

    - 建议下载安装 `32-bit-only` 版本

    - 注意安装时选择添加 `PATH`

  - [Visual Studio Code](https://code.visualstudio.com/) 和插件：

    - [Chinese (Simplified) Language Pack](https://marketplace.visualstudio.com/items?itemName=MS-CEINTL.vscode-language-pack-zh-hans)

    - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

    - [GN](https://marketplace.visualstudio.com/items?itemName=npclaudiu.vscode-gn)（可选）

    - [Path Intellisense](https://marketplace.visualstudio.com/items?itemName=christian-kohler.path-intellisense)（可选）

    - [TODO Highlight](https://marketplace.visualstudio.com/items?itemName=wayou.vscode-todo-highlight)（可选）

- 使用 VSCode 打开此文件夹来打开SDK

- 执行 `终端->运行任务->清理` 来清理中间文件

  - 也可以手动运行 `clean.cmd`

  - 若只修改了头文件则必须在编译前运行

  - 遇到未知的编译错误时也可以尝试运行

- 执行 `终端->运行生成任务（Ctrl+Shift+B）` 来构建插件

  - 也可以手动运行 `build.cmd`

  - 生成的中间文件在 `build/` 目录下

  - 生成的插件文件在 `out/` 目录下

    - 若要修改插件文件名，请在 `BUILD.gn` 中修改 `plugin_name`

- 如果需要使用其他 C++ 源文件，请在 `BUILD.gn` 中修改 `sources`

- 可以在 `build.cmd` 末尾加上复制编译后的插件到插件安装目录的命令

## 提示
- 以 `e` 开头的类型均为易语言原生类型，如 `ebool` 和 `etext`

- 若处理易语言结构（自定义数据类型）时遇到错误，可以考虑使用 `volatile` 修饰符来修饰相关指针

- C++ 源文件和头文件均采用 `UTF8` 编码，易语言采用 `ANSI` 编码混杂 `UCS2` 编码，必要时请使用 `e2s` 和 `s2e` 宏来转换编码

  - `etext` 对象均使用 `ANSI` 编码混杂 `UCS2` 编码，`std::string` 对象通常使用 `UTF8` 编码

  - API 调用使用的参数和返回值（不包括 `etext` 类型）均使用 `UTF8` 编码

- 如果编译缓慢，可以尝试预编译头文件

## 版权

Cornerstone SDK 使用 [MIT License](./LICENSE) 进行许可

版权所有 &copy; 2020 Contributors of Cornerstone SDK

## 致谢

- Corn SDK

- [JSON for modern C++](https://github.com/nlohmann/json)

- [Visual Studio](https://visualstudio.microsoft.com/vs/)

- [Visual Studio Code](https://code.visualstudio.com/) 和插件

- [tdm-gcc](https://jmeubank.github.io/tdm-gcc/)

- [GN](https://gn.googlesource.com/gn/) & [Ninja](http://www.ninja-build.org/)
