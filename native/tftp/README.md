tftp协议的实现：
-----------------------------------
原始项目网址：https://github.com/ideawu/tftpx

主要修改：
-----------------------------------
1.增加获取进度信息的接口。
2.编译成一个库。
3.一次只传输一个文件。
4.移植到windows。

对照测试工具(IPV4)：
-----------------------------------
https://www.kernel.org/pub/software/network/tftp/tftp-hpa/tftp-hpa-0.49.tar.bz2
