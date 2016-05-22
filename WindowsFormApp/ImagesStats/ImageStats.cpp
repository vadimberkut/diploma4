#include "ImagesStats.h"
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>

// defining it fixes the unresolved external:
std::string ImagesStats::statsFilename = "stats.txt";
std::string ImagesStats::resultStatsFilename = "result_stats.txt";

std::vector<std::string> ImagesStats::images; //image file names
std::vector<int> ImagesStats::methods; //detection, removal methods names in int
std::vector<int> ImagesStats::execTime; //excecution time (ticks)

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