#pragma once
#include <string>
#include <map>
#include <vector>

namespace Data {
	void Init();

	extern std::map<std::string, float> player; // �v���C���[�̏��
	extern std::map<std::string, float> ui;		// UI�̈ʒu���
	extern std::vector<int> levelUpCount;		// ���x���A�b�v����J�E���g��
	extern std::vector<float> levelTime;		// �e���x���̎���
}