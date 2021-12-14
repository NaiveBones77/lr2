#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#pragma once
class custom_socket
{
	static SOCKET get_socket();
	static sockaddr_in get_addr();
	static SOCKET socket_;
	static sockaddr_in destaddr_;
};

