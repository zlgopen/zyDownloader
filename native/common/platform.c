#include <stdio.h>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

void socketInit() {
	int iResult;
	WSADATA wsaData;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
	}
}

void socketDeinit() {
	WSACleanup();
}

void msleep(int ms) {
	Sleep(ms);
}

void closeSocket(int sock) {
	closesocket(sock);
}
#else
#include <unistd.h>
void socketInit() {}

void socketDeinit() {}

void msleep(int ms) {
	usleep(ms*1000);
}

void closeSocket(int sock) {
	close(sock);
}

#endif
