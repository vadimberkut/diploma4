#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"

class OpenedImageData
{
public:
	//			static System::String path;
	static char* path;

	static cv::Mat imgBGR;
	static cv::Mat imgBGRRes;
	static cv::Mat imgLAB;
	static cv::Mat shadowMask;

	static void SetPath(System::String ^path)
	{
		using namespace System::Runtime::InteropServices;
		OpenedImageData::path = (char*)(void*)Marshal::StringToHGlobalAnsi(path);
	}

	static void Open(System::String ^path)
	{
		OpenedImageData::SetPath(path);
//		imgBGR = cv::imread(OpenedImageData::path);
//		cv::cvtColor(imgBGR, imgLAB, CV_BGR2Lab);
//		imgBGRRes = cv::Mat(imgBGR.rows, imgBGR.cols, CV_8UC3);
//		shadowMask = cv::Mat(imgBGR.rows, imgBGR.cols, CV_8UC1);
	}

	//			static char* GetCharPath()
	//			{
	//				using namespace System::Runtime::InteropServices;
	//				myPath_char = (char*)(void*)Marshal::StringToHGlobalAnsi(path);
	//			}
};