#include "url.h"
#include <string>
#include "common.h"
#include "err_msg.h"
#include "fymodem.h"
#include "progress.h"
#include "stream_serial.h"
#include "transferer_serial.h"

using serial::stopbits_t;
using serial::flowcontrol_t;
using serial::bytesize_t;
using serial::parity_t;

typedef struct _transferer_serial_t {
	transferer_t base;
	size_t total_size;;
	size_t sent_size;
	stream_t* stream;
	url_t* url;
}transferer_serial_t;

static void on_progress(void* ctx, const char* tag, size_t finish, size_t total) {
	(void)tag;
	transferer_serial_t* serial = (transferer_serial_t*)ctx;
	serial->sent_size = finish;
	serial->total_size = total;
}

static bool_t transferer_serial_start(transferer_t* t, const char** err_msg){
	transferer_serial_t* serial = (transferer_serial_t*)t;
	url_t* url = serial->url;
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

	serial->stream = stream_serial_create(device, baudrate, bytesize, parity, stopbits, flowcontrol); 
	SET_ERR_MSG_IF(!serial->stream, err_msg, MSG_OPEN_SERIAL_FAILED);
	return_value_if_fail(serial->stream != NULL, FALSE);
	char* path = url->path;
	progress_set_hook(on_progress, serial);

	int size = 0;
	char* buff = read_file(path, &size);
	SET_ERR_MSG_IF(!buff, err_msg, MSG_OPEN_FILE_FAILED);
	return_value_if_fail(buff != NULL && size > 0, FALSE);
	serial->sent_size = 0;
	serial->total_size = size + 1024;
	bool_t ret = fymodem_send(serial->stream, (uint8_t*)buff, size, url->filename, err_msg);
	free(buff);

	printf("fymodem_send done\n");
	
	char lines[32];
	memset(lines, 0x00, sizeof(lines));
    stream_read(serial->stream, (uint8_t*)lines, sizeof(lines)-1);	
	printf("serial data:%s\n", lines);
	fflush(stdout);

	return ret;
}

static size_t transferer_serial_get_total_size(transferer_t* t){
	transferer_serial_t* serial = (transferer_serial_t*)t;
	return serial->total_size;
}

static size_t transferer_serial_get_sent_size(transferer_t* t){
	transferer_serial_t* serial = (transferer_serial_t*)t;
	return serial->sent_size;
}


static void transferer_serial_destroy(transferer_t* t){
	transferer_serial_t* serial = (transferer_serial_t*)t;
	stream_close(serial->stream);
	url_free(serial->url);
	memset(serial, 0x00, sizeof(transferer_serial_t));
}

static bool_t transferer_is_valid_url(url_t* url) {
	return url != NULL && strcmp("serial", url->schema) == 0 && url->host != NULL;
}

transferer_t* transferer_serial_create(const char* surl) {
	url_t* url = url_parse(surl);

	if(!transferer_is_valid_url(url)) {
		url_print(url);
		url_free(url);
		return NULL;
	}
	url_print(url);

	transferer_serial_t* serial = (transferer_serial_t*)calloc(1, sizeof(transferer_serial_t));
	serial->url =  url;
	
	transferer_t* transferer = (transferer_t*)serial;
	transferer->start = transferer_serial_start;
	transferer->get_total_size = transferer_serial_get_total_size;
	transferer->get_sent_size = transferer_serial_get_sent_size;
	transferer->destroy = transferer_serial_destroy;

	return (transferer_t*)serial;
}

#include "transferer_factory.h"

static std::string s_props_desc ="[\
	{\"type\":\"options\", \"name\":\"Device\", \"path\":\"device\", options:[\"Green\", \"Red\"}, \
]";


static const char* transferer_serial_get_props_desc() {
	std::string str = "";
	std::vector<serial::PortInfo> ports = serial::list_ports();
	size_t len = ports.size();
	str = "[{\"type\":\"options\", \"name\":\"serial port\", \"path\":\"device\",";
	if(len > 0) {
		for(size_t i = 0; i < len; i++) {
			serial::PortInfo pi = ports[i];
			if(i == 0) {
				str += "\"defValue\":\""+pi.port+"\", \"options\":[";
			}else{
				str += ", ";
			}
			str += "\""+pi.port+"\"";
		}
	}else{
		str += "\"defValue\":\"\", \"options\":[";
	}
	str += "]}";

	//baudrate
	str += ",{\"type\":\"options\", \"name\":\"baudrate\", \"path\":\"baudrate\",";
	str += "\"defValue\":\"115200\", \"options\" : [\"9600\", \"14400\", \"19200\", \"28800\", \"38400\", \"56000\", \"57600\", \"115200\", \"230400\", \"460800\", \"921600\"]}";
	
	//bytesize
	str += ",{\"type\":\"options\", \"name\":\"bytesize\", \"path\":\"bytesize\",";
	str += "\"defValue\":\"8\", \"options\" : [\"5\", \"6\", \"7\", \"8\"]}";
	
	//stopbits
	str += ",{\"type\":\"options\", \"name\":\"stopbits\", \"path\":\"stopbits\",";
	str += "\"defValue\":\"1\", \"options\" : [\"1\", \"2\"]}";
	
	//flowcontrol
	str += ",{\"type\":\"options\", \"name\":\"flowcontrol\", \"path\":\"flowcontrol\",";
	str += "\"defValue\":0, \"options\" : [{\"text\":\"none\", \"value\":0}, {\"text\":\"software\", \"value\":1}, {\"text\":\"hardware\", \"value\":2}]}";

	//parity
	str += ",{\"type\":\"options\", \"name\":\"parity\", \"path\":\"parity\",";
	str += "\"defValue\":0, \"options\" : [{\"text\":\"none\", \"value\":0}, {\"text\":\"odd\", \"value\":1}, {\"text\":\"even\", \"value\":2}]}";
	str += "]";

	s_props_desc = str;

	return s_props_desc.c_str();
}

static transferer_desc_t s_transferer_serial_creator_desc;
bool_t transferer_serial_register_creator_desc() {
	s_transferer_serial_creator_desc.name = "serial";
	s_transferer_serial_creator_desc.create = transferer_serial_create;
	s_transferer_serial_creator_desc.get_props_desc = transferer_serial_get_props_desc; 

	transferer_factory_register(&s_transferer_serial_creator_desc);
	return TRUE;
}

