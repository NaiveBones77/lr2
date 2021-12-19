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
	PPMs.insert(PPMs.end(), std::vector<double>{-10000, 10000, 10000});
	PPMs.insert(PPMs.end(), std::vector<double>{10000, 10000, 6000});
	PPMs.insert(PPMs.end(), std::vector<double>{20000, 10000, 1000});
	PPMs.insert(PPMs.end(), std::vector<double>{20000, 10000, -6000});
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
		
		countOperation += 1;
	}
}

std::vector<double> Aircraft::OPS(int index)
{
	std::vector<double> res = { 0 };
	
	double delta = tr.getAngleFromScalars(std::vector<double> {1, 0}, 
		std::vector<double> {PPMs[index][0] - startSK[0], PPMs[index][2] - startSK[2]});
	if (abs(delta - A) <= 0.011)
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

void Aircraft::run2()
{
	double dt = 0.1;
	
	coordinates.insert(coordinates.end(), startSK);
	if (index < PPMs.size())
	{
		mutex.lock();
		A = A + Xpr[0] * dt;
		Vx = V * cos(A);
		Vz = V * sin(A);
		startSK[0] = startSK[0] + Vx * dt;
		startSK[2] = startSK[2] + Vz * dt;
		coordinatesG = tr.fromStart2Geogr(startSK);
		longitude = coordinatesG[0];
		latitude = coordinatesG[2];
		if (tr.getDistance(startSK, PPMs[index]) < 500)
		{
			index += 1;
		}
		if (countOperation > 550)
		{
			printf("100");
		}
		countOperation += 1;
		mutex.unlock();
	}
	std::vector<double> SNS_vec = { A, longitude, latitude };
	std::vector<double> INS_vec = { latitude, longitude, A, pitch, roll, Vx, Vz };
	fillSNS(SNS_vec);
	fillINS(INS_vec);
}

void Aircraft::OPS2()
{
	mutex.lock();

	std::vector<double> ort = { 0, 0 };
	ort[0] = (distSP[0] - startSK[0]) / tr.getDistance(distSP, startSK);
	ort[1] = (distSP[1] - startSK[1]) / tr.getDistance(distSP, startSK);
	double delta = tr.getAngleFromScalars(ort, std::vector<double> {PPMs[index][0] - startSK[0], PPMs[index][2] - startSK[2]});
	if (abs(delta - A) <= 0.011)
	{
		Xpr[0] = 0;
	}

	if (delta > A)
	{
		Xpr[0] = yawmax_pr;
	}

	else if (delta < A)
	{
		Xpr[0]  = -yawmax_pr;
	}
	mutex.unlock();
}

void Aircraft::fillSNS(std::vector<double> vec)
{
	sns.mutex.lock();
	sns.H.value = 10000;
	sns.trackAngle.value = vec[0];
	sns.curLatitude.value = vec[1];
	sns.curLongitude.value = vec[2];
	sns.mutex.unlock();
}

void Aircraft::fillINS(std::vector<double> vec)
{
	ins.mutex.lock();
	ins.H.value = 10000;
	ins.Latitude.value = vec[0];
	ins.Longitude.value = vec[1];
	ins.CourseTrue.value = vec[2];
	ins.Tungazh.value = vec[3];
	ins.List.value = vec[4];
	ins.VelocityNS.value = vec[5];
	ins.VelocityEW.value = vec[6];
	ins.mutex.unlock();
}