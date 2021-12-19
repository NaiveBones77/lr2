#pragma once
#include "SNS.h"
#include "INS.h"
#include <vector>
#include "Transition.h"
#include <mutex>
using namespace std;

class Aircraft {
private:
	INS ins;
	SNS sns;
	Transition tr;
	mutex mutex;

	double roll, pitch, yaw;		//���� ������ ��������
	double longitude, latitude;		//������� ������
	double A;						//���� �����
	double V, Vx, Vz;				
	vector <double> startSK = { 0,10000,0 };

	vector <vector<double>> coordinates;		//���������� �� � ��������� ��
	vector <vector<double>> PPMs;				//���������� ����� � ��������� ��

	vector <double> Xpr = {0};					//���������� �� ��������
	int index = 0;								//������ �������� �� ���
	double yawmax_pr = 0.14;
	int countPPM = 0;							//���������� �����
	int countOperation = 0;						//���������� ��������

public:
	Aircraft();
	Aircraft(double longitude, double latitude, double V0, double A0);
		
	void run();
	void run2();

	vector<double> OPS(int index);
	void OPS2();
	void fillSNS(std::vector<double> vec);
	void fillINS(std::vector<double> vec);

};