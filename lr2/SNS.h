
#pragma once
#include <mutex>
#include <WinSock2.h>
#include <iostream>
#include "Conversion.h"
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
		int buff_count;
		Conversion cs1;

	public:

		// ����������� ������
		SNS(double H, double HDOP, double VDOP, double trackAngle, double curLatitude, double curLatitude_pr,
			double curLongitude, double curLambda_pr, double delay, double UTC_high, double UTC_low,
			double V_h);

		//����� ���� �������� ����� ���������
		void test();

		//����� ����������
		void preparation();

		//����� ���������
		void navigation();

		//�����, ����������� ������ ���
		void start();

		//����� �������� ������
		void sendPack();

		//����� ����������� ������� �������� ������
		int bindPort(SOCKET s, sockaddr_in destAddr);

		template <class T>
		void fill_buff(T pack);

};

