#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Library/Object2D.h"

namespace Data {
	void Init();

	extern std::map<std::string, float> player;			// プレイヤーの情報
	extern std::map<std::string, VECTOR2> ui;			// UIの座標の位置
	extern std::vector<int> levelUpCount;				// レベルアップするカウント数
	extern std::vector<float> levelTime;				// 各レベルの時間
	extern std::vector<std::vector<int>> stageLevel;	// 各レベルに出てくるステージの番号
}