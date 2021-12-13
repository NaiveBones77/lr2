#include <mutex>
#include <WinSock2.h>
#include <iostream>

#pragma once
class SNS
{
	private:
		double H, HDOP, VDOP, trackAngle, curLatitude, curLatitude_pr, curLongitude, curLongitude_pr, delay,
			UTC_high, UTC_low, V_h;
		std::mutex mutex;
		char* buffer;
		bool isStart = false;
		SOCKET _s;
		sockaddr_in _destAddr;
	public:

		// конструктор класса
		SNS(double H, double HDOP, double VDOP, double trackAngle, double curLatitude, double curLatitude_pr,
			double curLongitude, double curLambda_pr, double delay, double UTC_high, double UTC_low,
			double V_h);

		//метод тест контроля своих устройств
		void test();

		//метод подготовки
		void preparation();

		//метод навигации
		void navigation();

		//метод, запускающий работу СНС
		void start();

		//метод отправки пакета
		void sendPack();

		//метод определения адресса отправки пакета
		int bindPort(SOCKET s, sockaddr_in destAddr);

		//todo
		//
};

