#pragma once
#include "../../../Library/Object2D.h"

class Player : public Object2D {
public:
	Player(VECTOR2 pos);
	~Player();
	void Update() override;
	void Draw() override;
private:
	bool IsClear();			// �X�e�[�W���N���A�ł����� ���ԓ��ɐ��𓥂ނ��Ƃ��ł�����
	void SoundShuttleRun(); // soundTimer_�����ƂɃV���g�������̉����Č�����
	void SetSoundTime();

	int hp_;
	float timer_;			// 9�̔{���ɂ���
	float soundScaleTimer_;	// timer_��9�����������炢�̎���
	int soundScaleCounter_;	// ���K�Ŗ炷���߂̃J�E���^�[
	bool isGoRight_;		// true���E�ɐi��ł��� false�����ɐi��ł���
	int counter_;			// �N���A(���𓥂�)��

	// �d�͊֘A
	bool onGround_;			// �n�ʂɑ������Ă���
	float velocityY_;

	// �J�n��
	float startTimer_;		// �J�n����炷�^�C�}�[
	int soundStartCounter_;	// ����炷�񐔂��J�E���g����

	// �A�j���[�V�����֘A
	float animTimer_;
};