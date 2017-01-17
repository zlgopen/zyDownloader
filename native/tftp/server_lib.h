#include "types_def.h"

char* get_local_ips(char buff[256], size_t n);
bool_t start_tftp_server(int port, const char* docroot, const char* filename, const char** err_msg);

