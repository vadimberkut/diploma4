#include "ImagesStats.h"
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>

// defining it fixes the unresolved external:
std::string ImagesStats::statsFilename = "stats.txt";
std::string ImagesStats::resultStatsFilename = "result_stats.txt";

//std::vector<std::string> ImagesStats::images; //image file names
std::vector<int> ImagesStats::methods; //detection, removal methods names in int
std::vector<int> ImagesStats::execTime; //excecution time (ticks)

void ImagesStats::AddStat(int method, int time) //time - ticks
{
	ImagesStats::methods.push_back(method);
	ImagesStats::execTime.push_back(time);
}

std::string ImagesStats::GetMenthodName(int method)
{
	switch (method)
	{
	case ImagesStats::SHADOW_DETECTION_LAB:
		return "SHADOW_DETECTION_LAB";
	case ImagesStats::SHADOW_DETECTION_MS:
		return "SHADOW_DETECTION_MS";

	case ImagesStats::SHADOW_REMOVAL_ADITIVE:
		return "SHADOW_REMOVAL_ADITIVE";
	case ImagesStats::SHADOW_REMOVAL_BASIC_LIGHT_MODEL:
		return "SHADOW_REMOVAL_BASIC_LIGHT_MODEL";
	case ImagesStats::SHADOW_REMOVAL_COMBINED:
		return "SHADOW_REMOVAL_COMBINED";
	case ImagesStats::SHADOW_REMOVAL_LAB:
		return "SHADOW_REMOVAL_LAB";
	case ImagesStats::SHADOW_REMOVAL_CONSTANT:
		return "SHADOW_REMOVAL_CONSTANT";

	case ImagesStats::SHADOW_EDGES_PROCESSING_INPAINT:
		return "SHADOW_EDGES_PROCESSING_INPAINT";

	case ImagesStats::FOG_REMOVAL_DARK_CHANNEL_PRIOR:
		return "FOG_REMOVAL_DARK_CHANNEL_PRIOR";

	default:
		return "";
	}
}

//Calc stats/ Returns map: method => (avg|max|min => value in seconds)
std::map<int, std::map<int, double>> ImagesStats::CalcStats()
{
	//CLK_TCK
	std::vector<int> methodsList(methods);
	methodsList.erase(std::unique(methodsList.begin(), methodsList.end()), methodsList.end());
	std::map<int, std::map<int, double>> result;

	//loop methods
	for (int i = 0; i != methodsList.size(); i++)
	{
		int currentMethod = methodsList[i];
		double min = 100000000000000;
		double max = 0;
		double avg = 0;
		int count = 0;

		for (int i = 0; i != methods.size(); i++)
		{
			int method = methods[i];
			if (method != currentMethod)
				continue;

			if (execTime[i] < min)
				min = execTime[i];
			if (execTime[i] > max)
				max = execTime[i];
			avg += execTime[i];
			count += 1;
		}

		avg /= count;

		min /= (double)CLK_TCK; //to Seconds
		max /= (double)CLK_TCK; //to Seconds
		avg /= (double)CLK_TCK; //to Seconds

		std::map<int, double> subMap = { { MIN, min }, { MAX, max }, { AVG, avg } };
		result.insert(pair<int, std::map<int, double>>(currentMethod, subMap));
	}

	return result;
}

void ImagesStats::SaveResultStatsToFile()
{
	std::map<int, std::map<int, double>> stats = ImagesStats::CalcStats();

	ofstream myfile;
	myfile.open(ImagesStats::resultStatsFilename, ios::out);

	typedef std::map<int, std::map<int, double>>::iterator it_type;
	//typedef std::map<int, double>::iterator it_type2;
	for (it_type iterator = stats.begin(); iterator != stats.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		// Repeat if you also want to iterate through the second map.
		int method = iterator->first;
		std::map<int, double> methodStats = iterator->second;

		double min = methodStats[ImagesStats::MIN];
		double max = methodStats[ImagesStats::MAX];
		double avg = methodStats[ImagesStats::AVG];

		myfile << ImagesStats::GetMenthodName(method) << ":\n";
		//			myfile << "\t" << "min:" << min << "\n";
		//			myfile << "\t" << "max:" << max << "\n";
		//			myfile << "\t" << "avg:" << avg << "\n";

		myfile << "\t" << "avg:" << "\t\t" << "min:" << "\t\t" << "max:" << "\n";
		myfile << "\t" << avg << "\t" << min << "\t" << max << "\n";

		//			for (it_type2 iterator = methodStats.begin(); iterator != methodStats.end(); iterator++) {
		//
		//			}
	}

	myfile.close();
}

void ImagesStats::SaveStatsToFile()
{
	ofstream myfile;
	myfile.open(statsFilename, ios::out);// | ios::app);

	for (int i = 0; i != methods.size(); i++)
	{
		int currentMethod = methods[i];
		int currentTime = execTime[i];
		myfile << currentMethod << " " << currentTime << "\n";
	}

	myfile.close();

	SaveResultStatsToFile();
}

void ImagesStats::LoadStatsFromFile()
{
	ifstream myfile;
	std::string line;
	myfile.open(statsFilename, ios::in);

	//1. Assume that every line consists of two numbers and read token by token:
	int method, time;
	while (myfile >> method >> time)
	{
		// process pair
		methods.push_back(method);
		execTime.push_back(time);
	}

	myfile.close();
}