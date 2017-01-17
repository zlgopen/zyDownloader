
### 用C++扩展Electron(node-nan版)

Electron内置的node.js，理论上可以通过扩展node.js来扩展Electron。但是通常由于系统中存在的node.js与Electron内置的node.js的版本号不同，给node.js编译的扩展是无法在Electron中使用的，需要一些特殊处理才行。

0.先安装node.js和python(2.7)。请参考：

* https://nodejs.org/
* https://www.python.org

1.新建一个demo项目: 创建demo目录，并进入其中，然后运行下面命令。

```
mkdir demo
cd  demo
npm init
```

运行npm init时，把『entry point』设置成main.js，之后会生成一个package.json(具体内容与输入参数有关):

```
{
  "name": "demo",
  "version": "1.0.0",
  "description": "a demo for node call native functions",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "keywords": [
    "node"
  ],
  "author": "",
  "license": "ISC"
}
```

2.安装electron和编译工具和头文件。

```
sudo npm install -g prebuild node-gyp electron
npm install nan bindings --save
```

3.用C++编写原生代码( 为了让目录结构整洁一点，我们把代码放到native只目录下)。

下面的文件(native/demo.cc)，添加一个Add方法，计算两个数之和:

```
#include <nan.h>

void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  double arg0 = info[0]->NumberValue();
  double arg1 = info[1]->NumberValue();
  v8::Local<v8::Number> num = Nan::New(arg0 + arg1);

  info.GetReturnValue().Set(num);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("add").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Add)->GetFunction());
}

NODE_MODULE(demo, Init)
```

4.写一个node-gyp的配置文件(文件名固定为binding.gyp)，用来编译C++代码。

```
{
  "targets": [
    {
      "target_name": "demo",
      "sources": [ "native/demo.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
```

5.运行配置脚本(如果没有增删文件，不需要每次运行）

```
node-gyp configure
```

6.编译C++程序(1.4.12是electron的版本号)。。

```
prebuild -b 1.4.12 -r electron
```

7.编写Electron的入口(main.js)：

```
const electron = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow

const path = require('path')
const url = require('url')
let mainWindow
function createWindow () {
  mainWindow = new BrowserWindow({width: 800, height: 600})
  mainWindow.loadURL(url.format({
    pathname: path.join(__dirname, 'index.html'),
    protocol: 'file:',
    slashes: true
  }))
  mainWindow.webContents.openDevTools()

  mainWindow.on('closed', function () {
    mainWindow = null
  })
}

app.on('ready', createWindow)

app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', function () {
  if (mainWindow === null) {
    createWindow()
  }
})
```

8.编写Electron的index.html

```
<!DOCTYPE html>
<html>
<script>
var demo = require('bindings')('demo.node')
window.onload = function() {
	document.write('add(3, 5) => ' + demo.add(3, 5));
}

</script>
</html>
```

9.测试效果：

```
Electron .
```

参考：

[node原生函数绑定指南](http://luismreis.github.io/node-bindings-guide/)

[electron快速上手](https://github.com/electron/electron-quick-start.git)

[prebuild工具](https://github.com/mafintosh/prebuild)

