#include "stream_serial.h"

typedef struct _stream_serial_t {
	stream_t stream;
	serial::Serial* dev;
	const char* port;
}stream_serial_t;

static int stream_serial_read(stream_t* s, uint8_t* buff, size_t len) {
	stream_serial_t* stream = (stream_serial_t*)s;
	serial::Serial* dev = stream->dev;
	return (int)dev->read(buff, len);
}

static int stream_serial_write(stream_t* s, uint8_t* buff, size_t len) {
	stream_serial_t* stream = (stream_serial_t*)s;
	serial::Serial* dev = stream->dev;
	return (int)dev->write(buff, len);
}

static void   stream_serial_close(stream_t* s) {
	stream_serial_t* stream = (stream_serial_t*)s;
	serial::Serial* dev = stream->dev;
	delete dev;
	memset(stream, 0x00, sizeof(stream_serial_t));
	free(stream);
}

static void   stream_serial_flush(stream_t* s) {
	stream_serial_t* stream = (stream_serial_t*)s;
	serial::Serial* dev = stream->dev;
	dev->flush();
	printf("stream_serial_flush\n");
	return;
}

stream_t* stream_serial_create(
		const char* port,
		uint32_t baudrate,
		serial::bytesize_t bytesize,
		serial::parity_t parity,
		serial::stopbits_t stopbits,
		serial::flowcontrol_t flowcontrol
) {
	size_t timeo = 500;
	stream_serial_t* stream = (stream_serial_t*)calloc(1, sizeof(stream_serial_t));
	try {
		stream->dev = new serial::Serial(std::string(port), baudrate, serial::Timeout::simpleTimeout(timeo), 
			bytesize, parity, stopbits, flowcontrol);
		printf("device=%s baudrate=%d bytesize=%d parity=%d stopbits=%d flowcontrol=%d\n", port, 
			(int)baudrate, (int)bytesize, (int)parity, (int)stopbits, (int)flowcontrol);
	}catch(...) {
		free(stream);
		return NULL;
	}

	stream->port = port;
	stream->stream.read = stream_serial_read;
	stream->stream.write = stream_serial_write;
	stream->stream.flush = stream_serial_flush;
	stream->stream.close = stream_serial_close;

	return (stream_t*)stream;
}

