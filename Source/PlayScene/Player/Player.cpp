#include "Player.h"
#include "../Stage/BaseStage.h"
#include <assert.h>
#include "../../../Library/Input.h"
#include "../../Sound.h"
#include "../../Image.h"
#include "../../Screen.h" // プレイヤーが画面外に出ていないか判定するのに使用
#include "Level.h"
#include "../../Data.h"

namespace PLAYER {
	int halfSizeX = 24;
	const int MAX_HP = 2;

	// 音関連
	float SOUND_COUNT_MAX = 9.0f; // 9回音が鳴る
	float START_TIME = 1.0f;
	const int SOUND_START_COUNT_MAX = 3;

	// アニメーション
	const float ANIM_TIME = 0.1f;
}

Player::Player(VECTOR2 pos)
{
	hImage_ = LoadGraph("data/image/tamadot.png");
	assert(hImage_ > 0);

	imageSize_ = VECTOR2(64, 64);
	anim_ = { 4, 3 }; // 画像の位置
	position_ = pos;
	hp_ = PLAYER::MAX_HP; // シャトルランは2回失敗したら失格
	timer_ = Data::levelTime[0];
	soundScaleTimer_ = Data::levelTime[0] / PLAYER::SOUND_COUNT_MAX;
	soundScaleCounter_ = 0;
	isGoRight_ = true;	  // 最初は右に進む
	counter_ = 0;
	
	//重力関連
	onGround_ = false;
	velocityY_ = 0;
	jumpV0 = -sqrtf(2.0f * Data::player["Gravity"] * Data::player["JumpHeight"]);

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
	//if (PLAYER::time != Level::CountToTime(counter_))
	//{
	//	SetSoundTime();
	//}

	// 開始音がなっている場合
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

	SoundShuttleRun(); // まだ中身書いてない

	VECTOR2 move;

	// キーの入力
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
				velocityY_ = jumpV0;
			}
		}

		if (Input::IsKeyDown(KEY_INPUT_G)) // 雑にプレイヤーを殺害
		{
			hp_ -= 1;
		}
	}

	position_ = position_ + (move * Data::player["MoveSpeed"]);

	BaseStage* st = FindGameObject<BaseStage>();

	// ステージとの当たり判定・位置修正
	{
		// 左右のめり込み判定
		{
			if (move.x < 0)
			{
				int push = st->CheckLeft(position_ + VECTOR2(-PLAYER::halfSizeX, -(imageSize_.y / 2 - 1))); // 左上
				position_.x += push;
				push = st->CheckLeft(position_ + VECTOR2(-PLAYER::halfSizeX, imageSize_.y / 2 - 1)); // 左下
				position_.x += push;
			}
			if (move.x > 0)
			{
				int push = st->CheckRight(position_ + VECTOR2(PLAYER::halfSizeX, -(imageSize_.y / 2 - 1))); // 右上
				position_.x -= push;
				push = st->CheckRight(position_ + VECTOR2(PLAYER::halfSizeX, imageSize_.y / 2 - 1)); // 右下
				position_.x -= push;
			}
		}

		// 重力をかける
		position_.y += velocityY_;
		velocityY_ += Data::player["Gravity"];
		onGround_ = false;
		
		// 上下のめり込み判定
		{
			if (velocityY_ < 0.0f)
			{
				int push = st->CheckUp(position_ + VECTOR2(PLAYER::halfSizeX, -(imageSize_.y / 2))); // 右上
				if (push > 0)
				{
					velocityY_ = 0.0f;
					position_.y += push;
				}
				push = st->CheckUp(position_ + VECTOR2(-PLAYER::halfSizeX, -(imageSize_.y / 2))); // 左上
				if (push > 0)
				{
					velocityY_ = 0.0f;
					position_.y += push;
				}
			}
			else
			{
				int push = st->CheckDown(position_ + VECTOR2(PLAYER::halfSizeX, imageSize_.y / 2)); // 右下
				if (push > 0)
				{
					onGround_ = true;
					velocityY_ = 0.0f;
					position_.y -= push - 1;
				}
				push = st->CheckDown(position_ + VECTOR2(-PLAYER::halfSizeX, imageSize_.y / 2)); // 左下
				if (push > 0)
				{
					onGround_ = true;
					velocityY_ = 0.0f;
					position_.y -= push - 1;
				}
			}
		}

		// 画面外にプレイヤーを行かせないように位置を修正
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

	// クリア判定など
	if (timer_ <= 0)
	{
		// ステージをクリアできたか確認
		if (IsClear() == false)
		{
			hp_ -= 1;

			// 本来のゴール地点にワープさせる
			if (isGoRight_ == true)
			{
				position_.x = BASESTAGE::LINE_POS_RIGHT + imageSize_.x;
				position_.y = Screen::HEIGHT - 64 * 2;
			}
			else
			{
				position_.x = BASESTAGE::LINE_POS_LEFT - imageSize_.x;
				position_.y = Screen::HEIGHT - 64 * 2;
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
		// ステージをセット
		st->ChooseStage(Level::CountToLevel(counter_));

		// 向かう方向を変更
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
		SetSoundTime(); // カウントの数に合わせて時間をセット
	}

	// アニメーション
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

	// クリアカウント・レベルアップゲージ
	{
		DrawCircleGauge((int)Data::ui["Counter"].x, (int)Data::ui["Counter"].y, 100.0f, Image::ui["CircleGauge2"], 0.0f, 1.5, 0, 0);
		DrawCircleGauge((int)Data::ui["Counter"].x, (int)Data::ui["Counter"].y, 100.0f, Image::ui["CircleGauge1"], Level::RateCount(counter_), 1.5, 0, 0);
		SetFontSize(70);
		int DrawWidth = GetDrawFormatStringWidth("%d", counter_, -1);
		DrawFormatString((int)Data::ui["Counter"].x - (DrawWidth / 2), (int)Data::ui["Counter"].y - 35, GetColor(255, 255, 255), "%d", counter_);
		SetFontSize(20);
	}

	// HPの表示
	{
		DrawGraph((int)Data::ui["HP1"].x, (int)Data::ui["HP1"].y, Image::ui["Hp2"], TRUE);
		
		if (hp_ >= 2)
		{
			DrawGraph((int)Data::ui["HP2"].x, (int)Data::ui["HP2"].y, Image::ui["Hp2"], TRUE);
		}
		else
		{
			DrawGraph((int)Data::ui["HP2"].x, (int)Data::ui["HP2"].y, Image::ui["Hp1"], TRUE);
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

	if (soundStartCounter_ < PLAYER::SOUND_START_COUNT_MAX) // 開始音のUI
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
	if (isGoRight_ == true) // 右に進んでいる場合
	{
		if (BASESTAGE::LINE_POS_RIGHT <= position_.x)
		{
			return true;
		}
	}
	else // 左に進んでいる場合
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
		soundScaleTimer_ = soundScaleTimer_ + (Level::CountToTime(counter_) / PLAYER::SOUND_COUNT_MAX);
	}
}

void Player::SetSoundTime()
{
	timer_ = Level::CountToTime(counter_);
	soundScaleTimer_ = Level::CountToTime(counter_) / PLAYER::SOUND_COUNT_MAX;
}
