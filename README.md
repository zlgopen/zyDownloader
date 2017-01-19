# 开发板下载工具：

主要特色：
--------------------------
* 采用自描述的插件式设计，支持不同的下载方式，增加新的下载方式不需要修改界面。

* 界面用JS开发，实现用C/C++开发。界面和实现完全分离，同时支持图形界面和命令行界面。

* 目前支持基于串口的ymodem协议下载、TFTP网络下载和基于TCP的ymodem协议下载（仅用于测试ymodem协议）。

* 支持Linux、MacOS和Windows多个平台。

* 支持国际化，根据当前系统选择适当的语言。

预编译好的安装包
--------------------------
* 在[release下](https://github.com/ZHIYUAN-Electronics/zyDownloader/releases)可以下载预编译好的安装包。

安装依赖的工具:
--------------------------
0.先安装node.js, make, cmake, git和python(2.7)。请参考：

* https://nodejs.org/
* https://www.python.org
* https://git-scm.com/download
* https://cmake.org/download/
* http://www.equation.com/servlet/equation.cmd?fa=make

```
npm install -g asar prebuild node-gyp
npm install
```

编译:
-------------------------

```
make
```

测试运行:
-------------------------

```
Electron .
```

发布:
-------------------------

```
release.sh (or release.bat)
npm run dist
```

(生成的安装包在release/dist目录下)

目录结构:
-------------------------
* src          typescript开发的界面相关的代码(参考文件夹内的README)。
* js           typescript编译后生成的JS代码。
* www          Electron的相关的文件。
* www/asserts  GUI主题数据。
* native       C/C++开发的代码(参考文件夹内的README)。

