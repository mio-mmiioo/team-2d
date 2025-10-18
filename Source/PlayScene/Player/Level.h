#pragma once
#include "../../../Library/Object2D.h"
#include <vector>
class Level : public Object2D {
public:
	Level();
	~Level();
	void Update() override;
	void Draw() override;

	int CountToLevel(int count); // �J�E���g�����x��
	float LevelToTime(int level);  // ���x��������

private:
	std::vector<int> count_; // 
	std::vector<float> level_; // ���x���@�E����
};


