#pragma once
#include <mutex>
#include <WinSock2.h>
#include <iostream>
#include "Conversion.h"
#include <random>


class INS {
private:
	double Latitude, Longitude, H, CourseTrue, Tungazh, List, VelocityNS, VelocityEW,
		VelocityVI, AccelerationX, AccelerationZ, AccelerationY;
	std::mutex mutex;
	char* buffer;
	char buff2send[4];
	bool isStart = false;
	SOCKET _s;
	sockaddr_in _destAddr;
	int buff_count;
	int count_nav;
	Conversion conv1;
	std::mt19937 generator;


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

	template <class T>
	void fill_buff(T pack);
};