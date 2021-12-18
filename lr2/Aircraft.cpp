#pragma once
#include "Aircraft.h"
#include <cmath>
#include <vector>

Aircraft::Aircraft(double longitude, double latitude, double V0, double A0) {
	this->longitude = longitude;
	this->latitude = latitude;
	V = V0;
	A = A0;
	roll = 0;
	pitch = 0;
	yaw = 0;
	Vx = 0;
	Vz = 0;
	PPMs.insert(PPMs.end(), std::vector<double>{10000, 10000, 6000});
	PPMs.insert(PPMs.end(), std::vector<double>{20000, 10000, 1000});
	tr.setDefault(longitude, latitude);
}

Aircraft::Aircraft() {};

void Aircraft::run()
{
	double dt = 0.1;
	coordinates.insert(coordinates.end(), startSK);
	int countOperation = 0;
	int countPPM = 0;
	while (countPPM < PPMs.size())
	{
		Xpr = OPS(countPPM);
		A = A + Xpr[0] * dt;
		Vx = V * cos(A);
		Vz = V * sin(A);
		startSK[0] = startSK[0] + Vx * dt;
		startSK[2] = startSK[2] + Vz * dt;
		coordinates.insert(coordinates.end(), startSK);
		if (tr.getDistance(startSK, PPMs[countPPM]) < 1000)
		{
			countPPM += 1;
		}
		if (countOperation > 500)
		{
			printf("100");
		}
		countOperation += 1;
	}
}

std::vector<double> Aircraft::OPS(int index)
{
	std::vector<double> res = { 0 };
	double delta = tr.getAngleFromScalars(std::vector<double> {1, 0}, std::vector<double> {PPMs[index][0], PPMs[index][2]});
	if (delta - A <= 0.011)
	{
		res[0] = 0;
		return res;
	}

	if (delta > A)
	{
		res[0] = yawmax_pr;
		return res;
	}

	else if (delta < A)
	{
		res[0] = -yawmax_pr;
		return res;
	}
		
}