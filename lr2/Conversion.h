#include <cmath>

class Conversion
{
public:
	static double	conv_bin_to_dec(double max_value, int max_digit, int digit, double value);
	static int		conv_dec_to_bin(double max_value, int max_digit, int digit, int dec);
};
