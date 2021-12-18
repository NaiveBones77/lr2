#include "Transition.h"
#include <vector>
#include <cmath>

Transition::Transition() {
	lambda0 = 35;
	phi0 = 55;
}

Transition::Transition(double lambda, double phi) {
	lambda0 = lambda;
	phi0 = phi;
}
std::vector<double> Transition::fromStart2Geogr(std::vector<double> vec)
{
	std::vector<double> res = { 0 };
	return res;
}

void Transition::setDefault(double lambda, double phi)
{
	lambda0 = lambda;
	phi0 = phi;
}

double Transition::getAngleFromScalars(std::vector<double> x1, std::vector<double> x2)
{
	if (x1.size() == 3)
	{
		double x1len = sqrt(pow(x1[0], 2) + pow(x1[1], 2) + pow(x1[2], 2));
		double x2len = sqrt(pow(x2[0], 2) + pow(x2[1], 2) + pow(x2[2], 2));
		return  acos((x1[0] * x2[0] + x1[1] * x2[1] + x1[2] * x2[2]) / (x1len * x2len));
	}
	else if (x1.size() == 2)
	{
		double x1len = sqrt(pow(x1[0], 2) + pow(x1[1], 2));
		double x2len = sqrt(pow(x2[0], 2) + pow(x2[1], 2));
		if (x2[1] < 0)
			return  -acos((x1[0] * x2[0] + x1[1] * x2[1]) / (x1len * x2len));
		else if (x2[1] > 0)
			return  acos((x1[0] * x2[0] + x1[1] * x2[1]) / (x1len * x2len));
		else if (x2[1] == 0)
			return 0;
	}
}

double Transition::getDistance(std::vector<double> x1, std::vector<double> x2)
{
	double a = sqrt(pow(x1[0] - x2[0], 2) + pow(x1[1] - x2[1], 2) + pow(x1[2] - x2[2], 2));
	return a;
}