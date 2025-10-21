#pragma once
#include <string>
#include <map>
#include <vector>

namespace Data {
	void Init();

	extern std::map<std::string, float> player; // プレイヤーの情報
	extern std::map<std::string, float> ui;		// UIの位置情報
	extern std::vector<int> levelUpCount;		// レベルアップするカウント数
	extern std::vector<float> levelTime;		// 各レベルの時間
}