#include "Data.h"
#include "../Library/CsvReader.h"

namespace Data {
	std::map<std::string, float> player;
	std::map<std::string, VECTOR2> ui;
	std::vector<int> levelUpCount;
	std::vector<float> levelTime;

	void SetPlayer();
	void SetLevelAndTime();
	void SetUiPosition();
}

void Data::Init()
{
	SetPlayer();
	SetLevelAndTime();
	SetUiPosition();
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

void Data::SetUiPosition()
{
	CsvReader* csv = new CsvReader("data/ui.csv");
	for (int i = 1; i < csv->GetLines(); i++) {
		std::string tag = csv->GetString(i, 0);
		if (tag == "HP1")
		{
			ui["HP1"] = VECTOR2(csv->GetFloat(i, 1), csv->GetFloat(i, 2));
		}
		else if (tag == "HP2")
		{
			ui["HP2"] = VECTOR2(csv->GetFloat(i, 1), csv->GetFloat(i, 2));
		}
		else if (tag == "Counter")
		{
			ui["Counter"] = VECTOR2(csv->GetFloat(i, 1), csv->GetFloat(i, 2));
		}
	}
}
