#pragma once
#include <vector>

class Transition
{
private:
	double lambda0, phi0;
public:
	Transition();
	Transition(double lambda, double phi);
	std::vector<double> fromStart2Geogr(std::vector<double> vec);
	//static double fromGrad2Rad(double angle);
	//static double fromRad2Grad(double rads);
	void setDefault(double lambda, double phi);
	double getAngleFromScalars(std::vector<double> x1, std::vector<double> x2);
	double getDistance(std::vector<double> x1, std::vector<double> x2);
};

