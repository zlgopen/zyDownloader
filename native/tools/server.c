#include <stdio.h>
#include "stream_tcp.h"
#include "fymodem.h"

//
// 用TCP+ymodem传输文件的服务器（仅用于测试ymodem协议）
//
int main() {
	char filename[FYMODEM_FILE_NAME_MAX_LENGTH] = {0};
	socketInit();
	char buff[3*1024*1024] = {0};
	int sock = tcp_listen(DEFAULT_PORT);
	if(sock > 0) {
		printf("listen on %d\n", DEFAULT_PORT);
		stream_t* s = tcp_accept(sock);
		int ret = fymodem_receive(s,(uint8_t*) buff, sizeof(buff), filename);
		printf("%s: len=%d\n", filename, ret);
		stream_close(s);
		
		FILE* fp = fopen(filename, "w+b");
		fwrite(buff, ret, 1, fp);
		fclose(fp);
	}
	socketDeinit();
	return 0;
}
