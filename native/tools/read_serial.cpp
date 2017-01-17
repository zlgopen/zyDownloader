#include "stream_serial.h"
#include "send_file.h"
#include "url.h"

using serial::stopbits_t;
using serial::flowcontrol_t;
using serial::bytesize_t;
using serial::parity_t;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Usage: %s url\n", argv[0]);
		printf("Ex: %s \"serial://localhost/./data.bin?device=/dev/tty.wchusbserial14130&baudrate=115200&bytesize=8&stopbits=1&flowcontrol=0&parity=0\"\n", argv[0]);
		return 0;
	}

	url_t* url = url_parse(argv[1]);
	const char* s_baudrate = url_get_param(url, "baudrate");
	const char* s_parity = url_get_param(url, "parity");
	const char* s_bytesize = url_get_param(url, "bytesize");
	const char* s_flowcontrol = url_get_param(url, "flowcontrol");
	const char* s_stopbits = url_get_param(url, "stopbits");
	const char* device = url_get_param(url, "device");

	uint32_t baudrate = s_baudrate ? atoi(s_baudrate) : 115200;
	parity_t   parity = s_parity ? (parity_t)atoi(s_parity) : serial::parity_none;
	bytesize_t bytesize = s_bytesize ? (bytesize_t)atoi(s_bytesize) : serial::eightbits;
	stopbits_t stopbits = s_stopbits ? (stopbits_t)atoi(s_stopbits) : serial::stopbits_one;
	flowcontrol_t flowcontrol = s_flowcontrol ? (flowcontrol_t)atoi(s_flowcontrol) : serial::flowcontrol_none;

	stream_t* s = stream_serial_create(device, baudrate,
			bytesize, 
			parity, 
			stopbits, 
			flowcontrol);   
	printf("device=%s baudrate=%d bytesize=%d parity=%d stopbits=%d flowcontrol=%d\n", device, 
			(int)baudrate, (int)bytesize, (int)parity, (int)stopbits, (int)flowcontrol);
	int c = 0;
	while((c = stream_read_c(s)) > 0) {
		printf("%c", (char)c);
		fflush(stdout);
	}
	stream_close(s);

	return 0;
}
