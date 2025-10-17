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
	void SetStageData(std::vector<std::vector<int>> *stage, const char* filename); // �X�e�[�W�f�[�^���Z�b�g���邽�߂̊֐�
	void CreateStage(int number);
	void ChooseStage(); // �����_���Ȓl����肵�Ď��̃X�e�[�W�𐶐����邽�߂̕ϐ�

	std::vector<std::vector<int>> baseStage_; // �X�e�[�W�̗��[�̕���
	std::vector<std::vector<int>> currentStage_; // ���݂̃X�e�[�W

	int hImage_;
};