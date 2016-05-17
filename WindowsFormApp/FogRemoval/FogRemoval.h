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
Mat getMedianFilteredDarkChannel(Mat sourceImg, int patchSize)
{
	Mat rgbMinImg = Mat::zeros(sourceImg.rows, sourceImg.cols, CV_8UC1);
	Mat MDCP;
	Vec3b intensity;

	for (int m = 0; m < sourceImg.rows; m++)
	{
		for (int n = 0; n < sourceImg.cols; n++)
		{
			intensity = sourceImg.at<Vec3b>(m, n);
			rgbMinImg.at<uchar>(m, n) = min(min(intensity.val[0], intensity.val[1]), intensity.val[2]);
		}
	}
	medianBlur(rgbMinImg, MDCP, patchSize);
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

Mat1b getDarkChannel(const Mat3b& img, int patchSize)
{
	int radius = patchSize / 2;

	Mat1b dark;

	Mat1b low;
	minValue3b(img, low);
	minFilter(low, dark, radius);

	return dark;
}
//END dark channel2

//estimate airlight by the brightest pixel in dark channel
int estimateA(Mat DC)
{
	double minDC, maxDC;
	minMaxLoc(DC, &minDC, &maxDC);
	cout << "estimated airlight is:" << maxDC << endl;
	return maxDC;
}

//estimate airlight by the 0.1% brightest pixels in dark channel
int estimateAAdvance(Mat DC, Mat inputImage) //DC - darkChannel
{
	double minDC, maxDC;
	int size = DC.rows*DC.cols;
	double requiredPercent = 0.001; //0.1%
	int requiredAmount = size*requiredPercent; //

	////////////////////
	minMaxLoc(DC, &minDC, &maxDC);
	double max = maxDC;
	std::vector<int*> brightestDarkChannelPixels;
	for (int k = 0; k < requiredAmount && max >= 0; max--)
	{
		for (int i = 0; i < DC.rows; i++)
		{
			bool _break = false;
			for (int j = 0; j < DC.cols; j++)
			{
				uchar val = DC.at<uchar>(i, j);
				if (val == max)
					brightestDarkChannelPixels.push_back(new int[2] { i, j } );

				if (brightestDarkChannelPixels.size() >= requiredAmount - 1){
					_break = true;
					break;
				}
			}
			if (_break)
				break;
		}

		if (brightestDarkChannelPixels.size() >= requiredAmount)
			break;
	}

	//take pixels with highest intensity in the input image
	Mat inputImageLab;
	cvtColor(inputImage,inputImageLab,CV_BGR2Lab);
	int airlight = -1;
	for (int r = 0; r != brightestDarkChannelPixels.size(); r++)
	{
		int i = brightestDarkChannelPixels[r][0];
		int j = brightestDarkChannelPixels[r][1];

		cv::Vec3b pixel = inputImageLab.at<cv::Vec3b>(i, j);

		double L = pixel.val[0];
		double intensity = L; //take Lab L as insetsity
		if (intensity > airlight)
			airlight = intensity;
	}
	
	/////////////////

	return airlight;
}


//estimate transmission map
Mat estimateTransmission(Mat DC, int airlight) //DC - darkChannel
{
	double w = 0.75;
	//double w = 0.95;
	Mat transmission = Mat::zeros(DC.rows, DC.cols, CV_8UC1);
	Scalar intensity;

	for (int m = 0; m<DC.rows; m++)
	{
		for (int n = 0; n<DC.cols; n++)
		{
			intensity = DC.at<uchar>(m, n);
			transmission.at<uchar>(m, n) = (1 - w * (intensity.val[0] / airlight)) * 255;
		}
	}
	return transmission;
}


//dehazing foggy image
Mat getDehazed(Mat sourceImg, Mat transmissionImg, int airlight)
{
	double t0 = 0.1;
	double tmax;

	int A = airlight;//airlight
	Scalar t; //transmission
	Vec3b I; //I(x) - source image pixel
	Mat dehazed = Mat::zeros(sourceImg.rows, sourceImg.cols, CV_8UC3);

	for (int i = 0; i<sourceImg.rows; i++)
	{
		for (int j = 0; j<sourceImg.cols; j++)
		{
			t = transmissionImg.at<uchar>(i, j);
			I = sourceImg.at<Vec3b>(i, j);
			tmax = (t.val[0] / 255) < t0 ? t0 : (t.val[0] / 255);
			for (int k = 0; k<3; k++)
			{
				dehazed.at<Vec3b>(i, j)[k] = abs((I.val[k] - A) / tmax + A) > 255 ? 255 : abs((I.val[k] - A) / tmax + A);
			}
		}
	}
	return dehazed;
}
Mat removeFog(Mat source, Mat t, int al)
{
	return getDehazed(source,t,al);
}