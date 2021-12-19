#pragma once
#include "Transition.h"
#include <vector>
#include <cmath>
#include <map>
#include <iostream>

Transition::Transition() {
	lambda0 = 37.41255708413501;
	phi0 = 55.97313079458042;
}

Transition::Transition(double lambda, double phi) {
	lambda0 = lambda;
	phi0 = phi;
}


std::vector<double> Transition::fromStart2Geogr(std::vector<double> vec)
{
	double x, z, lambda, dlambda, phi, dphi, psi, dx, dz;
	x = 0; z = 0;
	lambda = lambda0;  phi = phi0;
	dx = 111000; // шаг по долготе
	while ((vec[0] - x) > 300 || (vec[2] - z) > 300)
	{
		psi = atan((vec[2] - z) / (vec[0] - x)); // текущий угол курса
		dlambda = floor(lambda0) + 1 - lambda0; // разница между текущей долготой и следующей (в градусах)
		dphi = floor(phi0) + 1 - phi0; // разница между текущей широтой и следующуй (в градусах)

		// шаг по широте:
		if (dphi < 0.5)
			dz = 1000 * table[int(floor(phi0) + 1)];
		else
			dz = 1000 * table[int(floor(phi0))];

		if ((vec[0] - x) < dx and (vec[2] - z) < dz)
		{
			lambda = lambda + ((vec[2] - z) / dz);
			phi = phi + ((vec[0] - x) / dx);
			x = x + (vec[0] - x);
			z = z + (vec[2] - z);
		}
		else
		{
			if (dlambda * dz < dphi * dx) // т.е. следующая широта ближе чем следующая долгота
			{
				x = x + dphi * dx;
				z = z + (tan(psi) * (dphi * dx));
				phi = phi + dphi;
				lambda = lambda + ((tan(psi) * (dphi * dx)) / dz); // считаем на сколько градусов передвинулись по широте, т.е. чему равна текущая долгота
			}
			else
			{
				z = z + dlambda * dz;
				x = x + (atan(psi) * (dlambda * dz));
				lambda = lambda + dlambda;
				phi = phi + ((atan(psi) * (dlambda * dz)) / dx);
			}
		}
	}
	std::vector<double> res = { lambda, phi, 10000 };
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
	if (x1.size() == 3)
	{
		double a = sqrt(pow(x1[0] - x2[0], 2) + pow(x1[1] - x2[1], 2) + pow(x1[2] - x2[2], 2));
		return a;
	}
	if (x1.size() == 2)
	{
		double a = sqrt(pow(x1[0] - x2[0], 2) + pow(x1[1] - x2[1], 2));
		return a;
	}
}


void Transition::WriteFile(FILE* file1, int flag, std::vector<double> vec) {
	if (flag == 1) {
		fprintf_s(file1, "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>");
		fprintf_s(file1, "\n<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\" xmlns:kml=\"http://www.opengis.net/kml/2.2\" xmlns:atom='http://www.w3.org/2005/Atom\">");
		fprintf_s(file1, "\n<Document>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "<name>Шереметьево-Хитроу.kml</name>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "<Style id=\"s_ylw-pushpin\">");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<IconStyle>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<scale>1.1</scale>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<Icon>");
		fprintf_s(file1, "\n%-32s", " ");
		fprintf_s(file1, "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "</Icon>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<hotSpot x=\"20\" y=\"2\" xunits=\"pixels\" yunits=\"pixels\"/>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "</IconStyle>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<LineStyle>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<color>ffffad41</color>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "</LineStyle>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "</Style>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "<Style id=\"s_ylw-pushpin_hl\">");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<IconStyle>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<scale>1.3</scale>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<Icon>");
		fprintf_s(file1, "\n%-32s", " ");
		fprintf_s(file1, "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "</Icon>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<hotSpot x=\"20\" y=\"2\" xunits=\"pixels\" yunits=\"pixels\"/>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "</IconStyle>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<LineStyle>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<color>ffffad41</color>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "</LineStyle>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "</Style>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "<StyleMap id=\"m_ylw-pushpin\">");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<Pair>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<key>normal</key>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<styleUrl>#s_ylw-pushpin</styleUrl>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "</Pair>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<Pair>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<key>highlight</key>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<styleUrl>#s_ylw-pushpin_hl</styleUrl>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "</Pair>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "</StyleMap>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "<Placemark>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<name>Шереметьево-Хитроу</name>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<styleUrl>#m_ylw-pushpin</styleUrl>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "<LineString>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<tessellate>1</tessellate>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<gx:altitudeMode>relativeToSeaFloor</gx:altitudeMode>");
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "<coordinates>");
		fprintf_s(file1, "\n%-32s", " ");
	}
	if (flag == 2) {
		fprintf_s(file1, "%-.14f", vec[0]); fprintf_s(file1, ",");
		fprintf_s(file1, "%-.14f", vec[1]); fprintf_s(file1, ",");
		fprintf_s(file1, "%-.0f", vec[2]); fprintf_s(file1, " ");
	}
	if (flag == 3) {
		fprintf_s(file1, "\n%-24s", " ");
		fprintf_s(file1, "</coordinates>");
		fprintf_s(file1, "\n%-16s", " ");
		fprintf_s(file1, "</LineString>");
		fprintf_s(file1, "\n%-8s", " ");
		fprintf_s(file1, "</Placemark>");
		fprintf_s(file1, "\n</Document>");
		fprintf_s(file1, "\n</kml>");
	}
}