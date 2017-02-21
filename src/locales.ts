import {StringTable}    from "qtk";

var zhStrings = {
	"open file failed.":"打开文件失败。",
	"open serial port failed.":"打开串口失败。",
	"create socket failed.":"创建套接字失败。",
	"bind port failed.":"绑定端口失败。",
	"connect to server failed.":"连接到服务失败",
	"Download Type":"选择下载方式",
	"Change Settings":"修改设置",
	"Choose File":"选择文件",
	"Start Download":"开始下载",
	"tcp":"TCP",
	"serial(ymodem)":"串口(ymodem)",
	"tftp_server":"TFTP",
	"serial port":"串口",
	"baudrate":"波特率",
	"bytesize":"数据位",
	"stopbits":"停止位",
	"flowcontrol":"流控",
	"parity":"校验",
	"Yes":"确定",
	"No":"否",
	"OK":"确定",
	"IP":"IP地址",
	"Cancel":"取消",
	"Server":"服务器",
	"Port":"端口",
	"none":"无",
	"odd":"奇",
	"even":"偶",
	"software":"软件",
	"hardware":"硬件",
	"Download Failed: ":"无法下载: ",
	"Settings(serial(ymodem))":"串口设置",
	"Settings(tcp)":"TCP设置",
	"Downloading...":"正在下载...",
	"send file content failed.":"发送文件失败。",
	"send file header failed.":"发送文件头失败。",
	"sync peer failed.":"同步设备失败。",
	"get file header CRC failed.":"没有收到文件头的CRC回应。",
	"Settings(tftp_server)":"TFTP设置"
};

export function initLocales() {
	StringTable.set(zhStrings, "zh");
}

