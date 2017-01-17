#include "transferer_tcp.h"
#include "transferer_serial.h"
#include "transferer_tftp_server.h"
#include "transferer_factory.h"

static void register_transferers() {
	transferer_tcp_register_creator_desc();
	transferer_serial_register_creator_desc();
	transferer_tftp_server_register_creator_desc();

	return;
}

//
// 命令行的下载工具，URL的格式如下：
//
//URL="tcp://localhost/./data.bin?server=localhost&port=9988"
//URL="tftp_server://localhost/./data.bin?server=localhost&port=10220"
//URL="serial://localhost/./data.bin?device=/dev/tty.wchusbserial14120&baudrate=115200&bytesize=8&stopbits=1&flowcontrol=0&parity=0"
//

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Usage: %s url\n", argv[0]);
		return 1;
	}
	const char* url = argv[1];
	
	socketInit();
	register_transferers();
	transferer_t* transferer = transferer_factory_create(url);
	if(transferer) {
		const char* err_msg = NULL;
		if(!transferer_start(transferer, &err_msg)) {
			printf("result: %s\n", err_msg);
		}
		transferer_destroy(transferer);
	}else{
		printf("not supported %s\n", url);
	}
	socketDeinit();

	return 0;
}

