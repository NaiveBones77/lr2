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

	double roll, pitch, yaw;		//крен тангаж рысканье
	double longitude, latitude;		//долгота широта
	double A;						//угол курса
	double V, Vx, Vz;				
	vector <double> startSK = { 0,10000,0 };

	vector <vector<double>> coordinates;		//координаты ЛА в стартовой СК
	vector <vector<double>> PPMs;				//координаты ППМов в стартовой СК

	vector <double> Xpr = {0};					//Произвоная по рысканью
	int index = 0;								//индекс элемента из ППМ
	double yawmax_pr = 0.14;
	int countPPM = 0;							//количество ППМОВ
	int countOperation = 0;						//количество операций

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