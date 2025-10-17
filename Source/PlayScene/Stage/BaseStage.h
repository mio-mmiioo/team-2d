#pragma once
#include "../../../Library/Object2D.h"
#include <vector>

namespace BASESTAGE {
	const int LINE_POS_LEFT  = 256;  // ���̐�
	const int LINE_POS_RIGHT = 1024; // �E�̐�
}

class BaseStage : public Object2D {
public:
	BaseStage();
	~BaseStage();
	void Update() override;
	void Draw() override;

	// �����蔻��֘A
	int CheckRight(VECTOR2 pos);
	int CheckLeft(VECTOR2 pos);
	int CheckDown(VECTOR2 pos);
	int CheckUp(VECTOR2 pos);

	void ChooseStage(int count); // �����_���Ȓl����肵�Ď��̃X�e�[�W�𐶐����邽�߂̕ϐ�

	// �Q�[���I�[�o�[�����֘A
	void SetPlayerAlive(bool isAlive) { isPlayerAlive_ = isAlive; }

private:
	void SetStageData(std::vector<std::vector<int>> *stage, const char* filename); // �X�e�[�W�f�[�^���Z�b�g���邽�߂̊֐�
	void SetStageData(std::vector<std::vector<int>>* stage, const char* filename, int startX, int startY);
	void CreateStage(int number);					// �X�e�[�W���쐬����
	bool IsWall(VECTOR2 pos);						// �ǂ��ǂ���

	std::vector<std::vector<int>> baseStage_;		// �X�e�[�W�̗��[�̕���
	std::vector<std::vector<int>> currentStage_;	// ���݂̃X�e�[�W

	int hImage_;
	bool isPlayerAlive_;
};