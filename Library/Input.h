#pragma once
#include "DxLib.h"

namespace Input {
	//�L�[�{�[�h�擾�֘A
	void KeyStateUpdate();				//�L�[�̏�Ԃ𖈃t���[���X�V����
	bool IsKeyUP(int keyCode);			//�������u��
	bool IsKeyDown(int keyCode);		//�������u��
	int IsKeyKeep(int keyCode);		//�����Ă����

	// �}�E�X�֘A
	bool IsMouseDown(int button);		//�{�^���������ꂽ�u��
	bool IsMouseUP(int button);			//�{�^���������ꂽ�u��
	bool IsMouseKeep(int button);		//�{�^����������Ă����
}
