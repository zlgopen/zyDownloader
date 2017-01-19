#include "url.h"
#include "common.h"
#include "progress.h"
#include "tftp/tftpx.h"
#include "tftp/server_lib.h"
#include "tftp/work_thread.h"
#include "transferer_tftp_server.h"

#include "transferer_factory.h"
static transferer_desc_t s_transferer_tftp_server_creator_desc;

typedef struct _transferer_tftp_server_t {
	transferer_t base;
	size_t total_size;
	size_t sent_size;
	url_t* url;
}transferer_tftp_server_t;

static void transferer_tftp_server_on_progress(void* ctx, const char* tag, size_t finish, size_t total) {
	(void)tag;
	transferer_tftp_server_t* tftp_server = (transferer_tftp_server_t*)ctx;
	tftp_server->sent_size = finish;
	tftp_server->total_size = total;
	printf("transferer_tftp_server_on_progress: %zu/%zu\n", finish, total);
}

static bool_t transferer_tftp_server_start(transferer_t* t, const char** err_msg){
	transferer_tftp_server_t* tftp_server = (transferer_tftp_server_t*)t;
	url_t* url = tftp_server->url;
	
	const char* sport = url_get_param(url, "port");
	int port = sport != NULL ? atoi(sport) : SERVER_PORT;

	progress_set_hook(transferer_tftp_server_on_progress, tftp_server);
	return start_tftp_server(port, url->dir, url->filename, err_msg);
}

static size_t transferer_tftp_server_get_total_size(transferer_t* t){
	transferer_tftp_server_t* tftp_server = (transferer_tftp_server_t*)t;
	return tftp_server->total_size;
}

static size_t transferer_tftp_server_get_sent_size(transferer_t* t){
	transferer_tftp_server_t* tftp_server = (transferer_tftp_server_t*)t;
	return tftp_server->sent_size;
}

static void transferer_tftp_server_destroy(transferer_t* t){
	transferer_tftp_server_t* tftp_server = (transferer_tftp_server_t*)t;
	url_free(tftp_server->url);
	memset(tftp_server, 0x00, sizeof(transferer_tftp_server_t));
}

static bool_t transferer_is_valid_url(url_t* url) {
	return url != NULL && strcmp(s_transferer_tftp_server_creator_desc.name, url->schema) == 0 && url->path;
}

transferer_t* transferer_tftp_server_create(const char* surl) {
	url_t* url = url_parse(surl);

	if(!transferer_is_valid_url(url)) {
		url_print(url);
		url_free(url);
		return NULL;
	}
	url_print(url);

	transferer_tftp_server_t* tftp_server = (transferer_tftp_server_t*)calloc(1, sizeof(transferer_tftp_server_t));
	tftp_server->url =  url;
	
	transferer_t* transferer = (transferer_t*)tftp_server;
	transferer->start = transferer_tftp_server_start;
	transferer->get_total_size = transferer_tftp_server_get_total_size;
	transferer->get_sent_size = transferer_tftp_server_get_sent_size;
	transferer->destroy = transferer_tftp_server_destroy;

	return (transferer_t*)tftp_server;
}

static char s_props_desc[1024];
static const char* s_props_desc_temp ="[\
{\"type\":\"text-readonly\", \"name\":\"IP\", \"path\":\"ip\", \"defValue\":\"%s\"}, \
{\"type\":\"number\", \"name\":\"Port\", \"path\":\"port\", \"defValue\":69} \
]";

static const char* transferer_tftp_server_get_props_desc() {
	char ips[256];
	get_local_ips(ips, 10);

	snprintf(s_props_desc, sizeof(s_props_desc), s_props_desc_temp, ips); 

	return s_props_desc;
}

bool_t transferer_tftp_server_register_creator_desc() {
	s_transferer_tftp_server_creator_desc.name = "tftp_server";
	s_transferer_tftp_server_creator_desc.create = transferer_tftp_server_create;
	s_transferer_tftp_server_creator_desc.get_props_desc = transferer_tftp_server_get_props_desc; 

	transferer_factory_register(&s_transferer_tftp_server_creator_desc);

	printf("%s\n", transferer_tftp_server_get_props_desc());

	return TRUE;
}

