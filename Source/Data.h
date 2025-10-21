#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Library/Object2D.h"

namespace Data {
	void Init();

	extern std::map<std::string, float> player;		// �v���C���[�̏��
	extern std::map<std::string, VECTOR2> ui;		// UI�̍��W�̈ʒu
	extern std::vector<int> levelUpCount;			// ���x���A�b�v����J�E���g��
	extern std::vector<float> levelTime;			// �e���x���̎���
}