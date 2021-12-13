#include "INS.h"
#include <mutex>
#include <WinSock2.h>
#include <iostream>
#include "protocol.h"
#include <cstdlib>

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
	auto start = std::chrono::system_clock::now();
	double time_test = 5;

	mutex.lock();
	delete[] buffer;
	char tmp[33];

	DISCRETE pack;   // Слово состояния с признаками "Исправность ИНС" и "Нет начальных данных"

	pack.value.address = 0270;
	pack.value.preparation = 0;
	pack.value.control = 0;
	pack.value.navigation = 0;
	pack.value.gyrocompas = 0;
	pack.value.restart = 0;
	pack.value.scale = 0;
	pack.value.heating = 1;
	pack.value.temp_control = 1;
	pack.value.init_data = 0;		// "Нет начальных данных"
	pack.value.no_reception = 0;
	pack.value.INS = 1;				// "Исправность ИНС"
	pack.value.acceleration = 0;
	pack.value.readiness = 0;
	pack.value.sm = 0;
	pack.value.p = 0;

	buffer = new char[sizeof(pack)];             
	memset(buffer, 0, sizeof(pack));            
	memcpy(buffer, &pack, sizeof(pack));     

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	while (elapsed_seconds.count() < time_test)
	{
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
	}

	delete[] buffer;
	buffer = new char[sizeof(pack)];            
	memset(buffer, 0, sizeof(pack));            
	memcpy(buffer, &pack, sizeof(pack));        

	mutex.unlock();
	std::cout << "test control end\n";
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

