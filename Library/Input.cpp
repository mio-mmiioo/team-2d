#include "Input.h"
#include "DxLib.h"

namespace Input {
	// �L�[�{�[�h�擾�֘A
	const int KEY_MAX = 255;
	char curKey[KEY_MAX];		// ���݂̃L�[
	char prevKey[KEY_MAX];		// 1�O�̃L�[ 
	char keyDown[KEY_MAX];		// �����ꂽ�u�� 
	char keyUp[KEY_MAX];		// �����ꂽ�u�� 
	char KeyKeep[KEY_MAX];		// �������ςȂ�

	// �}�E�X�̏��
	int prevMouse = 0;			// �O�̃}�E�X���
	int curMouse = 0;			// ���݂̃}�E�X���
}

void Input::KeyStateUpdate()
{
	memcpy_s(prevKey, sizeof(char) * KEY_MAX, curKey, sizeof(char) * KEY_MAX); // �O��̃L�[�̏�Ԃ�ۑ�	
	GetHitKeyStateAll(curKey); // �S�ẴL�[�̏�Ԃ��擾 

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (curKey[i] && prevKey[i]) KeyKeep[i]++;
		int keyXor = curKey[i] ^ prevKey[i];	// �O�t���[���ƌ��t���[����xor
		if (keyXor) KeyKeep[i] = 0;
		keyDown[i] = keyXor & curKey[i];		// �����ꂽ�u�� = (���݂�keyXor��AND) 
		keyUp[i] = keyXor & prevKey[i];			// �����ꂽ�u�� = (�O���keyXor��AND) 
	}

	// �}�E�X�֘A
	prevMouse = curMouse;					// �O��̃}�E�X��Ԃ�ۑ�
	curMouse = GetMouseInput();				// �}�E�X�̏�Ԃ��擾
}


bool Input::IsKeyUP(int keyCode)
{
	return(keyUp[keyCode]);
}

bool Input::IsKeyDown(int keyCode)
{
	return(keyDown[keyCode]);
}

int Input::IsKeyKeep(int keyCode)
{
	return(KeyKeep[keyCode]);
}


bool Input::IsMouseDown(int button)
{
	return(((prevMouse & button) == 0) && ((curMouse & button) != 0));
}

bool Input::IsMouseUP(int button)
{
	return(((prevMouse & button) != 0) && ((curMouse & button) == 0));
}

bool Input::IsMouseKeep(int button)
{
	return(((prevMouse & button) != 0) && ((curMouse & button) != 0));
}
