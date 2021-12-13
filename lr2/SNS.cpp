#include "SNS.h"
#include <mutex>
#include <WinSock2.h>
#include <iostream>

SNS::SNS(double H, double HDOP, double VDOP, double trackAngle, double curLatitude, double curLatitude_pr,
	double curLongitude, double curLongitude_pr, double delay, double UTC_high, double UTC_low,
	double V_h)
{
	this->H = H;
	this->HDOP = HDOP;
	this->VDOP = VDOP;
	this->trackAngle = trackAngle;
	this->curLatitude = curLatitude;
	this->curLatitude_pr = curLatitude_pr;
	this->curLongitude = curLongitude;
	this->curLongitude_pr = curLongitude_pr;
	this->delay = delay;
	this->UTC_high = UTC_high;
	this->UTC_low = UTC_low;
	this->V_h = V_h;
}



void SNS::test() {
	mutex.lock();

	mutex.unlock();
}

void SNS::preparation() {
	mutex.lock();

	mutex.unlock();
}

void SNS::navigation() {
	mutex.lock();

	mutex.unlock();
}

void SNS::start() {
	if (!isStart)
	{
		test();
		preparation();
		isStart = true;
	}
	navigation();
}

void SNS::sendPack()
{
	mutex.lock();
	if (!isStart)
	{
		sendto(_s, &buffer[0], sizeof(buffer), 0,           //
			(sockaddr*)&_destAddr, sizeof(_destAddr));		// 
															//
	}
	else
	{
		char buff[4];
		int count_word = 0;
		for (int i = 0; i < 14; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				buff[j] = buffer[count_word * 4 + j];
			}

			sendto(_s, &buff[0], sizeof(buff), 0,
				(sockaddr*)&_destAddr, sizeof(_destAddr));
			count_word++;
		}

	}

	mutex.unlock();
	std::cout << "send " << std::endl;
}

int SNS::bindPort(SOCKET s, sockaddr_in destAddr) {
	_s = s;
	_destAddr = destAddr;
	return 1;
}
