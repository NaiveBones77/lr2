#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#include "custom_socket.h"

#define PORT 12346
#define SERVERADDR "127.0.0.1"
#pragma warning(disable: 4996)

SOCKET custom_socket::get_socket()
{
	char buffer[10*1014];

	if (WSAStartup(0x202, (WSADATA*)&buffer[0]))
	{
		printf("WSAStartup error: %d\n", WSAGetLastError());
		return -1;
	}

	socket_ = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_ == INVALID_SOCKET)
	{
		printf("socket() error: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	return socket_;
}

sockaddr_in custom_socket::get_addr()
{
	HOSTENT* host;
	destaddr_;
	destaddr_.sin_family = AF_INET;
	destaddr_.sin_port = htons(PORT);

	if (inet_addr(SERVERADDR))
		destaddr_.sin_addr.s_addr = ((unsigned long**)host->h_addr_list)[0][0];

	else
	{
		printf("Unknown host: %d\n", WSAGetLastError());
		closesocket(socket_);
		WSACleanup();
	}

	return destaddr_;
}


