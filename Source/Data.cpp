#include "Data.h"
#include "../Library/CsvReader.h"

namespace Data {
	std::map<std::string, float> player;
	std::map<std::string, float> ui;

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
	for (int i = 0; i < csv->GetLines(); i++) {
		int level = csv->GetInt(i, 0);
		levelUpCount[level - 1] = csv->GetInt(i, 1);
		levelTime[level - 1] = csv->GetFloat(i, 2);
	}
}
