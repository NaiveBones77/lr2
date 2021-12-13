#include "Conversion.h"

double Conversion::conv_bin_to_dec(double max_value, int max_digit, int digit, double value)
{
	int* mass = new int[max_digit]();
	int last_i = 0;
	int sum = 0;
	int	i = 0;
	while (i <= digit - 1)
	{
		sum = sum + (max_value / pow(2, i));
		if (sum <= value) {
			mass[i] = 1;
		}
		else {
			mass[i] = 0;
			sum = sum - (max_value / pow(2, i));
		}
		last_i = i;
		i++;
	}
	if (last_i < max_digit - 1)
		i = last_i;
	while (i < max_digit)
	{
		++i;
		mass[i] = 0;
	}
	i = 0;
	sum = 0;
	while (i < max_digit)
	{
		++i;
		sum = sum + (mass[i] * pow(2, max_digit - (1 + i)));
	}
	delete[] mass;
	return sum;
}

int Conversion::conv_dec_to_bin(double max_value, int max_digit, int digit, int dec)
{
	double* bin = new double[max_digit]();
	int sum = 0;
	int i = 0;
	while (dec > 0)
	{
		bin[max_digit - (i + 1)] = (dec % 2);
		dec /= 2;
		i++;
	}
	i = 0;
	while (i <= digit - 1)
	{
		sum = sum + bin[i] * (max_value / pow(2, i));
		i++;
	}
	delete[] bin;
	return sum;
}

