#pragma once
#include "SNS.h"
#include "INS.h"
#include <vector>
#include "Transition.h"
using namespace std;

class Aircraft {
private:
	INS ins;
	SNS sns;
	Transition tr;

	double roll, pitch, yaw;		//���� ������ ��������
	double longitude, latitude;		//������� ������
	double A;						//���� �����
	double V, Vx, Vz;				
	vector <double> startSK = { 0,10000,0 };

	vector <vector<double>> coordinates;		//���������� �� � ��������� ��
	vector <vector<double>> PPMs;				//���������� ����� � ��������� ��

	vector <double> Xpr = {0};					//���������� �� ��������
	double yawmax_pr = 0.094;

public:
	Aircraft();
	Aircraft(double longitude, double latitude, double V0, double A0);
		
	void run();

	vector<double> OPS(int index);


};