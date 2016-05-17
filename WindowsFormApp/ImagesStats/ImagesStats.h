#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class ImagesStats
{
public:
	static const int SHADOW_DETECTION_LAB = 5;
	static const int SHADOW_DETECTION_MS = 6;

	static const int SHADOW_REMOVAL_ADITIVE = 10;
	static const int SHADOW_REMOVAL_BASIC_LIGHT_MODEL = 11;
	static const int SHADOW_REMOVAL_COMBINED = 12;
	static const int SHADOW_REMOVAL_LAB = 13;
	static const int SHADOW_REMOVAL_CONSTANT = 14;

	static const int FOG_REMOVAL_DARK_CHANNEL_PRIOR = 20;

	static const int MIN = 100;
	static const int MAX = 101;
	static const int AVG = 102;

	static std::string statsFilename;

	static std::vector<std::string> images; //image file names
	static std::vector<int> methods; //detection, removal methods names in int
	static std::vector<int> execTime; //excecution time (ticks)

	//Add Stat
	static void AddStat(int method, int time) //time - ticks
	{
		ImagesStats::methods.push_back(method);
		ImagesStats::execTime.push_back(time);
	}

	//Calc stats/ Returns map: method => (avg|max|min => value in seconds)
	static std::map<int, std::map<int, double>> CalcStats();

	static void SaveStatsToFile()
	{
		ofstream myfile;
		myfile.open(statsFilename, ios::out | ios::app);

		for (int i = 0; i != methods.size(); i++)
		{
			int currentMethod = methods[i];
			int currentTime = execTime[i];
			myfile << currentMethod << " " << currentTime << "\n";
		}

		myfile.close();
	}

	static void LoadStatsFromFile()
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
		
		//2. Line-based parsing, using string streams:
//		std::string line;
//		while (std::getline(infile, line))
//		{
//			std::istringstream iss(line);
//			int a, b;
//			if (!(iss >> a >> b)) { break; } // error
//
//			// process pair (a,b)
//		}



		myfile.close();
	}
};
