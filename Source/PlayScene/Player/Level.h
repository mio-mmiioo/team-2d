#pragma once
#include "../../../Library/Object2D.h"
#include <vector>
class Level : public Object2D {
public:
	Level();
	~Level();
	void Update() override;
	void Draw() override;

	int CountToLevel(int count); // カウント→レベル
	float LevelToTime(int level);  // レベル→時間

private:
	std::vector<int> count_; // 
	std::vector<float> level_; // レベル　・時間
};


