#include "INS.h"
#include <mutex>
#include <WinSock2.h>
#include <iostream>

INS::INS(double Latitude, double Longitude, double H, double CourseTrue,
	double Tungazh, double List, double VelocityNS, double VelocityEW, double VelocityVI,
	double AccelerationX, double AccelerationZ, double AccelerationY) {
	this->Latitude = Latitude;
	this->Longitude = Longitude;
	this->H = H;
	this->CourseTrue = CourseTrue;
	this->Tungazh = Tungazh;
	this->List = List;
	this->VelocityNS = VelocityNS;
	this->VelocityEW = VelocityEW;
	this->VelocityVI = VelocityVI;
	this->AccelerationX = AccelerationX;
	this->AccelerationZ = AccelerationZ;
	this->AccelerationY = AccelerationY;
}

void INS::test() {
	mutex.lock();

	mutex.unlock();
}

void INS::preparation() {
	mutex.lock();

	mutex.unlock();
}

void INS::navigation() {
	mutex.lock();

	mutex.unlock();
}

void INS::start() {
	mutex.lock();

	mutex.unlock();
}

int INS::bindPort(SOCKET s, sockaddr_in destAddr) {
	_s = s;
	_destAddr = destAddr;
	return 1;
}

