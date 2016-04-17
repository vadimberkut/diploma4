#include "ColorDifference.h"

double CIE76::STANDART_HUMAN_EYE_DELTA_E = 2.3;

double CIE76::GetMetric(cv::Vec3b pixel1, cv::Vec3b pixel2)
{
	double L1 = pixel1.val[0];
	double L2 = pixel2.val[0];
	double A1 = pixel1.val[1];
	double A2 = pixel2.val[1];
	double B1 = pixel1.val[2];
	double B2 = pixel2.val[2];

	return sqrt(pow(L2 - L1, 2) + pow(A2 - A1, 2) + pow(B2 - B1, 2));
}

double CIE76::GetMetric(double *pixel1, double *pixel2, int size)
{
	if (size == 2)
	{
		return sqrt(pow(pixel2[0] - pixel1[0], 2) + pow(pixel2[1] - pixel1[1], 2));
	}
	if (size == 3)
	{
		return sqrt(pow(pixel2[0] - pixel1[0], 2) + pow(pixel2[1] - pixel1[1], 2) + pow(pixel2[2] - pixel1[2], 2));
	}
	throw std::invalid_argument("received invalid size (required 2 or 3)");
}