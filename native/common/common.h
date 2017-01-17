
#ifndef COMMON_H
#define COMMON_H

#include "types_def.h"

BEGIN_C_DECLS

char* get_file_name(char* path);
char* read_file(const char* filename, int* size);

END_C_DECLS

#endif//COMMON_H
