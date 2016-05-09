#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgproc/imgproc_c.h"

//https://ru.wikipedia.org/wiki/Формула_цветового_отличия


//CIE76 standart to determine Color difference (useing delta E metric)
class CIE76
{
public:

	//примерно соответствует минимально различимому для человеческого глаза отличию между цветами
	static double STANDART_HUMAN_EYE_DELTA_E;

	static double GetMetric(cv::Vec3b pixel1, cv::Vec3b pixel2);

	static double GetMetric(double *pixel1, double *pixel2, int size);
//	{
//		double L1;
//		double L2;
//		double A1;
//		double A2;
//		double B1;
//		double B2;
//
//		return sqrt(pow(L2 - L1, 2) + pow(A2 - A1, 2) + pow(B2 - B1, 2));
//	}
};