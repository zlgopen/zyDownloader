#include "stream_tcp.h"
#include "send_file.h"
//
// 用TCP+ymodem传输文件的客户端（仅用于测试ymodem协议）
//
int main(int argc, char* argv[]) {
	if(argc < 4) {
		printf("Usage: %s host port filename\n", argv[0]);
		return 1;
	}

	const char* host = argv[1];
	int port = atoi(argv[2]);
	const char* filename = argv[3];

	stream_t* s = tcp_connect(host, port);
	if(s != NULL) {
		send_file(filename, s);
		stream_close(s);
	}

	return 0;
}
