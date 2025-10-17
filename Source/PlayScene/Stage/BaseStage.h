#pragma once
#include "../../../Library/Object2D.h"
#include <vector>

class BaseStage : public Object2D {
public:
	BaseStage();
	~BaseStage();
	void Update() override;
	void Draw() override;

private:
	void ChooseStage(); // �����_���Ȓl����肵�Ď��̃X�e�[�W�𐶐����邽�߂̕ϐ�

	std::vector<std::vector<int>> baseStage_; // �X�e�[�W�̗��[�̕���

	int hImage_;
};