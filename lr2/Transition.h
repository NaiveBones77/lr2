#pragma once
#include <vector>

class Transition
{
private:
	static double lambda0, phi0;
public:
	static std::vector<double> fromStart2Geogr(std::vector<double> vec);
	static double fromGrad2Rad(double angle);
	static double fromRad2Grad(double rads);
	static void setDefault(double lambda, double phi);
};

