#ifndef PROGRESS_H
#define PROGRESS_H

#include "types_def.h"

BEGIN_C_DECLS

typedef void (*on_progress_t)(void* ctx, const char* tag, size_t finish, size_t total);

void progress_set_hook(on_progress_t on_progress, void* ctx);
void progress_notify(const char* tag, size_t finish, size_t total);

END_C_DECLS

#endif//
