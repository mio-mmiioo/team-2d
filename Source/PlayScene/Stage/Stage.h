#pragma once
#include "../../../Library/Object2D.h"
#include <vector>

class Stage : public Object2D {
public:
	Stage(int number);
	~Stage();
	void Update() override;
	void Draw() override;
	
private:
	std::vector<std::vector<int>> stage_; // �X�e�[�W�̕ύX���镔��
	int hImage_;
};