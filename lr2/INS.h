#include <mutex>
#include <WinSock2.h>
#include <iostream>
#pragma once
class INS {
private:
	double Latitude, Longitude, H, CourseTrue, Tungazh, List, VelocityNS, VelocityEW,
		VelocityVI, AccelerationX, AccelerationZ, AccelerationY;
	std::mutex mutex;
	char* buffer;
	bool isStart = false;
	SOCKET _s;
	sockaddr_in _destAddr;

public:
	INS(double Latitude, double Longitude, double H, double CourseTrue,
		double Tungazh, double List, double VelocityNS, double VelocityEW, double VelocityVI,
		double AccelerationX, double AccelerationZ, double AccelerationY);

	void test();

	void preparation();

	void navigation();

	void start();

	void sendPack();

	int bindPort(SOCKET s, sockaddr_in destAddr);
};