#include <mutex>

#pragma once
class INS {
private:
	double Latitude, Longitude, H, CourseTrue, Tungazh, List, VelocityNS, VelocityEW,
		VelocityVI, AccelerationX, AccelerationZ, AccelerationY;
	std::mutex mutex;
	char* buffer;
	bool isStart = false;

public:
	INS(double Latitude, double Longitude, double H, double CourseTrue,
		double Tungazh, double List, double VelocityNS, double VelocityEW, double VelocityVI,
		double AccelerationX, double AccelerationZ, double AccelerationY);

	void test();

	void preparation();

	void navigation();

	void start();

	void sentpack();
};