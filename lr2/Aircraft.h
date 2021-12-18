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

	double roll, pitch, yaw;		//крен тангаж рысканье
	double longitude, latitude;		//долгота широта
	double A;						//угол курса
	double V, Vx, Vz;				
	vector <double> startSK = { 0,10000,0 };

	vector <vector<double>> coordinates;		//координаты ЛА в стартовой СК
	vector <vector<double>> PPMs;				//координаты ППМов в стартовой СК

	vector <double> Xpr = {0};					//Произвоная по рысканью
	double yawmax_pr = 0.094;

public:
	Aircraft();
	Aircraft(double longitude, double latitude, double V0, double A0);
		
	void run();

	vector<double> OPS(int index);


};