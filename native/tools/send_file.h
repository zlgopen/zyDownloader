
#include <stdio.h>
#include "fymodem.h"

void send_file(const char* filename, stream_t* s) {
	FILE* fp = fopen(filename, "r+b");

	if(fp != NULL) {
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* buff = (char*)malloc(len);
		fread(buff, len, 1, fp);
		const char* err_msg = NULL;		
		fymodem_send(s, (uint8_t*)buff, len, "data.bin", &err_msg);
		
		free(buff);
		fclose(fp);
	}
}
