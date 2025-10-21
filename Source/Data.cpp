#include "Data.h"
#include "../Library/CsvReader.h"

namespace Data {
	std::map<std::string, float> player;
	std::map<std::string, float> ui;

	void SetPlayer();
}

void Data::Init()
{
	SetPlayer();
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
