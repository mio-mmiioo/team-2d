#include "Player.h"
#include "../Stage/BaseStage.h"
#include <assert.h>
#include "../../../Library/Input.h"
#include "../../Sound.h"
#include "../../Image.h"
#include "../../Screen.h" // �v���C���[����ʊO�ɏo�Ă��Ȃ������肷��̂Ɏg�p
#include "Level.h"

namespace PLAYER {
	float moveSpeed = 1.0f;
	int halfSizeX = 24;
	const int MAX_HP = 2;

	const float GRAVITY = 0.05f;
	const float JUMP_HEIGHT = 64.0f * 2.0f;//�u���b�N�̍����
	const float JUMP_V0 = -sqrtf(2.0f * GRAVITY * JUMP_HEIGHT);

	// ���֘A
	float time = 9.0f;
	float scaleTime = PLAYER::time / 9.0f; // 9��̉����Ȃ炷
	float START_TIME = 1.0f;
	const int SOUND_START_COUNT_MAX = 3;

	// �A�j���[�V����
	const float ANIM_TIME = 0.1f;

	// UI�̕\���ʒu
	const int COUNTER_POS_X = Screen::WIDTH - 100;
	const int COUNTER_POS_Y = 100;
	const int HP_POS_X = 20;
	const int HP_POS_Y = 20;
	const int HP_IMAGE_WIDTH = 100;
}

Player::Player(VECTOR2 pos)
{
	hImage_ = LoadGraph("data/image/tamadot.png");
	assert(hImage_ > 0);

	imageSize_ = VECTOR2(64, 64);
	anim_ = { 4, 3 };
	position_ = pos;
	hp_ = PLAYER::MAX_HP; // �V���g��������2�񎸔s�����玸�i
	timer_ = PLAYER::time;
	soundScaleTimer_ = PLAYER::scaleTime;
	soundScaleCounter_ = 0;
	isGoRight_ = true;	  // �ŏ��͉E�ɐi��
	counter_ = 0;
	onGround_ = false;
	velocityY_ = 0;

	startTimer_ = PLAYER::START_TIME;
	soundStartCounter_ = 0;

	animTimer_ = PLAYER::ANIM_TIME;

	PlaySoundMem(Sound::se["Ready"], DX_PLAYTYPE_BACK, TRUE);
}

Player::~Player()
{
}

void Player::Update()
{
	if (PLAYER::time != Level::CountToTime(counter_))
	{
		SetSoundTime();
	}

	// �J�n�����Ȃ��Ă���ꍇ
	if (soundStartCounter_ < PLAYER::SOUND_START_COUNT_MAX)
	{
		startTimer_ -= Time::DeltaTime();
		if (startTimer_ <= 0)
		{
			startTimer_ = startTimer_ + PLAYER::START_TIME;
			soundStartCounter_ += 1;
			if (soundStartCounter_ == PLAYER::SOUND_START_COUNT_MAX)
			{
				PlaySoundMem(Sound::se["Go"], DX_PLAYTYPE_BACK, TRUE);
			}
			else
			{
				PlaySoundMem(Sound::se["Ready"], DX_PLAYTYPE_BACK, TRUE);
			}
		}
		return;
	}

	timer_ -= Time::DeltaTime();

	Level::SoundUp();

	SoundShuttleRun(); // �܂����g�����ĂȂ�

	VECTOR2 move;

	// �L�[�̓���
	{
		if (Input::IsKeyKeep(KEY_INPUT_D))
		{
			move.x += 1;
			anim_.y = 3;

			if (onGround_ == true)
			{
				animTimer_ -= Time::DeltaTime();
			}
		}
		else if (Input::IsKeyKeep(KEY_INPUT_A))
		{
			move.x -= 1;
			anim_.y = 1;
			if (onGround_ == true)
			{
				animTimer_ -= Time::DeltaTime();
			}
		}

		if (onGround_ == true)
		{
			if (Input::IsKeyDown(KEY_INPUT_SPACE))
			{
				velocityY_ = PLAYER::JUMP_V0;
			}
		}

		if (Input::IsKeyDown(KEY_INPUT_G)) // �G�Ƀv���C���[���E�Q
		{
			hp_ -= 1;
		}
	}

	position_ = position_ + (move * PLAYER::moveSpeed);

	BaseStage* st = FindGameObject<BaseStage>();

	// �X�e�[�W�Ƃ̓����蔻��E�ʒu�C��
	{
		// ���E�̂߂荞�ݔ���
		{
			if (move.x < 0)
			{
				int push = st->CheckLeft(position_ + VECTOR2(-PLAYER::halfSizeX, -(imageSize_.y / 2 - 1))); // ����
				position_.x += push;
				push = st->CheckLeft(position_ + VECTOR2(-PLAYER::halfSizeX, imageSize_.y / 2 - 1)); // ����
				position_.x += push;
			}
			if (move.x > 0)
			{
				int push = st->CheckRight(position_ + VECTOR2(PLAYER::halfSizeX, -(imageSize_.y / 2 - 1))); // �E��
				position_.x -= push;
				push = st->CheckRight(position_ + VECTOR2(PLAYER::halfSizeX, imageSize_.y / 2 - 1)); // �E��
				position_.x -= push;
			}
		}

		// �d�͂�������
		position_.y += velocityY_;
		velocityY_ += PLAYER::GRAVITY;
		onGround_ = false;
		
		// �㉺�̂߂荞�ݔ���
		{
			if (velocityY_ < 0.0f)
			{
				int push = st->CheckUp(position_ + VECTOR2(PLAYER::halfSizeX, -(imageSize_.y / 2))); // �E��
				if (push > 0)
				{
					velocityY_ = 0.0f;
					position_.y += push;
				}
				push = st->CheckUp(position_ + VECTOR2(-PLAYER::halfSizeX, -(imageSize_.y / 2))); // ����
				if (push > 0)
				{
					velocityY_ = 0.0f;
					position_.y += push;
				}
			}
			else
			{
				int push = st->CheckDown(position_ + VECTOR2(PLAYER::halfSizeX, imageSize_.y / 2)); // �E��
				if (push > 0)
				{
					onGround_ = true;
					velocityY_ = 0.0f;
					position_.y -= push - 1;
				}
				push = st->CheckDown(position_ + VECTOR2(-PLAYER::halfSizeX, imageSize_.y / 2)); // ����
				if (push > 0)
				{
					onGround_ = true;
					velocityY_ = 0.0f;
					position_.y -= push - 1;
				}
			}
		}

		// ��ʊO�Ƀv���C���[���s�����Ȃ��悤�Ɉʒu���C��
		{
			if (position_.x < PLAYER::halfSizeX)
			{
				position_.x = PLAYER::halfSizeX;
			}
			else if (position_.x > Screen::WIDTH - PLAYER::halfSizeX)
			{
				position_.x = Screen::WIDTH - PLAYER::halfSizeX;
			}
		}
	}

	// �N���A����Ȃ�
	if (timer_ <= 0)
	{
		// �X�e�[�W���N���A�ł������m�F
		if (IsClear() == false)
		{
			hp_ -= 1;

			// �{���̃S�[���n�_�Ƀ��[�v������
			if (isGoRight_ == true)
			{
				position_.x = BASESTAGE::LINE_POS_RIGHT + imageSize_.x;
			}
			else
			{
				position_.x = BASESTAGE::LINE_POS_LEFT - imageSize_.x;
			}
		}
		else
		{
			if (hp_ < PLAYER::MAX_HP)
			{
				hp_ = PLAYER::MAX_HP;
			}
		}

		if (hp_ <= 0)
		{
			st->SetPlayerAlive(false);
			DestroyMe();
		}
		// �X�e�[�W���Z�b�g
		st->ChooseStage(0); // ���i�K�ł͋@�\���ĂȂ�

		// ������������ύX
		if (isGoRight_ == true)
		{
			isGoRight_ = false;
			PlaySoundMem(Sound::scale[1], DX_PLAYTYPE_BACK, TRUE);
		}
		else
		{
			isGoRight_ = true;
			PlaySoundMem(Sound::scale[8], DX_PLAYTYPE_BACK, TRUE);
		}
		if (Level::RateCount(counter_))
		{
			Level::SoundUp();
		}
		SetSoundTime(); // �J�E���g�̐��ɍ��킹�Ď��Ԃ��Z�b�g
	}

	if (animTimer_ <= 0)
	{
		anim_.x += 1;
		if (anim_.x >= 7)
		{
			anim_.x = 4;
		}
		animTimer_ = animTimer_ + PLAYER::ANIM_TIME;
	}
}

void Player::Draw()
{
	Object2D::Draw();

	// �N���A�J�E���g�E���x���A�b�v�Q�[�W
	{
		DrawCircleGauge(PLAYER::COUNTER_POS_X, PLAYER::COUNTER_POS_Y, 100.0f, Image::ui["CircleGauge2"], 0.0f, 1.5, 0, 0);
		DrawCircleGauge(PLAYER::COUNTER_POS_X, PLAYER::COUNTER_POS_Y, 100.0f, Image::ui["CircleGauge1"], Level::RateCount(counter_), 1.5, 0, 0);
		SetFontSize(70);
		int DrawWidth = GetDrawFormatStringWidth("%d", counter_, -1);
		DrawFormatString(PLAYER::COUNTER_POS_X - (DrawWidth / 2), PLAYER::COUNTER_POS_Y - 35, GetColor(255, 255, 255), "%d", counter_);
		SetFontSize(20);
	}

	// HP�̕\��
	{
		DrawGraph(PLAYER::HP_POS_X, PLAYER::HP_POS_Y, Image::ui["Hp2"], TRUE);
		
		if (hp_ >= 2)
		{
			DrawGraph(PLAYER::HP_POS_X * 2 + PLAYER::HP_IMAGE_WIDTH, PLAYER::HP_POS_Y, Image::ui["Hp2"], TRUE);
		}
		else
		{
			DrawGraph(PLAYER::HP_POS_X * 2 + PLAYER::HP_IMAGE_WIDTH, PLAYER::HP_POS_Y, Image::ui["Hp1"], TRUE);
		}
	}

	DrawLine(BASESTAGE::LINE_POS_LEFT, 0, BASESTAGE::LINE_POS_LEFT, Screen::HEIGHT, GetColor(255, 255, 255));
	DrawLine(BASESTAGE::LINE_POS_RIGHT, 0, BASESTAGE::LINE_POS_RIGHT, Screen::HEIGHT, GetColor(255, 255, 255));

	if (isGoRight_)
	{
		DrawLine(BASESTAGE::LINE_POS_RIGHT, 0, BASESTAGE::LINE_POS_RIGHT, Screen::HEIGHT, GetColor(255, 100, 100), 3);
	}
	else
	{
		DrawLine(BASESTAGE::LINE_POS_LEFT, 0, BASESTAGE::LINE_POS_LEFT, Screen::HEIGHT, GetColor(255, 100, 100), 3);
	}

	if (soundStartCounter_ < PLAYER::SOUND_START_COUNT_MAX) // �J�n����UI
	{
		float rate = (1.0f - startTimer_) * 100;
		DrawCircleGauge(Screen::WIDTH / 2, Screen::HEIGHT / 2, 100.0f, Image::ui["CircleGauge1"], rate, 2.0, 0, 0);
		SetFontSize(70);
		int DrawWidth = GetDrawFormatStringWidth("%d", soundStartCounter_, -1);
		DrawFormatString((Screen::WIDTH - DrawWidth) / 2, Screen::HEIGHT / 2 - 35, GetColor(255, 255, 255), "%d", 3 - soundStartCounter_);
		SetFontSize(20);
	}
}

bool Player::IsClear()
{
	counter_ += 1;
	if (isGoRight_ == true) // �E�ɐi��ł���ꍇ
	{
		if (BASESTAGE::LINE_POS_RIGHT <= position_.x)
		{
			return true;
		}
	}
	else // ���ɐi��ł���ꍇ
	{
		if (BASESTAGE::LINE_POS_LEFT >= position_.x)
		{
			return true;
		}
	}
	return false;
}

void Player::SoundShuttleRun()
{
	soundScaleTimer_ -= Time::DeltaTime();
	if (soundScaleTimer_ <= 0)
	{
		if (isGoRight_ == true) // 1,2,3,...
		{
			soundScaleCounter_ += 1;
			PlaySoundMem(Sound::scale[soundScaleCounter_], DX_PLAYTYPE_BACK, TRUE);
		}
		else // 8,7,6,...
		{
			soundScaleCounter_ -= 1;
			PlaySoundMem(Sound::scale[soundScaleCounter_], DX_PLAYTYPE_BACK, TRUE);
		}
		soundScaleTimer_ = soundScaleTimer_ + PLAYER::scaleTime;
	}
}

void Player::SetSoundTime()
{
	PLAYER::time = Level::CountToTime(counter_); // �N���A�����񐔂������ɓn���āA���Ԃ����炤
	PLAYER::scaleTime = PLAYER::time / 9.0f;
	timer_ = PLAYER::time;
	soundScaleTimer_ = PLAYER::scaleTime;
}
