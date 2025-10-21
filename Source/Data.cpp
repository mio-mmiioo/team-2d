#include "Data.h"
#include "../Library/CsvReader.h"

namespace Data {
	std::map<std::string, float> player;
	std::map<std::string, float> ui;
	std::vector<int> levelUpCount;
	std::vector<float> levelTime;

	void SetPlayer();
	void SetLevelAndTime();
}

void Data::Init()
{
	SetPlayer();
	SetLevelAndTime();
}

void Data::SetPlayer()
{
	CsvReader* csv = new CsvReader("data/player.csv");
	for (int i = 0; i < csv->GetLines(); i++) {
		std::string tag = csv->GetString(i, 0);
		if (tag == "Gravity") {
			player["Gravity"] = csv->GetFloat(i, 1);
		}
		else if (tag == "JumpHeight") {
			player["JumpHeight"] = csv->GetFloat(i, 1);
		}
		else if (tag == "MoveSpeed") {
			player["MoveSpeed"] = csv->GetFloat(i, 1);
		}
	}
}

void Data::SetLevelAndTime()
{
	CsvReader* csv = new CsvReader("data/level.csv");
	for (int i = 1; i < csv->GetLines(); i++) {
		levelUpCount.push_back(csv->GetInt(i, 1));
		levelTime.push_back(csv->GetFloat(i, 2));
	}
}
