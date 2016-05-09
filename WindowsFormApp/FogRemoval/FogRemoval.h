//#include <cv.h>
//#include <highgui.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

//median filtered dark channel
Mat getMedianDarkChannel(Mat src, int patch)
{
	Mat rgbmin = Mat::zeros(src.rows, src.cols, CV_8UC1);
	Mat MDCP;
	Vec3b intensity;

	for (int m = 0; m<src.rows; m++)
	{
		for (int n = 0; n<src.cols; n++)
		{
			intensity = src.at<Vec3b>(m, n);
			rgbmin.at<uchar>(m, n) = min(min(intensity.val[0], intensity.val[1]), intensity.val[2]);
		}
	}
	medianBlur(rgbmin, MDCP, patch);
	return MDCP;

}

// dark channel2
void minFilter(const Mat1b& src, Mat1b& dst, int radius)
{
	Mat1b padded;
	copyMakeBorder(src, padded, radius, radius, radius, radius, BORDER_CONSTANT, Scalar(255));

	int rr = src.rows;
	int cc = src.cols;
	dst = Mat1b(rr, cc, uchar(0));

	for (int c = 0; c < cc; ++c)
	{
		for (int r = 0; r < rr; ++r)
		{
			uchar lowest = 255;
			for (int i = -radius; i <= radius; ++i)
			{
				for (int j = -radius; j <= radius; ++j)
				{
					uchar val = padded(radius + r + i, radius + c + j);
					if (val < lowest) lowest = val;
				}
			}
			dst(r, c) = lowest;
		}
	}
}

void minValue3b(const Mat3b& src, Mat1b& dst)
{
	int rr = src.rows;
	int cc = src.cols;

	dst = Mat1b(rr, cc, uchar(0));

	for (int c = 0; c<cc; ++c)
	{
		for (int r = 0; r<rr; ++r)
		{
			const Vec3b& v = src(r, c);

			uchar lowest = v[0];
			if (v[1] < lowest) lowest = v[1];
			if (v[2] < lowest) lowest = v[2];
			dst(r, c) = lowest;
		}
	}
}

Mat1b DarkChannel(const Mat3b& img, int patchSize)
{
	int radius = patchSize / 2;

	Mat1b dark;

	Mat1b low;
	minValue3b(img, low);
	minFilter(low, dark, radius);

	return dark;
}
//END dark channel2

//estimate airlight by the brightest pixel in dark channel (proposed by He et al.)
int estimateA(Mat DC)
{
	double minDC, maxDC;
	minMaxLoc(DC, &minDC, &maxDC);
	cout << "estimated airlight is:" << maxDC << endl;
	return maxDC;
}

//estimate airlight by the 0.1% brightest pixels in dark channel
int estimateAAdvance(Mat DC)
{
	double minDC, maxDC;
	//uchar intensity;
	int size = DC.rows*DC.cols;
	uchar *DCArray = new uchar[size]; // 1 channel
	//cv::minMaxLoc(DC, &minDC, &maxDC);

	//to array
	for (int i = 0; i < DC.rows; i++)
	{
		for (int j = 0; j < DC.cols; j++)
		{
			DCArray[i*DC.cols + j] = DC.at<uchar>(i, j);

		}
	}

	//find 0.1% brightest pixels in dark channel
	std::sort(DCArray, DCArray + size);  //// using default comparison (operator <)

	cout << "estimated airlight is:" << maxDC << endl;
	return maxDC;
}


//estimate transmission map
Mat estimateTransmission(Mat DCP, int ac)
{
	double w = 0.75;
	//double w = 0.95;
	Mat transmission = Mat::zeros(DCP.rows, DCP.cols, CV_8UC1);
	Scalar intensity;

	for (int m = 0; m<DCP.rows; m++)
	{
		for (int n = 0; n<DCP.cols; n++)
		{
			intensity = DCP.at<uchar>(m, n);
			transmission.at<uchar>(m, n) = (1 - w * intensity.val[0] / ac) * 255;
		}
	}
	return transmission;
}


//dehazing foggy image
Mat getDehazed(Mat source, Mat t, int al)
{
	double t0 = 0.1;
	double tmax;

	Scalar inttran;
	Vec3b intsrc;
	Mat dehazed = Mat::zeros(source.rows, source.cols, CV_8UC3);

	for (int i = 0; i<source.rows; i++)
	{
		for (int j = 0; j<source.cols; j++)
		{
			inttran = t.at<uchar>(i, j);
			intsrc = source.at<Vec3b>(i, j);
			tmax = (inttran.val[0] / 255) < t0 ? t0 : (inttran.val[0] / 255);
			for (int k = 0; k<3; k++)
			{
				dehazed.at<Vec3b>(i, j)[k] = abs((intsrc.val[k] - al) / tmax + al) > 255 ? 255 : abs((intsrc.val[k] - al) / tmax + al);
			}
		}
	}
	return dehazed;
}