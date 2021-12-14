#pragma once
#include "Conversion.h"
#include "INS.h"
#include "protocol.h"
#include "SNS.h"
#include "Timer.cpp"

#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

#define PORT 12346
#define SERVERADDR "127.0.0.1"
#pragma warning(disable: 4996)

SOCKET _s;
sockaddr_in _destAddr;

int main()
{
	setlocale(LC_ALL, "rus");


	INS ins(33, 55, 130, 15.3, 3.5, 6.3245, 400, 200, 6400, 0, 0, 0);

    char buff[10 * 1014];

    if (WSAStartup(0x202, (WSADATA*)&buff[0]))
    {
        printf("WSAStartup error: %d\n",
            WSAGetLastError());
        return -1;
    }

    _s = socket(AF_INET, SOCK_DGRAM, 0);
    if (_s == INVALID_SOCKET)
    {
        printf("socket() error: %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    HOSTENT* hst;
    _destAddr;
    _destAddr.sin_family = AF_INET;
    _destAddr.sin_port = htons(PORT);

    if (inet_addr(SERVERADDR))
        _destAddr.sin_addr.s_addr = inet_addr(SERVERADDR);

    else
    {
        if (hst = gethostbyname(SERVERADDR))
            _destAddr.sin_addr.s_addr = ((unsigned long**)hst->h_addr_list)[0][0];

        else
        {
            printf("Unknown host: %d\n", WSAGetLastError());
            closesocket(_s);
            WSACleanup();
            return -1;
        }
    }
	
	
	ins.bindPort(_s, _destAddr);

    Timer timer;
    timer.add(std::chrono::milliseconds(10), [&]() {ins.sendPack(); });
    timer.add(std::chrono::microseconds(2500), [&]() {ins.start(); });

    while (true) { std::this_thread::sleep_for(std::chrono::seconds(3600)); };
}
