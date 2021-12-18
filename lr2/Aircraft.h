#pragma once
#include "SNS.h"
#include "INS.h"
#include <vector>

class Aircraft {
private:
	INS ins;
	SNS sns;

	double roll, pitch, yaw;
	double longitude, latitude;
	std::vector <double> startSK = { 0,0,0 };




};