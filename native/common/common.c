
#include <stdio.h>
#include "common.h"

char* read_file(const char* filename, int* size) {
	FILE* fp = fopen(filename, "r+b");

	if(fp != NULL) {
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		return_value_if_fail(len > 0, NULL);

		char* buff = (char*)malloc(len);
		fread(buff, len, 1, fp);
		fclose(fp);
		
		*size = len;

		return buff;
	}else{
		perror("open file failed\n");
	}
	
	return NULL;
}

char* get_file_name(char* path) {
	char* filename = strrchr(path, '/');
	if(!filename) {
		filename = strrchr(path, '\\');
	}

	if(filename) {
		filename++;
	}else{
		filename = path;
	}

	return filename;
}
