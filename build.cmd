@echo off

%~d0
cd %~dp0
set path=%path%;%~dp0\bin\

::生成配置文件
gn gen build

::清理缓存
::del build\build\plugin.o /q >nul 2>&1

ninja -C "build" -j 5

::TODO: 可以在这里加上复制编译后的插件到对应插件安装目录的命令
:: copy out\*.dll ...
