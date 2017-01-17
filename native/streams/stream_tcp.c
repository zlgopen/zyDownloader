
#include <sys/types.h>
#ifdef WIN32
#include <windows.h>
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#endif

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include "stream_tcp.h"


typedef struct _stream_tcp_t {
	stream_t stream;
	int sock;
}stream_tcp_t;

static int stream_tcp_read(stream_t* s, uint8_t* buff, size_t len) {
	stream_tcp_t* tcp = (stream_tcp_t*)s;
	return (int)recv(tcp->sock, buff, (int)len, 0);
}

static int stream_tcp_write(stream_t* s, uint8_t* buff, size_t len) {
	stream_tcp_t* tcp = (stream_tcp_t*)s;
	return (int)send(tcp->sock, buff, (int)len, 0);
}

static void   stream_tcp_close(stream_t* s) {
	stream_tcp_t* tcp = (stream_tcp_t*)s;
	closeSocket(tcp->sock);
	memset(tcp, 0x00, sizeof(stream_tcp_t));
	free(tcp);
}

static void   stream_tcp_flush(stream_t* s) {
	(void)s;
	return;
}

static stream_t* stream_tcp_create(int sock) {
	stream_tcp_t* tcp = (stream_tcp_t*)calloc(1, sizeof(stream_tcp_t));
	tcp->sock = sock;
	tcp->stream.read = stream_tcp_read;
	tcp->stream.write = stream_tcp_write;
	tcp->stream.flush = stream_tcp_flush;
	tcp->stream.close = stream_tcp_close;

	return (stream_t*)tcp;
}

int       tcp_listen(int port) {
	int sock;
	struct sockaddr_in s;
	int on=1;

	if ((sock = (int)socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("socket error\n");
		return -1;
	}
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof (on)) < 0) {
		printf("setsockopt error\n");
		return -1;
	}

	memset (&s, 0, sizeof (s));
	s.sin_family = AF_INET;
	s.sin_port=htons(port);
	s.sin_addr.s_addr=htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&s, sizeof (s)) < 0) {
		printf("bind error\n");
		return -1;
	}
	if (listen(sock, 1) < 0) {
		printf("listen error\n");
		return -1;
	}

	return (sock);
}

 #define h_addr h_addr_list[0] 
stream_t* tcp_connect(const char* host, int port) {
	int sock;
	struct sockaddr_in s_in;

	memset(&s_in,0,sizeof(s_in));

	s_in.sin_family = AF_INET;
	struct hostent *h=gethostbyname(host);
	return_value_if_fail(h != NULL, NULL);

	memcpy(& s_in.sin_addr.s_addr,h->h_addr,h->h_length);
	s_in.sin_port = htons(port);

	if ((sock = (int)socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("socket error\n");
		return NULL;
	}

	if (connect (sock, (struct sockaddr *) &s_in, sizeof (s_in)) < 0) {
		printf("connect error\n");
		return NULL;
	}

	return stream_tcp_create(sock);
}

stream_t* tcp_accept(int sock) {
	int so;
	struct  sockaddr_in s;
	socklen_t namelen;

	namelen = sizeof(s);
	memset((char*)&s,0, namelen);

	if ((so = (int)accept(sock, (struct sockaddr*)&s, &namelen)) < 0) {
		return NULL;
	}

	return stream_tcp_create(so);
}

