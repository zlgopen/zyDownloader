/**********************************************
 * Author: ideawu(www.ideawu.net)
 * Date: 2007-04
 * File: server.c
 *********************************************/

#include "tftpx.h"
#include "work_thread.h"
bool_t start_tftp_server(int port, const char* docroot, const char* filename, const char** err_msg) {
	int sock;
	int done = 0;	// Server exit.
	socklen_t addr_len;
	struct sockaddr_in server;

	conf_document_root = docroot;
	conf_default_file_name = filename;

	if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror(MSG_CREATE_SOCKET_FAILED);
		SET_ERR_MSG(err_msg, MSG_CREATE_SOCKET_FAILED);
		return FALSE;
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0){
		perror("Server bind failed. Server already running? Proper permissions?\n");
		SET_ERR_MSG(err_msg, MSG_BIND_PORT_FAILED);
		return FALSE;
	}
	
	printf("Server started at 0.0.0.0:%d.\n", port);
	
	struct tftpx_request *request;
	addr_len = sizeof(struct sockaddr_in);
	while(!done){
		request = (struct tftpx_request *)malloc(sizeof(struct tftpx_request));
		memset(request, 0, sizeof(struct tftpx_request));
		request->size = recvfrom(
				sock, &(request->packet), MAX_REQUEST_SIZE, 0,
				(struct sockaddr *) &(request->client),
				&addr_len);
		request->packet.cmd = ntohs(request->packet.cmd);
		printf("Receive request.\n");
		work_thread(request);
		break;
	}

	closeSocket(sock);

	return TRUE;
}

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
#include <stdio.h>

char* get_local_ips(char buff[256], size_t n) {
	size_t i = 0;  
	char hname[128] ={0};
	*buff = '\0';

	gethostname(hname, sizeof(hname));
	struct hostent *phostinfo = gethostbyname(hname);    
	for(i = 0; NULL != phostinfo&& NULL != phostinfo->h_addr_list[i]; ++i)  {  
		char *ip = inet_ntoa(*(struct in_addr *)phostinfo->h_addr_list[i]);  
		if(i >= n) break;

		if(i > 0) {
			strcat(buff, ",");
		}
		strcat(buff, ip);
	}  
	printf("%s %s\n", hname, buff);
	fflush(stdout);
	
	return buff;
}
