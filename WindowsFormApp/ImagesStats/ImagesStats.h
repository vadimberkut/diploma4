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

	static const int SHADOW_EDGES_PROCESSING_INPAINT = 20;

	static const int FOG_REMOVAL_DARK_CHANNEL_PRIOR = 30;

	static const int MIN = 100;
	static const int MAX = 101;
	static const int AVG = 102;

	static std::string statsFilename;
	static std::string resultStatsFilename;

	static std::vector<int> methods; //detection, removal methods names in int
	static std::vector<int> execTime; //excecution time (ticks)

	static void AddStat(int method, int time);

	static std::string GetMenthodName(int method);

	//Calc stats/ Returns map: method => (avg|max|min => value in seconds)
	static std::map<int, std::map<int, double>> CalcStats();

	static void SaveResultStatsToFile();

	static void SaveStatsToFile();

	static void LoadStatsFromFile();
};
