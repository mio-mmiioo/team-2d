#pragma once
#include "../../../Library/Object2D.h"

class Player : public Object2D {
public:
	Player(VECTOR2 pos);
	~Player();
	void Update() override;
	void Draw() override;
private:
	bool IsClear(); // �X�e�[�W���N���A�ł����� ���ԓ��ɐ��𓥂ނ��Ƃ��ł����H

	int hp_;
	float soundTimer_;
	bool isGoRight_; // true���E�ɐi��ł��� false�����ɐi��ł���
	int counter_; // �N���A(���𓥂�)��
};