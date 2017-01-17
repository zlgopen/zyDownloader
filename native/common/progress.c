#include "progress.h"
#include <stdio.h>

static on_progress_t s_on_progress = NULL;
static void* s_on_progress_ctx = NULL;

void progress_set_hook(on_progress_t on_progress, void* ctx) {
	s_on_progress = on_progress;
	s_on_progress_ctx = ctx;
}

void progress_notify(const char* tag, size_t finish, size_t total) {
	if(s_on_progress) {
		s_on_progress(s_on_progress_ctx, tag, finish, total);
	}
	printf("progress_notify: %s %zu %zu\n", tag, finish, total);
}
