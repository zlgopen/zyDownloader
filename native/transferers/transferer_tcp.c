#include "url.h"
#include "fymodem.h"
#include "err_msg.h"
#include "common.h"
#include "progress.h"
#include "stream_tcp.h"
#include "transferer_tcp.h"
#include "transferer_factory.h"

static transferer_desc_t s_transferer_tcp_creator_desc;

typedef struct _transferer_tcp_t {
	transferer_t base;
	size_t total_size;
	size_t sent_size;
	stream_t* stream;
	url_t* url;
}transferer_tcp_t;

static void transferer_tcp_on_progress(void* ctx, const char* tag, size_t finish, size_t total) {
	(void)tag;
	transferer_tcp_t* tcp = (transferer_tcp_t*)ctx;
	tcp->sent_size = finish;
	tcp->total_size = total;
	printf("transferer_tcp_on_progress: %zu/%zu\n", finish, total);
}

static bool_t transferer_tcp_start(transferer_t* t, const char** err_msg){
	transferer_tcp_t* tcp = (transferer_tcp_t*)t;
	url_t* url = tcp->url;
	
	const char* server = url_get_param(url, "server");
	const char* sport = url_get_param(url, "port");

	int port = sport != NULL ? atoi(sport) : 9988;

	tcp->stream = tcp_connect(server, port);

	SET_ERR_MSG_IF(!tcp->stream, err_msg, MSG_CONNECT_FAILED);
	return_value_if_fail(tcp->stream != NULL, FALSE);
	char* path = url->path;
	progress_set_hook(transferer_tcp_on_progress, tcp);

	int size = 0;
	char* buff = read_file(path, &size);
	SET_ERR_MSG_IF(!buff, err_msg, MSG_OPEN_FILE_FAILED);
	return_value_if_fail(buff != NULL && size > 0, FALSE);

	tcp->sent_size = 0;
	tcp->total_size = size + 1024;
	bool_t ret = fymodem_send(tcp->stream, (uint8_t*)buff, size, url->filename, err_msg);
	free(buff);
	printf("fymodem_send done\n");

	return ret;
}

static size_t transferer_tcp_get_total_size(transferer_t* t){
	transferer_tcp_t* tcp = (transferer_tcp_t*)t;
	return tcp->total_size;
}

static size_t transferer_tcp_get_sent_size(transferer_t* t){
	transferer_tcp_t* tcp = (transferer_tcp_t*)t;
	return tcp->sent_size;
}

static void transferer_tcp_destroy(transferer_t* t){
	transferer_tcp_t* tcp = (transferer_tcp_t*)t;
	stream_close(tcp->stream);
	url_unref(tcp->url);
	memset(tcp, 0x00, sizeof(transferer_tcp_t));
}

static bool_t transferer_is_valid_url(url_t* url) {
	return url != NULL && strcmp(s_transferer_tcp_creator_desc.name, url->schema) == 0 
		&& url_get_param(url, "server") != NULL && url->path;
}

transferer_t* transferer_tcp_create(url_t* url) {
	url_print(url);
	if(!transferer_is_valid_url(url)) {
		return NULL;
	}
	transferer_tcp_t* tcp = (transferer_tcp_t*)calloc(1, sizeof(transferer_tcp_t));
	tcp->url =  url_ref(url);
	
	transferer_t* transferer = (transferer_t*)tcp;
	transferer->start = transferer_tcp_start;
	transferer->get_total_size = transferer_tcp_get_total_size;
	transferer->get_sent_size = transferer_tcp_get_sent_size;
	transferer->destroy = transferer_tcp_destroy;

	return (transferer_t*)tcp;
}

static const char* s_props_desc ="[\
	{\"type\":\"text\", \"name\":\"Server\", \"path\":\"server\", \"defValue\":\"localhost\"}, \
	{\"type\":\"number\", \"name\":\"Port\", \"path\":\"port\", \"defValue\":9988} \
]";

static const char* transferer_tcp_get_props_desc() {
	return s_props_desc;
}

bool_t transferer_tcp_register_creator_desc() {
	s_transferer_tcp_creator_desc.name = "tcp";
	s_transferer_tcp_creator_desc.create = transferer_tcp_create;
	s_transferer_tcp_creator_desc.get_props_desc = transferer_tcp_get_props_desc; 

	transferer_factory_register(&s_transferer_tcp_creator_desc);
	
	return TRUE;
}
