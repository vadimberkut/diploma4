#include <iostream>
#include <algorithm>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"

//Sort vector of vectors by size descending (used for countours Sort )
bool vectorOfVectorsSortFunctionDesc(std::vector<cv::Point> i, std::vector<cv::Point> j)
{
	return (i.size() > j.size());
}


void SortVectorOfVectorsDesc(std::vector<std::vector<cv::Point> > &vector)
{
	std::sort(vector.begin(), vector.end(), vectorOfVectorsSortFunctionDesc);
}